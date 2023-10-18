#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

vector<vector<string>> readFile(const string& fileName);
void createSymTab();
void generateObjectCode();
string toHex(int value, int width);

map<string, int> symbolTable;
map<string, string> opcode;
vector<vector<string>> vec;
vector<vector<string>> obj;

int main() {
    // Initialize opcode table
    opcode = {
        {"LDX", "04"}, {"LDA", "00"}, {"TD", "e0"}, {"JEQ", "30"}, {"RD", "d8"},
        {"COMP", "28"}, {"STCH", "54"}, {"TIX", "2c"}, {"JLT", "38"}, {"RSUB", "4c"},
        {"STL", "14"}, {"JSUB", "48"}, {"J", "3c"}, {"STA", "0c"}, {"LDL", "08"},
        {"LDCH", "50"}, {"WD", "dc"}, {"STX", "10"}
    };

    string fileName = "file.txt";
    vec = readFile(fileName);

    createSymTab();
    generateObjectCode();

    return 0;
}

vector<vector<string>> readFile(const string& fileName) {
    vector<vector<string>> vec;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "File not found." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        vec.push_back({});
        stringstream str(line);
        string word;
        while (str >> word) {
            vec.back().push_back(word);
        }
    }

    file.close();
    return vec;
}

void createSymTab() {
    int location_pointer = 0;

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].size() == 3) {
            if (vec[i][1] == "END") {
                symbolTable[vec[i][0]] = location_pointer;
                break;
            }

            if (vec[i][1] == "RESW" || vec[i][1] == "RESB") {
                symbolTable[vec[i][0]] = location_pointer;
                if (vec[i][1] == "RESW") {
                    location_pointer += stoi(vec[i][2]) * 3;
                } else {
                    location_pointer += stoi(vec[i][2]);
                }
            } else if (vec[i][1] == "BYTE") {
                if (vec[i][0] == "EOF") {
                    symbolTable[vec[i][0]] = location_pointer;
                    location_pointer += 3;
                } else {
                    symbolTable[vec[i][0]] = location_pointer;
                    location_pointer++;
                }
            } else {
                symbolTable[vec[i][0]] = location_pointer;
            }
        }
        location_pointer += 3;
    }
}

void generateObjectCode() {
    for (int i = 1; i < vec.size(); i++) {
        vector<string> v;

        if (vec[i].size() == 1) {
            if (vec[i][0] == "RSUB") {
                v.push_back("4c0000");
            }
        } else if (vec[i].size() == 2) {
            if (vec[i][0] == "END") {
                break;
            }

            string opcodeValue = opcode[vec[i][0]];
            v.push_back(opcodeValue);

            int symbolValue = symbolTable[vec[i][1]];
            v.push_back(toHex(symbolValue, 4)); // 4 characters wide
        } else if (vec[i].size() == 3) {
            if (vec[i][1] == "END") {
                break;
            } else if (vec[i][1] == "RESW" || vec[i][1] == "RESB" || vec[i][1] == "START") {
                obj.push_back(v);
                continue;
            } else if (vec[i][1] == "WORD") {
                int wordValue = stoi(vec[i][2]);
                v.push_back(toHex(wordValue, 6)); // 6 characters wide
            } else if (vec[i][1] == "BYTE") {
                string byteValue = vec[i][2].substr(2, vec[i][2].length() - 3);
                v.push_back(byteValue);
            } else {
                string opcodeValue = opcode[vec[i][1]];
                v.push_back(opcodeValue);

                int symbolValue = symbolTable[vec[i][2]];
                v.push_back(toHex(symbolValue, 4)); // 4 characters wide
            }
        }
        obj.push_back(v);
    }

    // Print object code
    for (const vector<string>& line : obj) {
        for (const string& code : line) {
            cout << code << "  "; // Add spaces between codes
        }
        cout << endl;
    }
}

string toHex(int value, int width) {
    stringstream ss;
    ss << hex << value;
    string result = ss.str();
    // Add leading zeros to meet the specified width
    while (result.length() < width) {
        result = "0" + result;
    }
    return result;
}
