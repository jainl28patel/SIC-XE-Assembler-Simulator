#ifndef PASS2_UTILS
#define PASS2_UTILS

#include<iostream>
#include<vector>
#include<map>
#include"structs.h"
#include"utils.h"
#include"tab.h"
using namespace std;

bool createObjCodeForWord(parsedLine& line) //create object code for WORD
{
    ObjectCode obj;
    if(line.op1 == "")
    {
        line.err = "WORD cannot be empty";
        return true;
    }
    if(isNumeric(line.op1))
    {
        obj.isWord = stoi(line.op1);
        return false;
    }
    pl.err = "Use BYTE for strings, integers for WORD";
    return true;
}

bool createObjectCodeForData(parsedLine &pl, int subStrIndex) //create object code for BYTE
{
    ObjCode obj;
    obj.isData = true;
    string str = pl.op1.substr(2 + subStrIndex, pl.op1.length() - 1);
    if (pl.op1[subStrIndex] == 'X')
    {
        obj.data = str;
    }
    else if (pl.op1[subStrIndex] == 'C')
    {

        obj.data = string_to_hex(str);
    }
    else
    {
        return true;
    }
    pl.objCode = obj;
    return false;
}

bool createObjectCodeWithRegisters(parsedLine &pl, map<string, OpCodeStruct> &opTab, map<string, int> &regs) //
{
    ObjCode obj;
    obj.ni = 3;
    int op = opTab.find(pl.opcode)->second.opcode;
    if (pl.opcode == "CLEAR" || pl.opcode == "TIXR")
    {
        if (pl.op2 != "")
        {
            pl.err = "Too many arguments for this opcode";
            return true;
        }
        if (regs.find(pl.op1) == regs.end())
        {
            pl.err = "Not a valid register " + pl.op1;
            return true;
        }
        obj.hasReg = true;
        obj.reg1 = regs.find(pl.op1)->second;
        obj.reg2 = -1;
        obj.opcode = op;
        pl.objCode = obj;
        return false;
    }
    if (regs.find(pl.op1) == regs.end() || regs.find(pl.op2) == regs.end())
    {
        pl.err = "Not a valid register " + pl.op1 + " or " + pl.op2;
        return true;
    }
    obj.hasReg = true;
    obj.reg1 = regs.find(pl.op1)->second;
    obj.reg2 = regs.find(pl.op2)->second;
    obj.opcode = op;
    pl.objCode = obj;
    return false;
}

bool createObjectCodeWithOnlyOpcode(parsedLine &pl, map<string, OpCodeStruct> &opTab)
{
    ObjCode obj;
    int op = opTab.find(pl.opcode)->second.opcode;
    obj.opcode = op;
    pl.objCode = obj; // handle operands should not come with zero operand instructions
    return false;
}

#endif