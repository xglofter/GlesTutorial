#include "Director.h"
#include "AppMacros.h"


static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f,
                                     -0.5f, 0.5f, -0.5f };

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
    _vPositionHandle = _glProgram->getAttribLocation("vPosition");

    glViewport(0, 0, width, height);
    checkGlError("glViewport");
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

    glVertexAttribPointer(_vPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(_vPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
}

void Director::onEnterBackground()
{
    LOGV("Director::onEnterBackground");
}

void Director::onEnterForeground()
{
    LOGV("Director::onEnterForeground");
}

