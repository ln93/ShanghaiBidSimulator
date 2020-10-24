#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QObject>
#include "playernum.h"
class ComputerPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ComputerPlayer(QObject *parent = 0);
signals:
    void SendOneBid(int cost,int time,int isPlayer);
public slots:
    void GetInfo(int cost, int time);
public:
    int bidStatus=0;//0,1,2
    int bidTime;
    int bidCost;
    int player;
};

#endif // COMPUTERPLAYER_H
