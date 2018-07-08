#ifndef INLINEOPERATIONROW_H
#define INLINEOPERATIONROW_H

#include <QWidget>

class QHBoxLayout;
class QString;
class QAbstractSpinBox;
class QAbstractButton;
class InlineOperationRow : public QWidget
{
    Q_OBJECT
public:
    explicit InlineOperationRow(const QString& labelText,
                                QAbstractSpinBox* spinBox,
                                QAbstractButton* btn,
                                QWidget *parent = nullptr);

private:
    QHBoxLayout* rowLayout;

    void setup(const QString& labelText, QAbstractSpinBox* spinBox, QAbstractButton* btn);
};

#endif // INLINEOPERATIONROW_H
