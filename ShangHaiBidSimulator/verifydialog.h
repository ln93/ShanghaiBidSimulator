#ifndef VERIFYDIALOG_H
#define VERIFYDIALOG_H

#include <QDialog>

namespace Ui {
class VerifyDialog;
}

class VerifyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VerifyDialog(QWidget *parent = 0);
    ~VerifyDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VerifyDialog *ui;
    void GenerateVerifyCode();
    int verifyCode;
signals:
    void pass();
};

#endif // VERIFYDIALOG_H
