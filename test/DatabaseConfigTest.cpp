#include "DatabaseConfigTest.h"

#include <src/DatabaseConfig.h>

void DatabaseConfigTest::testTableName() const
{
    DatabaseConfig config;
    QCOMPARE(config.getTableName(), "client");
}

void DatabaseConfigTest::testCreateTableSql() const
{
    DatabaseConfig config;
    QCOMPARE(config.getCreateTableSql(),
             "CREATE TABLE client (id INTEGER PRIMARY KEY, firstname "
             "VARCHAR(50), lastname VARCHAR(50), age INTEGER);");
}

QTEST_MAIN(DatabaseConfigTest)