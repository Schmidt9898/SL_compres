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
    //coder.Compres("files/kennedy.xls");
    //coder.Decompres("files/kennedy.xls.huff");
    
    
    int bit_pos = 0;
    int leftover = 0;
    unsigned long long bitbuffer = -1;
    unsigned long bit_copy = 0;
    //remove bits
    short shortest_code = 3;
    short longest_code = 10;
    short offset = 0;
    for (int i = shortest_code;i <= longest_code;i++)
    {
        offset = (32 - i);
        bit_copy = (bitbuffer >> (32 + offset)) << offset;
        std::bitset<32> bits(bit_copy);
        std::cout << bits.to_string() << "\n";

    }

    
    
    
    
    
    
    
    
    
    
    /*
    unsigned int a = 3;
    unsigned long long bitbuffer = a;
    bitbuffer = bitbuffer << 31;
    bitbuffer += 1;
    bitbuffer = bitbuffer << 1;
    a = bitbuffer>>32;
    std::cout << sizeof(bitbuffer) << "\n";

    std::bitset<64> bits(bitbuffer);
    std::cout << bits.to_string() << "\n";
    
    std::bitset<32> bits2(a);
    std::cout << bits2.to_string() << "\n";

    
    */







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

