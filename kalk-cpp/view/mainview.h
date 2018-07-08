#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
    class MainView;
}

class TabWidget;
class LogWidget;
class QVBoxLayout;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(TabWidget& tabWidget, LogWidget& logWidget, QWidget* parent = 0);
    ~MainView();

private:
    Ui::MainView *ui;
    QVBoxLayout* outerLayout;
    TabWidget& _tabWidget;
    LogWidget& _logWidget;

    void setup();
};

#endif // MAINVIEW_H
