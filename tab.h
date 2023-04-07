#ifndef TAB
#define TAB

#include <string>
#include <map>
#include<deque>
#include<iomanip>
#include "structs.h"

using namespace std;

// building the register map
map<string, int> regs;
void buildRegMap()
{
    regs["A"] = 0;
    regs["X"] = 1;
    regs["L"] = 2;
    regs["B"] = 3;
    regs["S"] = 4;
    regs["T"] = 5;
    regs["F"] = 6;
    regs["PC"] = 8;
    regs["SW"] = 9;
}

void build(map<string, OpCodeStruct> &opTab)
{
    string mnemonic = "";
    OpCodeStruct *op = new OpCodeStruct;
    mnemonic = "ADD";
    op->mnemonic = "ADD";
    op->opcode = 0x18;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "ADDF";
    op->mnemonic = mnemonic;
    op->opcode = 0x58;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "ADDR";
    op->mnemonic = mnemonic;
    op->opcode = 0x90;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "AND";
    op->mnemonic = mnemonic;
    op->opcode = 0x40;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "CLEAR";
    op->mnemonic = mnemonic;
    op->opcode = 0xB4;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "COMP";
    op->mnemonic = mnemonic;
    op->opcode = 0x28;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "COMPF";
    op->mnemonic = mnemonic;
    op->opcode = 0x88;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "COMPR";
    op->mnemonic = mnemonic;
    op->opcode = 0xA0;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "DIV";
    op->mnemonic = mnemonic;
    op->opcode = 0x24;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "DIVF";
    op->mnemonic = mnemonic;
    op->opcode = 0x64;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "DIVR";
    op->mnemonic = mnemonic;
    op->opcode = 0x9C;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "FIX";
    op->mnemonic = mnemonic;
    op->opcode = 0xC4;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "FLOAT";
    op->mnemonic = mnemonic;
    op->opcode = 0xC0;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "HIO";
    op->mnemonic = mnemonic;
    op->opcode = 0xF4;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "J";
    op->mnemonic = mnemonic;
    op->opcode = 0x3C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "JEQ";
    op->mnemonic = mnemonic;
    op->opcode = 0x30;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "JGT";
    op->mnemonic = mnemonic;
    op->opcode = 0x34;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "JLT";
    op->mnemonic = mnemonic;
    op->opcode = 0x38;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "JSUB";
    op->mnemonic = mnemonic;
    op->opcode = 0x48;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDA";
    op->mnemonic = mnemonic;
    op->opcode = 0x00;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDB";
    op->mnemonic = mnemonic;
    op->opcode = 0x68;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDCH";
    op->mnemonic = mnemonic;
    op->opcode = 0x50;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDF";
    op->mnemonic = mnemonic;
    op->opcode = 0x70;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDL";
    op->mnemonic = mnemonic;
    op->opcode = 0x08;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDS";
    op->mnemonic = mnemonic;
    op->opcode = 0x6C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDT";
    op->mnemonic = mnemonic;
    op->opcode = 0x74;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LDX";
    op->mnemonic = mnemonic;
    op->opcode = 0x04;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "LPS";
    op->mnemonic = mnemonic;
    op->opcode = 0xD0;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "MUL";
    op->mnemonic = mnemonic;
    op->opcode = 0x20;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "MULF";
    op->mnemonic = mnemonic;
    op->opcode = 0x60;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "MULR";
    op->mnemonic = mnemonic;
    op->opcode = 0x98;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "NORM";
    op->mnemonic = mnemonic;
    op->opcode = 0xC8;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "OR";
    op->mnemonic = mnemonic;
    op->opcode = 0x44;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "RD";
    op->mnemonic = mnemonic;
    op->opcode = 0xD8;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "RMO";
    op->mnemonic = mnemonic;
    op->opcode = 0xAC;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "RSUB";
    op->mnemonic = mnemonic;
    op->opcode = 0x4C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "SHIFTL";
    op->mnemonic = mnemonic;
    op->opcode = 0xA4;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "SHIFTR";
    op->mnemonic = mnemonic;
    op->opcode = 0xA8;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "SIO";
    op->mnemonic = mnemonic;
    op->opcode = 0xF0;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "SSK";
    op->mnemonic = mnemonic;
    op->opcode = 0xEC;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STA";
    op->mnemonic = mnemonic;
    op->opcode = 0x0C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STB";
    op->mnemonic = mnemonic;
    op->opcode = 0x78;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STCH";
    op->mnemonic = mnemonic;
    op->opcode = 0x54;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STF";
    op->mnemonic = mnemonic;
    op->opcode = 0x80;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STI";
    op->mnemonic = mnemonic;
    op->opcode = 0xD4;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STL";
    op->mnemonic = mnemonic;
    op->opcode = 0x14;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STS";
    op->mnemonic = mnemonic;
    op->opcode = 0x7C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STSW";
    op->mnemonic = mnemonic;
    op->opcode = 0xE8;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STT";
    op->mnemonic = mnemonic;
    op->opcode = 0x84;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "STX";
    op->mnemonic = mnemonic;
    op->opcode = 0x10;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "SUB";
    op->mnemonic = mnemonic;
    op->opcode = 0x1C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "SUBF";
    op->mnemonic = mnemonic;
    op->opcode = 0x5C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "SUBR";
    op->mnemonic = mnemonic;
    op->opcode = 0x94;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "SVC";
    op->mnemonic = mnemonic;
    op->opcode = 0xB0;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "TD";
    op->mnemonic = mnemonic;
    op->opcode = 0xE0;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "TIO";
    op->mnemonic = mnemonic;
    op->opcode = 0xF8;
    op->possibleFormat = FORMAT_1;
    opTab[mnemonic] = *op;

    mnemonic = "TIX";
    op->mnemonic = mnemonic;
    op->opcode = 0x2C;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;

    mnemonic = "TIXR";
    op->mnemonic = mnemonic;
    op->opcode = 0xB8;
    op->possibleFormat = FORMAT_2;
    opTab[mnemonic] = *op;

    mnemonic = "WD";
    op->mnemonic = mnemonic;
    op->opcode = 0xDC;
    op->possibleFormat = FORMAT_3_4;
    opTab[mnemonic] = *op;
}

