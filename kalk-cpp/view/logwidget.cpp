#include <QHBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include "logwidget.h"
#include "utils/layout/button.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    layout(new QHBoxLayout),
    deviceMessagesBtn(utils::layout::newButtonWithText<QPushButton>(tr("Clear"), tr("Clears logs and errors"))),
    deviceLogEdit(new QTextEdit)
{
    setup();
    wire();
    setLayout(layout);
    hide(); // TODO: remove
}

void LogWidget::onLog(const QString& command, const QString& data)
{
    deviceLogEdit->append(tr("[Log] %1: %2").arg(command).arg(data));
}

void LogWidget::onWarning(const QString& command, const QString& data)
{
    deviceLogEdit->append(tr("[Warning] %1: %2").arg(command).arg(data));
}

void LogWidget::clearLogEdit()
{
    deviceLogEdit->clear();
}

void LogWidget::setup()
{
    deviceLogEdit->setReadOnly(true);
    layout->addWidget(deviceLogEdit);
    layout->addWidget(deviceMessagesBtn);
}

void LogWidget::wire()
{
    connect(deviceMessagesBtn, SIGNAL(clicked(bool)), this, SLOT(clearLogEdit()));
}
