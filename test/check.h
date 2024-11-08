#include <QTest>

class MyTest : public QObject
{
    Q_OBJECT

private slots:
    void testFunction1() { QVERIFY2(true, "Test failed"); }
};

QTEST_MAIN(MyTest)
