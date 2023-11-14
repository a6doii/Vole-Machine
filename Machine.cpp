#include <bits/stdc++.h>
#include "Machine.h"
#include "Memory.cpp"

using namespace std;


void Machine :: menu(){

    cout << "1.Enter new program \n";
    cout << "2.Load all the instructions into the memory \n";
    cout << "3.Load the instructions step by step \n";
    cout << "4.Display the register, memory, PC and IR  \n";
    cout << "5.Reset the machine  \n";
    cout << "6.Exit the code \n";
    cout << "Enter your choice : ";
    cin >> choice;
    while ( choice < 1 || choice > 5 )
    {
        cout << "invalid choice \n";
        cout << "Enter new input : ";
        cin >> choice;
    }
}


Machine :: Machine(){};
void Machine ::  Reset_Machine(){
    Memory meMory; // we have defult constructor and it will initialize all the memory by 00
    CPU cpu;// the same as memory but here the register will be equal to 00 by the defult constructor
}

void Machine :: Display_info(){// memory ,, register , pc , ir 
    meMory.Display_memory();
    cpu.Display_CPU();
} 

void Machine :: Get_New_Program(){ // name ==> load ==> 
   cout << "Enter the name for the file : ";
   cin >> name_file ; // insturctions 
   name_file += ".txt";
}

void Machine :: Load_all_Instructions_toMemory(){ // fetch 
    cout << "Enter the start address: "; // start address 
    cin >> start_address ;
    ifstream output;
    output.open(name_file);
    string line ; // A0 ==> A1 ==> A9 ==> B0 
    while ( getline(output , line )){
        lines.push_back(line);
    }
    // fetch ===> instuctions ==> memory 
    meMory.set_memory (start_address, lines); // (1)
    meMory.Display_memory();
    cpu.Fetch( lines ,start_address , meMory.memory , line , step);
    cpu.Display_CPU();
}
void Machine ::  Load_all_Instructions_StepBySteo(){
    
    cout << "Enter the start address: "; // start address 
    cin >> start_address ;
    ifstream output;
    output.open(name_file);
    string line ; // A0 ==> A1 ==> A9 ==> B0 
    while (true){
    cout << "Press Fetch : "; // المفرةض انهاا تتعرضلو ياسحس وهو يختار فيتش يدوس عليها بالماوس بس انا هنا عاملهها ع انو يكتبها فاهم ؟ ولا فاهم اي حاجه
    string fetch;
    cin >> fetch;
    getline(output, line) ; // take line from our file;
    // fetch ===> instuctions ==> memory 
    // meMory.set_memory (start_address, lines); // (1)
    // meMory.Display_memory();
    if ( line == "C000")
    {
        cout << "program is halted";
        exit(0);
    }
    cout << line <<endl;
    step = true;
    cpu.Fetch( lines ,start_address , meMory.memory , line , step);
    cout << "Press  Decode "<<endl;
    string decode ;
    cin >> decode;
    cpu.Decod();
    cout <<"Press Excute " <<endl ;
    string excute;
    cin >> excute; // بص ياسحس انا عامل الوقتي ال فيتش وال ديكود والاكسكيوت التلاته بخليه يكتبهم انا عايزمك تخليهم بقا زرار وهو يدوس عليهم
    cpu.Excute_theInstruction(cpu.operation,meMory.memory );
    meMory.Display_memory();
    cpu.Display_CPU();
}
}

void Machine :: play () { 
    menu();
    while ( choice != 6 ){
        if ( choice == 1 ){
            this->Get_New_Program( );
        }  
        else if ( choice == 2)
            this->Load_all_Instructions_toMemory(); // file ==> vector
        else if ( choice == 3 )
        {
            this->Load_all_Instructions_StepBySteo();
        }
        else if ( choice == 4 )
            this->Display_info();
        else if ( choice == 5)
            this->Reset_Machine();
          menu();
    }
}
