// Cplusplus_tomor_base.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <bitset>
#include "Huffman.h"
using namespace std;


void printbyte(unsigned int& c)
{
    bitset<32> bits(c);
    cout << bits << endl;
}

int main()
{
    std::cout << "Hello World!\n";
    //open the file
    Huffman coder;
    coder.Compres("files/kennedy.xls");
    /*
    
    unsigned int byte = 0;
    unsigned int byte2 = 0;
    //printbyte(byte2);

    printbyte(byte);
    byte = byte | 4;
    printbyte(byte);
    byte = byte >> 10;
    printbyte(byte);
    byte = byte2 | byte;
    printbyte(byte);
    */
    




    //size_t pos = infile.tellg();
    /*
    
    
    uint8_t byte = 1;
    //char byte2 = 255;

    printbyte(byte);
    byte =  byte >> 1;
    printbyte(byte);
    byte =  byte << 1;
    printbyte(byte);
    //printbyte(byte2);
    //char byte3 = byte2 << 2;
    //printbyte(byte3);
    //printbyte(byte2);
    */

    //std::cout << buff << "\n";


    /*
    float b = 0.231;
    char* sbuff = (char*)(&b);
    for (int j = 0;j < 4;j++) {
        bitset<8> bits(sbuff[j]);
        cout << bits << endl;
    }
    */



    std::cin.get();
    //count the bytes -> distribution
    //make a dictionary
    //use the dictionary to reduce code











}

