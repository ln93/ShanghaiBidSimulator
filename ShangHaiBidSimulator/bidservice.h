#ifndef BIDSERVICE_H
#define BIDSERVICE_H

#include <QObject>
#include <QTime>
#include <QThread>
class BidService : public QThread
{
    Q_OBJECT
public:
    BidService();
    ~BidService();
    int maxPeople,cards=0;
protected:
    void run();
signals:
    void AvgCost(int cost,int time);
    void win(int win);
public:
    void stop();
    int* cost;
    int* avg;
    int* avg2;
    void internalBidMapGen(int MaxPeople, int BaseCost);
public slots:
    void GetOneBid(int Cost,int success);
private:
    int checkwin=0,playertime=0;
    int ms=0;
    int stopped=0;
    QTime Starttime;
    int average(int* input, int count);


};

#endif // BIDSERVICE_H
