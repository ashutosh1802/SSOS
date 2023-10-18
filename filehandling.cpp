#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream inputFile("testout.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open the file." <<"\n";
        return 1;
    }
    vector<vector<string>> words2DArray;
    string word;
    while (inputFile >> word) {
        words2DArray.push_back({word});
    }
    inputFile.close();
    for (const auto& row : words2DArray) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }

    }
    return 0;
}