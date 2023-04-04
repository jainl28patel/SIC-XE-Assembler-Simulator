#include<iostream>
#include<vector>
#include<map>
#include<string>
#include "struct.h"
#include "assemblyParser.h"
#include "objectProgramGenerator.h"
#include "pass1.h"
// #include "pass2.h"
#include "tab.h"
#include "utils.h"

using namespace std;


#define ll long long int


ll mod = 1e9 + 7;

int main (int argc, char *argv[])
{
    // fast input output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // check for valid arguments
    if (argc != 2)
    {
        cout << "Invalid arguments" << endl;
        cout << "Usage : ./assembler <input_file>.in" << endl;
        exit(1);
    }

    // setting the input and output 
    string input_file = argv[1];
    freopen((input_file + ".in").c_str(), "r", stdin);
    // freopen((input_file + ".out").c_str(), "w", stdout);

    // storing the parsed instructions
    vector<parsedLine> vec;
    map<string, OpCodeStruct> opTab;
    map<string, SymStruct> symTab;
    map<string, BlockTable> blkTab;
    map<string, LiteralStruct> litTab;
    vector<ModicationRecord> modifications;
    
    // default block
    BlockTable b;
    blkTab["DEFAULT"] = b;
    
    // build the opTab and regTab
    build(opTab);
    buildRegMap();

    // read the input file
    string s;
    ll startingAddress = 0; // custom startingAddress
    ll locCtr = startingAddress;
    ll programLength;
    string programName = "TEST";
    while (true)
    {
        getline(cin, s);
        if (cin.fail())
        {
            break;
        }
        parsedLine pline = parseLine(s);
        if (!(pline.label == "" && pline.opcode == "" && pline.op1 == "" && pline.op2 == ""))
        {
            vec.push_back(pline);
        }
    }

    try
    {
        cout << "***Intermediate File***\n\n"
             << endl;
        bool err = Pass1(vec, opTab, symTab, blkTab, litTab, programName);
        if (!err)
        {
            printTable(symTab);
            printTable(blkTab);
            printTable(litTab);
            cout << "\n\n***Listing File***\n"
                 << endl;
            // err = pass2(symTab, opTab, litTab, blkTab, regs, vec, programLength, modifications);
            // print();
            // cout << "\n\n***Object Program***\n"
            //      << endl;
        }
        // if (!err)
        // {
        //     writeHeaderRecord(programName, startingAddress);
        //     writeTextRecord(blkTab, vec);
        //     writeEndRecord(programLength);
        //     writeModificationRecord(modifications);
        // }
    }
    catch (string err)
    {
        print(err);
    }

    return 0;
}