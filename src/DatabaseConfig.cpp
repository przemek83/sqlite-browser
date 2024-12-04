#include "DatabaseConfig.h"

#include <QVector>

QString DatabaseConfig::getTableName() const { return tableName_; }

QString DatabaseConfig::getCreateTableSql() const
{
    QString sql{"CREATE TABLE " + tableName_ + " ("};
    const size_t columnCount{columns_.size()};
    for (size_t i = 0; i < columnCount; ++i)
    {
        const auto& column{columns_[i]};
        sql += column.columnName_ + " ";
        sql += typeToStringMap_[column.type_];
        if (column.primaryKey_)
            sql += QStringLiteral(" PRIMARY KEY");

        if (i < (columns_.size() - 1))
            sql += QStringLiteral(", ");
        else
            sql += QStringLiteral(");");
    }

    return sql;
}

QString DatabaseConfig::getCheckTableSql() const
{
    QString sql{QStringLiteral("SELECT ")};
    const size_t columnCount{columns_.size()};
    for (size_t i = 0; i < columnCount; ++i)
    {
        const auto& column{columns_[i]};
        sql += column.columnName_;

        if (i < (columns_.size() - 1))
            sql += QStringLiteral(", ");
        else
            sql += QStringLiteral(" ");
    }

    sql += " FROM " + tableName_ + " LIMIT 1;";

    return sql;
}
QVector<QString> DatabaseConfig::getColumnNames() const
{
    QVector<QString> columnNames{};

    // Transform from second element as primary key column is not needed.
    std::transform(columns_.cbegin() + 1, columns_.cend(),
                   std::back_inserter(columnNames),
                   [](const SqlColumn& column) { return column.columnName_; });

    return columnNames;
}

QVector<QString> DatabaseConfig::getUserFriendlyColumnNames() const
{
    QVector<QString> userFriendlyColumnNames{};

    // Transform from second element as primary key column is not needed.
    std::transform(columns_.cbegin() + 1, columns_.cend(),
                   std::back_inserter(userFriendlyColumnNames),
                   [](const SqlColumn& column)
                   { return column.userFriendlyColumnName_; });

    return userFriendlyColumnNames;
}
