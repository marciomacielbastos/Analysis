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
#include <thread_bucket.h>
#include <csvmanager.h>
#include <iostream>
using namespace std;

map<long, float> ThreadBucket::bbl_area = map<long, float>();
map<long, long> ThreadBucket::old_bbls_lookup_table = map<long, long>();

queue<string> tup;

class RealEstate{
private:
    vector<long> bbls;
    string output;
    vector<ThreadBucket> tb_vector;
    vector<string> completeSeries;
    int num_threads;
    CSVManager cs;
    bool key;

public:
    RealEstate(string bblslist, string input, string output, int n){
        this->cs = CSVManager(input);
        this->output = output;
        this->num_threads = n;
        this->key = false;
        ThreadBucket::setBbl_area(loadBBLS(bblslist));
        shareBBLs();
    }

    RealEstate(string bblslist, string input, string output, int n, bool key){
        this->cs = CSVManager(input);
        this->output = output;
        this->num_threads =n;
        this->key = key;
        ThreadBucket::setBbl_area(loadBBLS(bblslist));
        shareBBLs();
    }

    void setStartDate(string startDate){
        ThreadBucket::setStartDate(startDate);
    }

    void setDt(long dt){
        ThreadBucket::setDt(dt);
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

    map<long, long> load_bbl_lookup_table(string path_to_oldbbl_lookpu_table){
        map<long, long> bbl_oldbbl;
        long bbl;
        long oldbbl;
        CSVManager cs(path_to_oldbbl_lookpu_table);
        queue<string> fl = cs.readLine();
        while(!fl.empty()){
            bbl = atol(fl.front().c_str());
            fl.pop();
            oldbbl = atol(fl.front().c_str());
            bbl_oldbbl[bbl] = oldbbl;
            fl.pop();
            fl = cs.readLine();
        }
        return bbl_oldbbl;
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
            ThreadBucket re = ThreadBucket(b, e);
            this->tb_vector.push_back(re);
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

    static void feed(ThreadBucket *re){
        re->add(tup);
    }

    static void feedPt(ThreadBucket *re){
        re->addPt(tup);
    }

    void feedBunch(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feed, &(this->tb_vector[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
       ThreadBucket::setBbl_area(map<long, float>());
    }

    void feedBunchPt(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feedPt, &(this->tb_vector[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
       ThreadBucket::setBbl_area(map<long, float>());
    }

    static void bbl_synthesis(ThreadBucket *tb){
        tb->bbl_synthesize();
    }

    void synthesize_bbls(string path_to_oldbbl_lookpu_table){
        ThreadBucket::setOldBblLookupTable(load_bbl_lookup_table(path_to_oldbbl_lookpu_table));
        thread t[this->num_threads];
        for(int i = 0; i < this->num_threads ; i++){
            t[i] = thread(bbl_synthesis, &(this->tb_vector[i]));
        }
        for(int i = 0; i < this->num_threads ; i++){
            t[i].join();
        }
        ThreadBucket::setOldBblLookupTable(map<long, long>());
    }

    static void interpol(ThreadBucket *re){
        re->interpol();
    }

    void start(){
        thread t[this->num_threads];
        for(int i = 0; i < this->num_threads ; i++){
            t[i] = thread(interpol, &(this->tb_vector[i]));
        }
        for(int i = 0; i < this->num_threads ; i++){
            t[i].join();
        }
    }
};

#endif // KERNEL_H
