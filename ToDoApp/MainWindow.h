#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "Task.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void AddTask();
    void RemoveTask(Task* task);
    void taskStatusChanged(Task* task);

private:
    void updateStatusLabel();

private:
    Ui::MainWindow *ui;
    QVector<Task*> m_tasks;

    int m_completed;
    int m_total;
};

#endif // MAINWINDOW_H
