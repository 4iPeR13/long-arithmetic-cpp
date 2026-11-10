#pragma once
#include"LongNumber.h"

class LongNumberModulo {
private:
	LongNumber modulo;
	LongNumber mu;
	int digitLength;
public:
	LongNumberModulo(LongNumber& mod);

	LongNumber add(LongNumber& A, LongNumber& B);
	LongNumber sub(LongNumber& A, LongNumber& B);


	LongNumber mult(LongNumber& A, uint32_t& B);
	LongNumber mult(LongNumber& A, LongNumber& B);

	LongNumber square(LongNumber& A);

	LongNumber power(LongNumber& A, LongNumber& power);

	LongNumber Barrett(LongNumber& A);
	LongNumber Mu(LongNumber& mod);
};