SymStruct *createSymbol(string label, ll locCtr, BlockTable active)
{
    SymStruct *st = new SymStruct;
    st->label = label;
    st->location = locCtr;
    st->block = active;
    return st;
}

// creating new block
BlockTable createBlock(string name, int id)
{
    BlockTable b;
    b.name = name;
    b.number = id;
    return b;
}

// enter new symbol to the symbol table
bool enterSymbolTab(parsedLine& line, map<string, SymStruct> &symTab, BlockTable active, int locCtr)
{
    /*
        if label is empty :
            return error
        else if lable not present in symTab
            {
                process
            }
        else :
            return error -> lable already exist
    */
    if(line.label == "")
    {
        line.err = "Label can't be empty";
        return 1;
    }
    else if(symTab.find(line.label) != symTab.end())
    {
        line.err = "Label " + line.label + " already exits, can't be redeclared.";
        return 1;
    }
    else 
    {
        try 
        {
            string inValidArithmeticOperations = "*/&|!^";
            bool inValidOperation = false;
            for (auto op : inValidArithmeticOperations)
            {
                if (line.op1.find(op) != string::npos)
                {
                    inValidOperation = true; // use throw and catch into the error
                    string s = "";
                    s += op;
                    // throw(string) s;
                    line.err = "Invalid operation : " + s;
                    return true;
                }
            }
            // assembler will crash for any other unsupported operands, add them to above list etc.
            if (!inValidOperation)
            {
                // Note: Valid Expression SYNTAX is BUFEND-BUFFER+MAXLEN (No spaces between operands and operation)

                string validArithmeticOperations = "+-";
                string symLabel = "";
                deque<pair<SymStruct, int> > lable;
                deque<string> operations;
                int R = 0;
                for (int i = 0; i < line.op1.length(); i++)
                {
                    if (validArithmeticOperations.find(line.op1[i]) == string::npos)
                    {
                        symLabel.push_back(line.op1[i]);
                    }
                    else
                    {
                        if (isNumeric(symLabel))
                        {
                            lable.push_back({*createSymbol("numeric", stoi(symLabel), createBlock("numeric", 0)), 0});
                            operations.push_back(getString(line.op1[i]));
                            symLabel = "";
                            continue;
                        }
                        if (symTab.find(symLabel) == symTab.end())
                        {
                            line.err = "Undefined symbol : " + symLabel;
                            return true;
                        }
                        if (symLabel == "")
                        {
                            line.err = "Invalid Expression";
                            return true;
                        }
                        auto symbol = symTab.find(symLabel)->second;
                        lable.push_back({symbol, getRelativity(symbol)});
                        operations.push_back(getString(line.op1[i]));
                        symLabel = "";
                    }
                }
                bool num = false;
                if (isNumeric(symLabel))
                {
                    num = true;
                    lable.push_back({*createSymbol(line.label, stoi(symLabel), active), 0});
                    symLabel = "";
                }
                if (!num)
                {
                    if (symTab.find(symLabel) == symTab.end())
                    {
                        line.err = "Undefined symbol : " + symLabel;
                        return true;
                    }
                    auto symbol = symTab.find(symLabel)->second;

                    lable.push_back({symbol, getRelativity(symTab.find(symLabel)->second)});
                }
                while (!lable.empty() && !operations.empty())
                {
                    auto op1 = lable.front();
                    lable.pop_front();
                    auto op2 = lable.front();
                    lable.pop_front();
                    string arith = operations.front();
                    operations.pop_front();
                    ll location = 0;
                    int relativity = 0;
                    if (arith == "+")
                    {
                        location = op1.first.location + op2.first.location; // two symbols must be in same block
                        relativity = op1.second + op2.second;
                    }
                    else
                    {
                        location = op1.first.location - op2.first.location;
                        relativity = op1.second - op2.second;
                    }
                    lable.push_front({*createSymbol(line.label, location, active), relativity});
                }
                if (lable.front().second == 0 or lable.front().second == 1)
                {
                    SymStruct ssy = lable.front().first;
                    if (lable.front().second == 0)
                    {
                        ssy.flags = "A";
                    }
                    else
                    {
                        ssy.flags = "R";
                    }
                    symTab[line.label] = ssy;
                }
                else
                {
                    line.err = "Inappropriate Relative or Absolute Expression";
                    return true;
                }
            }
        }
        catch(char *err)
        {
            line.err = "Invalid operation for this constant";
            return 1;
        }
    }
}

