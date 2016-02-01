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

class Unit{
private:
    map<string,SubUnit> subunits;
    map<long,Point> timeSeries;
    float area;

public:
    Unit(){}

    Unit(float area){
        this->area = area;
    }

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


    void addPt(Point p){
        map<long,Point>::iterator it;
        it = this->timeSeries.find(p.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + p;
        } else {
            this->timeSeries[p.getSlot()] = p;
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

    void addPt(queue<string> p, bool key){
        if(key){
            Point pt(p);
            pt.setPrice(pt.getPrice()/(float)this->area);
            addPt(pt);
        } else {
           addPt(p);
        }
    }

    static string floatToString(float val){
        std::stringstream ss;
        ss << val;
        ss.flush();
        string s(ss.str());
        return s;
    }

    static string floatToString(long val){
        std::stringstream ss;
        ss << val;
        ss.flush();
        string s(ss.str());
        return s;
    }

    Spline load(){
        Spline s;
        s.load(this->timeSeries);
        map<long,Point>().swap(this->timeSeries);
        return s;
    }

    string interpol(){
        Spline s = load();
        string series = "[";
        long firstX;
        long lastX = Point::getSlot("2015-01-01");
        {
            vector<long> * temp = s.getXs();
            firstX= (*temp)[0];
        }
        float val;
        for(;firstX <= lastX ; firstX++){
            val = s.interpol(firstX);
            if(firstX != lastX){
                series += (floatToString(val)+",");
            } else {
               series += (floatToString(val)+"]");
            }
        }
        return series;
    }
};

#endif // UNIT_H
