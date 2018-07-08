#ifndef SPINBOX_H
#define SPINBOX_H

#include <type_traits>
#include <QAbstractSpinBox>
#include <QString>

namespace utils {
    namespace layout {
        template <typename SPIN_T,
                  typename = std::enable_if<std::is_base_of<QAbstractSpinBox, SPIN_T>::value>
        >
        SPIN_T* newSpinBox(int value) {
            SPIN_T* spinBox = new SPIN_T;
            spinBox->setValue(value);
            return spinBox;
        }

        template <typename SPIN_T,
                  typename = std::enable_if<std::is_base_of<QAbstractSpinBox, SPIN_T>::value>
        >
        SPIN_T* newSpinBox(int value, int minimum, int maximum) {
            SPIN_T* spinBox = utils::layout::newSpinBox<SPIN_T>(value);
            spinBox->setMinimum(minimum);
            spinBox->setMaximum(maximum);
            return spinBox;
        }

        template <typename SPIN_T,
                  typename = std::enable_if<std::is_base_of<QAbstractSpinBox, SPIN_T>::value>
        >
        SPIN_T* newSpinBox(int value, int minimum, int maximum, const QString& toolTip) {
            SPIN_T* spinBox = utils::layout::newSpinBox<SPIN_T>(value, minimum, maximum);
            spinBox->setToolTip(toolTip);
            return spinBox;
        }
    } // namespace layout
} // namespace utils

#endif // SPINBOX_H
