#include <QLabel>
#include <QString>
#include <QWidget>
#include "label.h"

namespace utils {
    namespace layout {
        QLabel* newLabel(const QString& text, QWidget* buddy) {
            QLabel* label = new QLabel(text);
            if (buddy != nullptr) {
                label->setBuddy(buddy);
            }
            return label;
        }
    }
}

