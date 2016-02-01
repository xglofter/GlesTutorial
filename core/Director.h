#ifndef _DRECTOR_H__
#define _DRECTOR_H__

class Director
{
public:
    static Director* getInstance();

    void init();

    inline void setFrameSize(float width, float height);

    void mainLoop();

    void onEnterForeground();

    void onEnterBackground();

private:
    Director();
    ~Director();

    float _fFrameWidth;
    float _fFrameHeight;
};


#endif
