#ifndef UTILS
#define UTILS

#include<iostream>
#include<string>
#include<map>
#include<vector>

using namespace std;
#define ll long long int

void print()
{
    cout << endl;
}
template <typename T, typename... Types>
void print(T var1, Types... var2)
{
    cout << var1 << ' ';
    print(var2...);
}
string getString(char x)
{
    string s(1, x);
    return s;
}
bool isNumeric(string s)
{
    if (s.length() == 0)
        return false;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (s.at(i) - '0' < 0 || s.at(i) - '0' > 9)
            return false;
    }
    return true;
}

string toUpperCase(string su)
{
    transform(su.begin(), su.end(), su.begin(), ::toupper);
    return su;
}

void printTable(map<string, SymStruct> &mp)
{
    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        print(it->first, it->second.location);
    }
}
void printTable(map<string, LiteralStruct> &mp)
{
    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        print(it->first, it->second.address, it->second.size, it->second.value, it->second.block.name);
    }
}
void printTable(map<string, BlockTable> &mp)
{
    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        print(it->first, it->second.name, it->second.blockLength, it->second.startingAddress, it->second.startingAddress, it->second.number);
    }
}

std::string string_to_hex(const std::string &input)
{
    static const char hex_digits[] = "0123456789ABCDEF";
    // trouble with quotes in c++
    std::string output;
    output.reserve((input.length() - 1) * 2);
    for (int i = 0; i < input.length() - 1; i++)
    {
        unsigned char c = input[i];
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

bool validf3(int disp)
{
    if (-2048 <= disp && disp <= 2047)
    {
        return true;
    }
    return false;
}
bool validf4(int disp)
{
    if (-524288 <= disp && disp <= 524287)
    {
        return true;
    }
    return false;
}

string print_hex_from_bin(int str)
{
    char buf[2];
    sprintf(buf, "%0x", str);
    // cout << "in print hex: " + string(buf) << endl;
    return string(buf);
}

string getProgramName(string label)
{
    if (label.length() > 6)
    {
        return label.substr(0, 6);
    }
    else
    {
        string ans = label;
        while (ans.length() < 6)
        {
            ans.push_back('_');
        }
        return ans;
    }
}

int getRelativity(SymStruct st)
{
    if (st.flags == "R")
        return 1;
    return 0;
}

#endif