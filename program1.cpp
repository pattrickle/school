/***************************************************************************
* File: program1.cpp
* Author: pql160030
* Procedures:
* main - initializes a struct var, calls that struct and prints out name and info of kernel
***************************************************************************/
/**************************************************************************
To execute:
g++ program1.cpp
./a.out
**************************************************************************/

#include <iostream>
#include <sys/utsname.h> //uname header

using namespace std;

int main(){
struct utsname unameData;
uname(&unameData); //call uname with pointer to the defined struct
cout << "System Name: " <<unameData.sysname<<endl;
cout << "Host Name: " <<unameData.nodename<<endl;
cout << "OS Version: " <<unameData.version<<endl;
cout << "OS Releasee: " <<unameData.release<<endl;
}
