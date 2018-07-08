#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "typechoicequestionwidget.h"
#include "kalkboardwidget.h"

class QWidget;
class QStringListModel;

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    enum class TAB_INDEXES {
        TYPE_CHOICE = 0,
        KALK_BOARD
    };

    explicit TabWidget(QWidget* parent = nullptr);
    ~TabWidget();
    TypeChoiceQuestionWidget* getTypeChoiceQuestionWidget() const;
    KalkBoardWidget* getKalkBoardWidget() const;

public slots:
    void initKalkBoardWidget();
    void onSettingsSuccess();
    void onSettingsError(const QString& message);

private:
    TypeChoiceQuestionWidget* typeChoiceQuestionWidget;
    KalkBoardWidget* kalkBoardWidget;

    void setup();
};

#endif // TABWIDGET_H
