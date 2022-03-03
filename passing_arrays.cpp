#include <iostream>
using namespace std;
#include <string.h>

void init_array(int* data, int len);
void print_strings(unsigned char chararray[]);
void print_strings2(const unsigned char* MYarray);


int main()
{
    cout << "Hello, World!"<< endl;
    int arr[10];
    int len = sizeof(arr)/sizeof(int);
    init_array(arr,len);
    cout <<"sizeof(arr): "<<sizeof(arr)<< endl; //40 Bytes
    cout <<"len: "<<len<< endl;//10

    for(int index = 0; index < len; index++)
	{
	cout <<arr[index]<< endl;
	}

    unsigned char char_arr[20] = "Hello Dude";
    cout <<"sizeof(char_arr): "<<sizeof(char_arr)<< endl;
    print_strings(char_arr);
	cout <<"after print_strings:"<<char_arr<< endl;

	unsigned char array[5]={'a', 'b', 'c', 'd', 0};
	print_strings2(array);

    return 0;
}
void print_strings(unsigned char chararray[])
{
 //cout<< chararray <<"\t length: "<< strlen(chararray)<<endl;
 chararray[6]= 'Z';
 cout<< chararray <<"\t length: "<< sizeof(chararray)<<endl;
}
void print_strings2(const unsigned char* MYarray)
{
	//MYarray[2] = 'Z';
	cout<<MYarray<<endl;
}

void init_array(int* data, int len)
{
	for(int index = 0; index < len; index++)
	{
		data[index] = 5;
	}
}
