#include <QStringListModel>
#include <QStringList>
#include "view/mainview.h"
#include "view/tabwidget.h"
#include "view/logwidget.h"
#include "viewmanager/kalkviewmanager.h"
#include "model/settingsprovider.h"
#include "bootstrap.h"

Bootstrap::Bootstrap() :
    QObject(nullptr),
    tabWidget(new TabWidget),
    logWidget(new LogWidget),
    mainView(new MainView(*tabWidget, *logWidget)),
    kalkViewManager(new KalkViewManager(*tabWidget, *logWidget, SettingsProvider::getSettings(), this))
{
    kalkViewManager->init();
}

void Bootstrap::show() const
{
    mainView->show();
}

Bootstrap::~Bootstrap()
{
    delete mainView;
}
