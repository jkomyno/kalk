#ifndef TYPECHOICEWIDGET_H
#define TYPECHOICEWIDGET_H

#include <QObject>
#include <QWidget>

class QComboBox;
class QLayout;
class QAbstractListModel;
class QString;

class TypeChoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TypeChoiceWidget(const QString& name, QWidget *parent = nullptr);
    int getChoice() const;

public slots:
    void setChoices(QAbstractListModel* choicesModel);

private:
    QLayout* layout;
    QString _name;
    QComboBox* kalkChoiceComboBox;
    void setup();
};

#endif // TYPECHOICEWIDGET_H
