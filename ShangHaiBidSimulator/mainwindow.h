#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "verifydialog.h"
#include "bidservice.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void on_StartSimPushButton_clicked();

public slots:
    void AvgCost(int cost,int time);
    void send();
    void win(int win);
private:
    Ui::MainWindow *ui;
    VerifyDialog *VD;
    BidService *Bid;
    int bidChance=2;
    int late=0;
signals:
    void sendPlayer(int cost,int success);
};

#endif // MAINWINDOW_H
