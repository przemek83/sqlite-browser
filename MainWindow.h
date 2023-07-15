#pragma once

#include <QMainWindow>

#include "DatabaseConfig.h"

namespace Ui
{
class MainWindow;
}  // namespace Ui

class QSqlTableModel;
class QSqlDatabase;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(DatabaseConfig databaseConfig,
                        QWidget* parent = nullptr);

    ~MainWindow() override;

    MainWindow& operator=(const MainWindow& other) = delete;
    MainWindow(const MainWindow& other) = delete;

    MainWindow& operator=(MainWindow&& other) = delete;
    MainWindow(MainWindow&& other) = delete;

private:
    void closeCurrentDatabase();

    QSqlTableModel* createNewModel(QSqlDatabase& database) const;

    bool databaseStructureOk(QSqlDatabase& database) const;

    void prepareView(QSqlDatabase& database);

    void openDatabaseFile(const QString& databaseFilePath);

    Ui::MainWindow* ui;

    DatabaseConfig databaseConfig_;

private slots:
    void createNewDb();

    void openExistingDb();

    void rowSelectionChanged(const QModelIndex& current,
                             const QModelIndex& previous);

    void deleteRow();

    void addRow();
};
