#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SysInfo.h"

#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_cpuWidget(this)
{
    ui->setupUi(this);
    SysInfo::instance().init();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget( &m_cpuWidget );

    ui->centralWidget->setLayout( layout );
}

MainWindow::~MainWindow()
{
    delete ui;
}
