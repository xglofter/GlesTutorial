#ifndef _GLPROGRAM_H__
#define _GLPROGRAM_H__

#include "AppMacros.h"

class GLProgram
{
public:
    GLProgram();
    ~GLProgram();

    /*
     * init GLProgram with vertex shader array data and fragment shader array data
     */
    bool initWithVertexShaderByteArray(const GLchar* vShaderByteArray, const GLchar* fShaderByteArray);

    /*
     * link shader
     */
    bool link();

    /*
     * use this opengl program
     */
    void use();

    /*
     * get location attrib
     */
    GLuint getAttribLocation(const GLchar* attrib);

private:
    GLuint loadShader(GLenum shaderType, const GLchar* shaderSrc);

    GLuint _uProgram;
    GLuint _uVertShader;
    GLuint _uFragShader;

};

#endif
