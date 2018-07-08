#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <QObject>

// class forwarding
class MainView;
class KalkViewManager;
class TabWidget;
class LogWidget;
class QStringListModel;

class Bootstrap final : public QObject
{
    Q_OBJECT
public:
    explicit Bootstrap();
    ~Bootstrap();

    void show() const;

private:
    TabWidget* tabWidget;
    LogWidget* logWidget;
    MainView* mainView;
    KalkViewManager* kalkViewManager;

    // static const QStringListModel kalkTypes;

    explicit Bootstrap(const Bootstrap& o) = delete;
    Bootstrap& operator=(const Bootstrap& o) = delete;
};

#endif // BOOTSTRAP_H
