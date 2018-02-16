#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QtCharts/QPieSeries>

#include "SysInfoWidget.h"

class CpuWidget : public SysInfoWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget *parent = nullptr);

protected slots:
    void updateSeries() override;

private:
    QtCharts::QPieSeries* m_series;
};

#endif // CPUWIDGET_H
