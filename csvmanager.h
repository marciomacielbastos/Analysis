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

#ifndef CSVMANAGER_H
#define CSVMANAGER_H
#include <queue>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


//Bizu do void -> str
//void *vp = static_cast<void*>(new string("it's easy to break stuff like this!"));
//string *sp = static_cast<string*>(vp);
//string s = *sp;

class CSVManager{
private:
    std::ifstream file;

    /*
     * setLine() : tokenize each attribute of the line tuple,
     * remove \" and add them to a queue;
     * attribute line: tuple of attributes written as string;
     * return: a queue of attributes (strings) without \";
     */
    queue<string> setLine(string line){
        string token;
        istringstream ss(line);
        queue<string> que;
        while(getline(ss, token, ',')) {
            while(token.find("\"")!=string::npos){
                token.replace(token.find("\""), string("\"").length(), "");
            }
            que.push(token);
        }
        return que;
    }

public:
    CSVManager(){}

    CSVManager(string filename){
        this->file = ifstream(filename);
    }

    /*
     * readQueue(): read each line of the file and push them in a queue of
     * queue of attributes;
     * return: a queue of queue of attributes (strings);
     */
    queue<queue<string>> readQueue(){
        string line;
        queue<queue<string>> que;
        while ( file.good() )
        {
             getline ( file, line,'\n');
             que.push(setLine(line));
        }
        this->file.close();
        return que;
    }

    /*
     * readVector(): read each line of the file and push them in a vector of
     * queue of attributes;
     * return: a vector of queue of attributes (strings);
     */
    vector<queue<string>> readVector(){
        string line;
        vector<queue<string>> vec;
        while ( file.good() )
        {
             getline ( file, line,'\n');
             vec.push_back(setLine(line));
        }
        this->file.close();
        return vec;
    }

    /*
     * readLine(): read and return each line of the file as a queue of attributes;
     * attribute line: tuple of attributes written as string;
     * return : a queue of attributes (strings);
     */
    queue<string> readLine(){
        string line;
        if ( file.good() ){
             getline ( file, line,'\n');
             return setLine(line);
        } else {
            this->file.close();
            return queue<string>();
        }
    }


    /*
     * write(): write the time series for each bbl as a tuple;
     * vector<string> series: vector of the tuple (bbl, time series) written as string;
     * output: string with the path of where the series will be written;
     * return: void;
     */
    void write(vector<string> series, string output){
        std::fstream outfile;
        outfile.open (output, std::fstream::in | std::fstream::out | std::fstream::app);
        for(auto i : series){
            outfile << i+"\n";
        }
        outfile.close();
    }
};

#endif // CSVMANAGER_H
