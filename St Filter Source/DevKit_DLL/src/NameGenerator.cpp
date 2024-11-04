#include "NameGenerator.h"

const wchar_t *tokens1[] = {
        L"Dragon",
        L"Monster",
        L"Evil",
        L"Fire",
        L"Water",
        L"Earth",
        L"Dark",
        L"Fallen",
        L"Undead"
};


const wchar_t *tokens2[] = {
        L"Slayer",
        L"Hunter",
        L"Daemon",
        L"Lord",
        L"King",
        L"Warrior"
};


std::n_wstring GenerateRandomName() {
    std::n_wstring result;

    int tok1 = rand() % ARRAYSIZE(tokens1);
    int tok2 = rand() % ARRAYSIZE(tokens2);
    result = tokens1[tok1];
    result += tokens2[tok2];

    result += rand() % 10000;

    return result;
}
