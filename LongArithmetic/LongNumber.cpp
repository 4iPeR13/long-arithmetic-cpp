#include "LongNumber.h"


LongNumber::LongNumber() {
	for (int i = 0; i < NUMBER_LENGTH; i++) 
	{
		number_array[i] = 0;
	}
}

LongNumber::LongNumber(const LongNumber& B)
{
	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		number_array[i] = B.number_array[i];
	}
}

LongNumber::LongNumber(const uint32_t number)
{
	*this = LongNumber();
	number_array[0] = number;
}

LongNumber::LongNumber(const std::string hex)
{
	*this = ConvertToNumber(hex);
}

LongNumber LongNumber::zero()
{
	return LongNumber(0);
}

LongNumber LongNumber::one()
{
	return LongNumber(1);
}

LongNumber LongNumber::operator+(LongNumber& B) const
{
	LongNumber result;
	uint32_t carry = 0;

	for (int i = 0; i < NUMBER_LENGTH; i++) 
	{
		uint64_t temp = static_cast<uint64_t>(this->number_array[i]) + B.number_array[i] + carry;
		result.number_array[i] = temp & UINT32_MAX;
		carry = temp >> 32;
	}
	return result;
}

LongNumber LongNumber::operator-(LongNumber& B) const
{
	LongNumber result;
	uint32_t borrow = 0;

	for (int i = 0; i < NUMBER_LENGTH; i++)
	{
		int64_t temp = static_cast<int64_t>(this->number_array[i]) - static_cast<int64_t>(B.number_array[i]) - borrow;
		if (temp >= 0) {
			result.number_array[i] = static_cast<uint32_t>(temp);
			borrow = 0;
		}
		else {
			result.number_array[i] = static_cast<uint32_t>(UINT32_MAX + temp + 1);
			borrow = 1;
		}
	}
	if (borrow == 1) {
		throw std::invalid_argument("number \n" + ConvertToHex(*this) + "\nsmaller than \n" + ConvertToHex(B));
	}
	return result;
}



LongNumber LongNumber::operator*(uint32_t B) const
{
	uint32_t carry = 0;
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH; i++) {
		uint64_t temp = static_cast<uint64_t>(this->number_array[i]) * static_cast<uint64_t>(B) + static_cast<uint64_t>(carry);
		result.number_array[i] = static_cast<uint32_t>(temp & UINT32_MAX);
		carry = static_cast<uint32_t>(temp >> 32);
	}
	result.number_array[NUMBER_LENGTH - 1] = carry;
	return result;
}

LongNumber LongNumber::operator *(LongNumber& B) const
{
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH; i++) {
		LongNumber temp = *this * B.number_array[i];
		temp = temp.LongShiftDigitsToHigh(i);
		result = result + temp;
	}
	return result;
}

LongNumber LongNumber::operator/(LongNumber& B) const
{
	int k = B.BitLength();
	LongNumber Q;
	LongNumber R(*this);
	while (R >= B) {
		int temp = R.BitLength();
		LongNumber C = B.LongShiftBitsToHigh(temp - k);
		if (R < C) {
			temp--;
			C = B.LongShiftBitsToHigh(temp - k);
		}
		R = R - C;
		LongNumber powerOfTwo(1);
		powerOfTwo = powerOfTwo.LongShiftBitsToHigh(temp - k);
		Q = Q + powerOfTwo;
	}
	return Q;
}

LongNumber LongNumber::operator%(LongNumber& B) const
{
	int k = B.BitLength();
	LongNumber Q;
	LongNumber R(*this);
	while (R >= B) {
		int temp = R.BitLength();
		LongNumber C = B.LongShiftBitsToHigh(temp - k);
		if (R < C) {
			temp--;
			C = B.LongShiftBitsToHigh(temp - k);
		}
		R = R - C;
		LongNumber powerOfTwo(1);
		powerOfTwo = powerOfTwo.LongShiftBitsToHigh(temp - k);
		Q = Q + powerOfTwo;
	}
	return R;
}

LongNumber LongNumber::power(LongNumber& B) const
{
	LongNumber result(1);

	for (int i = B.BitLength() - 1; i >= 0; i--) {
		uint32_t bit = B.number_array[i / 32] >> i % 32;
		bit = bit & 1;
		if (bit == 1) {
			result = *this * result;
		}
		if (i > 0) {
			result = result * result;
		}
	}
	return result;
}

int LongNumber::BitLength() const
{
	int digit = NUMBER_LENGTH - 1;
	while (this->number_array[digit] == 0) {
		digit--;
	}
	if (digit == -1) return 0;
	int bit_length = digit * 32;
	uint32_t temp = this->number_array[digit];
	while (temp != 0) {
		temp >>= 1;
		bit_length++;
	}
	return bit_length;
}

int LongNumber::DigitLength() const
{
	for (int i = NUMBER_LENGTH - 1; i >= 0; i--) {
		if (number_array[i] != 0) {
			return i + 1;
		}
	}
	return 0;
}



bool LongNumber::operator<(LongNumber& B) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == B.number_array[i] && i >= 0) {
		i--;
	}
	if (i == -1) return false;
	return this->number_array[i] < B.number_array[i];
}

bool LongNumber::operator>(LongNumber& B) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == B.number_array[i] && i >= 0) {
		i--;
	}
	if (i == -1) return false;
	return this->number_array[i] > B.number_array[i];
}

bool LongNumber::operator<=(LongNumber& B) const
{
	return *this < B || *this == B;
}

bool LongNumber::operator>=(LongNumber& B) const
{
	return *this > B || *this == B;
}

