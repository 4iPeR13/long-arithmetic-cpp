#pragma once
#include<stdint.h>
#include<iostream>

static const int NUMBER_LENGTH = 64;



class LongNumber {
public:
	uint32_t number_array[NUMBER_LENGTH];

	LongNumber();
	LongNumber(const LongNumber& B);
	LongNumber(const uint32_t number);
	LongNumber(const std::string hex);

	static LongNumber zero();
	static LongNumber one();


	LongNumber operator + (LongNumber& B) const;
	LongNumber operator - (LongNumber& B) const;

	LongNumber operator * (uint32_t B) const;
	LongNumber operator * (LongNumber& B) const;

	LongNumber operator / (LongNumber& B) const;
	LongNumber operator % (LongNumber& B) const;

	LongNumber power(LongNumber& B) const;

	int BitLength() const;
	int DigitLength() const;

	LongNumber LongShiftDigitsToLow(int shift) const;
	LongNumber LongShiftDigitsToHigh(int shift) const;

	LongNumber LongShiftBitsToHigh(int shift) const;

	LongNumber LongShiftBitsToLow(int shift) const;

	bool operator < (LongNumber& B) const;
	bool operator > (LongNumber& B) const;
	bool operator <= (LongNumber& B) const;
	bool operator >= (LongNumber& B) const;

	bool operator == (LongNumber& const B) const;
	bool operator != (LongNumber& B) const;

	static LongNumber GCD(LongNumber& A,LongNumber& B);
	static LongNumber LCM(LongNumber& A,LongNumber& B);

	friend std::ostream& operator<<(std::ostream& os, const LongNumber& LongNumber);


};


uint32_t ConvertHexToDigit(char hex);

char ConvertDigitToHex(uint32_t digit);

LongNumber ConvertToNumber(std::string hex);

std::string ConvertToHex(LongNumber number);
