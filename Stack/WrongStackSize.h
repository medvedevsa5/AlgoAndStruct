#pragma once
#include "StackArray.h"
#include <iostream>

class WrongStackSize
{
public:
    static void StackFlowTest()
    {
        StackArray<int>& stack = *new StackArray<int>(); // std size - 128

        try
        {
            for (int i = 1; i < 150; i++)
            {
                stack.push(i);
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what();
        }

        std::cout << std::endl;

        try
        {
            for (size_t i = 1; i < 150; i++)
            {
                stack.pop();
            }
        }
        catch (const std::exception& e)
        {
            std::cout << e.what();
        }

        std::cout << std::endl;
    }
};