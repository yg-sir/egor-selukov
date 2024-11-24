#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include "Cipher.h"
#include <locale>
#include <codecvt>


using namespace std;
string wst (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.CoderPerestanCipher(w, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
string wst1 (int k, wstring s1)
{
    PerestanCipher w(k);
    wstring s=w.DecoderPerestanCipher(k, s1);
    const string s2 (s.begin(), s.end() );
    return s2;
}
SUITE (KeyTest)
{
    wstring test = L"SVERCHKOV";
    int k;
    TEST (ValidKey) {
        CHECK_EQUAL(wst(k=3,test),"EHVVCOSRK");
    }
    TEST(EmptyKey) {
        CHECK_THROW(wst(k=0,test), cipher_error);
    }
    TEST(NegativeKey) {
        CHECK_THROW(wst(k=-3,test), cipher_error);
    }
    TEST(LargeKey) {
        CHECK_THROW(wst(k=52,test), cipher_error);
    }
    TEST(A_characters_in_the_key_instead_of_numbers) {
        CHECK_THROW(wst(k='$', test), cipher_error);
    }
}
SUITE(EncryptTest)
{
    TEST(ValidText) {
        CHECK_EQUAL(wst(3,L"SVERCHKOV"),"EHVVCOSRK");
    }
    TEST(LowText) {
        CHECK_EQUAL(wst(3,L"sverchkov"),"ehvvcosrk");
    }
    TEST(SpaceText) {
        CHECK_EQUAL(wst(3,L"SVERCH KOV"),"EHVVCO SRK");
    }
    TEST(EmptyText) {
        CHECK_THROW(wst(3,L" "),cipher_error);
    }
    TEST(ValiDTextWithoutletters) {
        CHECK_THROW(wst(3,L"$"),cipher_error);
    }
    TEST(TextWithNumber) {
        CHECK_EQUAL(wst(3,L"SV3RCHKOV"),"3HVVCOSRK");
    }
    TEST(TextWithSpaceAndPunct) {
        CHECK_EQUAL(wst(9,L"$VERCH KOV"),"VOKHCR EV$");
    }
}
SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(wst1(3,L"EHVVCOSRK"),"SVERCHKOV");
    }
    TEST(LowTEXT) {
        CHECK_EQUAL(wst1(3,L"ehvvcosrk"),"sverchkov");
    }
    TEST(SpaceTEXT) {
        CHECK_EQUAL(wst1(3,L"EHVVCO SRK"),"SVERCH KOV");
    }
    TEST(EmptyTEXT) {
        CHECK_THROW(wst1(3,L" "),cipher_error);
    }
    TEST(TextNumberText) {
        CHECK_EQUAL(wst1(3,L"3HVVCOSRK"),"SV3RCHKOV");
    }
    TEST(TextSymbolText) {
        CHECK_EQUAL(wst1(3,L"VOKHCREV$"),"$VERCHKOV");
    }

}

int main()
{
    return UnitTest::RunAllTests();
}
