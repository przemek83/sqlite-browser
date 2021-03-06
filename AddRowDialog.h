#pragma once

#include <QDialog>

namespace Ui
{
class AddRowDialog;
}

class AddRowDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddRowDialog(const QVector<QString>& userFriendlyColumnNames,
                          QWidget* parent = nullptr);
    virtual ~AddRowDialog();

    QVector<QVariant> getUserInputData() const;

private:
    Ui::AddRowDialog* ui;
};
