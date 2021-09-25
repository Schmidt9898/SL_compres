#include "Huffman.h"
inline int ByteLengthFromCodeLenght(short codelength)
{
	return (codelength % 8 == 0) ? codelength / 8 : codelength / 8 + 1;
}

int Huffman::EntrycompareInterval(const void* a, const void* b)
{
	const Entry* as = (const Entry*)a;
	const Entry* bs = (const Entry*)b;
	return (as->P == bs->P) ? 0 : (as->P > bs->P) ? -1 : 1;
}
int Huffman::EntrycompareIntervalbylength(const void* a, const void* b)
{
	const Entry* as = (const Entry*)a;
	const Entry* bs = (const Entry*)b;
	return (as->P == bs->P) ? 0 : (as->code_length > bs->code_length) ? -1 : 1;
}


Huffman::Huffman()
{
	outputbuffer = new char[outputbuffer_size] {};
	//TODO init outputfile for writing
}
Huffman::Huffman(std::string outputfilename) : outpuf_file_name(outputfilename)
{
	Huffman();
}
Huffman::~Huffman()
{
	//TODO free/delete tree, dictionary, arrays, buffers, close open files
	std::cout << "Huffman deleted. you havent implemented the deleting, you peace of shit.\n";
}

//Huffman::
//public functions :


void Writedicttofile(Huffman::Entry* arr,size_t arrsize,std::ofstream* stream)
{
	//Entry to byte
	//char* dist = (char*)arr;
	size_t size = arrsize * sizeof(Huffman::Entry);
	stream->write((char*)&size, sizeof(size_t));
	stream->write((char*)arr, arrsize * sizeof(Huffman::Entry));
	stream->flush();

}




void Huffman::Compres(std::string sourcefilename)
{
	Prepare_file(sourcefilename);

	Get_Distribution();
	std::cout << "Distribution is done.\n";
	//return;
	Build_Dictionary();

	std::cout << "Tree is done.\n";
	//At this point the tree is irrelevant

	//write to file the dictionary
	outfile = new std::ofstream(outpuf_file_name, std::ios_base::binary);
	Writedicttofile(words, dictionary_size, outfile);


	Compressing_file();


	std::cout << "DONE\n";

	/*
	for(int i = 0;i < dictionary_size;i++)
	{
		//cout<<words[i].code_length<<"\n";

		addbits(words[i].codebyte, words[i].code_length);

	}*/




}


//private functions


void Huffman::Prepare_file(std::string sourcefilename)
{
	infile = new std::ifstream(sourcefilename, std::ios_base::binary);

	if (!infile->is_open()) {
		std::cerr << "Error " << sourcefilename << " was not found!\n";
		return;
	}
	//get length of file
	infile->seekg(0, infile->end);
	infile_length = infile->tellg();
	//set to the begining
	infile->seekg(0, infile->beg);
	std::cout << " Lenght of the "<<sourcefilename<<" file: " << infile_length << " \n";
	//size_t s= infile.gcount();

}

void Huffman::Get_Distribution()
{
	unsigned int dist[256]{};
	char* infilebuffer = new char[infile_buffer_size];
	
	size_t byte_left = infile_length;

	while (byte_left > infile_buffer_size)
	{
		infile->read(infilebuffer, infile_buffer_size);
		byte_left -= infile_buffer_size;

		for (int j = 0;j < infile_buffer_size;j++) {
			//printf("%d\n", (uint8_t)file_buffer[j]);
			//cout << (uint8_t)file_buffer[j] << "\n";
			dist[(uint8_t)infilebuffer[j]]++;
		}
	}

	// read the rest of the file
	if (byte_left > 0)
	{
		//cout << "rest\n";
		infile->read(infilebuffer, byte_left);
		for (int j = 0;j < byte_left;j++) {
			dist[(uint8_t)infilebuffer[j]]++;;
		}
	}

	dictionary_size = 0;
	for (int i = 0;i < 256;i++)
	{
		if (dist[i] > 0)
			dictionary_size++;
	}

	words = new Entry[dictionary_size];
	for (unsigned int i = 0, j = 0;i < 256;i++)
	{
		//cout <<i <<" helo\n";
		if (dist[i] > 0) {
			words[j].word = (char)i;
			words[j].P = (float)dist[i] / (float)infile_length;
			//cout << (char)i << "  " << dist[i] << " " << words[j].P << "\n";
			j++;
		}
	}
	qsort((void*)words, (size_t)dictionary_size, sizeof(Entry), EntrycompareInterval);

	delete[] infilebuffer;


	//cout << words[0].P << "\n";
	/*float a = 0;
	for (int i = 0;i < dictionary_size;i++)
	{
		a += words[i].P;
		cout << words[i].word << "  " << words[i].P << "\n";
	}
	cout << a << "  a\n";*/
}

void Huffman::Build_Dictionary()
{
	Node* root = new Node;
	root->parent = nullptr;
	if (dictionary_size <= 0)
	{
		std::cout << "bajvan szótár üres\n";
		return;
	}
	Recursive_build(root, words, dictionary_size, 1.0f);
	std::string code = "";
	unsigned int codebyte = 0;
	Recursive_crawling(root, code, codebyte, 0);



}

