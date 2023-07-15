#pragma once

#include <QMainWindow>

#include "DatabaseConfig.h"

namespace Ui
{
class MainWindow;
}

class QSqlTableModel;
class QSqlDatabase;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(DatabaseConfig databaseConfig,
                        QWidget* parent = nullptr);

    ~MainWindow() override;

private:
    void closeCurrentDatabase();

    QSqlTableModel* createNewModel(QSqlDatabase& database) const;

    bool databaseStructureOk(QSqlDatabase& database) const;

    void prepareView(QSqlDatabase& database);

    void openDatabaseFile(const QString& databaseFilePath);

    Ui::MainWindow* ui;

    DatabaseConfig databaseConfig_;

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void rowSelectionChanged(const QModelIndex& current,
                             const QModelIndex& previous);

    void on_actionDelete_row_triggered();

    void on_actionAdd_row_triggered();
};
