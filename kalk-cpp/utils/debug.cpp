#include <QString>
#include <QDebug>
#include "debug.h"

namespace utils {
    void debug(const QString& message, const QString& whatToShow) {
        qDebug() << QString("%1: %2").arg(message).arg(whatToShow);
    }
}
