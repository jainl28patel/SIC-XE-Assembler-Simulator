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
    line.err = "Use BYTE for strings, integers for WORD";
    return true;
}

bool createObjectCodeForData(parsedLine &pl, int subStrIndex) //create object code for BYTE
{
    ObjectCode obj;
    obj.isData = true;
    string str = pl.op1.substr(2 + subStrIndex, pl.op1.length() - 1); // op1 will be of format ="<hex>"
    if (pl.op1[subStrIndex] == 'X')
    {
        obj.data = str; //we already have hex
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

bool createObjectCodeWithRegisters(parsedLine &pl, map<string, OpCodeStruct> &opTab, map<string, int> &regs) // format 2
{
    ObjectCode obj;
    obj.ni = 3;
    int op = opTab.find(pl.opcode)->second.opcode;
    if (pl.opcode == "CLEAR" || pl.opcode == "TIXR")
    {
        if (pl.op2 != "") //format 2 instructions should have only 1 operand
        {
            pl.err = "Too many arguments for this opcode";
            return true;
        }
        if (regs.find(pl.op1) == regs.end()) // invalid register
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
    obj.reg1 = regs.find(pl.op1)->second; //
    obj.reg2 = regs.find(pl.op2)->second;
    obj.opcode = op;
    pl.objCode = obj;
    return false;
}

bool createObjectCodeWithOnlyOpcode(parsedLine &pl, map<string, OpCodeStruct> &opTab) //format 1
{
    ObjectCode obj;
    int op = opTab.find(pl.opcode)->second.opcode;
    obj.opcode = op;
    pl.objCode = obj; // handle operands should not come with zero operand instructions
    return false;
}

ModicationRecord createModificationRecord(int start, int modify)
{
    ModicationRecord m;
    m.start = start;
    m.modified = modify;
    return m;
}

SymStruct getSymbol(map<string, SymStruct> &symTab, parsedLine &pl, int substrIndex)
{
    string str = pl.op1.substr(substrIndex);
    auto symbol = symTab.find(str);
    if (symbol == symTab.end())
    {
        pl.err = "Undefined Label";
        throw pl.err;
    }
    return symbol->second;
}

ObjectCode pcOrBaseRelativeAddressing(map<string, SymStruct> &symTab, map<string, OpCodeStruct> &opTab, ll &locCtr, parsedLine &pl, int ni, int subStrIndex, vector<ModicationRecord> &modi, bool &base, int& baseRegister)
{
    ObjectCode obj;
    auto symbol = getSymbol(symTab, pl, subStrIndex);
    bool isAbsolute = symbol.flags == "A";
    long long effectiveLoc = symbol.block.startingAddress + symbol.location;
    bool simple = false;
    int isIndexed = 0;
    if (pl.op2 != "")
    {
        if (pl.op2 == "X")
        {
            isIndexed = 1;
        }
        else
        {
            throw "Index Register should be X";
        }
    }
    if (isAbsolute)
    {
        effectiveLoc = symbol.location;
    }
    if (pl.isFormat4)
    {
        if (validf4(effectiveLoc))
        {
            obj.format = 4;
            obj.displacement = effectiveLoc;
            obj.ni = ni;
            obj.xbpe = 1 | (isIndexed << 3);
            obj.opcode = opTab[pl.opcode].opcode;
            if (!isAbsolute)
            {
                modi.push_back(createModificationRecord(pl.location + 1, 5));
            }
            return obj;
        }
        else
        {
            pl.err = "Symbol " + pl.op1 + "displacement overflows";
        }
    }
    else
    {
        effectiveLoc -= locCtr;
        if (validf3(effectiveLoc))
        {
            obj.format = 3;
            obj.displacement = effectiveLoc;
            obj.ni = ni;
            obj.xbpe = 2 | (isIndexed << 3);
            obj.opcode = opTab[pl.opcode].opcode;
            return obj;
        }
        else if (base)
        {
            effectiveLoc += locCtr - baseRegister;
            if (validf3(effectiveLoc))
            {obj.format = 3;
                obj.displacement = effectiveLoc;
                obj.ni = ni;
                obj.xbpe = 4 | (isIndexed << 3);
                obj.opcode = opTab[pl.opcode].opcode;
                return obj;
            }
            simple = true;
        }
        else if (simple)
        {
            long long simpleLoc = symbol.location;
            if (validf3(simpleLoc))
            {obj.format = 3;
                obj.displacement = simpleLoc;
                obj.ni = ni;
                obj.xbpe = 0 | (isIndexed << 3);
                obj.opcode = opTab[pl.opcode].opcode;
                return obj;
            }
            else
            {
                throw "Invalid Displacement";
            }
        }
        throw "Invalid Displacement";
    }
}

bool createObjectCodeForInstruction(parsedLine &pl, map<string, OpCodeStruct> &opTab, map<string, SymStruct> &symTab, map<string, LiteralStruct> &litTab, long long &locCtr, vector<ModicationRecord> &modifications, bool &base, int& baseRegister)
{

    try
    {
        ObjectCode obj;
        if (pl.opcode == "RSUB")
        {
            int op = opTab.find(pl.opcode)->second.opcode;
            obj.displacement = 0;
            obj.ni = 3;
            obj.xbpe = 0;
            obj.opcode = op;
            pl.objCode = obj;
            obj.format = 3;
            return false;
        }

        if (pl.op1[0] == '@')
        {
            obj = pcOrBaseRelativeAddressing(symTab, opTab, locCtr, pl, 2, 1, modifications, base, baseRegister);
        }
        else if (pl.op1[0] == '#')
        {
            if (pl.op2 != "")
            {
                pl.err = "Too many arguments";
                return true;
            }

            string str = pl.op1.substr(1);

            if (isNumeric(str))
            {
                int disp = stoi(str);
                bool simple = false;

                if (pl.isFormat4)
                {
                    if (validf4(disp))
                    {
                        obj.format = 4;
                        obj.displacement = disp;
                        obj.ni = 1;
                        obj.xbpe = 1;
                        obj.opcode = opTab[pl.opcode].opcode;
                    }
                    else
                    {
                        pl.err = "Immediate " + pl.op1 + "displacement overflows";
                    }
                }
                else
                {
                    if (validf3(disp))
                    {
                        obj.format = 3;
                        obj.displacement = disp;
                        obj.ni = 1;
                        obj.xbpe = 0;
                        obj.opcode = opTab[pl.opcode].opcode;
                    }
                    else
                    {
                        throw "Invalid Displacement";
                    }
                }
            }
            else
            {
                auto symbol = getSymbol(symTab, pl, 1);
                bool isAbsolute = symbol.flags == "A";
                long long effectiveLoc = symbol.block.startingAddress + symbol.location;
                bool simple = false;

                if (isAbsolute)
                {
                    effectiveLoc = symbol.location;
                }
                if (pl.isFormat4)
                {

                    if (validf4(effectiveLoc))
                    {
                        obj.format = 4;
                        obj.displacement = effectiveLoc;
                        obj.ni = 1;
                        obj.xbpe = 1;
                        obj.opcode = opTab[pl.opcode].opcode;
                        if (!isAbsolute)
                        {
                            modifications.push_back(createModificationRecord(pl.location + 1, 5));
                        }
                    }
                    else
                    {
                        pl.err = "Symbol " + pl.op1 + "displacement overflows";
                    }
                }
                else
                {
                    if (!isAbsolute)
                    {
                        effectiveLoc -= locCtr;
                    }
                    if (validf3(effectiveLoc))
                    {
                        obj.format = 3;
                        obj.displacement = effectiveLoc;
                        obj.ni = 1;
                        obj.xbpe = 2;
                        obj.opcode = opTab[pl.opcode].opcode;
                    }
                    else if (base && !isAbsolute)
                    {
                        effectiveLoc += locCtr - baseRegister;
                        if (validf3(effectiveLoc))
                        {obj.format = 3;
                            obj.displacement = effectiveLoc;
                            obj.ni = 1;
                            obj.xbpe = 4;
                            obj.opcode = opTab[pl.opcode].opcode;
                        }
                        else
                        {
                            simple = true;
                        }
                    }
                    else if (simple && !isAbsolute)
                    {
                        long long simpleLoc = symbol.location;
                        if (validf3(simpleLoc))
                        {obj.format = 3;
                            obj.displacement = simpleLoc;
                            obj.ni = 1;
                            obj.xbpe = 0;
                            obj.opcode = opTab[pl.opcode].opcode;
                        }
                        else
                        {
                            throw "Invalid Displacement";
                        }
                    }
                    else
                    {
                        throw "Invalid Displacement";
                    }
                }
            }
        }
        else if (pl.op1[0] == '=')
        {
            auto literal = litTab.find(pl.op1)->second;
            bool simple = false;

            if (pl.isFormat4)
            {
                long long effectiveLoc = literal.block.startingAddress + literal.address;
                if (validf4(effectiveLoc))
                {
                    obj.format = 4;
                    obj.displacement = effectiveLoc;
                    obj.ni = 3;
                    obj.xbpe = 1;
                    obj.opcode = opTab[pl.opcode].opcode;
                    modifications.push_back(createModificationRecord(pl.location + 1, 5));
                }
                else
                {
                    pl.err = "Literal " + pl.op1 + "displacement overflows";
                }
            }
            else
            {

                long long effectiveLoc = literal.block.startingAddress + literal.address - locCtr;
                if (validf3(effectiveLoc))
                {obj.format = 3;
                    obj.displacement = effectiveLoc;
                    obj.ni = 3;
                    obj.xbpe = 2;
                    obj.opcode = opTab[pl.opcode].opcode;
                }
                else if (base)
                {
                    effectiveLoc += locCtr - baseRegister;
                    if (validf3(effectiveLoc))
                    {obj.format = 3;
                        obj.displacement = effectiveLoc;
                        obj.ni = 3;
                        obj.xbpe = 4;
                        obj.opcode = opTab[pl.opcode].opcode;
                    }
                    else
                    {
                        simple = true;
                    }
                }
                else if (simple)
                {
                    long long simpleLoc = literal.address;
                    if (validf3(simpleLoc))
                    {obj.format = 3;
                        obj.displacement = simpleLoc;
                        obj.ni = 3;
                        obj.xbpe = 0;
                        obj.opcode = opTab[pl.opcode].opcode;
                    }
                    else
                    {
                        throw "Invalid Displacement";
                    }
                }
                else
                {
                    throw "Invalid Displacement";
                }
            }
        }
        else
        {
            obj = pcOrBaseRelativeAddressing(symTab, opTab, locCtr, pl, 3, 0, modifications, base, baseRegister);
        }
        pl.objCode = obj;
        if (pl.opcode == "LDB")
        {
            baseRegister = obj.displacement;
        }
    }
    catch (string err)
    {
        return true;
    }
    return false;
}


#endif