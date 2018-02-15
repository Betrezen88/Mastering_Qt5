#include "Task.h"
#include "ui_Task.h"

#include <QInputDialog>

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);

    connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
    connect(ui->removeButton, &QPushButton::clicked, [this] { emit removed(this);} );
    connect(ui->taskName, &QCheckBox::toggled, this, &Task::checked);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->taskName->setText(name);
}

QString Task::name() const
{
    return ui->taskName->text();
}

bool Task::isComplited() const
{
    return ui->taskName->isChecked();
}

void Task::rename()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Rename task", "New name", QLineEdit::Normal, this->name(), &ok);

    if ( ok && !name.isEmpty())
        setName(name);
}

void Task::checked(bool checked)
{
    QFont font;
    font.setStrikeOut( checked );
    ui->taskName->setFont( font );
    emit statusCHanged( this );
}
