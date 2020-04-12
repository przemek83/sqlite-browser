#include "AddRowDialog.h"
#include "ui_AddRowDialog.h"

AddRowDialog::AddRowDialog(const QVector<QString>& userFriendlyColumnNames,
                           QWidget* parent)
    : QDialog(parent), ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);

    Q_ASSERT(userFriendlyColumnNames.size() == ui->gridLayout->rowCount());

    for (int i = 0; i < ui->gridLayout->rowCount(); ++i)
    {
        QWidget* itemWidget = ui->gridLayout->itemAtPosition(i, 0)->widget();
        dynamic_cast<QLabel*>(itemWidget)->setText(userFriendlyColumnNames[i]);
    }
}

AddRowDialog::~AddRowDialog() { delete ui; }

QVector<QVariant> AddRowDialog::getUserInputData() const
{
    QVector<QVariant> userData;

    userData.append(ui->firstNameLineEdit->text());
    userData.append(ui->lastNameLineEdit->text());
    userData.append(ui->ageSpinBox->value());

    return userData;
}
