#ifndef PASS1
#define PASS1

#include<iostream>
#include<vector>
#include<map>
#include"structs.h"
#include"utils.h"
#include"tab.h"
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;



bool Pass1(vector<parsedLine> &vec, map<string, OpCodeStruct> &opTab, map<string, SymStruct> &symTab, map<string, BlockTable> &blkTab, map<string, LiteralStruct> &litTab, string &programName, ll& startingAddress)
{
    /*
        Setting the initial data:
            starting address = 0
            program length = 0
            error = false
            active block = DEFAULT
            locCtr = locCtr of active block
            id = number of active block
    */
    ll programLength = 0;
    bool err = false;
    BlockTable active = blkTab["DEFAULT"];
    ll locCtr = active.locCtr;
    int id = active.number;

    vector<pair<int, parsedLine> > lits;

    /*
        Reading each parsed line and persorming the pass-1 operation of identification of literals and symbols
    */
    for (int i = 0; i < vec.size(); i++)
    {
        parsedLine line = vec[i];
        line.location   = locCtr;

        // classifying the instructions into different types: if-else ladder
        if(line.opcode == "START")
        {
            // DONE
            programName = line.label;
            startingAddress = stoi(line.op1);
            locCtr = startingAddress;
        }
        else if(line.opcode == "END")
        {
            /*
            * Perform operation performed while leaving program-block and manage the litTab
            */
            blkTab[active.name].locCtr = locCtr;
            manageBlocks(blkTab, symTab, programLength, startingAddress, litTab);
            manageLitTab(litTab, locCtr, vec, lits, i+1, blkTab["DEFAULT"]);
        }
        else if(line.opcode == "*")
        {
            // DONE
            continue;
        }
        else if(line.opcode == "USE")
        {
            /* DONE
            * Check if only USE -> move to default block
            * Else : create new block, set the active block and continue
            */
           if(line.op1 == "")
           {
                line.op1 = "DEFAULT";
           }
           blkTab[active.name].locCtr = locCtr;
           // Create new if not exist
           if(blkTab.find(line.op1) == blkTab.end()) 
           {
                blkTab[line.op1] = createBlock(line.op1, id+1);
           }
           // set the current configs
           active = blkTab[line.op1];
           locCtr = active.locCtr;
        }
        else if(line.opcode == "EQU")
        {
            // DONE : make entry to the symbol table
           err = enterSymbolTab(line, symTab, active, locCtr);
        }
        else if(line.opcode == "ORG")
        {
            // TODO: Implement whole
        }
        else if(line.opcode == "BASE")
        {
            // DONE : handelled in pass-2
        }
        else if(line.opcode == "LTORG")
        {
            // handlelitrals and update the locCtr and required var accordingly
            manageLitTab(litTab, locCtr, vec, lits, i+1, active);
        }
        else
        {
            // insert symbol if label present
            if(line.label != "")
            {
                symTab[line.label] = *createSymbol(line.label, locCtr, active);
            }

            // memory allocation instructions
            if (line.opcode == "RESB")
            {
                locCtr += stoi(line.op1); // raise error if empty or not a valid integer
            }
            else if (line.opcode == "WORD")
            {
                locCtr += 3;
            }
            else if (line.opcode == "RESW")
            {
                locCtr += 3 * stoi(line.op1);
            }
            else if (line.opcode == "BYTE")
            {
                if (line.op1[0] == 'C')
                {
                    locCtr += line.op1.length() - 3;
                }
                else if (line.op1[0] == 'X')
                {
                    locCtr += (line.op1.length() - 3) / 2; // raise error if not a valid prepended hex
                }
            }
            else
            {
                // check Format-4
                bool isFormat4 = false;
                string opcode = line.opcode;
                if(opcode[0] == '+')
                {
                    opcode = line.opcode.substr(1);
                    isFormat4 = true;
                }
                if(opcode[0] == '.')
                {
                    // comment line
                    continue;
                }

                auto op = opTab.find(opcode);

                if (op == opTab.end())
                {
                    line.err = "Invalid Opcode " + opcode;
                    err = true;
                }
                else 
                {
                    // check if literal used
                    if(line.op1[0] == '=')
                    {
                        auto literal = litTab.find(line.op1);
                        // if already not present in the LitTab
                        if(literal == litTab.end())
                        {
                            int litSize = 0;
                            switch (line.op1[1])
                            {
                            case '*':
                                if (line.op1.length() != 2)
                                {
                                    line.err = "Invalid literal format";
                                    err = true;
                                }
                                litSize = 3; //* means current PC and PC is of 3 bytes

                                break;
                            case 'C':
                                if (line.op1.length() <= 4){
                                    cout << "Bad literal\n";
                                    err = true;
                                    break;
                                }
                                litSize = line.op1.length() - 4; //=C"<lit-val>"
                                break;
                            case 'X':
                                if (line.op1.length() <= 4){
                                    cout << "Bad literal\n";
                                    err = true;
                                    break;
                                }
                                litSize = (line.op1.length() - 4) / 2; // raise error if not a vaild prepended hex
                                break;

                            default:
                                line.err = "Invalid literal format";
                                err = true;
                                break;
                            }
                            litTab[line.op1] = createLiteral(line.op1, active, litSize);
                        }
                    }

                    line.isFormat4 = isFormat4;
                    line.opcode = opcode;
                    if (isFormat4)
                    {
                        locCtr += 4;
                    }
                    else
                    {
                        locCtr += op->second.possibleFormat;
                    }
                }
            }   
        }
        vec[i] = line;
        if (line.opcode != "END" && line.opcode != "LTORG" && line.opcode != "USE" && line.opcode[0] != '.' && line.opcode != "BASE")
        {
            cout << setfill('0') << setw(4) << right << hex << line.location << " " << line.label << " " << line.opcode << " " << line.op1 << " " << line.op2 << " " << line.err << "\n";
        }
    }
    sort(lits.begin(), lits.end(), litsComparator);
    for (int i = 0; i < lits.size(); i++)
    {
        vec.insert(vec.begin() + lits[i].first, lits[i].second);
    }
    return err;
}

#endif