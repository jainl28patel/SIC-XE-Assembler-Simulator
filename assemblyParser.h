#ifndef PARSER
#define PARSER

#include<iostream>
#include<string>
#include"structs.h"
#include"utils.h"
using namespace std;

bool needNoOperands(string s)
{
    // This function check the operand for Format 1 type.
    // Because in that case no operand will be required to be supplies with them.
    s = toUpperCase(s);
    // Whole string is converted to Uppercase to bring uniformity for comparision
    return s.compare("RSUB") == 0 || s.compare("NOBASE") == 0 || s.compare("HIO") == 0 || s.compare("FIX") == 0 || s.compare("NORM") == 0 || s.compare("TIO") == 0 || s.compare("START") == 0 || s.compare("SIO") == 0 || s.compare("FLOAT") == 0 || s.compare("CSECT") == 0;
}


/*
    This function parses the line and returns the parsedLine struct.
    * Create array of 5 strings to store the parsed line.
    * Iterate and skip the blank spaces.
    * Store the value in the arrays as you iterate.

     Interpreting the array:
     * size == 0 => empty line
     * size == 1 => only one opcode
     * size == 2 => [label, opcode] or [opcode, operand]
     * size == 3 => [label, opcode, operand] or [opcode, operand1, operand2]
     * size == 4 => [label, opcode, operand1, operand2] or [opcode, operand1, operand2, operand3]
*/


parsedLine parseLine(string line) 
{
    parsedLine pl;
    
    // line length
    int i = 0;

    // temp storage of max five elements
    string s[5] = {"", "", "", "", ""};
    for(int j = 0; j < 5 && i < line.length(); j++)
    {
        // skip all the blank space
        for (; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
            ;
        // store the value
        for (; i < line.length() && (line[i] != ' ' && line[i] != '\t'); i++)
            s[j] += line[i];
    }

    for (; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
        ;
    
    // comment line begins with '.'
    if (s[0] != "" && s[0][0] == '.')
    {
        for (i = 0; i < line.length() && (line[i] == ' ' || line[i] == '\t'); i++)
            ;
        for (; i < line.length(); i++)
            pl.opcode += line[i];
        return pl;
    }

    // args shouldn't be more than 5
    if (i != line.length())
        throw "Too Many Arguments";

    if (s[0] == "")
        return pl;
    else if (s[1] == "")
        // format 1
        pl.opcode = s[0];
    else if (s[2] == "")
    {
        // format 1
        if(needNoOperands(s[1]))
        {
            pl.label = s[0];
            pl.opcode = s[1];
        }
        // format 2
        else
        {
            pl.opcode = s[0];
            pl.op1 = s[1];
        }
    }
    else if (s[3] == "")
    {
        // format 2
        if (s[1][s[1].length() - 1] == ',' || s[2][0] == ',')
        {
            pl.opcode = s[0];
            pl.op1 = s[1] + s[2];
        }
        // format 3
        else
        {
            pl.label = s[0];
            pl.opcode = s[1];
            pl.op1 = s[2];
        }
    }
    else if (s[4] == "")
    {
        if (s[2].compare(",") == 0)
        {
            pl.opcode = s[0];
            pl.op1 = s[1] + s[2] + s[3];
        }
        else
        {
            pl.label = s[0];
            pl.opcode = s[1];
            pl.op1 = s[2] + s[3];
        }
    }
    else
    {
        if (s[3].compare(",") != 0)
            throw "Too Many Arguments";
        // line containging too many arguments

        pl.label = s[0];
        pl.opcode = s[1];
        pl.op1 = s[2] + s[3] + s[4];
    }

    s[0] = "";
    s[1] = "";
    for (i = 0; i < pl.op1.length() && pl.op1[i] != ','; i++)
        s[0] += pl.op1[i];
    if (i == pl.op1.length() - 1 && pl.op1[i] == ',')
        s[1] = ",";
    else
        for (i++; i < pl.op1.length(); i++)
            s[1] += pl.op1[i];
    pl.op1 = s[0];
    pl.op2 = s[1];
    return pl;
}

#endif