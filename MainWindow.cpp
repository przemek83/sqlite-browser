#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QString>
#include <QSqlRecord>
#include <QFileDialog>

#include "AddRowDialog.h"

MainWindow::MainWindow(DatabaseConfig databaseConfig, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    databaseConfig_(std::move(databaseConfig))
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered(bool)), QCoreApplication::instance(), SLOT(quit()));

    QStyle* style = QApplication::style();
    ui->actionConnect->setIcon(style->standardIcon(QStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));
}

MainWindow::~MainWindow()
{
    closeCurrentDatabase();

    delete ui;
}

void MainWindow::closeCurrentDatabase()
{
    QAbstractItemModel* currentModel = ui->tableView->model();
    ui->tableView->setModel(nullptr);
    delete currentModel;

    QString currentDatabasePath;
    {
        QSqlDatabase database = QSqlDatabase::database();

        currentDatabasePath = database.connectionName();
        database.close();
    }
    QSqlDatabase::removeDatabase(currentDatabasePath);
}

QSqlTableModel* MainWindow::createNewModel(QSqlDatabase& database) const
{
    QSqlTableModel* model = new QSqlTableModel(ui->tableView, database);
    model->setTable(databaseConfig_.getTableName());
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    const QVector<QString>& userFriendlyColumnNames = databaseConfig_.getUserFriendlyColumnNames();
    for (int i = 0; i < userFriendlyColumnNames.size(); ++i)
    {
        // Skip primary key column (column 0).
        model->setHeaderData(i + 1, Qt::Horizontal, userFriendlyColumnNames[i]);
    }

    model->select();

    return model;
}

bool MainWindow::databaseStructureOk(QSqlDatabase& database) const
{
    QSqlQuery query(database);
    bool result = query.exec(databaseConfig_.getCheckTableSql());
    if (!result)
    {
        result = query.exec(databaseConfig_.getCreateTableSql());
        if (!result)
        {
            return false;
        }
    }

    return true;
}

void MainWindow::prepareView(QSqlDatabase& database)
{
    ui->tableView->clearFocus();

    ui->tableView->setModel(createNewModel(database));

    ui->tableView->hideColumn(0);

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(rowSelectionChanged(QModelIndex, QModelIndex)));
}

void MainWindow::on_actionConnect_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("SQLiteDB (*.sqlite3);; All (*.*))"));

    if (!dialog.exec())
    {
        return;
    }

    closeCurrentDatabase();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    QString newDatabasePath = dialog.selectedFiles().first();
    database.setDatabaseName(newDatabasePath);

    if (!database.open())
    {
        ui->statusBar->showMessage(tr("Cannot open database") + " " + newDatabasePath);
        return;
    }

    if (!databaseStructureOk(database))
    {
        ui->statusBar->showMessage(tr("Cannot query database") + " " + newDatabasePath);
        return;
    }

    prepareView(database);

    ui->actionAdd_row->setEnabled(true);

    ui->actionDelete_row->setEnabled(false);

    ui->statusBar->showMessage(tr("Connected to") + " " + newDatabasePath + "...");
}

void MainWindow::rowSelectionChanged(const QModelIndex& current, const QModelIndex& /*previous*/)
{
    ui->actionDelete_row->setEnabled(current.isValid());
}

void MainWindow::on_actionDelete_row_triggered()
{
    QSqlTableModel* model = dynamic_cast<QSqlTableModel*>(ui->tableView->model());
    int rowToBeRemove = ui->tableView->currentIndex().row();

    if (model->removeRow(rowToBeRemove))
    {
        ui->statusBar->showMessage(tr("Row removed."));
    }

    model->select();

    ui->actionDelete_row->setEnabled(false);
}

void MainWindow::on_actionAdd_row_triggered()
{
    AddRowDialog addRowDialog(databaseConfig_.getUserFriendlyColumnNames(), this);
    if (!addRowDialog.exec())
    {
        return;
    }

    QSqlTableModel* model = dynamic_cast<QSqlTableModel*>(ui->tableView->model());
    QSqlRecord recordToInsert = model->record();

    const QVector<QString>& columnNames = databaseConfig_.getColumnNames();
    const QVector<QVariant> userInputData = addRowDialog.getUserInputData();

    Q_ASSERT(columnNames.size() == userInputData.size());

    for (int i = 0; i < columnNames.size(); ++i)
    {
        const QString& columnName = columnNames[i];
        const QVariant& userInputDataItem = userInputData[i];

        recordToInsert.setValue(columnName, userInputDataItem);
    }

    model->insertRecord(-1, recordToInsert);
    model->select();

    ui->statusBar->showMessage(tr("Row added."));

    ui->actionDelete_row->setEnabled(false);
}
