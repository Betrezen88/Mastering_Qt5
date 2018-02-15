#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::AddTask);

    updateStatusLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddTask()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Task", "Task Name", QLineEdit::Normal, "Untitled Task", &ok);

    if ( ok && !name.isEmpty() ) {
        Task* task = new Task(name);
        connect(task, &Task::removed, this, &MainWindow::RemoveTask);
        connect(task, &Task::statusCHanged, this, &MainWindow::taskStatusChanged);
        m_tasks.append(task);
        ui->taskLayout->addWidget(task);
        updateStatusLabel();
    }
}

void MainWindow::RemoveTask(Task *task)
{
    ui->taskLayout->removeWidget(task);
    m_tasks.removeOne(task);
    updateStatusLabel();
    task->setParent(0);
    delete task;
}

void MainWindow::taskStatusChanged(Task *task)
{
    Q_UNUSED(task);
    updateStatusLabel();
}

void MainWindow::updateStatusLabel()
{
    int completed = 0;
    for ( auto task : m_tasks )
        if ( task->isComplited() )
            ++completed;
    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                .arg(m_tasks.count()-completed).arg(completed) );
}
