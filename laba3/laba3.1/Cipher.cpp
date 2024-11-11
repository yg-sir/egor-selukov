#include "Cipher.h"

// Конструктор класса Cipher
Cipher::Cipher(int skey, string text) {
    shiftKey = validateKey(skey, text);
}

// Метод шифрования текста
string Cipher::encrypt(const string& text) {
    string openText = validateOpenText(text);
    int index = 0;
    int numChars = openText.size();
    int numRows = (numChars + shiftKey - 1) / shiftKey;
    char** table = new char* [numRows];
    for (int i = 0; i < numRows; i++)
        table[i] = new char[shiftKey];

    // Заполнение таблицы
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < shiftKey; j++) {
            if (index < numChars) {
                table[i][j] = openText[index];
                index++;
            } else {
                table[i][j] = ' '; // Заполнение пустые ячейки пробелами
            }
        }

    index = 0;
    // Извлечение шифрованного текста из таблицы в обратном порядке по столбцам
    for (int j = shiftKey - 1; j >= 0; j--)
        for (int i = 0; i < numRows; i++) {
            openText[index] = table[i][j];
            index++;
        }

    // Удаление таблицы из памяти
    for (int i = 0; i < numRows; i++)
        delete[] table[i];
    delete[] table;

    return openText;
}

// Метод расшифровки текста
string Cipher::decrypt(const string& cipherText, const string& openText) {
    if (cipherText.empty() || openText.empty()) {
        throw CipherError("Один из текстов пуст!");
    }

    for (char c : cipherText) {
        if (!isalpha(c) && c != ' ') { 
            throw CipherError("Некорректные символы в зашифрованном тексте!");
        }
    }

    for (char c : openText) {
        if (!isalpha(c) && c != ' ') { 
            throw CipherError("Некорректные символы в открытом тексте!");
        }
    }

    string validCipherText = validateCipherText(cipherText, openText);
    int index = 0;
    int numChars = validCipherText.size();
    int numRows = (numChars + shiftKey - 1) / shiftKey;
    char** table = new char* [numRows];
    for (int i = 0; i < numRows; i++)
        table[i] = new char[shiftKey];

    for (int j = shiftKey - 1; j >= 0; j--)
        for (int i = 0; i < numRows; i++) {
            table[i][j] = validCipherText[index];
            index++;
        }

    index = 0;
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < shiftKey; j++) {
            if (table[i][j] != ' ') { 
                validCipherText[index] = table[i][j];
                index++;
            }
        }

    validCipherText.resize(index); // Изменение размера строки для удаления лишних символов

    for (int i = 0; i < numRows; i++)
        delete[] table[i];
    delete[] table;

    return validCipherText;
}

// Валидация зашифрованного текста
inline string Cipher::validateCipherText(const string& cipherText, const string& openText) {
    int r1 = cipherText.size();
    int r2 = openText.size();
    if (r1 != r2) {
        throw CipherError("Неправильный зашифрованный текст: " + cipherText);
    }
    return cipherText;
}

// Валидация и очистка открытого текста
inline string Cipher::validateOpenText(const string& text) {
    string cleanedText = text;

    if (cleanedText.empty()) {
        throw CipherError("Отсутствует открытый текст!");
    }

    cleanedText.erase(remove_if(cleanedText.begin(), cleanedText.end(), [](char c) {
        if (!isalpha(c) && c != ' ') {
            throw CipherError("В тексте встречены некорректные символы!");
        }
        return c == ' ';
    }), cleanedText.end());

    return cleanedText;
}

// Валидация ключа
inline int Cipher::validateKey(int key, const string& text) {
    if (key < 2 || key > text.length()) {
        throw CipherError("Ключ некорректного размера");
    }
    return key;
}
