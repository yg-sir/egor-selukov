#include <iostream>
#include <string>
#include <Cipher.h>
void check(string Text, int key) {
    string cipherText;
    string decryptedText;
    Cipher cipher(key, Text);
    cipherText = cipher.encryption(Text);
    decryptedText = cipher.transcript(cipherText, Text);
    cout << "Ключ = " << key << endl;
    cout << Text << endl;
    cout << cipherText << endl;
    cout << decryptedText << endl;
}
int main() {
    try {
    check("WhiteBlackWhiteBlack", 6);
    } catch(const cipher_error & e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}
