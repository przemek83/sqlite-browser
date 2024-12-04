#include "MainWindow.h"

#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QString>
#include <memory>

#include "ui_MainWindow.h"

#include "AddRowDialog.h"

MainWindow::MainWindow(DatabaseConfig databaseConfig, QWidget* parent)
    : QMainWindow(parent),
      ui_{std::make_unique<Ui::MainWindow>()},
      databaseConfig_(std::move(databaseConfig))
{
    ui_->setupUi(this);

    connect(ui_->actionExit, &QAction::triggered, QCoreApplication::instance(),
            &QCoreApplication::quit);

    connect(ui_->actionNew, &QAction::triggered, this,
            &MainWindow::createNewDb);

    connect(ui_->actionOpen, &QAction::triggered, this,
            &MainWindow::openExistingDb);

    connect(ui_->actionDelete_row, &QAction::triggered, this,
            &MainWindow::deleteRow);

    connect(ui_->actionAdd_row, &QAction::triggered, this, &MainWindow::addRow);

    const QStyle* style{QApplication::style()};
    ui_->actionNew->setIcon(
        style->standardIcon(QStyle::SP_FileDialogNewFolder));
    ui_->actionOpen->setIcon(style->standardIcon(QStyle::SP_DialogOpenButton));
    ui_->actionExit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));
}

MainWindow::~MainWindow() { reset(); }

void MainWindow::reset()
{
    removeCurrentModel();
    const QString currentDbPath{closeCurrentDatabase()};
    QSqlDatabase::removeDatabase(currentDbPath);
}

QString MainWindow::closeCurrentDatabase() const
{
    QSqlDatabase database{QSqlDatabase::database()};
    QString currentDatabasePath{database.connectionName()};
    database.close();
    return currentDatabasePath;
}

QSqlTableModel* MainWindow::createNewModel(const QSqlDatabase& database) const
{
    QSqlTableModel* model{new QSqlTableModel(ui_->tableView, database)};
    model->setTable(databaseConfig_.getTableName());
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    const QVector<QString> userFriendlyColumnNames{
        databaseConfig_.getUserFriendlyColumnNames()};
    const int columnCount{static_cast<int>(userFriendlyColumnNames.size())};
    for (int i = 0; i < columnCount; ++i)
    {
        // Skip primary key column (column 0).
        model->setHeaderData(i + 1, Qt::Horizontal, userFriendlyColumnNames[i]);
    }

    model->select();

    return model;
}

bool MainWindow::databaseStructureOk(const QSqlDatabase& database) const
{
    QSqlQuery query(database);
    if (const bool canQueryDb{query.exec(databaseConfig_.getCheckTableSql())};
        canQueryDb)
        return true;

    return query.exec(databaseConfig_.getCreateTableSql());
}

void MainWindow::prepareView(const QSqlDatabase& database)
{
    ui_->tableView->clearFocus();

    ui_->tableView->setModel(createNewModel(database));

    ui_->tableView->hideColumn(0);

    connect(ui_->tableView->selectionModel(),
            &QItemSelectionModel::currentRowChanged, this,
            &MainWindow::rowSelectionChanged);
}

void MainWindow::openDatabaseFile(const QString& databaseFilePath)
{
    if (databaseFilePath.isNull())
        return;

    reset();

    QSqlDatabase database{QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"))};
    database.setDatabaseName(databaseFilePath);

    if (!database.open())
    {
        ui_->statusBar->showMessage(tr("Cannot open database") + " " +
                                    databaseFilePath);
        return;
    }

    if (!databaseStructureOk(database))
    {
        ui_->statusBar->showMessage(tr("Cannot query database") + " " +
                                    databaseFilePath);
        return;
    }

    prepareView(database);

    ui_->actionAdd_row->setEnabled(true);

    ui_->actionDelete_row->setEnabled(false);

    ui_->statusBar->showMessage(tr("Connected to") + " " + databaseFilePath +
                                "...");
}

void MainWindow::removeCurrentModel()
{
    std::unique_ptr<QAbstractItemModel> currentModel{ui_->tableView->model()};
    ui_->tableView->setModel(nullptr);
}

std::pair<bool, QVector<QVariant>> MainWindow::getUserInputData()
{
    AddRowDialog addRowDialog(databaseConfig_.getUserFriendlyColumnNames(),
                              this);
    if (QDialog::Rejected == addRowDialog.exec())
        return {false, {}};

    return {true, addRowDialog.getUserInputData()};
}

void MainWindow::prepareRecord(QSqlRecord& record,
                               const QVector<QVariant>& userData) const
{
    const QVector<QString> columnNames{databaseConfig_.getColumnNames()};
    Q_ASSERT(columnNames.size() == userData.size());

    const auto* model{::qobject_cast<QSqlTableModel*>(ui_->tableView->model())};
    QSqlRecord recordToInsert{model->record()};

    const qsizetype columnCount{columnNames.size()};
    for (qsizetype i = 0; i < columnCount; ++i)
    {
        const QString& columnName{columnNames[i]};
        const QVariant& userInputDataItem{userData[i]};
        record.setValue(columnName, userInputDataItem);
    }
}

void MainWindow::createNewDb()
{
    const QString newDatabasePath{QFileDialog::getSaveFileName(
        this, QStringLiteral("Create new DB file"), QStringLiteral(""),
        tr("SQLiteDB (*.sqlite3);; All (*.*))"))};

    openDatabaseFile(newDatabasePath);
}

void MainWindow::openExistingDb()
{
    const QString databasePath{QFileDialog::getOpenFileName(
        this, QStringLiteral("Open DB file"), QStringLiteral(""),
        tr("SQLiteDB (*.sqlite3);; All (*.*))"))};

    openDatabaseFile(databasePath);
}

void MainWindow::rowSelectionChanged(
    const QModelIndex& current, [[maybe_unused]] const QModelIndex& previous)
{
    ui_->actionDelete_row->setEnabled(current.isValid());
}

void MainWindow::deleteRow()
{
    auto* model{::qobject_cast<QSqlTableModel*>(ui_->tableView->model())};

    if (const int rowToBeRemove{ui_->tableView->currentIndex().row()};
        model->removeRow(rowToBeRemove))
        ui_->statusBar->showMessage(tr("Row removed."));

    model->select();

    ui_->actionDelete_row->setEnabled(false);
}

void MainWindow::addRow()
{
    auto [success, userInputData]{getUserInputData()};
    if (!success)
        return;

    auto* model{::qobject_cast<QSqlTableModel*>(ui_->tableView->model())};
    QSqlRecord recordToInsert{model->record()};

    prepareRecord(recordToInsert, userInputData);
    model->insertRecord(-1, recordToInsert);
    model->select();

    ui_->statusBar->showMessage(tr("Row added."));

    ui_->actionDelete_row->setEnabled(false);
}
