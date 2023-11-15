/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */
#ifndef Memory_H
#define Memory_H

#include <bits/stdc++.h>

using namespace std;

class Memory {
private:

    int Hex_to_decimal(const string &hex);

    string decimal_to_hex(int decimal);

public :
    Memory();

    map<string, string> memory;

    void set_memory(string start, const vector<string> &lines);

    void Display_memory();

    char indices[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
};


#endif
