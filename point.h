#ifndef POINT_H
#define POINT_H
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock
#include <queue>
using namespace std;

class Point{
private:
    unsigned long slot;
    float price;
    time_t date;
    time_t startDate;
    int dt;
    int n;

public:
    static time_t strToDate(string date){
        std::tm tm = {};
        stringstream ss(date);
        ss >> get_time(&tm, "%Y-%m-%d");
        time_t tt = mktime(&tm);
        return tt;
    }

    static string dateToStr(time_t tt){
        struct std::tm * ptm = std::localtime(&tt);
        string day = std::to_string(ptm->tm_mday);
        string month = std::to_string(ptm->tm_mon+1);
        string year = std::to_string(ptm->tm_year+1900);
        if(ptm->tm_mon < 9){
            month = "0"+month;
        }
        string date = year+"-"+month+"-"+day;
        return date;
    }

    static struct tm* timeToTm(time_t tt){
        struct tm * timeinfo;
        time ( &tt );
        timeinfo = localtime ( &tt );
        return timeinfo;
    }

    static time_t slotToDate(time_t startDate, unsigned long slot){
        struct std::tm * ptm = std::localtime(&tt);
        ptm->tm_mday += slot;
        return mktime(tm);
    }

    Point(){}

    Point(string startDate, unsigned long slot, float price){
        this->startDate = strToDate(startDate);
        this->date = slotToDate(this->startDate, slot);
        this->price = price;
        this->slot = slot;
        this->n = 1;
    }

    Point(queue<string> que, string startDate){
        this->date = strToDate(que.front());
        que.pop();
        this->price = atof(que.front().c_str());
        que.pop();
        this->startDate = strToDate(startDate);
        this->slot = setSlot();
        this->n = 1;
    }

    Point(string startDate, string date, string price){
        this->date = strToDate(date);
        this->price = atof(price.c_str());
        this->startDate = strToDate(startDate);
        this->slot = setSlot();
        this->n = 1;
    }

    Point(time_t startDate, time_t date, float price, int n){
        this->date = date;
        this->price = price;
        this->startDate = startDate;
        this->slot = setSlot();
        this->n = n;
    }

    void setSlot(int dt){
        struct tm * date = timeToTm(this->date);
        struct tm * startDate = timeToTm(this->startDate);
        unsigned long slot = ((date->tm_year - startDate->tm_year)*12 + (date->tm_mon - startDate->tm_mon)) / dt;
        this->slot = slot;
    }

    int setSlot(){
        return difference(this->startDate, this->date);
    }

    int getSlot(){
        return slot;
    }

    double difference(time_t t1, time_t t2){
        double difference = std::difftime(t2, t1) / (60 * 60 * 24);
        return difference;
    }

    void setDt(int dt){
        this->dt = dt;
    }

    float getPrice(){
        return price;
    }

    Point operator + (Point pto){
        float num = this->price*(this->n) + pto.getPrice();
        this->n++;
        float price = (num)/(float)(this->n);
        Point p(startDate, date, price, n);
        return p;
    }

};

#endif // POINT_H
