#include <QApplication>
#include "MainWindow.h"

#include "DatabaseConfig.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DatabaseConfig config;
    MainWindow w(std::move(config));
    w.show();

    return a.exec();
}
