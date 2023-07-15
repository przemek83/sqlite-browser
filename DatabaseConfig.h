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

    enum class DbColumnType
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

        const DbColumnType type_;

        const bool primaryKey_;
    };

    const QMap<DbColumnType, QString> typeToStringMap_{
        {DatabaseConfig::DbColumnType::INTEGER, "INTEGER"},
        {DatabaseConfig::DbColumnType::REAL, "REAL"},
        {DatabaseConfig::DbColumnType::TEXT, "VARCHAR(50)"}};

    const QString tableName_{QStringLiteral("client")};

    const std::vector<SqlColumn> columns_{
        {"id", "id", DatabaseConfig::DbColumnType::INTEGER, true},
        {"firstname", "First name", DatabaseConfig::DbColumnType::TEXT, false},
        {"lastname", "Last name", DatabaseConfig::DbColumnType::TEXT, false},
        {"age", "Age", DatabaseConfig::DbColumnType::INTEGER, false}};
};
