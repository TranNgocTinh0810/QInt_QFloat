#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class Bit
{
private:
	bool m_bit;
public:
	Bit();
	Bit(bool bit);
	Bit(const Bit& bit);
	~Bit();

	Bit& operator=(const Bit& bit);
	bool operator==(const Bit& bit)const;
	bool operator!=(const Bit& bit)const;
	Bit operator|(const Bit& bit);
	Bit operator&(const Bit& bit);
	Bit operator^(const Bit& bit);
	Bit operator~();

	bool isBit0()const;
	bool isBit1()const;
};

