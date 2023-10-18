#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<map>

using namespace std;
int main() {
  ifstream inputFile("test.txt");
  map<string, int> map;
  map["ADD"] = 18;
  map["ADDF"] = 58;
  map["ADDR"] = 90;
  map["AND"] = 40;
  map["CLEAR"] = 34;

  if (inputFile.is_open()) {
    string line;
    while (getline(inputFile, line)) {
    	int count=0;
      stringstream ss(line);
      string word;
      while (ss >> word) {
        count++;
        if(count==1){
        	if(map.find(word)!=map.end()){
        		cout<<map[word]<<" ";
			}
			else{
				cout<<word<<" ";
			}
		}
		else{
			cout<<word<<" ";
		}
      }
      cout<<endl;
    }
    inputFile.close();
  } else {
    cout << "Failed to open the file.";
  }
  return 0;
}