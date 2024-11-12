#include <UnitTest++/UnitTest++.h>
#include "Cipher.h"
#include <string>

std::string s = "SVERCHKOV";

SUITE(KeyTest) {
    TEST(ValidKey) {
        Cipher cipher(3, "SVERCHKOV");
        CHECK_EQUAL("EHVVCOSRK", cipher.encrypt(s));
    }
    TEST(LongKey) {
        CHECK_THROW(Cipher(1, "SVERCHKOV"), CipherError);
    }
}

struct CipherFixture {
    Cipher* cipherInstance;
    CipherFixture() {
        cipherInstance = new Cipher(3, "SVERCHKOV");
    }
    ~CipherFixture() {
        delete cipherInstance;
    }
};

SUITE(EncryptTest) {
    TEST_FIXTURE(CipherFixture, UpCaseString) {
        std::string input = "SVERCHKOV";
        CHECK_EQUAL("EHVVCOSRK", cipherInstance->encrypt(input));
    }
    TEST_FIXTURE(CipherFixture, LowCaseString) {
        std::string input = "sverchkov";
        CHECK_EQUAL("ehvvcosrk", cipherInstance->encrypt(input));
    }
    TEST_FIXTURE(CipherFixture, StringWithWhitespaceAndPunct) {
        std::string input = "SVERCH KOV";
        CHECK_EQUAL("EHVVCOSRK", cipherInstance->encrypt(input));
    }
    TEST_FIXTURE(CipherFixture, StringWithNumbers) {
        std::string input = "sver4kov";
        CHECK_THROW(cipherInstance->encrypt(input), CipherError);
    }
    TEST_FIXTURE(CipherFixture, EmptyString) {
        std::string input = "";
        CHECK_THROW(cipherInstance->encrypt(input), CipherError);
    }
    TEST_FIXTURE(CipherFixture, NoAlphaString) {
        std::string input = "4*4";
        CHECK_THROW(cipherInstance->encrypt(input), CipherError);
    }
    TEST(MaxShiftKey) {
        Cipher cipher(9, "SVERCHKOV");
        std::string input1 = "VOKHCREVS";
        std::string input2 = "SVERCHKOV";
        CHECK_EQUAL("Sverchkov", cipher.decrypt(input1, input2));
    }
}

SUITE(DecryptTest) {
    TEST_FIXTURE(CipherFixture, UpCaseString) {
        std::string input1 = "EHVVCOSRK";
        std::string input2 = "SVERCHKOV";
        CHECK_EQUAL("SVERCHKOV", cipherInstance->decrypt(input1, input2));
    }
    TEST_FIXTURE(CipherFixture, LowCaseString) {
        std::string input1 = "ehvvcosrk";
        std::string input2 = "sverchkov";
        CHECK_EQUAL("sverchkov", cipherInstance->decrypt(input1, input2));
    }
    TEST_FIXTURE(CipherFixture, WhitespaceString) {
        std::string input1 = "EHVVCOSRK";
        std::string input2 = "EHVVCO SRK";
        CHECK_THROW(cipherInstance->decrypt(input1, input2), CipherError);
    }
    TEST_FIXTURE(CipherFixture, DigitsString) {
        std::string input1 = "ehv4cosrk";
        std::string input2 = "ehv4cosrk";
        CHECK_THROW(cipherInstance->decrypt(input1, input2), CipherError);
    }
    TEST_FIXTURE(CipherFixture, PunctString) {
        std::string input1 = "ehv!cosrk";
        std::string input2 = "ehv!cosrk";
        CHECK_THROW(cipherInstance->decrypt(input1, input2), CipherError);
    }
    TEST_FIXTURE(CipherFixture, EmptyString) {
        std::string input1 = "";
        std::string input2 = "";
        CHECK_THROW(cipherInstance->decrypt(input1, input2), CipherError);
    }
    TEST(MaxShiftKey) {
        Cipher cipher(9, "SVERCHKOV");
        std::string input1 = "VOKHCREVS";
        std::string input2 = "SVERCHKOV";
        CHECK_EQUAL("Sverchkov", cipher.decrypt(input1, input2));
    }
}

int main(int argc, char **argv) {
    return UnitTest::RunAllTests();
}
