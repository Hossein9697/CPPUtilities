#include "math/MathUtility.hpp"

int MathUtility::div(int number1, int number2)
{
    if (number2 == 0)
        return -1;
    return (number1 / number2);
}

bool MathUtility::isOdd(int number)
{
    return (number % 2);
}

bool MathUtility::isEven(int number)
{
    return !isOdd(number);
}
