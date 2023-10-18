#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream example;
    fstream output;

    output.open("ans4.txt",ios::out);
    example.open("assembly.txt",ios::in);

    unordered_map<string,string> sic;
    // SICmapping(sic);
    fstream f;
    f.open("SIC.txt",ios::in);
    
    string s1;
    while(!f.eof()){
        getline(f,s1);
        stringstream ss(s1);
        string a,b;

        ss >> a;
        ss >> b;

        sic[a] = b;
    }
    f.close();

    // Initializing Symbol Table
    unordered_map<string,int> symbol_table;
    string s;
    int loc = -1;
    while(!example.eof()){
        getline(example,s);

        stringstream ss(s);
        vector<string> line;
        string word;
        while(ss >> word) line.push_back(word);

        if(line[0] == "START") {loc = stoi(line[1]); continue;}
        else if(line[0] == "END") break;

        if(line.size() == 3) symbol_table[line[0]] = loc;

        if(line[1] == "BYTE") loc++;
        else if(line[1] == "RESB") loc += stoi(line[2]);
        else loc += 3;
    }


    example.seekg(0);
    while(!example.eof()){
        getline(example,s);

        stringstream ss(s);
        vector<string> line;
        string word;
        while(ss >> word) line.push_back(word);

        int i=0;
        if(line.size() == 3) i++;

        string temp = "";
        if(line[i] == "START") continue;

        else if(line[i] == "END") break;

        if(line[i] == "RESB"){
            int x = stoi(line[i+1]);
            while(x--) temp += "00";
        }

        else if(line[i] == "BYTE")
            temp = line[i+1];
        
        else{
            bool check = false;

            while(i<line.size()){
                string word = line[i];
                if(sic.find(word) != sic.end())
                    temp += sic[word] + " ";

                else if(symbol_table.find(word) != symbol_table.end())
                     temp += to_string(symbol_table[word]) + " ";
                
                else {
                    output<<"Error : "<<word<<" symbol not declared "<<endl;
                    check = true;
                    break;
                }
                i++;
            }

            if(check) break;
        }

        output<<temp<<endl;
    }

    output.close();
    example.close();
   return 0;
}
