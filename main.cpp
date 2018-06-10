#include "MainWindow.h"
#include <QApplication>

#include "DatabaseConfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w(std::move(DatabaseConfig()));
    w.show();

    return a.exec();
}
