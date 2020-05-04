#pragma once
#include"Bit.h"
typedef unsigned char uchar;
typedef unsigned int uint;
class BitArray
{
private:
	vector<uint> m_vBlockbit;
public:
	BitArray();
	BitArray(uint bitLength );
	BitArray(const uint* bytes, uint nBytes);
	BitArray(const Bit* bits, uint bitLength);
	BitArray(const string& bits);
	BitArray(const BitArray& bitArr);
	~BitArray();

	void setBit(uint index,uint bit);   //Set gia tri bit (0,1).o vi tri index
	void setBit(BitArray& a, int bit, int i);

	Bit getBit(uint index)const;    //nhan gia tri bit tai vi tri index
	void setBlock(uint index, uint value); // Set gia tri 1 byte tai vi tri index
	uint getBlock(uint index)const;//Nhan gia tri byte tu vi tri index

	uint getNumBlock()const;  //tra ve tong so Byte
	uint getBitLength()const;  //tra ve tong so bit
	void resize(uint NewBitLength);
	void clear();//xoa du lieu

	BitArray operator=(const BitArray& rhs);
	BitArray operator+(const BitArray& rhs);
	BitArray operator-(const BitArray& rhs);
	//BitArray operator*(const BitArray& rhs);
	//BitArray operator/(const BitArray& rhs);
	BitArray& operator+=(const BitArray& rhs);
	BitArray& operator-=(const BitArray& rhs);
	//BitArray& operator*=(const BitArray& rhs);
	//BitArray& operator/=(const BitArray& rhs);

	BitArray operator|(const BitArray& rhs);
	BitArray operator&(const BitArray& rhs);
	BitArray operator^(const BitArray& rhs);
	BitArray operator~()const;
	BitArray operator>>(uint nBits);
	BitArray operator<<(uint nBits);

	bool checkIfZero()const;
	BitArray Twocomplement()const;
	void print();
protected:
	void normalizeBitLength(uint& bitLength);
};
