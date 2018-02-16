#include "CpuWidget.h"

using namespace QtCharts;

CpuWidget::CpuWidget(QWidget *parent)
    : SysInfoWidget(parent), m_series(new QPieSeries(this))
{

}

void CpuWidget::updateSeries()
{

}
