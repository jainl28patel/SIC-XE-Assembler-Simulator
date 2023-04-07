#ifndef STRUCT
#define STRUCT

#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;
#define ll long long int

const unsigned int FORMAT_1 = 1;
const unsigned int FORMAT_2 = 2;
const unsigned int FORMAT_3_4 = 3;

struct BlockTable
{
    string name = "DEFAULT";
    int number = 0;
    long long int locCtr = 0;
    long long int startingAddress = 0;
    long long int blockLength;
};

struct ObjectCode
{
    bool isData = false;
    bool hasReg = false;
    bool isOnlyOpcode = false;
    int isWord = -13371337;
    int opcode;
    int displacement;
    int reg1;
    int reg2;
    int ni;
    int xbpe;
    int format;
    string data;
};

struct parsedLine
{
    string label;
    string opcode;
    string op1;
    string op2;
    string err;
    ll location;
    bool isComment = false;
    bool isFormat4 = false;
    bool isEmpty = false;
    ObjectCode objCode;
};

struct OpCodeStruct
{
    string mnemonic;
    int opcode;
    int possibleFormat;
};

struct SymStruct
{
    string label;
    int location = -1;
    BlockTable block;
    string flags = "R";
};

struct LiteralStruct
{
    string value;
    long long int address;
    BlockTable block;
    int size;
    bool dumped = false;
};

struct ModicationRecord
{
    char label = 'M';
    int start;
    int modified;
};
struct TextRecord
{
    int startingAddress;
    int size;
    string text;
    string label;
};

#endif