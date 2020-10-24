#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Bid=new BidService;
    connect(this,SIGNAL(sendPlayer(int,int)),Bid,SLOT(GetOneBid(int,int)));


}

MainWindow::~MainWindow()
{
    delete ui;
    Bid->stop();
    Bid->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    VD=new VerifyDialog;
    connect(VD,SIGNAL(pass()),this,SLOT(send()));
    VD->show();
}
void MainWindow::send()
{
    int money=ui->PlayerCostSpinBox->text().toInt();
    int limit=ui->MidCostlabel->text().toInt();
    if(money<limit-300||money>limit+300)
    {
        ui->successLabel->setText("您的出价无效");
    }
    else
    {
        int success=Bid->cost[ui->PlayerNumSpinBox->text().toInt()-ui->WinnerNumSpinBox->text().toInt()];
        if (late)
        {
            ui->successLabel->setText("您的出价太晚");
        }
        else if(bidChance>0)
        {
            bidChance--;
            sendPlayer(money,ui->WinnerNumSpinBox->text().toInt());
        }

    }
}
void MainWindow::AvgCost(int cost,int time)
{
    ui->MidCostlabel->setText(QString::number(cost));
    ui->AllCostlabel->setText(QString::number(cost-300)+"-"+QString::number(cost+300));
    ui->Timelabel->setText("11:29:"+QString::number(time/1000));
}

void MainWindow::on_StartSimPushButton_clicked()
{
    Bid->internalBidMapGen(ui->PlayerNumSpinBox->text().toInt(),ui->MidCostSpinBox->text().toInt());
    connect(Bid,SIGNAL(AvgCost(int,int)),this,SLOT(AvgCost(int,int)));
    connect(this,SIGNAL(sendPlayer(int,int)),Bid,SLOT(GetOneBid(int,int)));
    connect(Bid,SIGNAL(win(int)),this,SLOT(win(int)));
    Bid->start();
}
void MainWindow::win(int win)
{
    late=1;
    if(win)
        ui->successLabel->setText("您拍到了车牌");
    else
        ui->successLabel->setText("下次努力");
}
