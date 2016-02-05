#include "Director.h"
#include "AppMacros.h"


static const char gVertexShader[] =
    "attribute vec4 a_position;\n"
    "attribute vec4 a_color;\n"
    "varying vec4 v_color;\n"
    "void main()\n"
    "{\n"
    "  v_color = a_color;\n"
    "  gl_Position = a_position;\n" 
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;   \n"
    "varying vec4 v_color;\n"
    "void main()\n"
    "{\n"
    "  gl_FragColor = v_color;\n"
    "}\n";

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

const GLfloat gColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

const GLfloat gData[] = { 0.0f, 0.5f,
                         -0.5f, -0.5f, 
                         0.5f, -0.5f, 
                         1.0f, 1.0f, 0.0f, 1.0f};


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

    glViewport(0, 0, width, height);
}

void Director::mainLoop()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // use white color as background
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    GLint idxColor = glGetAttribLocation(_glProgram->getProgramHandle(), "a_color");
    GLint idxPos = glGetAttribLocation(_glProgram->getProgramHandle(), "a_position");

    glVertexAttrib4fv(idxColor, gColor);

    //// not use VBO's code  ////
    // glVertexAttribPointer(idxPos, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices); 
    // glEnableVertexAttribArray(idxPos);
    //// not use VBO's code  ////

    //// use VBO ////
    GLuint arrayBuff[1];
    glGenBuffers(1, arrayBuff);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBuff[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*6, gTriangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(idxPos);
    glVertexAttribPointer(idxPos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //// use VBO ////

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Director::onEnterBackground()
{
    LOGV("Director::onEnterBackground");
}

void Director::onEnterForeground()
{
    LOGV("Director::onEnterForeground");
}

