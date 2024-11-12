#include "AddRowDialog.h"

#include "ui_AddRowDialog.h"

AddRowDialog::AddRowDialog(const QVector<QString>& userFriendlyColumnNames,
                           QWidget* parent)
    : QDialog(parent), ui_(std::make_unique<Ui::AddRowDialog>())
{
    ui_->setupUi(this);

    Q_ASSERT(userFriendlyColumnNames.size() == ui_->gridLayout->rowCount());

    for (int i = 0; i < ui_->gridLayout->rowCount(); ++i)
    {
        QWidget* itemWidget{ui_->gridLayout->itemAtPosition(i, 0)->widget()};
        dynamic_cast<QLabel*>(itemWidget)->setText(userFriendlyColumnNames[i]);
    }
}

AddRowDialog::~AddRowDialog() = default;

QVector<QVariant> AddRowDialog::getUserInputData() const
{
    return {ui_->firstNameLineEdit->text(), ui_->lastNameLineEdit->text(),
            ui_->ageSpinBox->value()};
}
