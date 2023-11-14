#ifndef Memory_H
#define Memory_H

#include <bits/stdc++.h>

using namespace std;

class Memory{
private:
    
    int Hexa_to_decimal(string hexa);
    string decimal_to_hexa(int decimal);

public : 
    Memory();
    map<string,string >memory; 
    void set_memory( string start , vector<string>lines);
    void Display_memory(); 
    char indicies [16] = {'0','1', '2', '3', '4', '5','6','7','8','9','a','b','c','d','e','f'} ;
}; 


#endif