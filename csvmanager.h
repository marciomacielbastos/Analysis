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

    queue<string> read(bool b){
        if(b){}
        string line;
        if ( file.good() ){
             getline ( file, line,'\n');
             return setLine(line);
        } else {
            this->file.close();
            queue<string> empty;
            return empty;
        }
    }
};

#endif // CSVMANAGER_H
