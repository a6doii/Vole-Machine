#include "Memory.h"

Memory :: Memory(){
    for (int i = 0 ; i < 16 ; i++ ){
        for (int j = 0 ; j < 16 ; j++ ){
            char ch = this->indicies[i]; 
            string s = ""; 
            s += ch;
            s += this->indicies[j];
            memory[s] = "00";
        }
    }
}

string Memory :: decimal_to_hexa( int decimal){
        stringstream ss;
        ss << hex << decimal;
        return ss.str();
}

int Memory :: Hexa_to_decimal ( string hexa){
     int decimalValue = stoi(hexa, nullptr, 16);
     return decimalValue;
}

void Memory :: set_memory (string start ,  vector<string> lines ){ // ( A0 ) // 0F ==>  15 ==> F ==> 0F
    // A0 A1 A2 A3 /// 1234 ,, 3456
    // 12 34 34 56 
    // first put value inside this addrees (start) in our memory
    // and convert it to int and add 1 to it and convert it again into hexa and put the value inside this (hexa) address
    for (int i =0 ;i < lines.size( ) ; i++ ){
        transform(start.begin( ),start.end(),start.begin(), :: tolower);
        string first_half = lines[i].substr(0,2), second_half = lines[i].substr(2); // take the first and the second half of the instruction
         if ( start.size( ) == 1 )
        {
            start = "0" + start;
        }
        this -> memory [start] = first_half; // put the first one inside the address start 
        int integer_address = Hexa_to_decimal ( start) + 1 ;
        start = decimal_to_hexa( integer_address); // A1 
        if ( start.size() == 1 )
        {
            start = "0" + start;
        }
        this->memory [start] = second_half; 
         integer_address = Hexa_to_decimal ( start) + 1 ; 
        
        start = decimal_to_hexa( integer_address); //A2
        if ( start.size() == 1 )
        {
            start = "0" + start;
        }

    }
}
 
void Memory ::  Display_memory() {
    cout << "  ";
    for (int i = 0 ;i  < 16 ; i++ ){
        cout << ( isalpha (this->indicies[i] ) ? (char)toupper(this->indicies[i]) : this->indicies[i] )<< "   "; // to print it with capital letter
    }
    cout << endl;
    for (int i = 0 ; i < 16 ; i++ ){ 
         cout <<  ( isalpha (this->indicies[i] ) ? (char)toupper(this->indicies[i]) : this->indicies[i] ) << " ";
        for (int j = 0 ; j < 16 ; j++ ){
            char ch = this->indicies[i]; 
            string s = ""; // this is a concatination between the two indicies to get the specific cell (A0) (FA)
            s += ch;
            s += this->indicies[j];
            cout << memory[s] <<"  " ;
        }
        cout << endl;
    }
 }