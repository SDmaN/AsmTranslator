#include <algorithm>
#include <iostream>
#include <sstream>
#include <bitset>

#include "MathExpressionCalculator.h"
#include "Utils.h"
#include "../ErrorsHandling/Exceptions/ArgumentIncorrectException.h"

MathExpressionCalculator::MathExpressionCalculator(LabelContainer *labelContainer, Address placingCounter)
        : m_labelContainer(labelContainer), m_placingCounter(placingCounter)
{
}

int MathExpressionCalculator::evaluate(const std::string &expression)
{
    m_expression = expression; // Сохраняем выражение
    removeSpaces(m_expression); // Удаляем пробелы

    // Если выражение пустое, бросаем исключение об ошибке
    if(expressionEmpty())
    {
        throw ArgumentIncorrectException(expression);
    }

    m_expressionIt = std::begin(m_expression); // Начинаем анализ с начала выражения

    updateToken();

    int value = 0;
    int sign = 1;
    atom(value, sign); // Начали вычисления

    if(m_tokenType != TokenType::End)
    {
        throw ArgumentIncorrectException(m_expression);
    }

    return value;
}

bool MathExpressionCalculator::expressionEmpty() const
{
    return m_expression.empty();
}

bool MathExpressionCalculator::itAtEnd() const
{
    return m_expressionIt == std::end(m_expression);
}

void MathExpressionCalculator::updateToken()
{
    m_tokenType = TokenType::Undefined; // Возвращаемый тип токена

    // Если дошли до конца выражения
    if(itAtEnd())
    {
        m_tokenType = TokenType::End;
    }
    else
    {
        char c = *m_expressionIt;

        // Нашли оператор
        if(isOperator(c))
        {
            collectOperator();
        }
        else if(isBracket(c)) // Нашли скобку
        {
            collectBracket();
        }
        else if(isDecimalDigit(c)) // Нашли десятичную константу
        {
            collectDecimal();
        }
        else if(isAlpha(c)) // Метка или недесятичная константа
        {
            m_token = c; // Опасно. Сбор начинается до вызова соответствующего метода
            ++m_expressionIt;

            if(isX(c)) // Возможно шестнадцатиричная константа
            {
                collectHexadecimal();
            }

            else if(isB(c)) // Возможно двоичная константа
            {
                collectBinary();
            }
            else
            {
                collectLabel(); // Метка, начинающаяся с буквы
            }
        }
        else if(isLabel(c))
        {
            collectLabel(); // Метка со знака '_'
        }
        else if(isPlacingCounter(c))
        {
            collectPlacingCounter();
        }
    }
}

void MathExpressionCalculator::collectOperator()
{
    m_token = *m_expressionIt; // Сохранили оператор в качестве токена
    m_tokenType = TokenType::Operator;

    ++m_expressionIt; // К следующему символу
}

void MathExpressionCalculator::collectBracket()
{
    m_token = *m_expressionIt; // Сохранили скобку в качестве токена
    m_tokenType = TokenType::Delimiter;

    ++m_expressionIt;
}

void MathExpressionCalculator::collectDecimal()
{
    m_token = *m_expressionIt;
    ++m_expressionIt;

    while(!itAtEnd() && !isDelimiter(*m_expressionIt))
    {
        // Собираем только десятичное число
        if(!isDecimalDigit(*m_expressionIt))
        {
            throw ArgumentIncorrectException(m_expression);
        }

        m_token += *m_expressionIt;
        ++m_expressionIt;
    }

    m_tokenType = TokenType::DecimalConstant;
}

void MathExpressionCalculator::collectHexadecimal()
{
    m_tokenType = TokenType::HexadecimalConstant; // Может смениться на метку

    while(!itAtEnd() && !isDelimiter(*m_expressionIt))
    {
        char c = *m_expressionIt;

        // Попалось не шестнадцатиричное число.
        // Проверяем на метку или ошибку
        if(!isHexadecimalDigit(c))
        {
            // Все же нашли метку (например x10g5 - допустимое имя метки, но не константы)
            if(isLabel(c))
            {
                collectLabel();
                break;
            }
            else
            { // Иначе точно ошибка
                throw ArgumentIncorrectException(m_expression);
            }
        }

        m_token += c;
        ++m_expressionIt;
    }
}

void MathExpressionCalculator::collectBinary()
{
    m_tokenType = TokenType::BinaryConstant;

    while(!itAtEnd() && !isDelimiter(*m_expressionIt))
    {
        char c = *m_expressionIt;

        // Если не двоичное число
        if(!isBinaryDigit(c))
        {
            // Все же нашли метку (например b10g1 - допустимое имя метки, но не константы)
            if(isLabel(c))
            {
                collectLabel();
                break;
            }
            else
            {
                throw ArgumentIncorrectException(m_expression);
            }
        }

        m_token += c;
        ++m_expressionIt;
    }
}

