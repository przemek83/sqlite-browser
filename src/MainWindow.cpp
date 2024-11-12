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

MainWindow::~MainWindow() { closeCurrentDatabase(); }

void MainWindow::closeCurrentDatabase()
{
    QAbstractItemModel* currentModel{ui_->tableView->model()};
    ui_->tableView->setModel(nullptr);
    delete currentModel;

    QString currentDatabasePath;
    {
        QSqlDatabase database{QSqlDatabase::database()};
        currentDatabasePath = database.connectionName();
        database.close();
    }
    QSqlDatabase::removeDatabase(currentDatabasePath);
}

QSqlTableModel* MainWindow::createNewModel(const QSqlDatabase& database) const
{
    QSqlTableModel* model{new QSqlTableModel(ui_->tableView, database)};
    model->setTable(databaseConfig_.getTableName());
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    const QVector<QString> userFriendlyColumnNames{
        databaseConfig_.getUserFriendlyColumnNames()};
    for (int i = 0; i < userFriendlyColumnNames.size(); ++i)
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
    if (bool result{query.exec(databaseConfig_.getCheckTableSql())}; !result)
    {
        result = query.exec(databaseConfig_.getCreateTableSql());
        if (!result)
            return false;
    }

    return true;
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

    closeCurrentDatabase();

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

void MainWindow::rowSelectionChanged(const QModelIndex& current,
                                     const QModelIndex& /*previous*/)
{
    ui_->actionDelete_row->setEnabled(current.isValid());
}

void MainWindow::deleteRow()
{
    auto* model{qobject_cast<QSqlTableModel*>(ui_->tableView->model())};
    const int rowToBeRemove{ui_->tableView->currentIndex().row()};

    if (model->removeRow(rowToBeRemove))
        ui_->statusBar->showMessage(tr("Row removed."));

    model->select();

    ui_->actionDelete_row->setEnabled(false);
}

void MainWindow::addRow()
{
    AddRowDialog addRowDialog(databaseConfig_.getUserFriendlyColumnNames(),
                              this);
    if (QDialog::Rejected == addRowDialog.exec())
        return;

    auto* model{qobject_cast<QSqlTableModel*>(ui_->tableView->model())};
    QSqlRecord recordToInsert{model->record()};

    const QVector<QString> columnNames{databaseConfig_.getColumnNames()};
    const QVector<QVariant> userInputData(addRowDialog.getUserInputData());

    Q_ASSERT(columnNames.size() == userInputData.size());

    for (int i = 0; i < columnNames.size(); ++i)
    {
        const QString& columnName{columnNames[i]};
        const QVariant& userInputDataItem{userInputData[i]};

        recordToInsert.setValue(columnName, userInputDataItem);
    }

    model->insertRecord(-1, recordToInsert);
    model->select();

    ui_->statusBar->showMessage(tr("Row added."));

    ui_->actionDelete_row->setEnabled(false);
}
