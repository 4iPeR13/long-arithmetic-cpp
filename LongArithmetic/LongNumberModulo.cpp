#include "LongNumberModulo.h"

LongNumberModulo::LongNumberModulo(LongNumber& mod)
{
    modulo = mod;
    mu = Mu(mod);
    digitLength = modulo.DigitLength();

}

LongNumber LongNumberModulo::add(LongNumber& A, LongNumber& B)
{
    LongNumber result = A + B;
    return Barrett(result);
}

LongNumber LongNumberModulo::sub(LongNumber& A, LongNumber& B)
{
    LongNumber result;
    if (A < B) {
        result = B - A;
        result = Barrett(result);
        result = modulo - result;
    }
    else {
        result = A - B;
        result = Barrett(result);
    }
    return result;
}

LongNumber LongNumberModulo::mult(LongNumber& A, uint32_t& B)
{
    LongNumber result = A * B;
    return Barrett(result);
}

LongNumber LongNumberModulo::mult(LongNumber& A, LongNumber& B)
{
    LongNumber result = A * B;
    return Barrett(result);
}

LongNumber LongNumberModulo::square(LongNumber& A)
{
    LongNumber result = A * A;
    return Barrett(result);
}

LongNumber LongNumberModulo::power(LongNumber& A, LongNumber& power)
{
    LongNumber result(1);

    for (int i = power.BitLength() - 1; i >= 0; i--) {
        uint32_t bit = power.number_array[i / 32] >> i % 32;
        bit = bit & 1;
        if (bit == 1) {
            result = mult(A, result);
        }
        if (i > 0) {
            result = mult(result,result);
        }
    }
    return result;
}


LongNumber LongNumberModulo::Barrett(LongNumber& A)
{
    if (A < modulo) {
        return A;
    }
    LongNumber Q = A.LongShiftDigitsToLow(digitLength - 1);
    Q = Q * mu;
    Q = Q.LongShiftDigitsToLow(digitLength + 1);

    Q = Q * modulo;
    LongNumber R = A - Q;

    while (R >= modulo) {
        R = R - modulo;
    }
    return R;
}

LongNumber LongNumberModulo::Mu(LongNumber& mod)
{
    int digitLength = mod.DigitLength();
    LongNumber beta(1);
    beta = beta.LongShiftDigitsToHigh(digitLength * 2);
    return beta / mod;
}
