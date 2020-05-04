#include "BitArray.h"

BitArray::BitArray()//cho gia tri mac dinh gom 4 byte int=0
{
	for (int i = 0; i < 4; i++)
	{
		this->m_vBlockbit.push_back(0);
	}
}
BitArray::BitArray(uint bitLength )
{
	normalizeBitLength(bitLength);
	for (int i = 0; i < bitLength / 32;i++)
	{
		this->m_vBlockbit.push_back(0);
	}
}
BitArray::BitArray(const uint* bytes, uint nBytes)//khoi tao nBytes voi chuoi Bytes
{
	for (int i = 0; i < nBytes; i++)
	{
		this->m_vBlockbit[i]=bytes[i];
	}	
}
BitArray::BitArray(const Bit* bits, uint bitLength)//khoi tao n bit=bitLength voi chuoi bits
{
	for (int i = 0; i < bitLength; i++)
	{
		if (bits[i].isBit1())
		{
			setBit(i,1);
		}
		else
		{
			setBit(i, 0);
		}
	}
}
BitArray::BitArray(const string& bits)
{
	int bitLength = bits.size();
	for (int i = 0; i < bitLength; i++)
	{
		if (bits[i] == '1')
		{
			setBit(i,1);
		}
		else
		{
			setBit(i,0);
		}
	}	
}
BitArray::BitArray(const BitArray& bitArr)
{
	for(int i=0;i<bitArr.getNumBlock();i++)
	{
		this->m_vBlockbit.push_back(bitArr.m_vBlockbit[i]);
	}
}
BitArray::~BitArray()
{

}

void BitArray::setBit(uint index,uint bit)
{
	int byte = index / 32;
	this->m_vBlockbit[byte] = this->m_vBlockbit[byte] | bit << (31 - index % 32);
}
void BitArray::setBit(BitArray& a, int bit, int i)
{
	a.m_vBlockbit[i / 32] = a.m_vBlockbit[i / 32] | (bit << (31 - (i % 32)));
}
Bit BitArray::getBit(uint index)const
{
	int byte = index / 32;
	return (this->m_vBlockbit[byte] >> (31-index % 32)) & 1;
}
void BitArray::setBlock(uint index, uint value)
{
	this->m_vBlockbit[index] = value;
}
uint BitArray::getBlock(uint index)const
{
	return this->m_vBlockbit[index];
}
uint BitArray::getNumBlock()const
{
	return this->m_vBlockbit.size();
}

uint BitArray::getBitLength()const
{
	return this->m_vBlockbit.size()*32;
}

void BitArray::resize(uint NewBitLength)
{
	normalizeBitLength(NewBitLength);
	if (NewBitLength > this->getBitLength())
	{
		BitArray temp(NewBitLength);
		for (int i = 0; i < this->getBitLength(); i++)
		{
			if (getBit(i) == 0)
			{
				temp.setBit(i,0);
			}
			else
			{
				temp.setBit(i,1);
			}
		}
		for (uint i = this->getBitLength(); i < NewBitLength; i++)
		{
			temp.setBit(i, 0);
		}
		*this = temp;
	}
	else
	{
		BitArray temp(NewBitLength);
		for (uint i = 0; i < NewBitLength; i++)
		{
			if (getBit(i) == 0)
			{
				temp.setBit(i, 0);
			}
			else
			{
				temp.setBit(i, 1);
			}
		}
		*this = temp;
	}
}
void BitArray::clear()
{
	this->m_vBlockbit.clear();
}
BitArray BitArray::operator=(const BitArray& rhs)
{
	if (this == &rhs)//neu trung return ve this
		return *this;

	this->clear();//xoa du lieu o this 
	for (int i = 0; i < rhs.getNumBlock(); i++)
	{
		this->m_vBlockbit.push_back(rhs.m_vBlockbit[i]); // gan rhs vao this
	}
	return *this;
}

