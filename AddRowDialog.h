#pragma once

#include <QDialog>

#include "ui_AddRowDialog.h"

namespace Ui
{
class AddRowDialog;
}  // namespace Ui

class AddRowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddRowDialog(const QVector<QString>& userFriendlyColumnNames,
                          QWidget* parent = nullptr);

    QVector<QVariant> getUserInputData() const;

private:
    std::unique_ptr<Ui::AddRowDialog> ui_;
};
