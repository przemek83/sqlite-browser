#pragma once

#include <QMap>
#include <QString>
#include <unordered_map>
#include <vector>

class DatabaseConfig
{
public:
    QString getTableName() const;

    QString getCreateTableSql() const;

    QString getCheckTableSql() const;

    QVector<QString> getColumnNames() const;

    QVector<QString> getUserFriendlyColumnNames() const;

    enum class SqLite3ColumnType
    {
        INTEGER,
        REAL,
        TEXT
    };

private:
    struct SqlColumn
    {
    public:
        const QString columnName_;

        const QString userFriendlyColumnName_;

        const SqLite3ColumnType type_;

        const bool primaryKey_;
    };

    const QMap<SqLite3ColumnType, QString> typeToStringMap_{
        {DatabaseConfig::SqLite3ColumnType::INTEGER, "INTEGER"},
        {DatabaseConfig::SqLite3ColumnType::REAL, "REAL"},
        {DatabaseConfig::SqLite3ColumnType::TEXT, "VARCHAR(50)"}};

    const QString tableName_{QStringLiteral("client")};

    const std::vector<SqlColumn> columns_{
        {"id", "id", DatabaseConfig::SqLite3ColumnType::INTEGER, true},
        {"firstname", "First name", DatabaseConfig::SqLite3ColumnType::TEXT,
         false},
        {"lastname", "Last name", DatabaseConfig::SqLite3ColumnType::TEXT,
         false},
        {"age", "Age", DatabaseConfig::SqLite3ColumnType::INTEGER, false}};
};
