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

#ifndef KERNEL_H
#define KERNEL_H
#include <vector>
#include <queue>
#include <thread>
#include <realestate.h>
#include <csvmanager.h>
#include <iostream>
using namespace std;

queue<string> tup;

class Kernel{
private:
    map<long, float> bbl_area;
    vector<long> bbls;
    string output;
    vector<RealEstate> re;
    vector<string> completeSeries;
    int num_threads;
    CSVManager cs;
    bool key;

public:
    Kernel(string bblslist, string input, string output, int n){
        this->cs = CSVManager(input);
        this->output = output;
        this->num_threads = n;
        this->key = false;
        this->bbl_area = loadBBLS(bblslist);
        shareBBLs();
    }

    Kernel(string bblslist, string input, string output, int n, bool key){
        this->cs = CSVManager(input);
        this->output = output;
        this->num_threads =n;
        this->key = key;
        this->bbl_area = loadBBLS(bblslist);
        shareBBLs();
    }

    void setStartDate(string startDate){
        RealEstate::setStartDate(startDate);
    }

    void setDt(long dt){
        RealEstate::setDt(dt);
    }

    void setBblArea(){
        if(this->key){
            this->bbls.push_back(0);
        }
    }

    map<long, float> loadBBLS(string bblslist){
        setBblArea();
        map<long, float> bbl_area;
        long bbl;
        float area;
        CSVManager cs(bblslist);
        queue<string> fl = cs.readLine();
        while(!fl.empty()){
            bbl = atol(fl.front().c_str());
            fl.pop();
            area = atof(fl.front().c_str());
            bbl_area[bbl] = area;
            fl.pop();
            this->bbls.push_back(bbl);
            fl = cs.readLine();
        }
        return bbl_area;
    }

    void shareBBLs(){
        long offset = this->bbls.size() % this->num_threads;
        long len = this->bbls.size() / this->num_threads;
        unsigned long begin = 0, end = 0;
        long b, e;
        while(end < this->bbls.size()-1){
            begin = end;
            end += len;
            if(offset){
                end++;
                offset--;
            }
            if(end >= this->bbls.size()){
                end = this->bbls.size()-1;
            }
            b = this->bbls[begin];
            e = this->bbls[end];
            RealEstate re = RealEstate(b, e);
            this->re.push_back(re);
        }
        //Empty this->bbls, since it will be not used anymore
        vector<long>().swap(this->bbls);
    }

    bool getTup(){
        queue<string> fl = this->cs.readLine();
        if (!fl.empty()){
            tup = fl;
            return true;
        } else {
            return false;
        }
    }

    static void feed(RealEstate *re){
        re->add(tup);
    }

    static void feedPt(RealEstate *re){
        re->addPt(tup);
    }

    void feedBunch(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feed, &(this->re[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
    }

    void feedBunchPt(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feedPt, &(this->re[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
    }

    static void interpol(RealEstate *re){
        re->interpol();
    }

    void start(){
        thread t[this->num_threads];
        for(int i = 0; i < this->num_threads ; i++){
            t[i] = thread(interpol, &(this->re[i]));
        }
        for(int i = 0; i < this->num_threads ; i++){
            t[i].join();
        }
    }
};

#endif // KERNEL_H
