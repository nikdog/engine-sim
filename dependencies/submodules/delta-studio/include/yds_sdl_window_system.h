#ifndef YDS_SDL_WINDOW_SYSTEM_H
#define YDS_SDL_WINDOW_SYSTEM_H

#include "yds_window_system.h"

class ysSdlWindowSystem : public ysWindowSystem {
public:
    ysSdlWindowSystem();
    virtual ~ysSdlWindowSystem();

    virtual ysError NewWindow(ysWindow **window) override;
    virtual ysMonitor *NewMonitor() override;
    virtual void SurveyMonitors() override;
    virtual void ProcessMessages() override;
};

#endif