void Huffman::Recursive_build(Node* parent, Entry* arr, int arr_size, float P)
{
	if (arr_size == 1) {
		parent->entry = &arr[0];
		return;
	}
	parent->left = new Node;
	parent->right = new Node;

	float Phalf = P / 2.0f;

	float P_left = 0;
	int i = 0;
	for (i = 0;i < arr_size;i++)
	{
		P_left += arr[i].P;
		if (P_left >= Phalf)
		{
			break;
		}
	}

	float P_right = 0;
	for (int j = i + 1;j < arr_size;j++)
	{
		P_right += arr[j].P;
	}
	/*
	if (P - P_left != P_right)
	{
		cout << "na ez baj\n";
	}*/


	//cout << "Pleft " << P_left << "\n";
	i++;
	Recursive_build(parent->left, &arr[0], i, P_left);
	Recursive_build(parent->right, &arr[i], arr_size - i, P_right);
}

void Huffman::Recursive_crawling(Node* parent, std::string code, unsigned int& codebyte, int code_length)
{
	//note thet only the left is enought
	if (parent->left == nullptr || parent->right == nullptr)
	{
		parent->entry->code_length = code_length;
		parent->entry->codebyte = codebyte << (32 - code_length);

		char_to_code_dictionary.insert(std::pair<char, Entry*>(parent->entry->word, parent->entry));

		/*if (code.length() != code_length)
		{
			cout << "bajvan\n";
		}
		*/
		//std::cout << "word: " << parent->entry->word << "  code: " << code << " length: " << code_length << " P: " << parent->entry->P <<"\n";

		return;
	}
	code_length++;
	codebyte = codebyte << 1;
	Recursive_crawling(parent->left, code.append("0"), codebyte, code_length);
	code.pop_back();
	codebyte = codebyte | 1;
	Recursive_crawling(parent->right, code.append("1"), codebyte, code_length);
	code.pop_back();
	codebyte = codebyte >> 1;
	code_length--;

}

void Huffman::Compressing_file()
{

	infile->seekg(0, infile->beg);
	//size_t byte_pos = infile->tellg();
	size_t byte_left = infile_length;

	


	char* infilebuffer = new char[infile_buffer_size];
	outputbuffer = new char[outputbuffer_size];

	Entry* entry_temp = nullptr;
	while (byte_left > infile_buffer_size)
	{
		infile->read(infilebuffer, infile_buffer_size);
		byte_left -= infile_buffer_size;

		for (int j = 0;j < infile_buffer_size;j++) {
			//get the correct code
			entry_temp = char_to_code_dictionary[infilebuffer[j]];
			//add them to the bitbuffer
			addbits_tobitbuffer(entry_temp->codebyte, entry_temp->code_length);
		}
	}

	// read the rest of the file
	if (byte_left > 0)
	{

		//cout << "rest\n";
		infile->read(infilebuffer, byte_left);

		for (int j = 0;j < byte_left;j++) {
			//get the correct code
			entry_temp = char_to_code_dictionary[infilebuffer[j]];
			//add them to the bitbuffer
			addbits_tobitbuffer(entry_temp->codebyte, entry_temp->code_length);
		}
	}
	//clear the rest of the bitbuffer
	bitbuffer_to_filebuffer(bitbuff, ByteLengthFromCodeLenght(leftover));
	outfile->write(outputbuffer, output_buffer_pos);
	std::bitset<32> b(bitbuff);
	std::cout << b << std::endl;
	comlen += ByteLengthFromCodeLenght(leftover);
	std::cout << "compresed length: " << comlen << std::endl;




	delete[] infilebuffer;

	delete[] outputbuffer;

	outfile->flush();
	outfile->close();

}

void Huffman::addbits_tobitbuffer(const unsigned int bits, short bit_length)
{
	unsigned int bits_copy = bits >> bitpos;
	bitbuff = bitbuff | bits_copy;
	bitpos += bit_length;
	if (bitpos >= 31)
	{
		comlen += 4;
		//clear bytes write to buffer or disc
		bitbuffer_to_filebuffer(bitbuff, 4);


		//std::bitset<32> b(bitbuff);
		//std::cout << b << std::endl;
		bitbuff = 0;

		leftover = bitpos - 32;

		if (leftover > 0) {
			bits_copy = bits << leftover;
			bitbuff = bitbuff | bits_copy;
		}
		bitpos = leftover;

	}
}



void Huffman::bitbuffer_to_filebuffer(const unsigned int& bits, const size_t byte_size)
{
	memcpy(outputbuffer + output_buffer_pos, &bits, byte_size);
	output_buffer_pos += byte_size;
	if (output_buffer_pos >= outputbuffer_size)
	{
		outfile->write(outputbuffer,outputbuffer_size);
		outfile->flush();
		//std::cout << "repultek a bytok\n";
		output_buffer_pos = 0;
		//filebuffer_to_stream(outputbuffer, outputbuffer_size, outfile);
	}
}
void Huffman::filebuffer_to_stream(const char* buffer_, size_t size, std::ofstream* File)
{
	std::cout << "ha ezt látod akkor valamit elbasztál\n";
}




/*unsigned int* StringToBytearr(const string code, const short length)
{
	//int bytesize = ByteLengthFromCodeLenght(length);
	//char* bytes = new char[bytesize] {};
	unsigned int* bytecode = new unsigned int[1]{};

	//bitset<length> bits;
	for (size_t i = 0; i < length; i++)
	{


	}


}*/








