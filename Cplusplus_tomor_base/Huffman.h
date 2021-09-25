#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include<search.h>
#include <map>
//using namespace std;

class Huffman
{

public :
	struct Entry {
		char word;
		short code_length;
		float P;
		unsigned int codebyte;
	};
	struct Node {
		Entry* entry;
		Node* parent = nullptr;
		Node *left=nullptr, *right = nullptr;
	};
	//helper function for quick sort
	static int EntrycompareInterval(const void* a, const void* b);
	static int EntrycompareIntervalbylength(const void* a, const void* b);




private:
	//input file parameters
	std::string infile_name = "file.txt";
	size_t infile_length=0;
	size_t infile_buffer_size = 1024;//40 for testing
	std::ifstream* infile;
	//char* file_buffer;

	// szotar
	Node* Distribution_Tree_Root = nullptr;
	int dictionary_size = -1;
	//codes in P distribution order
	Entry* words = nullptr;
	//byte code dictionary
	std::map<char, Entry*> char_to_code_dictionary;
	//std::map<unsigned int, Entry*> code_to_char_dictionary;

	//output file parameters
	std::string outpuf_file_name = "output.huff";
	std::ofstream* outfile;
	size_t outputbuffer_size = 1024;
	size_t output_buffer_pos = 0;
	char* outputbuffer;



	//addbits helper variables
	unsigned int bitbuff = 0;
	int bitpos = 0;
	int leftover = 0;
	
	//count how many bytes was writen into bitbuff and outfile
	//can be removed
	size_t comlen = 0;


public:
	Huffman();
	Huffman(std::string outfilename);
	~Huffman();

	//compres sourcefilename file to outputfilename file
	void Compres(std::string sourcefilename = "file.txt");
	//void Decompres(std::string sourcefilename = "output.huff");

private:
	void Prepare_file(std::string sourcefilename);
	void Get_Distribution();
	void Build_Dictionary();
	void Recursive_build(Node* parent, Entry* arr, int arr_size, float P);
	void Recursive_crawling(Node* parent, std::string code, unsigned int& codebyte, int code_length);
	void Compressing_file();

	void addbits_tobitbuffer(const unsigned int bits, short bit_length);
	

	void bitbuffer_to_filebuffer(const unsigned int &bits,const unsigned int byte_size);
	void filebuffer_to_stream(const char* buffer_,size_t size,std::ofstream *File);




	



	






};
