/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */
#ifndef CPU_H
#define CPU_H

#include <bits/stdc++.h>

using namespace std;

class CPU {
private :
    int Hex_to_decimal(const string &hex);

    string decimal_to_hex(int decimal);

public:
    CPU();

    int programCounter = 0; // ( address   )   A0
    string IR = "0000";
    int cont = 0;
    bool stp = false;
    char operation;
    char register_address;
    string x, y;
    map<char, string> Register; // 1A34 ==> A register[ int (A) ]
    bitset<8> addTwoNumbers(const bitset<8> &num1, const bitset<8> &num2);

    bitset<8> decimalToBinary(int decimalNumber);

    string binaryToHexadecimal(const bitset<8> &binaryNumber);

    void Fetch(const vector<string> &lines, const string &start_address, map<string, string> memory, const string &line,
               bool step); // give (IR) and (PC) values;
    void Valid_instruction();

    void Decode();

    void Execute_theInstruction(char op, map<string, string> &memory); // call instructions and memory
    void Display_CPU();
};

#endif