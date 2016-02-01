/*************************************************************************
 *
 * Author: Marcio Maciel Bastos
 * __________________
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Marcio Maciel Bastos.
 * The intellectual and technical concepts contained
 * herein are proprietary to Marcio Maciel Bastos
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Marcio Maciel Bastos.
 */

#ifndef REALESTATE_H
#define REALESTATE_H
#include <unit.h>
#include <queue>
#include <map>
#include <point.h>
#include <ctime>
#include <vector>

using namespace std;

long Point::dt = 0;
time_t Point::startDate = Point::strToTime("1980-01-01");


class RealEstate{

protected:
    long inf;
    long sup;
    map<long,Unit> units;
    vector<string> series;
    static map<long, float> bbl_area;

public:
    RealEstate(long inf, long sup){
        this->inf = inf;
        this->sup = sup;
    }

    static void setDt(long dt){
        Point::setDt(dt);
    }

    static void setBbl_area(map<long, float> bbl_area){
        RealEstate::bbl_area = bbl_area;
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
                this->units[bbl].addPt(tup, true);
            } else {
                float area = this->bbl_area[bbl];
                this->units[bbl] = Unit(area);
                this->units[bbl].addPt(tup, true);
            }
        } else {
            return;
        }
    }

    void interpol(){
        for(auto i: this->units){
           string series = this->units[i.first].interpol();
           series = Unit::floatToString(i.first)+","+series;
           this->series.push_back(series);
        }
        map<long,Unit>().swap(this->units);
    }

    vector<string> getSeries(){
        return this->series;
    }

    void clearSeries(){
        vector<string>().swap(this->series);
    }
};

#endif // REALESTATE_H
