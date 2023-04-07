#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "assemblyParser.h"
#include "objectProgramGenerator.h"
#include "pass1.h"
#include "pass2.h"
#include "tab.h"
#include "utils.h"

using namespace std;

#define ll long long int

int main(int argc, char *argv[])
{
    // check for valid arguments
    if (argc != 3)
    {
        cout << "Invalid arguments" << endl;
        cout << "Usage : ./assembler <input file name> <output file name>" << endl;
        exit(1);
    }


    // setting the input and output
    string input_file = argv[1];
    string output_file = argv[2];
    freopen((input_file).c_str(), "r", stdin);
    freopen((output_file).c_str(), "w", stdout);

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
        if(pline.err != "")
        {
            cout << "ERROR on line " << pline.location << " : " << pline.err << endl;
        }
        else if (!pline.isEmpty && !pline.isComment && !(pline.label == "" && pline.opcode == "" && pline.op1 == "" && pline.op2 == ""))
            vec.push_back(pline);
    }

    try
    {
        cout << "-------------------------------------------------------------------\n"
             << "|                          INTERMEDIATE FILE                      |\n"
             << "-------------------------------------------------------------------\n\n";
        bool err = Pass1(vec, opTab, symTab, blkTab, litTab, programName, startingAddress);
        if (!err)
        {
            cout << "\n\n";
            cout << "--- symTab ---\n";
            printTable(symTab);
            cout << "\n\n--- blkTab ---\n";
            printTable(blkTab);
            err = Pass2(symTab, opTab, litTab, blkTab, regs, vec, programLength, modifications);
            print();
            cout << "-------------------------------------------------------------------\n"
                 << "|                          OBJECT PROGRAM                          |\n"
                 << "-------------------------------------------------------------------\n\n";
        }
        if (!err)
        {
            writeHeaderRecord(programName, startingAddress, programLength);
            writeTextRecord(blkTab, vec);
            writeModificationRecord(modifications);
            writeEndRecord(startingAddress);
        }
    }
    catch (char *err)
    {
        cout<<"Error in the pass :"<<err<<endl;
        return 1;
    }

    return 0;
}