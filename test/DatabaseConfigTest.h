#pragma once

#include <QTest>

class DatabaseConfigTest : public QObject
{
    Q_OBJECT

private slots:
    void testTableName() const;

    void testCreateTableSql() const;

    void testCheckTableSql() const;

    void testColumnNames() const;

    void testUserFriendlyColumnNames() const;
};
