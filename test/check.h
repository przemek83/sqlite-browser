#include <QTest>

#include <QFile>

class MyTest : public QObject
{
    Q_OBJECT

private slots:
    void testQFile()
    {
        QFile file("check.txt");
        QVERIFY2(file.fileName() == "check.txt", "Test failed");
    }
};

QTEST_MAIN(MyTest)