void MathExpressionCalculator::collectLabel()
{
    m_tokenType = TokenType::Name; // Тип токена - метка
    char c;

    while(!itAtEnd() && !isDelimiter(*m_expressionIt))
    {
        c = *m_expressionIt;

        // Не символ метки, то ошибка
        if(!isLabel(c))
        {
            throw ArgumentIncorrectException(m_expression);
        }

        m_token += c;
        ++m_expressionIt;
    }
}

void MathExpressionCalculator::collectPlacingCounter()
{
    m_token = *m_expressionIt; // Сохранили скобку в качестве токена
    m_tokenType = TokenType::PlacingCounter;

    ++m_expressionIt;
}

bool MathExpressionCalculator::isOperator(char c) const
{
    const std::string operators = "+-*/%";

    // Ищем наш символ в строке операторов
    return std::find(std::begin(operators), std::end(operators), c) != std::end(operators);
}

bool MathExpressionCalculator::isBracket(char c) const
{
    return c == '(' || c == ')';
}

bool MathExpressionCalculator::isDecimalDigit(char c) const
{
    return isdigit(c);
}

bool MathExpressionCalculator::isDelimiter(char c) const
{
    return isBracket(c) || isOperator(c);
}

bool MathExpressionCalculator::isX(char c) const
{
    return c == 'x' || c == 'X';
}

bool MathExpressionCalculator::isB(char c) const
{
    return c == 'b' || c == 'B';
}

bool MathExpressionCalculator::isAlpha(char c) const
{
    return isalpha(c);
}

bool MathExpressionCalculator::isBinaryDigit(char c) const
{
    return c == '1' || c == '0';
}

bool MathExpressionCalculator::isHexadecimalDigit(char c) const
{
    const std::string hexDigits = "1234567890abcdefABCDEF";
    return std::find(std::begin(hexDigits), std::end(hexDigits), c) != std::end(hexDigits);
}

bool MathExpressionCalculator::isPlacingCounter(char c) const
{
    return c == '@';
}

bool MathExpressionCalculator::isLabel(char c) const
{
    return isAlpha(c) || isDecimalDigit(c) || c == '_';
}

void MathExpressionCalculator::atom(int &value, int &sign)
{
    if(m_tokenType == TokenType::Operator)
    {
        if(m_token == "-")
        {
            sign = -1;
        }
        else if(m_token == "+")
        {
            sign = +1;
        }

        updateToken();
    }

    expr(value, sign);
}

void MathExpressionCalculator::expr(int &value, int &sign)
{
    int tmp = 0;
    term(value, sign);

    while(m_token == "+" || m_token == "-")
    {
        char op = m_token[0];
        updateToken();
        term(tmp, sign);

        switch(op)
        {
            case '-':
                value -= tmp;
                break;

            case '+':
                value += tmp;
                break;
        }
    }
}

void MathExpressionCalculator::term(int &value, int &sign)
{
    int tmp = 0;
    factor(value, sign);

    while(m_token == "*" || m_token == "/" || m_token == "%")
    {
        char op = m_token[0];
        updateToken();
        factor(tmp, sign);

        switch(op)
        {
            case '*':
                value *= tmp;
                break;

            case '/':
                if(tmp == 0)
                {
                    throw ArgumentIncorrectException(m_expression);
                }

                value /= tmp;
                break;

            case '%':
                if(tmp == 0)
                {
                    throw ArgumentIncorrectException(m_expression);
                }

                value %= tmp;
                break;
        }
    }
}

void MathExpressionCalculator::factor(int &value, int &sign)
{
    if(m_token == "(")
    {
        updateToken();
        atom(value, sign);

        if(m_token != ")")
        {
            throw ArgumentIncorrectException(m_expression);
        }
    }
    else
    {
        val(value, sign);
    }

    updateToken();
}

void MathExpressionCalculator::val(int &value, int &sign)
{
    switch(m_tokenType)
    {
        case Name:
            break;

        case DecimalConstant:
        {
            std::stringstream ss;
            ss << m_token;
            ss >> value;

            break;
        }

        case BinaryConstant:
        {
            std::bitset<sizeof(value)> bs(m_token.substr(1));
            value = static_cast<int>(bs.to_ulong());
            break;
        }

        case HexadecimalConstant:
        {
            std::stringstream ss;
            ss << m_token.substr(1);
            ss >> value;

            break;
        }

        case PlacingCounter:
            value = m_placingCounter;
            break;
    }

    value *= sign;
    sign = 1;
}