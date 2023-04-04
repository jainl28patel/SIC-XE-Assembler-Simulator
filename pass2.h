#ifndef PASS2
#define PASS2

#include<iostream>
#include<vector>
#include<map>
#include"structs.h"
#include"utils.h"
#include"tab.h"
#include"pass2_utils.h"
using namespace std;

int baseRegister = 0;
bool base = false;

bool Pass2(map<string, SymStruct> &symTab, map<string, OpCodeStruct> &opTab, map<string, LiteralStruct> &litTab, map<string, BlockTable> &blkTab, map<string, int> &regs, vector<parsedLine> &v, ll &programL, vector<ModicationRecord> &modifications)
{
    ll startingAddress = 0, locCtr = 0, programLength = 0; //by default start address is 0
    bool err = false;
    BlockTable active = blkTab["DEFAULT"];
    int numLines = v.size(); // number of parsed lines

    // iterate through the vector of parsed lines
    for (int i = 0; i < numLines; i++)
    {
        parsedLine line = v[i];
        if(line.opcode == "START")
        {
            startingAddress = line.op1;
            locCtr = startingAddress;
        }
        else if(line.opcode == "END")
        {
            // Get and Set the program length
            computeProgramLength(blkTab, programLength);
            programL = programLength;
        }
        else if(line.opcode == "EQU")
        {
            // Implemented in pass-1
        }
        else if(line.opcode == "ORG")
        {
            // TODO
        }
        else if(line.opcode == "USE")
        {
            blkTab[active.name].locCtr = locCtr;
            active = blkTab[line.op1]; // block error
            locCtr = active.locCtr;
        }
        else if(line.opcode == "BASE")
        {
            auto sym = symTab.find(line.op1);
            if (sym == symTab.end())
            {
                line.err = "Symbol Undefined";
                err = true;
                continue;
            }
            base = true;
        }
        else if(line.opcode == "LTORG")
        {
            // Implemented in pass-1
        }
        else if(line.opcode == "RESW")
        {
            locCtr += 3 * stoi(line.op1);
        }
        else if(line.opcode == "RESB")
        {
            locCtr += stoi(line.op1);
        }
        else if(line.opcode == "WORD")
        {
            locCtr += 3;
            err = createObjCodeForWord(*line);
        }
        else if(line.opcode == "*")
        {
            createObjectCodeForData(line, 1);
            if (line.op1[0] == 'C')
            {
                locCtr += line.op1.length() - 4;
            }
            else if (line.op1[0] == 'X')
            {
                locCtr += (line.op1.length() - 4) / 2; // raise error if not a valid prepended hex
            }
        }
        else if(line.opcode == "BYTE" || line.opcode == "*")
        {
            createObjectCodeForData(line, 0);
            if (line.op1[0] == 'C')
            {
                locCtr += line.op1.length() - 3;
            }
            else if (line.op1[0] == 'X')
            {
                locCtr += (line.op1.length() - 3) / 2; // raise error if not a valid prepended hex
            }
        }
        else if(line.opcode == "NOBASE")
        {
            base = false;
        }
        else
        {
            OpCodeStruct op = opTab.find(line.opcode)->second;
            if (line.isFormat4)
            {
                locCtr += 4;
            }
            else
            {
                locCtr += op.possibleFormat;
            }
            ll pcRel = active.startingAddress + locCtr;
            if (op.possibleFormat == FORMAT_2)
            {
                err = createObjectCodeWithRegisters(line, opTab, regs);
            }
            else if (op.possibleFormat == FORMAT_1)
            {
                err = createObjectCodeWithOnlyOpcode(line, opTab);
            }
            else
            {
                err = createObjectCodeForInstruction(line, opTab, symTab, litTab, pcRel, modifications);
            }
        }

    }
}

#endif