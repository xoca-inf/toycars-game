#include "Config.h"

ConfigData Config::m_data;

W4_JS_IMPORT int getWindowSizeWidth();
W4_JS_IMPORT int getWindowSizeHeight();

void Config::initialize()
{
    size sz = Render::getSize();
    uint width = 600;
    uint height = 300;
    W4_LOG_DEBUG("screen size {%d, %d}", sz.w, sz.h);

    int w = getWindowSizeWidth();
    int h = getWindowSizeHeight();
    W4_LOG_DEBUG("win size {%d, %d}", w, h);

    std::string build;
    if (w > h)
    {
        build = "landscape";
    }
    else
    {
        build = "portrait";
    }
    build = "portrait";

    if (build == "portrait") {
        m_data.aspect = size(height, width);
        m_data.orientation = build;
        m_data.guiResolution = size(height, width);
    }
    else if (build == "landscape")
    {
        m_data.aspect = size(width, height);
        m_data.orientation = build;
        m_data.guiResolution = size(width, height);
    }

    //Render::getScreenCamera()->setFov(90);
    //w4::platform::Platform::setWindowAspect(m_data.aspect.w, m_data.aspect.h);
    //w4::platform::Platform::setWindowStyle(m_data.orientation.c_str());
    //w4::gui::setVirtualResolution(m_data.guiResolution);
}

const ConfigData& Config::getData() {
    return m_data;
}