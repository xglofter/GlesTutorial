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
    "varying vec4 v_color;\n"
    "void main()\n"
    "{\n"
    "  gl_FragColor = v_color;\n"
    "}\n";

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f,
                                     -0.5f, 0.5f, -0.5f };

const GLfloat gColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };


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
    printGLString("Extensions", GL_EXTENSIONS);
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
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glVertexAttrib4fv(0, gColor);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices); 
    glEnableVertexAttribArray(1);
    glBindAttribLocation(_glProgram->getProgramHandle(), 0, "a_color"); 
    glBindAttribLocation(_glProgram->getProgramHandle(), 1, "a_position");
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

