#include "modAlphaCipher.h"

#include <cctype>
#include <iostream>
#include <locale>

using namespace std;

void check(const string& Text, const string& key, const bool destructCipherText = false)
{
    try {
        string cipherText;
        string decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if(destructCipherText)
            cipherText[1] += 32;
        decryptedText = cipher.decrypt(cipherText);
        cout << "Ключ = " << key << endl;
        cout << Text << endl;
        cout << cipherText << endl;
        cout << decryptedText << endl;
    } catch(const cipher_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

int main()
{
    check("ВЕЛИКИЙХАОС", "КЛЮЧ");
    check("ВЕЛИКИЙХАОС", "Ключ");
    check("ВЕЛИКИЙХАОС", "");
    check("ВЕЛИКИЙХАОС", "Клю4");
    check("Великий хаос", "КЛЮЧ");
    check("123", "КЛЮЧ");
    check("Великий хаос", "КЛЮЧ", true);
    return 0;
}
