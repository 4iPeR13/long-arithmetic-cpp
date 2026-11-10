#include "pch.h"

#include "../LongArithmetic/LongNumber.h"

LongNumber AddNumber(LongNumber A, int numOfAddings) {
	LongNumber result;
	for (int i = 0; i < numOfAddings; i++) {
		result = result + A;
	}
	return result;
}

namespace arithmetic {
	TEST(Addition, IsCorrectAddition) {
		EXPECT_EQ(ConvertToHex((LongNumber("66304bb0503b8960d50032bcdb764712") + LongNumber("be6a58664690d8c1d1a995ecc90c836d"))), "1249aa41696cc6222a6a9c8a9a482ca7f");
		EXPECT_EQ(ConvertToHex((LongNumber("a57a24d603ca7e0162c70713a94e18ab") + LongNumber("eb7628b832d6024d13cce8e758e9d3d8"))), "190f04d8e36a0804e7693effb0237ec83");
		EXPECT_EQ(ConvertToHex((LongNumber("c90a5c6a968c294d6e3785eda8c24b3b") + LongNumber("d81db71a8a1516401262cb287a4dabd1"))), "1a128138520a13f8d809a5116230ff70c");
		EXPECT_EQ(ConvertToHex((LongNumber("40c3eb495c67a24e1b4ab1937bd58c3b") + LongNumber("c77acb90a7d361095db875a561d449b5"))), "1083eb6da043b035779032738dda9d5f0");
		EXPECT_EQ(ConvertToHex((LongNumber("61171b9c0a247597dcd863c8547ecba7") + LongNumber("888a344800d0547263c32cb6de6730a6"))), "e9a14fe40af4ca0a409b907f32e5fc4d");
	}

	TEST(Addition, MultipleAdditionsTest) {
		EXPECT_EQ(ConvertToHex(AddNumber(LongNumber("c7c41cd7c2555ccdee6e3c30d9ddae1e"), 100)), ConvertToHex(LongNumber("c7c41cd7c2555ccdee6e3c30d9ddae1e") * 100));
		EXPECT_EQ(ConvertToHex(AddNumber(LongNumber("a53908e7440ed214b774e3daa9641b0a"), 100)), ConvertToHex(LongNumber("a53908e7440ed214b774e3daa9641b0a") * 100));
		EXPECT_EQ(ConvertToHex(AddNumber(LongNumber("b19186c5741ae7979cdddd465d9380e"), 100)), ConvertToHex(LongNumber("b19186c5741ae7979cdddd465d9380e") * 100));
		EXPECT_EQ(ConvertToHex(AddNumber(LongNumber("e807bae2643340ae08884ca97b0b917"), 100)), ConvertToHex(LongNumber("e807bae2643340ae08884ca97b0b917") * 100));
		EXPECT_EQ(ConvertToHex(AddNumber(LongNumber("70b1baae6489458a3c3311e4a9869218"), 100)), ConvertToHex(LongNumber("70b1baae6489458a3c3311e4a9869218") * 100));
	}

	TEST(Addition, DistributiveTest1) {
		LongNumber A("c7c41cd7c2555ccdee6e3c30d9ddae1e");
		LongNumber B("a53908e7440ed214b774e3daa9641b0a");
		LongNumber C("70b1baae6489458a3c3311e4a9869218");

		EXPECT_EQ(ConvertToHex((A + B) * C), ConvertToHex(C * (A + B)));
		EXPECT_EQ(ConvertToHex((A + B) * C), ConvertToHex(C * A + C * B));
	}

	TEST(Addition, DistributiveTest2) {
		LongNumber A("be6a58664690d8c1d1a995ecc90c836d");
		LongNumber B("a57a24d603ca7e0162c70713a94e18ab");
		LongNumber C("61171b9c0a247597dcd863c8547ecba7");

		EXPECT_EQ(ConvertToHex((A + B) * C), ConvertToHex(C * (A + B)));
		EXPECT_EQ(ConvertToHex((A + B) * C), ConvertToHex(C * A + C * B));
	}

	TEST(Substraction, IsCorrectSubtraction) {
		EXPECT_EQ(ConvertToHex((LongNumber("512bc16a1c51cbd8c24856972979a147") - LongNumber("c4aa74edec6d4a5281ae20bb87"))), "512bc0a571dcddec54fe04157b58e5c0");
		EXPECT_EQ(ConvertToHex((LongNumber("b6908d30e6c5796a9a72bd85505ced8a") - LongNumber("70779e78625a792822eebd1226"))), "b6908cc06f2701083ff99562619fdb64");
		EXPECT_EQ(ConvertToHex((LongNumber("beb5ee60871942a8c96a228aacda439d") - LongNumber("37b9287b960e7451e61b4252b7"))), "beb5ee28cdf0c712baf5d0a49197f0e6");
		EXPECT_EQ(ConvertToHex((LongNumber("4b1c2e014110cba0eb449b5e49085531") - LongNumber("7aec997d8656489aa52ede299d"))), "4b1c2d8654774e1a94fc00b91a2a2b94");
		EXPECT_EQ(ConvertToHex((LongNumber("dc0ec9747744d548dd00c5e24bb344e5") - LongNumber("ae1c3508aac6768b42de7d2d8b"))), "dc0ec8c65b0fcc9e168a3a9f6d36175a");
	}


