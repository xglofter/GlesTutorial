#include "Director.h"
#include "AppMacros.h"

Director* Director::getInstance()
{
    static Director s_instance;
    return &s_instance;
}

Director::Director() :
  _fFrameWidth(0),
  _fFrameHeight(0)
{
	LOGV("Direcotr()");
}

Director::~Director()
{
	LOGV("~Director()");
}

void Director::init()
{

}

void Director::setFrameSize(float width, float height)
{
    LOGI("Director::setFrameSize(%lf, %lf)", width, height);
    _fFrameWidth = width;
    _fFrameHeight = height;
}

void Director::mainLoop()
{
	// LOGV("Director::mainLoop");
}

void Director::onEnterBackground()
{
	LOGV("Director::onEnterBackground");
}

void Director::onEnterForeground()
{
	LOGV("Director::onEnterForeground");
}

