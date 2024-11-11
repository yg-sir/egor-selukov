#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

class Cipher {
private:
    int shiftKey;
    inline int validateKey(int shiftKey, const string& text);
    inline string validateOpenText(const string& text);
    inline string validateCipherText(const string& cipherText, const string& openText);
public:
    Cipher() = delete;
    Cipher(int skey, string text);
    string encrypt(const string& text);
    string decrypt(const string& cipherText, const string& openText);
};

class CipherError: public invalid_argument {
public:
    explicit CipherError (const string& what_arg):
        invalid_argument(what_arg) {}
    explicit CipherError (const char* what_arg):
        invalid_argument(what_arg) {}
};
