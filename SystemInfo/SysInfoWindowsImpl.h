#ifndef SYSINFOWINDOWSIMPL_H
#define SYSINFOWINDOWSIMPL_H

#include "SysInfo.h"

class SysInfoWindowsImpl : public SysInfo
{
public:
    SysInfoWindowsImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;
};

#endif // SYSINFOWINDOWSIMPL_H
