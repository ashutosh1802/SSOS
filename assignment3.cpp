#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct Optab
{
    string mnemonic;
    int opcode;
};

struct Symtab
{
    string symbol;
    int address;
};

int main()
{
    ifstream fp1("table.txt");
    ifstream fp2("optab.txt");
    ofstream fp3("symtab.txt");

    if (!fp1.is_open())
    {
        cout<< "Error opening input file." << endl;
        return 1;
    }

    if (!fp2.is_open())
    {
        cout << "Error opening optab file." << endl;
        return 1;
    }

    if (!fp3.is_open())
    {
        cout << "Error opening symtab file." << endl;
        return 1;
    }

    int locctr, startaddr, symcount = 0, optabcount = 0, found = 0;
    string line, label, opcode, operand, symbol;

    fp1 >> label >> opcode >> startaddr;
    if (opcode == "START")
    {
        locctr = startaddr;
        cout << "\t" << label << "\t" << opcode << "\t" << startaddr << endl;
        fp1 >> label >> opcode >> operand;
    }
    else
    {
        locctr = 0;
    }

    vector<Symtab> symtab;
    vector<Optab> optab;

    while (opcode != "END")
    {
        cout << locctr;
        if (label != "**")
        {
            fp3 << label << "\t" << locctr << endl;
            Symtab entry;
            entry.symbol = label;
            entry.address = locctr;
            symtab.push_back(entry);
            symcount++;
        }
        fp2.clear(); 
        fp2.seekg(0, ios::beg); 
        Optab optEntry;

        while (fp2 >> optEntry.mnemonic >> optEntry.opcode)
        {
            if (opcode == optEntry.mnemonic)
            {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            if (opcode == "START")
            {
              
            }
            else if (opcode == "END")
            {
               
            }
            else if (opcode == "RESB")
            {
                locctr += stoi(operand);
            }
            else if (opcode == "BYTE")
            {
                if (operand[0] == 'X')
                {
                    locctr++;
                }
                else
                {
                    locctr += operand.length() - 3;
                }
            }
            else
            {
                cerr << "Invalid opcode" << endl;
                return 1;
            }
        }
        cout << "\t" << label << "\t" << opcode << "\t" << operand << endl;
        found = 0;
        fp1 >> label >> opcode >> operand;
    }

    fp1.close();
    fp2.close();
    fp3.close();

    return 0;
}