bool LongNumber::operator==(LongNumber& const B) const
{
	int i = NUMBER_LENGTH - 1;
	while (this->number_array[i] == B.number_array[i] && i >= 0) {
		i--;
	}
	return i == -1;
}

bool LongNumber::operator!=(LongNumber& B) const
{
	return !(*this == B);
}

LongNumber LongNumber::GCD(LongNumber& A,LongNumber& B)
{
	LongNumber Q, R = 0;
	LongNumber aTemp = A;
	LongNumber bTemp = B;

	LongNumber Zero = zero();

	while (bTemp > Zero) {
		Q = aTemp / bTemp;
		LongNumber qTemp = Q * bTemp;
		R = aTemp - qTemp;
		aTemp = bTemp;
		bTemp = R;
	}
	return aTemp;
}

LongNumber LongNumber::LCM(LongNumber& A,LongNumber& B)
{
	LongNumber a = (A * B);
	LongNumber b = GCD(A,B);
	return a / b;
}

LongNumber LongNumber::LongShiftDigitsToLow(int shift) const
{
	LongNumber result;
	for (int i = NUMBER_LENGTH - 1; i >= shift; i--) {
		result.number_array[i - shift] = this->number_array[i];
	}
	return result;
}

LongNumber LongNumber::LongShiftDigitsToHigh(int shift) const
{
	LongNumber result;
	for (int i = 0; i < NUMBER_LENGTH - shift; i++) {
		result.number_array[i + shift] = this->number_array[i];
	}
	return result;
}

LongNumber LongNumber::LongShiftBitsToHigh(int shift) const
{
	int digitShifts = shift / 32;
	int bitShifts = shift % 32;
	uint32_t carry = 0;

	LongNumber temp(*this);
	LongNumber result;

	if (bitShifts == 0) {
		for (int i = 0; i < NUMBER_LENGTH; i++)
		{
			temp.number_array[i] = this->number_array[i];
		}
		for (int j = digitShifts; j < NUMBER_LENGTH; j++)
		{
			result.number_array[j] = temp.number_array[j - digitShifts];
		}
	}
	else {
		for (int i = 0; i < NUMBER_LENGTH; i++) {
			temp.number_array[i] = (this->number_array[i] << shift) + carry;
			carry = (this->number_array[i] >> (32 - shift));
		}
		for (int j = digitShifts; j < NUMBER_LENGTH; j++)
		{
			result.number_array[j] = temp.number_array[j - digitShifts];
		}
	}
	return result;
}
LongNumber LongNumber::LongShiftBitsToLow(int shift) const
{
	int digitShifts = shift / 32;
	int bitShifts = shift % 32;
	uint32_t carry = 0;

	LongNumber temp(*this);
	LongNumber result;

	if (bitShifts == 0) {
		for (int i = 0; i < NUMBER_LENGTH; i++)
		{
			temp.number_array[i] = this->number_array[i];
		}
		for (int j = NUMBER_LENGTH - 1 - digitShifts; j >= 0; j-- )
		{
			result.number_array[j] = temp.number_array[j - digitShifts];
		}
	}
	else {
		for (int i = NUMBER_LENGTH - 1; i >= 0; i--) {
			temp.number_array[i] = (this->number_array[i] >> shift) + (carry << 32 - shift);
			carry = this->number_array[i] & static_cast<uint32_t>(bitShifts);
		}
		
		for (int j = NUMBER_LENGTH - 1 - digitShifts; j >= 0; j--)
		{
			result.number_array[j] = temp.number_array[j + digitShifts];
		}
	}
	return result;
}





char ConvertDigitToHex(uint32_t digit) 
{
	std::string hexs = "0123456789abcdef";
	return hexs[digit];
}



std::ostream& operator<<(std::ostream& os, const LongNumber& number)
{
	os << ConvertToHex(number);
	return os;
}

uint32_t ConvertHexToDigit(char hex)
{
	if (hex == '0') return 0;
	if (hex == '1') return 1;
	if (hex == '2') return 2;
	if (hex == '3') return 3;
	if (hex == '4') return 4;
	if (hex == '5') return 5;
	if (hex == '6') return 6;
	if (hex == '7') return 7;
	if (hex == '8') return 8;
	if (hex == '9') return 9;
	if (hex == 'A' || hex == 'a') return 10;
	if (hex == 'B' || hex == 'b') return 11;
	if (hex == 'C' || hex == 'c') return 12;
	if (hex == 'D' || hex == 'd') return 13;
	if (hex == 'E' || hex == 'e') return 14;
	if (hex == 'F' || hex == 'f') return 15;
	
	throw std::invalid_argument("Digit is incorrect: " + hex);
}

LongNumber ConvertToNumber(std::string hex)
{
	LongNumber result;
	for (int i = 0; i < hex.length(); i++) {
		uint32_t modulo = i % 8;
		uint32_t digit = ConvertHexToDigit(hex[hex.length() - i - 1]);
		result.number_array[i/8] += digit * (1 << (4 * modulo));
	}
	return result;
}

std::string ConvertToHex(LongNumber number) {
	std::string hex = "";
	for (int i = 0; i < NUMBER_LENGTH*8; i++) {
		uint32_t modulo = i % 8;
		hex += ConvertDigitToHex((number.number_array[i/8] >> (4 * modulo)) & 15);
	}
	hex = hex.erase(hex.find_last_not_of('0') + 1);
	std::string reverse_hex;
	for (int i = hex.length() - 1; i >= 0; i--) {
		reverse_hex += hex[i];
	}
	return reverse_hex;
}



