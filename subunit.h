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

#ifndef SUBUNIT_H
#define SUBUNIT_H
#include <map>
#include <point.h>
#include <queue>
#include <interpol.h>
using namespace std;


class SubUnit{
private:
    map<long,Point> timeSeries;
public:
    SubUnit(){}

    void add(queue<string> p){
        Point pto(p);
        map<long,Point>::iterator it;
        it = this->timeSeries.find(pto.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pto;
        } else {
            this->timeSeries[pto.getSlot()] = pto;
        }
    }

    void interpol(){
//        for(map<long, Point>::iterator it = timeSeries.begin(); it != timeSeries.end(); it++){

//        }
        Interpol i(&timeSeries);
        i.calcHlist();
    }
};

#endif // SUBUNIT_H
