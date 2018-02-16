#include "CpuWidget.h"
#include "SysInfo.h"

using namespace QtCharts;

CpuWidget::CpuWidget(QWidget *parent)
    : SysInfoWidget(parent), m_series(new QPieSeries(this))
{
    m_series->setHoleSize(0.35);
    m_series->append("CPU Load", 30.0);
    m_series->append("CPU Free", 70.0);

    QChart* chart = chartView().chart();
    chart->addSeries(m_series);
    chart->setTitle("CPU average load");
}

void CpuWidget::updateSeries()
{
    double cpuLoadAverage = SysInfo::instance().cpuLoadAverage();
    m_series->clear();
    m_series->append("Load", cpuLoadAverage);
    m_series->append("Free", 100.0 - cpuLoadAverage);
}
