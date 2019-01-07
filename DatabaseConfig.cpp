#include "DatabaseConfig.h"

#include <QVector>

const QMap<DatabaseConfig::SqLite3ColumnType, QString>
DatabaseConfig::typeToStringMap_ {{DatabaseConfig::SqLite3ColumnType::INTEGER, "INTEGER"},
                                  {DatabaseConfig::SqLite3ColumnType::REAL, "REAL"},
                                  {DatabaseConfig::SqLite3ColumnType::TEXT, "VARCHAR(50)"}};

const std::vector<DatabaseConfig::SqlColumn>
DatabaseConfig::columns_ {{"id", "id", DatabaseConfig::SqLite3ColumnType::INTEGER, true},
                          {"firstname", "First name", DatabaseConfig::SqLite3ColumnType::TEXT, false},
                          {"lastname", "Last name", DatabaseConfig::SqLite3ColumnType::TEXT, false},
                          {"age", "Age", DatabaseConfig::SqLite3ColumnType::INTEGER, false}};

QString DatabaseConfig::getTableName() const
{
    return tableName_;
}

QString DatabaseConfig::getCreateTableSql() const
{
    QString sql;
    sql += "CREATE TABLE " + tableName_ + " (";
    for (size_t i = 0; i < columns_.size(); ++i)
    {
        const auto& column = columns_[i];
        sql += column.columnName_ + " ";
        sql += typeToStringMap_[column.type_];
        if (column.primaryKey_)
        {
            sql += " PRIMARY KEY";
        }

        sql += (i < columns_.size() - 1 ? ", " : ");");
    }

    return sql;
}

QString DatabaseConfig::getCheckTableSql() const
{
    QString sql;
    sql += "SELECT ";
    for (size_t i = 0; i < columns_.size(); ++i)
    {
        const auto& column = columns_[i];
        sql += column.columnName_;
        sql += (i < columns_.size() - 1 ? ", " : " ");
    }

    sql += " FROM " + tableName_ + " LIMIT 1;";

    return sql;
}

const QVector<QString>& DatabaseConfig::getColumnNames() const
{
    static QVector<QString> columnNames {};
    if (columnNames.empty())
    {
        for (const auto& column : columns_)
        {
           columnNames.push_back(column.columnName_);
        }

        // Primary key column not needed.
        columnNames.pop_front();
    }

    return columnNames;
}

const QVector<QString>& DatabaseConfig::getUserFriendlyColumnNames() const
{
    static QVector<QString> userFriendlyColumnNames {};
    if (userFriendlyColumnNames.empty())
    {
        for (const auto& column : columns_)
        {
           userFriendlyColumnNames.push_back(column.userFriendlyColumnName_);
        }

        // Primary key column not needed.
        userFriendlyColumnNames.pop_front();
    }

    return userFriendlyColumnNames;
}
