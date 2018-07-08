#include "QHBoxLayout"
#include "QAbstractListModel"
#include "QComboBox"
#include "QLabel"
#include "typechoicewidget.h"

TypeChoiceWidget::TypeChoiceWidget(const QString& name, QWidget* parent) :
    QWidget(parent),
    layout(new QHBoxLayout),
    _name(name),
    kalkChoiceComboBox(new QComboBox)
{
    setup();
    setLayout(layout);
}

int TypeChoiceWidget::getChoice() const
{
    return kalkChoiceComboBox->currentIndex();
}

void TypeChoiceWidget::setChoices(QAbstractListModel* choicesModel)
{
    kalkChoiceComboBox->setModel(choicesModel);
    auto width = kalkChoiceComboBox->minimumSizeHint().width();
    kalkChoiceComboBox->setMinimumWidth(width);
}

void TypeChoiceWidget::setup()
{
    kalkChoiceComboBox->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContentsOnFirstShow);
    kalkChoiceComboBox->setToolTip(QString("%1 %2").arg(tr("Select matrix type for")).arg(_name));

    QLabel* nameLabel = new QLabel(_name);
    nameLabel->setFrameShape(QFrame::Box);
    nameLabel->setFrameShadow(QFrame::Raised);

    layout->addWidget(nameLabel);
    layout->addWidget(kalkChoiceComboBox);
}
