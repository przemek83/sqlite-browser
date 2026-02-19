#pragma once

#include <QMainWindow>

#include "DatabaseConfig.h"

namespace Ui
{
class MainWindow;
}  // namespace Ui

class QSqlTableModel;
class QSqlDatabase;
class QSqlRecord;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(DatabaseConfig databaseConfig,
                        QWidget* parent = nullptr);

    ~MainWindow() override;

private:
    void reset();

    static QString closeCurrentDatabase();

    QSqlTableModel* createNewModel(const QSqlDatabase& database) const;

    bool databaseStructureOk(const QSqlDatabase& database) const;

    void prepareView(const QSqlDatabase& database);

    void openDatabaseFile(const QString& databaseFilePath);

    void removeCurrentModel();

    std::pair<bool, QVector<QVariant>> getUserInputData();

    void prepareRecord(QSqlRecord& record,
                       const QVector<QVariant>& userData) const;

    std::unique_ptr<Ui::MainWindow> ui_;

    DatabaseConfig databaseConfig_;

    const QString filesFilter_{tr("SQLiteDB (*.sqlite3);; All files (*)")};

private slots:
    void createNewDb();

    void openExistingDb();

    void rowSelectionChanged(const QModelIndex& current,
                             const QModelIndex& previous);

    void deleteRow();

    void addRow();
};
