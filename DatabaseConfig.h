#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QString>
#include <unordered_map>

class DatabaseConfig
{
public:
    DatabaseConfig();

    ~DatabaseConfig();

    DatabaseConfig& operator=(const DatabaseConfig& other) = delete;
    DatabaseConfig(const DatabaseConfig& other) = delete;

    DatabaseConfig& operator=(DatabaseConfig&& other) = default;
    DatabaseConfig(DatabaseConfig&& other) = default;

    QString getTableName() const;

    QString getCreateTableSql() const;

    QString getCheckTableSql() const;

    const QVector<QString>& getColumnNames() const;

    const QVector<QString>& getUserFriendlyColumnNames() const;

private:
    struct SqlColumn
    {
    public:
        const QString columnName_;

        const QString userFriendlyColumnName_;

        const QString type_;

        const bool primaryKey_;
    };

    static const QString tableName_;

    static const std::vector<SqlColumn> columns_;
};

#endif // DATABASECONFIG_H
