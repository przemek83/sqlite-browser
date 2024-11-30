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

void DatabaseConfigTest::testCheckTableSql() const
{
    DatabaseConfig config;
    QCOMPARE(config.getCheckTableSql(),
             "SELECT id, firstname, lastname, age  FROM client LIMIT 1;");
}

void DatabaseConfigTest::testColumnNames() const
{
    QVector<QString> expected{"firstname", "lastname", "age"};
    DatabaseConfig config;
    QCOMPARE(config.getColumnNames(), expected);
}

void DatabaseConfigTest::testUserFriendlyColumnNames() const
{
    QVector<QString> expected{"First name", "Last name", "Age"};
    DatabaseConfig config;
    QCOMPARE(config.getUserFriendlyColumnNames(), expected);
}

QTEST_MAIN(DatabaseConfigTest)