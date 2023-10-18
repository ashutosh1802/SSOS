#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;
int main()
{
   ifstream fin("sample.txt");

   if(fin.is_open())
   {
    string line;
    int wordcount=0;

    while(getline(fin,line))
    {
        int cnt=0;
        stringstream ss(line);
        string word;
        vector<string> v;

        while (ss>>word)
        {
        wordcount++;
        cnt++;
        v.push_back(word);
        }

        cout<<"no. word ="<<cnt<<'\n';
        cout<<"array =";
        for(int i=0;i<v.size();i++){
            cout<<v[i]<<' ';
        }

        fin.close();
        cout<<"no. of words in file ="<<wordcount; }
   }

        else
        cout<<"failed to open file";

        
    
    return 0;
}
   