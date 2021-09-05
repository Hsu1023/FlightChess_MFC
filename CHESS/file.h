#pragma once
#include<fstream>
#include<iostream>
using namespace std;
class file
{
public:
	ofstream of;
public:
	file()
	{
		of.open("1.txt");
	}
	~file()
	{
		of.close();
	}
};
