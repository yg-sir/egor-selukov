#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;
class modShifr {
    private:
        int key;
    public:
        modShifr()=delete;
        modShifr(int skey);
        string encrypt(string &text);
        string decrypt(string &text);
};
