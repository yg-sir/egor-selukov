#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

using namespace std;

locale loc("ru_RU.UTF-8");
wstring_convert<codecvt_utf8<wchar_t>> codec;

modAlphaCipher::modAlphaCipher(const string& skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;
    key = convert(getValidKey(skey));
    int n = 0;
 for (auto e:key) {
 if (e==0)
 n++;
 }
 if (2*n > key.size())
 throw cipher_error("WeakKey");
}

string modAlphaCipher::encrypt(const string& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    return convert(work);
}

string modAlphaCipher::decrypt(const string& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    return convert(work);
}

inline vector<int> modAlphaCipher::convert(const string& s)
{
    wstring ws = codec.from_bytes(s);
    vector<int> result;
    for (auto c : ws)
        result.push_back(alphaNum[c]);
    return result;
}

inline string modAlphaCipher::convert(const vector<int>& v)
{
    string result;
    wstring ws;
    for (auto i : v)
        ws.push_back(numAlpha[i]);
    result = codec.to_bytes(ws);
    return result;
}

inline string modAlphaCipher::getValidKey(const string& s)
{
    wstring ws = codec.from_bytes(s);
    if (ws.empty())
        throw cipher_error("Пустой ключ");
    
    for (auto& c : ws) {
        if (c < L'А' || c > L'я')
            throw cipher_error(string("Неправильный ключ: ") + s);
        
        if (c >= L'а' && c <= L'я')
            c -= (L'а' - L'А');
    }
    
    return codec.to_bytes(ws);
}

inline string modAlphaCipher::getValidOpenText(const string& s)
{
    wstring tmp;
    wstring ws = codec.from_bytes(s);
    
    for (auto c : ws) {
        if (c >= L'А' && c <= L'я') {
            if (c >= L'а' && c <= L'я')
                tmp.push_back(c - (L'а' - L'А'));
            else
                tmp.push_back(c);
        }
    }
    
    if (tmp.empty())
        throw cipher_error("Отсутствует текст");
    
    return codec.to_bytes(tmp);
}

inline string modAlphaCipher::getValidCipherText(const string& s)
{
    wstring ws = codec.from_bytes(s);

    if (ws.empty())
        throw cipher_error("Пустой текст");

    for (auto c : ws) {
        if ((c < L'А' || c > L'Я') && c != L'Ё')
            throw cipher_error(string("Неправильно зашифрованный текст ") + s);
    }

    return codec.to_bytes(ws);
}
