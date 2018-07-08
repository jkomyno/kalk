#ifndef LABEL_H
#define LABEL_H

class QLabel;
class QString;
class QWidget;

namespace utils {
    namespace layout {
        QLabel* newLabel(const QString& text = "", QWidget* buddy = nullptr);
    } // namespace layout
} // namespace utils

#endif // LABEL_H
