#include "bidservice.h"

#include "math.h"


BidService::BidService()
{
    Starttime=QTime::currentTime();
}
BidService::~BidService()
{
    delete[] cost;
    delete[] avg;
    delete[] avg2;
}
void BidService::stop()
{
    stopped=1;
}

void BidService::run()
{
    ms=0;
    Starttime=QTime::currentTime();
    for(;ms<60000&&stopped!=1;)
    {
        if(checkwin&&playertime==0)
        {
            playertime=ms;
        }
        QTime Now=QTime::currentTime();
        ms=Starttime.msecsTo(Now);
        if(ms<45000)
        {
            int dice=int(maxPeople*double(ms)/45000);
            AvgCost(((avg[dice])+50)/100*100,ms);
        }
        else
        {
            if(ms>60000)
            {
                ms=60000;
            }
            int dice=int((maxPeople-1)*double(pow(ms-45000,3))/pow(15000,3));
            AvgCost((avg2[dice]+100)/100*100,ms);//predict fix
        }
        msleep(10);
    }
    int validate=cost[maxPeople-cards-1];
    if(checkwin>cost[maxPeople-cards-1])
        win(1);
    else if(checkwin==cost[maxPeople-cards-1])
    {
        int min,max=maxPeople-1;
        for(int i=0;cost[i]<checkwin&&i<maxPeople;i++)
        {
            min=i;
            max=i;
        }
        for(int i=min+1;cost[i]==checkwin&&i<maxPeople;i++)
        {
            max=i;
        }
        int truewinner=maxPeople-max;
        int race=cards-truewinner;
        int dice=min+race;
        if(int((maxPeople-1)*double(pow(playertime-45000,3))/pow(15000,3))<dice)
        {
            win(1);
        }
        else
            win(0);
    }
    else
        win(0);

}

void BidService::GetOneBid(int Cost, int success)
{
    checkwin=Cost;
    cards=success;
    ms=0;


}
int BidService::average(int* input, int count)
{
    int64_t sum=0;
    for(int i=0;i<count;i++)
    {
        sum+=input[i];
    }
    return(sum/count);
}

void BidService::internalBidMapGen(int MaxPeople,int BaseCost)
{
    cost=new int [MaxPeople];
    avg=new int [MaxPeople];
    avg2=new int [MaxPeople];
    maxPeople=MaxPeople;
#pragma omp parallel for
    for (int i=0;i<MaxPeople;i++)
    {
        avg[i]=BaseCost;
        cost[i]=BaseCost;
    }

    for (int i=0;i<MaxPeople;i++)
    {
        avg[i]=average(cost,MaxPeople);
        cost[i]=int((avg[i]+50)/100)*100+300;
    }

    for (int i=0;i<MaxPeople/2;i++)
    {
        avg2[i]=average(cost,MaxPeople);
        cost[i]=int((avg2[i]+50)/100)*100+300;
    }

    for (int i=MaxPeople/2;i<MaxPeople;i++)
    {
        avg2[i]=average(cost,MaxPeople);
        cost[i]=int((avg2[i]+100)/100)*100+300;
    }

}


