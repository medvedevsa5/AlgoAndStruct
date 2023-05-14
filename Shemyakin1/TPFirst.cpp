#include <algorithm>
#include <fstream>
#include <iostream>
#include <complex>
#include <vector>

#include "DataStruct.h"

void copyTest();
bool isLeftLess(const DataStruct& left, const DataStruct& right);

int main()
{
    copyTest();
}

void copyTest()
{
    std::ifstream inputFile("test.txt");
    std::vector<DataStruct> data;

    int test = 0;
    
    while (!inputFile.eof())
    {
        std::copy(
            std::istream_iterator<DataStruct>(inputFile),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (inputFile.fail() && !inputFile.eof())
        {
            inputFile.clear();
            inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "ERROR: invalid output!" << std::endl;
        }
    }

    std::sort(data.begin(), data.end(), isLeftLess);
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<DataStruct>{std::cout , "\n"});
};

bool isLeftLess(const DataStruct& left, const DataStruct& right)
{
    if (left.key1 < right.key1)
    {
        return true;
    }

    bool isFirstEqual = left.key1 == right.key1;
    if (isFirstEqual)
    {
        bool isSecondLess = std::abs(right.key2) - std::abs(left.key2) > COMPARISON_ACCURACY;
        if (isSecondLess)
        {
            return true;
        }

        bool isSecondEqual = std::abs(std::abs(left.key2) - std::abs(right.key2)) < COMPARISON_ACCURACY;
        if (isSecondEqual)
        {
            bool isThirdLess = left.key3.length() < right.key3.length();
            return isThirdLess;
        }
    }

    return false;
};