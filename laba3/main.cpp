#include <UnitTest++/UnitTest++.h>
#include "modAlphaCipher.h"

SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("СЛССЛ",modAlphaCipher("СЛС").encrypt("ААААА"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("СЛСВИ",modAlphaCipher("СЛСВИПШО").encrypt("ААААА"));
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("СЛССЛ",modAlphaCipher("слс").encrypt("ААААА"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("С1"),cipher_error);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("С,ЛС"),cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("С Л С"),cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"),cipher_error);
    }
}

struct KeyC_fixture {
    modAlphaCipher * p;
    KeyC_fixture()
    {
        p = new modAlphaCipher("С");
    }
    ~KeyC_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyC_fixture, UpCaseString) {
        CHECK_EQUAL("ЪГДЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ", p->encrypt("ИСТИННОСМЕРТНЫЙПЕРЕДБОГОМ"));
    }
    TEST_FIXTURE(KeyC_fixture, LowCaseString) {
        CHECK_EQUAL("ЪГДЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ", p->encrypt("истинносмертныйпередбогом"));
    }
    TEST_FIXTURE(KeyC_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ЪГДЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ", p->encrypt("ИСТИННО СМЕРТНЫЙ ПЕРЕД БОГОМ!"));
    }
    TEST_FIXTURE(KeyC_fixture, StringWithNumbers) {
        CHECK_EQUAL("ГЮЦВДЯМЫБЦВЦХТАФАЮ", p->encrypt("7СМЕРТНЫЙПЕРЕДБОГОМ"));
    }
    TEST_FIXTURE(KeyC_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyC_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("4*4"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ЗРСЗММНРЛДПСМЪИОДПДГАНВНЛ", modAlphaCipher("Я").encrypt("ИСТИННОСМЕРТНЫЙПЕРЕДБОГОМ"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyC_fixture, UpCaseString) {
        CHECK_EQUAL("ИСТИННОСМЕРТНЫЙПЕРЕДБОГОМ", p->decrypt("ЪГДЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ"));
    }
    TEST_FIXTURE(KeyC_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("ъгдЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ"), cipher_error);
    }
    TEST_FIXTURE(KeyC_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ЪГДЪЯЯА ГЮЦВДЯМЫ БЦВЦХ ТАФАЮ"), cipher_error);
    }
    TEST_FIXTURE(KeyC_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("7ГЮЦВДЯМЫБЦВЦХТАФАЮ"), cipher_error);
    }
    TEST_FIXTURE(KeyC_fixture, PunctString) {
        CHECK_THROW(p->decrypt("ЪГДЪЯЯАГЮЦВДЯМЫБЦВЦХТАФАЮ!"), cipher_error);
    }
    TEST_FIXTURE(KeyC_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ИСТИННОСМЕРТНЫЙПЕРЕДБОГОМ", modAlphaCipher("Я").decrypt("ЗРСЗММНРЛДПСМЪИОДПДГАНВНЛ"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
