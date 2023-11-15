#include "CPU.h"
/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */
CPU :: CPU (){
    for (int i = 0 ; i < 16 ; i++ ){
        string s = decimal_to_hexa(i);
        char ch = s[0];
        if ( isalpha(ch)){
            ch = toupper(ch);
        }
         this->Register[ch]= "00"; // intialize the register with 00 foreach cell 0 == > 15 = 0 ==> F
    }
}

string CPU :: decimal_to_hexa( int decimal){
        stringstream ss;
        ss << hex << decimal;
        return ss.str();
}

int CPU :: Hexa_to_decimal ( string hexa){
     int decimalValue = stoi(hexa, nullptr, 16);
     return decimalValue;
}

void CPU :: Decod ( ){
    operation = IR[0]; // 1 
    registr_adress = IR[1]; // 2 
    x = IR[2];// 3 
    y = IR[3];// 4 
    if (stp){
        cout << "operation = " << operation <<endl << "Register = " << registr_adress << endl
        << "X = " << x <<endl << "Y = " << y <<endl;
    }
}


bitset<8> CPU ::  addTwoNumbers(const bitset<8>& num1, const bitset<8>& num2) {
    bitset<8> sum = num1.to_ulong() + num2.to_ulong();
    return sum;
}
bitset<8> CPU :: decimalToBinary(int decimalNumber) {
    return bitset<8>(decimalNumber);
}

string CPU :: binaryToHexadecimal(const bitset<8>& binaryNumber) {
    stringstream hexStream;
    hexStream << hex <<uppercase << binaryNumber.to_ulong();
    return hexStream.str();
}

void CPU :: Excute_theInstruction(char op ,map<string,string> &memory ){
    string memory_adress = x+y ;
    if ( op == '1' ){
        Register[registr_adress] = memory[memory_adress] ;
    }
    else if ( op == '2'){
        Register[registr_adress] = x+y ;
    }
    else if ( op == '3'){
        memory[memory_adress] =  Register[registr_adress] ;
    }
    else if ( op == '4'){ // copy the value of the register of index x to register with index y 
        char register_adress_for_reg1 = x [0];
        char register_adress_for_reg2 = y[0];
        Register[register_adress_for_reg2] = Register[register_adress_for_reg1];
    }
    else if ( op == '5'){// RXY ==> x + y ==> 
        char x_x = x[0] , y_y = y[0];
        int decimal_X , decimal_Y;
        string val_x = Register[x_x], val_y = Register[y_y] ;
        decimal_X = Hexa_to_decimal(val_x); // conveting the value inside the regiter x and t into decimal number
        decimal_Y = Hexa_to_decimal(val_y);
        bitset<8> binary_X = decimalToBinary(decimal_X);
        bitset<8> binary_Y = decimalToBinary(decimal_Y);
        // cout << binary_X << endl << binary_Y << endl;
        bitset<8> sum_xandy = addTwoNumbers(binary_X,binary_Y); // adding two number and ignore the last digit if there is a carry 
        // sum_xandy = twosComplement(sum_xandy);
        // cout << sum_xandy <<endl;
        string value = binaryToHexadecimal(sum_xandy);
        if ( value.size() == 1 )
            value = "0" + value;
        Register[registr_adress] = value;

    }
    else if ( op == 'B'){ // ORXY ==> Rigeter['R'] == Rigester['0'] ==> jumb to addrees xy ==> program counter  
        // 22 ==> 2 * 16 + 2 ==> 34 
        if ( Register[registr_adress] == Register['0'] )
        {
            string new_address = x + y ;
            programcounter = Hexa_to_decimal( new_address);
        }
    }
}

void CPU :: Fetch ( map<string , string > lines_step , string start_adress , map<string,string> memory , string line , bool step ){
   if (!step)
    {   
        int start_adress_int = Hexa_to_decimal(start_adress);
        programcounter = start_adress_int;
        while ( true ){ // we iterate over the instuctions and we fetch and decod and excute on each step line by line 
            // IR = lines[i]; // ORXY;  // 1234 
            // hexa ==> string  ==> hexa ==> decimal + 1 ==> hexa ==> string 
            string first_half_insructions , second_half_insructions ; // 00 02
            string valuee =  decimal_to_hexa( programcounter ); // to handle zero if the hexa is only one number because i want it to be two numbers 1 no i want it to be 01 to access the memory 
            if ( valuee.size() == 1)
                valuee = "0" + valuee;
            string programcounter_str = valuee; //00
            first_half_insructions =  memory [programcounter_str]; // 00 
            programcounter += 1 ;//01
            valuee =  decimal_to_hexa( programcounter );
            if ( valuee.size() == 1)
                valuee = "0" + valuee;
            programcounter_str = valuee;
            second_half_insructions = memory[ programcounter_str];
            IR = first_half_insructions + second_half_insructions;
            cout << programcounter << ' ' << IR <<endl;
            if ( IR == "C000")
            {
                cout << "the program is halted :D \n";
                exit(0);
            }
            programcounter +=1;
            // cout <<programcounter_str << ' ' << IR <<endl;
            Decod();
            Excute_theInstruction( operation, memory); // opeartion 1 
            
    }   }
    else {
        stp = true;
        if (cont == 0 )
            programcounter = Hexa_to_decimal(start_adress);
        cont ++;
         string first_half_insructions , second_half_insructions ; // 00 02
            string valuee =  decimal_to_hexa( programcounter ); // to handle zero if the hexa is only one number because i want it to be two numbers 1 no i want it to be 01 to access the memory 
            if ( valuee.size() == 1)
                valuee = "0" + valuee;
            string programcounter_str = valuee; //00
            first_half_insructions =  lines_step [programcounter_str]; // 00 
            programcounter += 1 ;//01
            valuee =  decimal_to_hexa( programcounter );
            if ( valuee.size() == 1)
                valuee = "0" + valuee;
            programcounter_str = valuee;
            second_half_insructions = lines_step[ programcounter_str];
            IR = first_half_insructions + second_half_insructions;
            if ( IR == "C000")
            {
                
                this->Display_CPU();
                cout << "the program is halted :D \n";
                exit(0);
            }
            programcounter +=1;
            cout << IR <<endl;
    }
}

void CPU :: Display_CPU(){
    char arr[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    for (int i = 0 ; i < 8 ; i ++ ){
        cout << 'R'<< i << ":" << Register[arr[i]] << "  " ;
    }
    string value = decimal_to_hexa(programcounter); // 32 
    if ( value.size() ==  1) // 2 
      { 
        if ( programcounter < 15 )
        {    
            char ch = value[0];
            if ( isalpha(ch))
                ch = toupper(ch);
            value = "0";
            value += ch;
        }
        else {
            char ch = value[0];
            if ( isalpha(ch))
                ch = toupper(ch);
            value = ch;
            value += "0";
        }
      }
    cout << "PC:" << value << endl;
    for (int i = 8 ; i < 16 ; i++ ){
        cout << 'R'<< arr[i] << ":" << Register[arr[i]] << "  " ;
    }
    cout << "IR:" << IR <<endl;
}

