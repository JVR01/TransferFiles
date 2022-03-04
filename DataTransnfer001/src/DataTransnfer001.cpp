//============================================================================
// Name        : DataTransnfer001.cpp
// Author      : Jav
// Version     :
// Copyright   : Your copyright notice
// Description : The idea is to put 3 different variables into a char array and then reconstruct the data and create with it
//               new variables. The Idea is to understand the variables inside a Buffer and Byte processing
//============================================================================

#include <iostream>
using namespace std;
#include <string.h> //added for the memset() function

#include "useful_stuf.h"

const int BUFFER_SIZE = 50;
unsigned char buffer[BUFFER_SIZE]; //a buffer with 30 Bytes


uint32_t message_integer = 654321;
string   message_word = "hello Dude!"; //Strings are chr[] * arrays
float    message_float = 10.75f; //floats are 32bit->4Byte long
char     sub_buffer_word[] = "hAllo amigos!"; //13 characters

class Result
{

 public:

 uint32_t Integer;
 string   SString;
 float    Float; //floats are 32bit->4Byte long
 char     c_Word[20]; //13 characters
};


void print_strings(unsigned char chararray[]);
void print_strings2(const unsigned char* MYarray, const int bytes_size);
Result reconstruct_variables(const unsigned char* chararray, const int array_size);


int main() {
	buffer[0] = 'A';
	buffer[BUFFER_SIZE] = 'Z';
	uint16_t UsedByteCount = 3U;

	//write the Integer inside the buffer From Byte 3
	/*
	 * Equivalent to: //654321 DEC = 0000 1001 -1111 1011-1111 0001 BIN
	 * buffer[3] = message_integer >> (0*8); //start from Bite 0, 241 DEC --> 1111 0001  (LSB)
	   buffer[4] = message_integer >> (1*8); //read from bit LSB, 251 DEC --> 1111 1011
	   buffer[5] = message_integer >> (2*8); //read from bit LSB, 9 DEC   --> 0000 1001  (MSB)
	   buffer[6] = message_integer >> (3*8); //copy the 4th Byte, 0 DEC   --> 0000 0000   nix
	 * */
	for(int i = 0; i <sizeof(message_integer);i++) //Put info inside 4 bytes to write the uint_32
	{
		buffer[UsedByteCount] = message_integer >> (i*8);
		UsedByteCount++;
	}

	////write the String inside the buffer
	for(int i = 0; i < message_word.size()/*sizeof(message_word)*/;i++)//12 Characters but message_word.size()=11
	{
		buffer[UsedByteCount] = message_word[i];
		UsedByteCount++;
	}
    //Strings do not work exactly as Char[]

	////write the char-array inside the buffer
	for(int i = 0; i < sizeof(sub_buffer_word);i++)
	{
		buffer[UsedByteCount] = sub_buffer_word[i];
		UsedByteCount++;
	}

	////write the float inside the buffer
	//one way is first convert the flot into a 32bit Integer an then put it inside the buffer
	uint32_t fbits = 0;
	memcpy(&fbits, &message_float, sizeof fbits); //puts the 4Bytes inside uint32_t
	print_bytes(&fbits, sizeof(fbits));
	//01000001 00101100 00000000 00000000 //should be the result float(10.75)
	//   65       44
	//or 1093402624 as Decimal
	for(int i = 0; i <sizeof(fbits);i++) //Put info inside 4 bytes to write the uint_32
	{
		buffer[UsedByteCount] = fbits >> (i*8); //start from Bite 0 and write the LSB
		UsedByteCount++;
	}

    //Show the content of the hole aray
	for(int i = 0; i <= sizeof(buffer);i++)
	{
		//cout << "Character["<< i <<"]: " << buffer[i]<< endl;
		printf ("Character[%u]: %c equivalent to: %u \n", i, buffer[i], buffer[i]); //%c is character //
	}

	cout << " "<< endl;
	//print_strings2(buffer, sizeof(buffer));
	Result decoded_message = reconstruct_variables(buffer, sizeof(buffer));
	cout << "result.Integer: " << decoded_message.Integer<< endl;
	cout << "result.SString: " << decoded_message.SString<< endl;
	cout << "result.c_Word:  "  << decoded_message.c_Word<< endl;
	cout << "result.Float:   "   << decoded_message.Float<< endl;
	//printf("content: %s \n", decoded_message.c_Word);
	return 0;
}

void print_strings(unsigned char chararray[])
{
 //cout<< chararray <<"\t length: "<< strlen(chararray)<<endl;
 chararray[6]= 'Z';
 cout<< chararray <<endl;
}
void print_strings2(const unsigned char* MYarray, const int bytes_size)
{
	//MYarray[2] = 'Z';
	cout<<"Array content: "<<MYarray[bytes_size]<<endl;
	//print_bytes(&MYarray, bytes_size);
	for(int i = 0; i <= bytes_size;i++)
	{
		//cout << "Character["<< i <<"]: " << buffer[i]<< endl;
		printf ("input Character[%u]: %c equivalent to: %u \n", i, MYarray[i], MYarray[i]); //%c is character //
		print_bytes(&MYarray[i], sizeof(unsigned char));
	}
}
Result reconstruct_variables(const unsigned char* chararray, const int array_size)
{
	Result result;
	uint8_t readed_counter = 3;//Read start position

    //*****Get the Integer from buffer
	//654321 DEC = 1001  1111  1011  1111  0001 BIN
	for(int i = 0; i < sizeof(result.Integer);i++) //Put info inside 4 bytes to write the uint_32
	{
      result.Integer |= chararray[readed_counter]<<(i)*8; //i=0-->(i-3)*8=0 write the
      //print_bytes(&result.Integer, sizeof(result.Integer));
      readed_counter++;
	}


	//*****Get the String from buffer
	for(int i = 0; i < message_word.size() ;i++)
	{
	  result.SString += chararray[readed_counter];
	  readed_counter++;
	}
	//cout << "readed_counter: "<< readed_counter << endl; //some how wont show the DEC number
	//printf("readed_counter: %u \n", readed_counter);


	//*****Get the Characteer array from buffer
	for(int i = 0; i <sizeof(sub_buffer_word) ;i++) //Put info inside 4 bytes to write the uint_32
	{
	  result.c_Word[i] = chararray[readed_counter]; //a Char array can never Start will NULL or it will be treted as empty string! +1
	  readed_counter++;
	}
	//printf("content: %s \n", result.c_Word);

	//*****Get the Float from buffer
	uint32_t float_content;
	for(int i = 0; i < sizeof(message_float);i++) //Put info inside 4 bytes to write the float (32bit)
	{
		float_content|= chararray[readed_counter]<<(i)*8; //i=0-->(i-3)*8=0 write the
	  //print_bytes(&result.Integer, sizeof(result.Integer));
	  readed_counter++;
	}
	result.Float = bintofloat(float_content);

	return result;
}
