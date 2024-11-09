#pragma once

#include <QTest>

class DatabaseConfigTest : public QObject
{
    Q_OBJECT

private slots:
    void testTableName() const;
};
