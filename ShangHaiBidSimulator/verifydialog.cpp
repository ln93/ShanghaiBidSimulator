#include "verifydialog.h"
#include "ui_verifydialog.h"
#include <QTime>

VerifyDialog::VerifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerifyDialog)
{
    ui->setupUi(this);
    GenerateVerifyCode();
}

VerifyDialog::~VerifyDialog()
{
    delete ui;
}

void VerifyDialog::GenerateVerifyCode()
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n1 = 1000+qrand() % 8999;
    int n2 = 1000+qrand() % 8999;
    int choose = qrand() %2;
    ui->Verify1->setText(QString::number(n1));
    ui->Verify2->setText(QString::number(n2));

    if(choose==0)
    {
        ui->Chooselabel->setText("请输入苹果后方验证码");
        verifyCode=n1;
    }
    else
    {
        ui->Chooselabel->setText("请输入橘子后方验证码");
        verifyCode=n2;
    }
}

void VerifyDialog::on_buttonBox_accepted()
{
    if (ui->VerifylineEdit->text().toInt()==verifyCode)
    {
        //do something
        pass();
    }
}
