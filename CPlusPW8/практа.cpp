#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {
    setlocale(0, "rus");
    string inputStr;
    string inputChars;

    cout << "Введите строку: ";
    std::cin >> inputStr;

    cout << "Введите символы для поиска: ";
    std::cin >> inputChars;

    HINSTANCE hLib = LoadLibrary(L"DynamicLib.dll");
    if (hLib == NULL) {
        cerr << "Не удалось загрузить библиотеку!" << endl;
        return 1;
    }

    ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
    if (contains_all_chars == NULL) {
        cerr << "Не удалось получить адрес функции!" << endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

    if (result) {
        cout << "Содержит ли строка \"" << inputStr << "\" символы \"" << inputChars << "\" ?\n";
        cout << "Да." << endl;
    }
    else {
        cout << "Содержит ли строка \"" << inputStr << "\" символы \"" << inputChars << "\" ?\n";
        cout << "Нет." << endl;

    }

    FreeLibrary(hLib);

    return 0;
}