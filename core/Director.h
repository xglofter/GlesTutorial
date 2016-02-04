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

private:
    Director();
    ~Director();

    void init();

    GLProgram *_glProgram;

    float _fFrameWidth;
    float _fFrameHeight;
};


#endif
