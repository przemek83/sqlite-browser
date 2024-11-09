#include "DatabaseConfigTest.h"

#include <src/DatabaseConfig.h>

void DatabaseConfigTest::testTableName() const
{
    DatabaseConfig config;
    QCOMPARE(config.getTableName(), "client");
}

QTEST_MAIN(DatabaseConfigTest)