	TEST(Multiplication, IsCorrectMultiplication) {
		EXPECT_EQ(ConvertToHex((LongNumber("8297a89c4300bc0d") * LongNumber("8c5ab0542a42946b"))), "47993379eed18ee9143dd95b0b601d6f");
		EXPECT_EQ(ConvertToHex((LongNumber("74b42d4b2d75a48b") * LongNumber("e15422303a30cde"))), "66b8b683d9f2dc403ad7529553c348a");
		EXPECT_EQ(ConvertToHex((LongNumber("460acb106404d394") * LongNumber("ad4e5a089416e1e5"))), "2f6abb2616d458415efd14ed74fe5764");
		EXPECT_EQ(ConvertToHex((LongNumber("20e57abb489861b6") * LongNumber("61e9c7990cb4174"))), "c94fe03b826a52ba62891d712d7c78");
		EXPECT_EQ(ConvertToHex((LongNumber("16835bd73c5d502c") * LongNumber("5ca00a6c8a52cacc"))), "82548056d6281b610a032d121b69b10");
	}

	TEST(Division, IsCorrectDivision) {
		EXPECT_EQ(ConvertToHex((LongNumber("999a2d7905521145662c") / LongNumber("496e7dcb28a93e5d"))), "2177e");
		EXPECT_EQ(ConvertToHex((LongNumber("46dd17853c5ea4770b44") / LongNumber("189d342bd8392e9a"))), "2e105");
		EXPECT_EQ(ConvertToHex((LongNumber("a547aa29a66caad59d01") / LongNumber("194bcc35d378a873"))), "688a8");
		EXPECT_EQ(ConvertToHex((LongNumber("a496dd87daadd57289d5") / LongNumber("c22202b79ea81bb3"))), "d90a");
		EXPECT_EQ(ConvertToHex((LongNumber("e4c060d1c8ad33ab9681") / LongNumber("ba4b11e9d5d94939"))), "13a58");
	}

	TEST(Modulo, IsCorrectModulo) {
		EXPECT_EQ(ConvertToHex((LongNumber("9cdc252ac7543816baaa") % LongNumber("4602b0c84c0218a2"))), "31f1a2f82dc21446");
		EXPECT_EQ(ConvertToHex((LongNumber("e6723305d236a0b8bd63") % LongNumber("3ac7cad2dd8cbae7"))), "38ef4ec00d636a35");
		EXPECT_EQ(ConvertToHex((LongNumber("771421636c679970cbb3") % LongNumber("7da8d2990894a953"))), "6bba8a0701b075be");
		EXPECT_EQ(ConvertToHex((LongNumber("d77d779786e1ea6c9945") % LongNumber("39897dad1de6e76d"))), "3968ff6995e4cd8a");
		EXPECT_EQ(ConvertToHex((LongNumber("a86c0ab930b763357cd2") % LongNumber("18c358baad9eea3a"))), "cd327b539f01aaa");
	}

	TEST(Power, IsCorrectPower) {
		EXPECT_EQ(ConvertToHex(LongNumber("7122ab170b").power(LongNumber("8"))), "5f5b319747941031e76329cd53790f7dfcc3d6a583c8572999b905155d43104cff45f2338f0361");
		EXPECT_EQ(ConvertToHex(LongNumber("47908c80a8").power(LongNumber("e"))), "4c734afb91d719e60dd8730c7a3fa84f67431ad9c98949861dff53fe7362f4f4e391a51e3832c00afc41dfff41d9630d4ead119a313247a2602949893d240000000000");
		EXPECT_EQ(ConvertToHex(LongNumber("7b00bb9e07").power(LongNumber("b"))), "14a63ffaf0c22bceaa5f882ddb37c1504fc476de65ba732a585b817817b5784f7c0189e1bd92c7035a42afe7835a18e2f0bfcb00c697");
		EXPECT_EQ(ConvertToHex(LongNumber("ebb79cd9e9").power(LongNumber("5"))), "a96ebba35b42257834504f56004f6eabc4048085ce22a84c09");
	}
}