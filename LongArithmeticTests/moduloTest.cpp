#include "pch.h"

#include "../LongArithmetic/LongNumber.h"
#include "../LongArithmetic/LongNumberModulo.h"


LongNumber AddNumber(LongNumber A, uint32_t numOfAddings) {
	LongNumber result;
	for (int i = 0; i < numOfAddings; i++) {
		result = result + A;
	}
	return result;
}



namespace modulo_arithmetic {
	static bool equal( LongNumber& A,  LongNumber& B) { return A == B; }

	TEST(addition, distributive) {
		LongNumber A("c7c41cd7c2555ccdee6e3c30d9ddae1e");
		LongNumber B("a53908e7440ed214b774e3daa9641b0a");
		LongNumber C("70b1baae6489458a3c3311e4a9869218");

		EXPECT_TRUE((A + B) * C == C * (A + B));
		EXPECT_TRUE((A + B) * C == C * A + C * B);
	}

	TEST(addition, multiple_additions) {
		LongNumberModulo modulo(LongNumber("595b4d4453a69337abed466384883cacc1"));
		uint32_t k = 3924;

		EXPECT_TRUE(modulo.Barrett(AddNumber(LongNumber("c634b11c23293c3354956e50ea5b53ba66987884d7e64bdd7ece4b33650a4e864461"), k)) == 
			modulo.mult(LongNumber("c634b11c23293c3354956e50ea5b53ba66987884d7e64bdd7ece4b33650a4e864461"), k));
		EXPECT_TRUE(modulo.Barrett(AddNumber(LongNumber("1667a282552c1a79908e31e028e2238dd3b052610714204b7013427cd404c30bcbec"), k)) == 
			modulo.mult(LongNumber("1667a282552c1a79908e31e028e2238dd3b052610714204b7013427cd404c30bcbec"), k));
		EXPECT_TRUE(modulo.Barrett(AddNumber(LongNumber("b2aa3ace6d088e8589a5880736eb3a41bba11927c649713269a969944cebcbe5ee3d"), k)) == 
			modulo.mult(LongNumber("b2aa3ace6d088e8589a5880736eb3a41bba11927c649713269a969944cebcbe5ee3d"), k));
		EXPECT_TRUE(modulo.Barrett(AddNumber(LongNumber("1c02e8c581c2b3beb79224bb1c4d46468da24544369d2717ea2dbae91c75010be519"), k)) == 
			modulo.mult(LongNumber("1c02e8c581c2b3beb79224bb1c4d46468da24544369d2717ea2dbae91c75010be519"), k));
		EXPECT_TRUE(modulo.Barrett(AddNumber(LongNumber("d46ae4518b84367348d85bc894d139d98eb6dcca1a6bea6ccdcdce8d1ca1a5035e2a"), k)) == 
			modulo.mult(LongNumber("d46ae4518b84367348d85bc894d139d98eb6dcca1a6bea6ccdcdce8d1ca1a5035e2a"), k));
	}



	TEST(multiplication, power_of_Mersen_number1) {
		LongNumber one(1);
		LongNumber prime = one.LongShiftBitsToHigh(127) - one;
		LongNumberModulo modulo(prime);
		LongNumber A("e5a313b70555582465ed7ac86e218948");
		EXPECT_TRUE(modulo.power(A, prime - one) == one);
	}

	TEST(multiplication, power_of_Mersen_number2) {
		LongNumber one(1);
		LongNumber prime = one.LongShiftBitsToHigh(521) - one;
		LongNumberModulo modulo(prime);
		LongNumber A("9a782222016d647ec63147125629ed4a8b5b68d42197279069ec3be4e5b89bb342806375d56933c0531e8e82a2549ebe5790d3607d10ae02159940dd5eb6b1cc2e");
		EXPECT_TRUE(modulo.power(A, prime - one) == one);
	}

	TEST(multiplication, power_of_three_in_power_k) {
		LongNumber one(1);
		LongNumber mod = LongNumber(3).LongShiftBitsToHigh(100);
		LongNumber eulerNumber = LongNumber(3).LongShiftBitsToHigh(99).LongShiftBitsToHigh(1);
		LongNumberModulo modulo(mod);
		LongNumber A("a9e92d79a8c3e8b563a660d9b6b8d3162361a897");
		EXPECT_TRUE(modulo.power(A, eulerNumber) == one);
	}
}