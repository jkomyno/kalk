#include <QIcon>
#include <QPixmap>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include "tabwidget.h"
#include "logwidget.h"
#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(TabWidget& tabWidget, LogWidget& logWidget, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    outerLayout(new QVBoxLayout),
    _tabWidget(tabWidget),
    _logWidget(logWidget)
{
    ui->setupUi(this);
    setWindowTitle("Kalk - UNIPD @2018 - Alberto Schiabel");
    setWindowIcon(QIcon(QPixmap(":/img/img/logo.png")));
    setup();
    ui->centralWidget->setLayout(outerLayout);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::setup()
{
    _logWidget.setMaximumHeight(125);
    outerLayout->addWidget(&_tabWidget);
    outerLayout->addWidget(&_logWidget);
}
