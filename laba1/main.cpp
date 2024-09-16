#include "modAlphaCipher.h"
#include <cctype>
#include <iostream>
#include <locale>
using namespace std;
bool isValid(const wstring& s)
{
    locale loc("ru_RU.UTF-8");
    for(auto c : s) {
        if(!isalpha(c, loc) || !isupper(c, loc)) {
            return false;
        }
    }
    return true;
}
int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wstring key, text;
    unsigned op;
    wcout << L"Key: ";
    wcin >> key;
    if(!isValid(key)) {
        wcerr << L"Wrong key" << endl;
        return 1;
    }
    wcout << L"Key upload." << endl;
    modAlphaCipher cipher(key);
    do {
        wcout << L"Что сделать?(0-Выйти, 1-Зашифровать, 2-Расшифровать): ";
        wcin >> op;
        if(op > 2) {
            wcout << L"Неверный номер" << endl;
        } else if(op > 0) {
            wcout << L"Text: ";
            wcin >> text;
            if(isValid(text)) {
                if(op == 1) {
                    wcout << L"Encrypted text: " << cipher.encrypt(text) << endl;
                } else {
                    wcout << L"Decrypted text: " << cipher.decrypt(text) << endl;
                }
            } else {
                wcout << L"Wrong text" << endl;
            }
        }
    } while(op != 0);
    return 0;
}
