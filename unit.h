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

#ifndef UNIT_H
#define UNIT_H
#include <subunit.h>
#include <map>
#include <queue>
#include <point.h>
#include <spline.h>
#include <sstream>

class Unit
{
private:
    map<string,SubUnit> subunits;
    map<long,Point> timeSeries;
    Spline s;

public:
    Unit(){}

    void add(queue<string> su){
        string su_id = su.front();
        su.pop();
        map<string,SubUnit>::iterator it;
        it = this->subunits.find(su_id);
        if (it!= this->subunits.end()){
            it->second.add(su);
        } else {
            subunits[su_id] = SubUnit();
            subunits[su_id].add(su);
        }
    }

    void addPt(queue<string> p){
        Point pt(p);
        map<long,Point>::iterator it;
        it = this->timeSeries.find(pt.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pt;
        } else {
            this->timeSeries[pt.getSlot()] = pt;
        }
    }

//    void interpol(){
////        for(map<string, SubUnit>::iterator it = subunits.begin(); it != subunits.end(); it++){
////            (it->second).interpol();
////        }
//        this->s.load((this->timeSeries));
//        float c = 1.5;
//        c = this->s.interpol(c);
//        c = 0;
//    }

    string interpol(){
        this->s.load((this->timeSeries));
        string series = "[";
        string temp_;
        stringstream ss (stringstream::in | stringstream::out);
        vector<long> * temp = this->s.getXs();
        long firstX = (*temp)[0];
        long lastX = Point::getSlot("2015-01-01");
        for(;firstX <= lastX ; firstX++){
            ss << s.interpol(firstX);
            if(firstX != lastX){
                ss >> temp_;
                series += (temp_+",");
            } else {
               series += (ss.str()+"]");
            }
        }
        return series;
    }
};

#endif // UNIT_H
