#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QString>
#include <QMap>
#include <unordered_map>
#include <vector>

class DatabaseConfig
{
public:
    DatabaseConfig() = default;

    ~DatabaseConfig() = default;

    DatabaseConfig& operator=(const DatabaseConfig& other) = delete;
    DatabaseConfig(const DatabaseConfig& other) = delete;

    DatabaseConfig& operator=(DatabaseConfig&& other) = default;
    DatabaseConfig(DatabaseConfig&& other) = default;

    QString getTableName() const;

    QString getCreateTableSql() const;

    QString getCheckTableSql() const;

    const QVector<QString>& getColumnNames() const;

    const QVector<QString>& getUserFriendlyColumnNames() const;

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

    static const QMap<SqLite3ColumnType, QString> typeToStringMap_;

    const QString tableName_{"client"};

    static const std::vector<SqlColumn> columns_;
};

#endif // DATABASECONFIG_H
