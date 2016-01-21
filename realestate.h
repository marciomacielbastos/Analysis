#ifndef REALESTATE_H
#define REALESTATE_H
#include <unit.h>
#include <queue>
#include <map>
#include <point.h>
#include <ctime>

using namespace std;

long Point::dt = 0;
time_t Point::startDate = Point::strToTime("1980-01-01");


class RealEstate{

protected:
    long inf;
    long sup;
    map<long,Unit> units;

public:
    RealEstate(long inf, long sup){
        this->inf = inf;
        this->sup = sup;
    }

    static void setDt(long dt){
        Point::setDt(dt);
    }

    static void setStartDate(string startDate){
        Point::setStartDate(startDate);
    }

    bool canBeAdd(long bbl){
        //remind to put a extra row 00000000 in the bbl
        if(this->inf < bbl && bbl <= this->sup){
            return true;
        } else {
            return false;
        }
    }

    bool add(queue<string> tup){
        long bbl = atol(tup.front().c_str());
        tup.pop();
        if (canBeAdd(bbl)){
            map<long,Unit>::iterator it;
            it = this->units.find(bbl);
            if (it!= this->units.end()){
                it->second.add(tup);
            } else {
                this->units[bbl] = Unit();
                this->units[bbl].add(tup);
            }
            return true;
        } else {
            return false;
        }
    }

    void addPt(queue<string> tup){
        long bbl = atol(tup.front().c_str());
        tup.pop();
        if (canBeAdd(bbl)){
            map<long,Unit>::iterator it;
            it = this->units.find(bbl);
            if (it!= this->units.end()){
                this->units[bbl].addPt(tup);
            } else {
                this->units[bbl] = Unit();
                this->units[bbl].addPt(tup);
            }
        } else {
            return;
        }
    }

    void interpol(){
        for(auto i: this->units){
            (i.second).interpol();
        }
    }
};

#endif // REALESTATE_H
