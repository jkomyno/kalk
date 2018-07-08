#include <QApplication>
#include "bootstrap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Bootstrap bootstrap;
    bootstrap.show();

    return app.exec();
}
