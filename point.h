#ifndef POINT_H
#define POINT_H
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock
#include <queue>
#include <iostream>
using namespace std;

class Point{
private:
    unsigned long slot;
    float price;
    time_t date;
    static time_t startDate;
    static unsigned long dt;
    int n;

public:
    static time_t strToTime(string date){
        std::tm tm = strToTm(date);
        time_t tt = mktime(&tm);
        return tt;
    }

    static std::tm strToTm(string date){
        std::tm tm = {};
        stringstream ss(date);
        ss >> get_time(&tm, "%Y-%m-%d");
        return tm;
    }

    static string timeToStr(time_t tt){
        struct std::tm * ptm = timeToTm(tt);
        string day = std::to_string(ptm->tm_mday);
        string month = std::to_string(ptm->tm_mon+1);
        string year = std::to_string(ptm->tm_year+1900);
        if(ptm->tm_mday < 9){
            day = "0"+day;
        }
        if(ptm->tm_mon < 9){
            month = "0"+month;
        }
        string date = year+"-"+month+"-"+day;
        return date;
    }

    static struct tm* timeToTm(time_t tt){
        struct tm * timeinfo;
        timeinfo = localtime ( &tt );
        return timeinfo;
    }

    static time_t slotToTime(unsigned long slot){
        struct std::tm * ptm = timeToTm(Point::startDate);
        ptm->tm_mday += slot;
        return mktime(ptm);
    }

    static unsigned long getSlot(string dt){
        struct std::tm date = strToTm(dt);
        struct std::tm * startDate = timeToTm(getStartDate());
        unsigned long slot = ((date.tm_year - startDate->tm_year)*12 + (date.tm_mon - startDate->tm_mon)) / getDt();
        return slot;
    }

    static void setStartDate(string startDate){
        Point::startDate = strToTime(startDate);
    }

    static time_t getStartDate(){
        return Point::startDate;
    }

    static void setDt(unsigned long dt){
        Point::dt = dt;
    }

    static unsigned long getDt(){
        return Point::dt;
    }

    Point(){}

    Point(unsigned long slot, float price){
        this->date = slotToTime(slot);
        this->price = price;
        this->slot = slot;
        this->n = 1;
    }

    Point(queue<string> que){
        this->date = strToTime(que.front());
        que.pop();
        this->price = atof(que.front().c_str());
        que.pop();
        this->slot = setSlot((getDt()>0));
        this->n = 1;
    }

    Point(string date, string price){
        this->date = strToTime(date);
        this->price = atof(price.c_str());
        this->slot = setSlot((getDt()>0));
        this->n = 1;
    }

    Point(time_t date, float price, unsigned long slot, int n){
        this->date = date;
        this->price = price;
        this->slot = slot;
        this->n = n;
    }

    unsigned long setSlot(bool key){
        if(key){
            struct std::tm * startDate = timeToTm(this->date);
            struct std::tm date = *startDate;
            startDate = timeToTm(getStartDate());
            unsigned long slot = ((date.tm_year - startDate->tm_year)*12 + (date.tm_mon - startDate->tm_mon)) / getDt();
            return slot;
        } else {
            return difference(getStartDate(), this->date);
        }
    }

    unsigned long getSlot(){
        return slot;
    }

    double difference(time_t t1, time_t t2){
        double difference = std::difftime(t2, t1) / (60 * 60 * 24);
        return difference;
    }



    float getPrice(){
        return price;
    }

    Point operator + (Point pto){
        float num = this->price*(this->n) + pto.getPrice();
        this->n++;
        float price = (num)/(float)(this->n);
        Point p(this->date, price, this->slot, n);
        return p;
    }

};

#endif // POINT_H
