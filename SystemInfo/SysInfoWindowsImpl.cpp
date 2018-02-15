#include "SysInfoWindowsImpl.h"

#include "windows.h"

SysInfoWindowsImpl::SysInfoWindowsImpl() : SysInfo()
{

}

void SysInfoWindowsImpl::init()
{

}

double SysInfoWindowsImpl::cpuLoadAverage()
{

}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    qulonglong memoryPhisicalUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return (double)memoryPhisicalUsed / (double)memoryStatus.ullTotalPhys * 100.0;
}