// Called on LTORG and at program end
bool litsComparator(pair<int, parsedLine> &p1, pair<int, parsedLine> &p2)
{
    return p1.second.location < p2.second.location;
}
void manageLitTab(map<string, LiteralStruct> &lt, long long &locCtr, vector<parsedLine> &v, vector<pair<int, parsedLine>> &lits, int index, BlockTable active)
{
    for(auto it = lt.begin(); it != lt.end(); it++) 
    {
        if(!it->second.dumped)
        {
            it->second.dumped = true;
            it->second.block = active;
            parsedLine p;
            it->second.address = locCtr;
            p.opcode = "*";
            p.op1 = it->second.value;
            p.location = locCtr;
            lits.push_back({index, p});
            // v.insert(v.begin() + index, p);
            // printParsedLineInterMediate(p); // insert into vector
            locCtr += it->second.size;
        }
    }
}


// manage blocks at the END
bool comparator(BlockTable b1, BlockTable b2)
{
    return b1.number < b2.number;
}

void manageBlocks(map<string, BlockTable> &blkTab, map<string, SymStruct> &symTab, long long &programLength, ll &startingAddress, map<string, LiteralStruct> &litTab)
{
    vector<BlockTable> v;

    // program length = sum of lenght of all block
    programLength = 0;
    for (auto it = blkTab.begin(); it != blkTab.end(); ++it)
    {
        programLength += it->second.locCtr;
        v.push_back(it->second);
    }
    sort(v.begin(), v.end(), comparator);
    v[0].blockLength = v[0].locCtr;
    v[0].startingAddress = startingAddress;
    blkTab[v[0].name] = v[0];

    for (auto it = v.begin() + 1; it != v.end(); ++it)
    {
        auto prev = it - 1;
        it->blockLength = it->locCtr;
        it->startingAddress = prev->startingAddress + prev->blockLength;
        it->locCtr = 0;
        blkTab[it->name] = *it;
    }
    // reassigning blocks after ordering them
    for (auto &sym : symTab)
    {
        sym.second.block = blkTab[sym.second.block.name];
    }
    // reassigning blocks after ordering them
    for (auto &lit : litTab)
    {
        lit.second.block = blkTab[lit.second.block.name];
    }
}

LiteralStruct createLiteral(string name, BlockTable active, int litSize)
{
    LiteralStruct lt;
    lt.value = name;
    lt.block = active;
    lt.size = litSize;
    return lt;
}

#endif