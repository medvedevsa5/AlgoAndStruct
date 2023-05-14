#include <iostream>
#include "DictionaryList.h"

int main()
{
    auto dict = new DictionaryArray<std::string>();

    dict->insertWord("12345");
    dict->insertWord("12345");
    dict->insertWord("12345");
    dict->insertWord("12345");
    dict->insertWord("12345");

    dict->insertWord("12345");


    std::cout << *dict;

    return 0;
}
