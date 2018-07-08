#ifndef TYPECHOICEQUESTIONWIDGET_H
#define TYPECHOICEQUESTIONWIDGET_H

#include <QWidget>

class QVBoxLayout;
class TypeChoiceWidget;
class QPushButton;
class QLabel;
class QAbstractListModel;
class TypeChoiceQuestionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TypeChoiceQuestionWidget(QWidget *parent = nullptr);

signals:
    void onFirstChoiceDone(int choiceAIndex, int choiceBIndex);
    void onChangeChoiceDone(int choiceAIndex, int choiceBIndex);

public slots:
    void setChoices(QAbstractListModel* choicesModel);
    void emitChoiceDone();

private:
    QVBoxLayout* layout;
    TypeChoiceWidget* choiceAWidget;
    TypeChoiceWidget* choiceBWidget;
    QPushButton* insertBtn;
    QLabel* question;
    bool insertedOnce = false;

    void setup();
    void wire();
};

#endif // TYPECHOICEQUESTIONWIDGET_H
