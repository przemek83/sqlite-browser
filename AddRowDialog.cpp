#include "AddRowDialog.h"

AddRowDialog::AddRowDialog(const QVector<QString>& userFriendlyColumnNames,
                           QWidget* parent)
    : QDialog(parent), ui_(std::make_unique<Ui::AddRowDialog>())
{
    ui_->setupUi(this);

    Q_ASSERT(userFriendlyColumnNames.size() == ui_->gridLayout->rowCount());

    for (int i = 0; i < ui_->gridLayout->rowCount(); ++i)
    {
        QWidget* itemWidget = ui_->gridLayout->itemAtPosition(i, 0)->widget();
        dynamic_cast<QLabel*>(itemWidget)->setText(userFriendlyColumnNames[i]);
    }
}

QVector<QVariant> AddRowDialog::getUserInputData() const
{
    QVector<QVariant> userData;

    userData.append(ui_->firstNameLineEdit->text());
    userData.append(ui_->lastNameLineEdit->text());
    userData.append(ui_->ageSpinBox->value());

    return userData;
}
