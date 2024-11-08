#include <QApplication>

#include "DatabaseConfig.h"
#include "MainWindow.h"

int main(int argc, char** argv)
{
    const QApplication a{argc, argv};

    DatabaseConfig config;
    MainWindow w{std::move(config)};
    w.show();

    return QApplication::exec();
}
