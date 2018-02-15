#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include "SysInfo.h"

#include <QtGlobal>
#include <QVector>

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();

private:
    QVector<qulonglong> m_cpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
