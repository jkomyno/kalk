#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QTextEdit;
class QString;

class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = nullptr);

public slots:
    void onLog(const QString& data, const QString& command);
    void onWarning(const QString& data, const QString& command);
    void clearLogEdit();

private:
    QHBoxLayout* layout;
    QPushButton* deviceMessagesBtn;
    QTextEdit* deviceLogEdit;

    void setup();
    void wire();
};

#endif // LOGWIDGET_H
