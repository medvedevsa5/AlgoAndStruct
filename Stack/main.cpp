#include <iostream>
#include <iomanip>
#include "StackArray.h"
#include "QueueArray.h"
#include "WrongStackSize.h"
#include "WrongQueueSize.h"

bool checkParentheses(std::string equation);
void parenthesesTest();

int main()
{
    parenthesesTest();

    std::cout << "Flows tests:" << std::endl;

    WrongStackSize::StackFlowTest();
    WrongQueueSize::QueueFlowTest();
}

void parenthesesTest()
{
    std::cout << "Parentheses test: " << std::endl;
    std::cout << std::boolalpha
        << checkParentheses("((()))((()))") << '\n' 
        << checkParentheses("{}[{}()]{()}") << '\n'
        << checkParentheses("((()))(((]))") << std::endl;
}

bool checkParentheses(std::string equation)
{
    size_t stringLength = equation.length();
    StackArray<char> stackRoamer (stringLength);

    for (size_t i = 0; i < stringLength; i++)
    {
        try
        {
            if (equation[i] == '(' || 
                equation[i] == '[' || 
                equation[i] == '{')
            {
                stackRoamer.push(equation[i]);
            }
            else if (
                equation[i] == ')' || 
                equation[i] == ']' || 
                equation[i] == '}')
            {
                char character = stackRoamer.pop();
                if (equation[i] == ')' && equation[i] != char(character + 1)) // Разница между закр. и откр. круглыми скобками 1 байт
                {
                    return false;
                }
                else if (equation[i] != ')' && equation[i] != char(character + 2)) // А между остальными два байта
                {
                    return false;
                }
            }
                
        }
        catch (std::exception& e)
        {
            std::cout << e.what();
            return false;
        }
    }

    return true;
}