BitArray BitArray::operator+(const BitArray& rhs)
{
	uint longer;
	if (this->getBitLength() > rhs.getBitLength()) //xac dinh day bit nao dai hon
	{
		longer = this->getBitLength();
	}
	else
	{
		longer = rhs.getBitLength();
	}
	BitArray result(longer);  //tao 1 BitArray ket qua

	int remember = 0;//gia tri nho
	for (int i = longer-1; i >=0; i--)
	{
		if (remember == 0)
		{
			if (this->getBit(i) == 0 && rhs.getBit(i) == 0)
				setBit(result, 0, i);
			else if (this->getBit(i) == 1 && rhs.getBit(i) == 1)
			{
				remember = 1;
				setBit(result, 0, i);
			}
			else setBit(result, 1, i);
		}
		else
		{
			if (this->getBit(i) == 0 && rhs.getBit(i) == 0)
			{
				setBit(result, 1, i);
				remember = 0;
			}
			else if (this->getBit(i) == 1 && rhs.getBit(i) == 1)
			{
				setBit(result, 1, i);
				remember = 1;
			}
			else
			{
				setBit(result, 0, i);
				remember = 1;
			}
		}
	}
	return result;
}

BitArray BitArray::Twocomplement()const
{
    BitArray one(this->getBitLength());
	one.setBit(this->getBitLength()-1,1);
	return ~*this + one;
}
BitArray BitArray::operator-(const BitArray& rhs)
{
	return *this + rhs.Twocomplement();
}

bool BitArray::checkIfZero()const
{
	for (int i = 0; i < this->getNumBlock(); i++)
		if (this->m_vBlockbit[i] != 0)
			return 0;
	return 1;
}

BitArray& BitArray::operator+=(const BitArray& rhs)
{
	*this = this->operator+(rhs);
	return *this;
}
BitArray& BitArray::operator-=(const BitArray& rhs)
{
	*this = this->operator-(rhs);
	return *this;
}
BitArray BitArray::operator|(const BitArray& rhs)
{
	uint n;//chieu dai bit lon hon
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
	}
	else
	{
		n = rhs.getBitLength();
	}
	for (int i = 0; i < n / 32; i++)
	{
		this->m_vBlockbit[i] = this->m_vBlockbit[i] | rhs.m_vBlockbit[i];
	}
	return *this;
}
BitArray BitArray::operator&(const BitArray& rhs)
{
	uint n;//chieu dai bit lon hon
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
	}
	else
	{
		n = rhs.getBitLength();
	}
	for (int i = 0; i < n / 32; i++)
	{
		this->m_vBlockbit[i] = this->m_vBlockbit[i] & rhs.m_vBlockbit[i];
	}
	return *this;
}
BitArray BitArray::operator^(const BitArray& rhs)
{
	uint n;//chieu dai bit lon hon
	if (this->getBitLength() > rhs.getBitLength())
	{
		n = this->getBitLength();
	}
	else
	{
		n = rhs.getBitLength();
	}
	for (int i = 0; i < n / 32; i++)
	{
		this->m_vBlockbit[i] = this->m_vBlockbit[i] ^ rhs.m_vBlockbit[i];
	}
	return *this;
}


BitArray BitArray::operator~()const
{
	BitArray result;
	for (int i = 0; i < this->getBitLength(); i++)
	{
		if (this->getBit(i) == 1)
		{
			result.setBit(i, 1);
		}
		else
		{
			result.setBit(i, 0);
		}
	}
	return result;
}

BitArray BitArray::operator>>(uint nBits)
{
	uint n = this->getBitLength();
	BitArray temp(n);
	for (uint i = n-1; i >= nBits; i--)
		if (this->getBit(i).isBit1())
			setBit(temp, 1, i - nBits);
	return temp;
}
BitArray BitArray::operator<<(uint nBits)
{
	uint n = this->getBitLength();
	BitArray temp(n);
	for (uint i = 0; i <128- nBits; i++)
		if (this->getBit(i).isBit1())
			setBit(temp, 1, i + nBits);
	return temp;
}


void BitArray::normalizeBitLength(uint& bitLength)
{
	if (bitLength > 0 & bitLength < 32)
	{
		bitLength = 32;
	}
	if (bitLength > 32 & bitLength < 64)
	{
		bitLength = 64;
	}
	if (bitLength > 64 & bitLength < 96)
	{
		bitLength = 96;
	}
	if (bitLength > 96 & bitLength < 128)
	{
		bitLength = 128;
	}
}
void BitArray::print()
{
	for (uint i = 0; i < this->getBitLength(); i++)
	{
		if (getBit(i) == 0)
		{
			cout << 0 << " ";
		}
		else
		{
			cout << 1 << " ";
		}
	}
}


