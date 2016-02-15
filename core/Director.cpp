#include "Director.h"
#include "AppMacros.h"


static const char gVertexShader[] =
    "attribute vec4 a_position;   \n"
    "attribute vec2 a_texCoord;   \n"
    "varying vec2 v_texCoord;     \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = a_position; \n"
    "   v_texCoord = a_texCoord;  \n"
    "}                            \n";

static const char gFragmentShader[] =
    "precision mediump float;                            \n"
    "varying vec2 v_texCoord;                            \n"
    "uniform sampler2D s_texture;                        \n"
    "void main()                                         \n"
    "{                                                   \n"
    "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
    "}                                                   \n";

GLfloat gVertices[] = { -0.5f,  0.5f, 0.0f,  // Position 0
                        0.0f,  0.0f,        // TexCoord 0 
                       -0.5f, -0.5f, 0.0f,  // Position 1
                        0.0f,  1.0f,        // TexCoord 1
                        0.5f, -0.5f, 0.0f,  // Position 2
                        1.0f,  1.0f,        // TexCoord 2
                        0.5f,  0.5f, 0.0f,  // Position 3
                        1.0f,  0.0f         // TexCoord 3
                     };
GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

Director* Director::getInstance()
{
    static Director s_instance;
    return &s_instance;
}

Director::Director() :
  _fFrameWidth(0),
  _fFrameHeight(0),
  _glProgram(nullptr)
{
    LOGV("Direcotr()");
}

Director::~Director()
{
    LOGV("~Director()");
}

void Director::init()
{
    LOGV("===========================================");
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    LOGV("===========================================");
}


// Generate an RGB8 checkerboard image
static GLubyte* GenCheckImage( int width, int height, int checkSize )
{
    int x, y;
    GLubyte *pixels = (GLubyte*)malloc( width * height * 3 );

    if ( pixels == NULL )
        return NULL;

    for ( y = 0; y < height; y++ )
        for ( x = 0; x < width; x++ )
        {
            GLubyte rColor = 0;
            GLubyte bColor = 0;

            if ( ( x / checkSize ) % 2 == 0 )
            {
                rColor = 255 * ( ( y / checkSize ) % 2 );
                bColor = 255 * ( 1 - ( ( y / checkSize ) % 2 ) );
            }
            else
            {
                bColor = 255 * ( ( y / checkSize ) % 2 );
                rColor = 255 * ( 1 - ( ( y / checkSize ) % 2 ) );
            }

            pixels[(y * height + x) * 3] = rColor;
            pixels[(y * height + x) * 3 + 1] = 0;
            pixels[(y * height + x) * 3 + 2] = bColor; 
        } 
    return pixels;
}


static GLuint textureId;
static GLint positionLoc;
static GLint texCoordLoc;
static GLint samplerLoc;

void Director::setFrameSize(float width, float height)
{
    this->init();

    LOGI("Director::setFrameSize(%lf, %lf)", width, height);
    _fFrameWidth = width;
    _fFrameHeight = height;

    _glProgram = new GLProgram();
    _glProgram->initWithVertexShaderByteArray(gVertexShader, gFragmentShader);
    _glProgram->link();
    _glProgram->use();

    positionLoc = glGetAttribLocation(_glProgram->getProgramHandle(), "a_position");
    texCoordLoc = glGetAttribLocation(_glProgram->getProgramHandle(), "a_texCoord");
    samplerLoc = glGetUniformLocation(_glProgram->getProgramHandle(), "s_texture");

    const char* fileName = "/sdcard/1.tga";
    int wid, hei;
    char *buffer = this->loadTGA(fileName, &wid, &hei);

    if (buffer == NULL)
    {
       LOGE("Error loading (%s) image.\n", fileName);
       return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wid, hei, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(buffer);

    glViewport(0, 0, width, height);
}

void Director::mainLoop()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // use white color as background
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, 
                            GL_FALSE, 5 * sizeof(GLfloat), gVertices);
    glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT,
                            GL_FALSE, 5 * sizeof(GLfloat), &gVertices[3]);
    glEnableVertexAttribArray(positionLoc);
    glEnableVertexAttribArray(texCoordLoc);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set the sampler texture unit to 0
    glUniform1i(samplerLoc, 0);

    // Draw quad with nearest sampling
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}

void Director::onEnterBackground()
{
    LOGV("Director::onEnterBackground");
}

void Director::onEnterForeground()
{
    LOGV("Director::onEnterForeground");
}

char* Director::loadTGA(const char *fileName, int *width, int *height)
{
    char *buffer = NULL;
    FILE *f;
    unsigned char tgaheader[12];
    unsigned char attributes[6];
    unsigned int imagesize;

    f = fopen(fileName, "rb");
    if (f == NULL) 
    {
        LOGE("file %s not find!", fileName);
        return NULL;
    }
    if (fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
    {
        fclose(f);
        return NULL;
    }
    if (fread(attributes, sizeof(attributes), 1, f) == 0)
    {
        fclose(f);
        return 0;
    }

    *width = attributes[1] * 256 + attributes[0];
    *height = attributes[3] * 256 + attributes[2];
    imagesize = attributes[4] / 8 * *width * *height;
    buffer = (char*)malloc(imagesize);
    if (buffer == NULL)
    {
        fclose(f);
        return 0;
    }

    if(fread(buffer, 1, imagesize, f) != imagesize)
    {
        free(buffer);
        return NULL;
    }
    fclose(f);

    LOGV("Director::loadTGA %s: width %d, height %d.", fileName, *width, *height);

    return buffer;
}





