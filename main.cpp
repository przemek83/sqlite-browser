#include "MainWindow.h"
#include <QApplication>

#include "DatabaseConfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseConfig config;
    MainWindow w(std::move(config));
    w.show();

    return a.exec();
}
