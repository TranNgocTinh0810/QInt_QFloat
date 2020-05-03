#include "Bit.h"

Bit::Bit()
{
	m_bit = 0;
}

Bit::Bit(bool bit)
{
	m_bit = bit;
}
Bit::Bit(const Bit& bit)
{
	m_bit = bit.m_bit;
}
Bit& Bit::operator=(const Bit& bit)
{
	if (this == &bit)
	{
		return *this;
	}
	else
	{
		this->m_bit = bit.m_bit;
		return *this;
	}
}
bool Bit::operator==(const Bit& bit)const
{
	if (this->m_bit != bit.m_bit)
		return 0;
	return 1;
}
bool Bit::operator!=(const Bit& bit)const
{
	if (this->m_bit != bit.m_bit)
		return 1;
	return 0;
}
Bit Bit::operator|(const Bit& bit)
{
	this->m_bit = this->m_bit | bit.m_bit;
	return *this;
}
Bit Bit::operator&(const Bit& bit)
{
	this->m_bit = this->m_bit & bit.m_bit;
	return *this;
}
Bit Bit::operator^(const Bit& bit)
{
	this->m_bit = this->m_bit ^ bit.m_bit;
	return *this;
}
Bit Bit::operator~()
{
	this->m_bit = ~this->m_bit;
	return *this;
}
bool Bit::isBit0()const
{
	if (this->m_bit == 0)
	{
		return 1;
	}
	return 0;
}
bool Bit::isBit1()const
{
	if (this->m_bit == 1)
	{
		return 1;
	}
	return 0;
}
Bit::~Bit()
{
}
