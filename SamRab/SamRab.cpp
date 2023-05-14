#include <iostream>
#include "StackArray.h"

using std::string;

void wrongExpression();

bool checkParentheses(std::string& equation);
void getPostfixFromInfix(const string& infix, string& postfix, const size_t stackSize);
bool isOperator(char ch);
int getPriority(char ch);
double evalPostfix(const string& postfix);

int main()
{
    setlocale(LC_ALL, "ru");

    std::string input = "";
    std::string output = "";
    double result = 0;

    std::cin >> input;

    if (!checkParentheses(input))
    {
        wrongExpression();
    }

    try
    {
        getPostfixFromInfix(input, output, input.length());
    }
    catch (std::exception)
    {
        wrongExpression();
    }

    try
    {
        result = evalPostfix(output);
    }
    catch (std::exception)
    {
        wrongExpression();
    }

    std::cout << "Постфиксная запись:" << std::endl;
    std::cout << output << std::endl;

    std::cout << "Результат выражения:" << std::endl;
    std::cout << result << std::endl;
}

void wrongExpression()
{
    std::cerr << "Ошибка! Неверное выражение!";
    exit(1);
}

void getPostfixFromInfix(const string& infix, string& postfix, const size_t stackSize)
{
    StackArray<char> stack(stackSize);

    for (size_t i = 0; i < infix.length(); i++)
    {
        char symbol = infix[i];
        if (isdigit(symbol))
        {
            postfix += symbol;
        }
        else
        {
            if (stack.isEmpty() && isOperator(symbol))
            {
                stack.push(symbol);
            }
            else if (!stack.isEmpty() && isOperator(symbol))
            {
                char tmp = stack.peek();
                while (!stack.isEmpty() && (getPriority(tmp) >= 0 && getPriority(symbol)) && getPriority(tmp) >= getPriority(symbol))
                {
                    postfix += stack.pop();
                    tmp = stack.peek();
                }
                stack.push(symbol);
            }
            else if (symbol == '(')
            {
                stack.push(symbol);
            }
            else if (symbol == ')')
            {
                if (stack.peek() == '(')
                {
                    throw std::exception();
                }
                while (!stack.isEmpty())
                {
                    char buffer = stack.pop();
                    if (buffer == '(')
                    {
                        break;
                    }
                    else
                    {
                        postfix += buffer;
                    }
                }
            }
            else
            {
                throw std::exception();
            }
        }
    }

    while (!stack.isEmpty())
    {
        postfix += stack.pop();
    }
}

double evalPostfix(const string& postfix)
{
    double result = 0;
    StackArray<double> stack(postfix.length());

    for (size_t i = 0; i < postfix.length(); i++)
    {
        if (isdigit(postfix[i]))
        {
            stack.push(postfix[i] - 48);
            continue;
        }
        else if (getPriority(postfix[i]) >= 0)
        {
            double num1 = stack.pop();
            double num2 = stack.pop();
            if (postfix[i] == '+')
            {
                result = num2 + num1;
            }
            else if (postfix[i] == '-')
            {
                result = num2 - num1;
            }
            else if (postfix[i] == '*')
            {
                result = num2 * num1;
            }
            else if (postfix[i] == '/')
            {
                result = num2 / num1;
            }

            stack.push(result);
        }
        else
        {
            throw std::exception();
        }
    }

    result = stack.pop();

    if (!stack.isEmpty())
    {
        throw std::exception();
    }

    return result;
}

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' ||
        ch == '*' || ch == '/';
}

int getPriority(char ch)
{
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    else return -1;
}

bool checkParentheses(std::string& equation)
{
    size_t stringLength = equation.length();
    StackArray<char> stackRoamer(stringLength);

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
            return false;
        }
    }

    return true;
}