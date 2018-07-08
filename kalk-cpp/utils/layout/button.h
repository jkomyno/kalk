#ifndef LAYOUT_BUTTON_H
#define LAYOUT_BUTTON_H

#include <type_traits>
#include <QAbstractButton>
#include <QString>
#include <QWidget>

namespace utils {
    namespace layout {
        template <typename BUTTON_T,
                  typename = std::enable_if<std::is_base_of<QAbstractButton, BUTTON_T>::value>
        >
        BUTTON_T* newButtonWithText(const QString& text) {
            BUTTON_T* btn = new BUTTON_T;
            btn->setText(text);
            return btn;
        }

        template <typename BUTTON_T,
                  typename = std::enable_if<std::is_base_of<QAbstractButton, BUTTON_T>::value>
        >
        BUTTON_T* newButtonWithText(const QString& text, const QString& toolTip) {
            BUTTON_T* btn = utils::layout::newButtonWithText<BUTTON_T>(text);
            btn->setToolTip(toolTip);
            return btn;
        }
    } // namespace layout
} // namespace utils

#endif // LAYOUT_BUTTON_H
