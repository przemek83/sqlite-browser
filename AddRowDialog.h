#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>

namespace Ui {
class AddRowDialog;
}

class AddRowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRowDialog(const QVector<QString>& userFriendlyColumnNames, QWidget* parent = 0);
    virtual ~AddRowDialog();

    QVector<QVariant> getUserInputData() const;

private:
    Ui::AddRowDialog* ui;
};

#endif // ADDROWDIALOG_H
