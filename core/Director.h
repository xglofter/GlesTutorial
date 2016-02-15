#ifndef _DRECTOR_H__
#define _DRECTOR_H__

#include "GLProgram.h"

class Director
{
public:
    static Director* getInstance();

    /*
     * set OpenGL view frame size
     */
    void setFrameSize(float width, float height);

    /*
     * render each frame
     */
    void mainLoop();

    /*
     * call when app enter foreground
     */
    void onEnterForeground();

    /*
     * call when app enter background
     */
    void onEnterBackground();

    /*
     * get 24-bit TGA image fron a file
     * @param fileName[in]: file name
     * @param width[out]: image width
     * @param height[out]: image height
     */
    char* loadTGA(const char *fileName, int *width, int *height);

private:
    Director();
    ~Director();

    void init();

    GLProgram *_glProgram;

    float _fFrameWidth;
    float _fFrameHeight;
};


#endif
