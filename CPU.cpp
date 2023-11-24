/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */
#include "CPU.h"

CPU::CPU() {
    for (int i = 0; i < 16; i++) {
        string s = decimal_to_hex(i);
        char ch = s[0];
        if (isalpha(ch)) {
            ch = toupper(ch);
        }
        this->Register[ch] = "00"; // initialize the register with 00 foreach cell 0 == > 15 = 0 ==> F
    }
}

string CPU::decimal_to_hex(int decimal) {
    stringstream ss;
    ss << hex << decimal;
    return ss.str();
}

int CPU::Hex_to_decimal(const string &hex) {
    int decimalValue = stoi(hex, nullptr, 16);
    return decimalValue;
}

void CPU::Decode() {
    operation = IR[0]; // 1 
    register_address = IR[1]; // 2
    x = IR[2];// 3 
    y = IR[3];// 4 
    if (stp) {
        cout << "operation = " << operation << endl << "Register = " << register_address << endl
             << "X = " << x << endl << "Y = " << y << endl;
    }
}


bitset<8> CPU::addTwoNumbers(const bitset<8> &num1, const bitset<8> &num2) {
    bitset<8> sum = num1.to_ulong() + num2.to_ulong();
    return sum;
}

bitset<8> CPU::decimalToBinary(int decimalNumber) {
    return (bitset<8>) decimalNumber;
}

string CPU::binaryToHexadecimal(const bitset<8> &binaryNumber) {
    stringstream hexStream;
    hexStream << hex << uppercase << binaryNumber.to_ulong();
    return hexStream.str();
}

void CPU::excuteInstruction(char op , map<string,string> &memory ) {
    string memory_address = x + y;
    if (op == '1') {
        Register[register_address] = memory[memory_address];
    } else if (op == '2') {
        Register[register_address] = x + y;
    } else if (op == '3') {
        memory[memory_address] = Register[register_address];
    } else if (op == '4') { // copy the valur of the register of index x to register with index y
        char register_address_for_reg1 = x[0];
        char register_address_for_reg2 = y[0];
        Register[register_address_for_reg2] = Register[register_address_for_reg1];
    } else if (op == '5') {// RXY ==> x + y ==>
        char x_x = x[0], y_y = y[0];
        int decimal_X, decimal_Y;
        string val_x = Register[x_x], val_y = Register[y_y];
        decimal_X = Hex_to_decimal(val_x); // converting the value inside the register x and t into decimal number
        decimal_Y = Hex_to_decimal(val_y);
        bitset<8> binary_X = decimalToBinary(decimal_X);
        bitset<8> binary_Y = decimalToBinary(decimal_Y);
        bitset<8> sum_X_Y = addTwoNumbers(binary_X,
                                          binary_Y); // adding two number and ignore the last digit if there is a carry
        string value = binaryToHexadecimal(sum_X_Y);
        if (value.size() == 1)
            value = "0" + value;
        Register[register_address] = value;

    } else if (op == 'B') { // ORXY ==> Register['R'] == Register['0'] ==> jump to address xy ==> program counter
        // 22 ==> 2 * 16 + 2 ==> 34 
        if (Register[register_address] == Register['0']) {
            string new_address = x + y;
            programCounter = Hex_to_decimal(new_address);
        }
    }
}

void CPU:: Fetch(const map<string, string> &lines_step,const string &start_adress, map<string, string> memory,const string &line,
                     bool step){
    if (!step) {
        int start_address_int = Hex_to_decimal(start_adress);
        programCounter = start_address_int;
        while (true) { // we iterate over the instructions, and we fetch and decode and execute on each step line by line
            // IR = lines[i]; // ORXY;  // 1234 
            // hex ==> string  ==> hex ==> decimal + 1 ==> hex ==> string
            string first_half_instructions, second_half_instructions; // 00 02
            string value = decimal_to_hex(programCounter);
            // to handle zero if the hex is only one number because I want it to be two numbers 1 no I want it to be 01 to access the memory
            if (value.size() == 1)
                value.insert(0, "0");
            string programCounter_str = value; //00
            first_half_instructions = memory[programCounter_str]; // 00
            programCounter += 1;//01
            value = decimal_to_hex(programCounter);
            if (value.size() == 1)
                value.insert(0, "0");
            programCounter_str = value;
            second_half_instructions = memory[programCounter_str];
            IR = first_half_instructions + second_half_instructions;
            if (IR == "C000") {
                this->Display_CPU();
                cout << "the program is halted :D \n";
                exit(0);
            }
            programCounter += 1;
            Decode();
            excuteInstruction(operation, memory); // opeartion 1

        }
    } else {
        stp = true;
        IR = line;
        if (cont == 0)
            programCounter = Hex_to_decimal(start_adress);
        cont++;
    }
}

void CPU::Display_CPU() {
    char arr[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < 8; i++) {
        cout << 'R' << i << ":" << Register[arr[i]] << "  ";
    }
    string value = decimal_to_hex(programCounter);
    if (value.size() == 1) {
        char ch = value[0];
        if (isalpha(ch))
            ch = toupper(ch);
        value = "0";
        value += ch;
    }
    cout << "PC:" << value << endl;
    for (int i = 8; i < 16; i++) {
        cout << 'R' << arr[i] << ":" << Register[arr[i]] << "  ";
    }
    cout << "IR:" << IR << endl;
    if (stp) {
        programCounter += 2;
    }
}