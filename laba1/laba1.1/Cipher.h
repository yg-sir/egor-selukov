#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;
class Cipher {
    private:
        int key;
    public:
        Cipher()=delete;
        Cipher(int skey);
        string encrypt(string &text);
        string decrypt(string &text);
};
