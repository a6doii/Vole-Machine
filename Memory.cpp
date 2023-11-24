/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */
#include "Memory.h"

Memory::Memory() {
    for (char ch: this->indices) {
        for (char index: this->indices) {
            string s;
            s += ch;
            s += index;
            memory[s] = "00";
        }
    }
}

string Memory::decimal_to_hex(int decimal) {
    stringstream ss;
    ss << hex << decimal;
    return ss.str();
}

int Memory::Hex_to_decimal(const string &hex) {
    int decimalValue = stoi(hex, nullptr, 16);
    return decimalValue;
}

void Memory::set_memory(string start ,  const vector<string>& lines , map<string , string > &lines_step , bool step  ) { // ( A0 ) // 0F ==>  15 ==> F ==> 0F
    // A0 A1 A2 A3 /// 1234 , 3456
    // 12 34 34 56 
    // first put value inside this address (start) in our memory
    // and convert it to int and add 1 to it and convert it again into hex and put the value inside this (hex) address
    for (const auto &line: lines) {
        transform(start.begin(), start.end(), start.begin(), ::tolower);
        string first_half = line.substr(0, 2), second_half = line.substr(
                2); // take the first and the second half of the instruction
        if (start.size() == 1) {
            start.insert(0, "0");
        }
        this->memory[start] = first_half; // put the first one inside the address start
        int integer_address = Hex_to_decimal(start) + 1;
        start = decimal_to_hex(integer_address); // A1
        if (start.size() == 1) {
            start.insert(0, "0");
        }
        this->memory[start] = second_half;
        integer_address = Hex_to_decimal(start) + 1;

        start = decimal_to_hex(integer_address); //A2
        if (start.size() == 1) {
            start.insert(0, "0");
        }

    }
}

void Memory::Display_memory() {
    cout << "  ";
    for (char index: this->indices) {
        cout << (isalpha(index) ? (char) toupper(index) : index) << "   "; // to print it with capital letter
    }
    cout << endl;
    for (char index: this->indices) {
        cout << (isalpha(index) ? (char) toupper(index) : index) << " ";
        for (char j: this->indices) {
            char ch = index;
            string s; // this is a concatenation between the two index to get the specific cell (A0) (FA)
            s += ch;
            s += j;
            cout << memory[s] << "  ";
        }
        cout << endl;
    }
}