#ifndef MATHEXPRESSIONCALCULATOR_H
#define MATHEXPRESSIONCALCULATOR_H

#include <string>
#include "../TypeDefines.h"

class LabelContainer;

/*
 * Грамматика для выражений:
 * A->+E|-E|E
 * E->T{+T|-T}
 * T->F{*F|/F|%F}
 * F->const|name|(A)
 */

// Класс для вычисления математических выражений
class MathExpressionCalculator
{
public:
    explicit MathExpressionCalculator(LabelContainer *labelContainer, Address placingCounter);

    int evaluate(const std::string &expression); // Вычисляет выражение

private:
    // Тип токена
    enum TokenType
    {
        Undefined, // Неопределено
        Name, // Название (метка)
        DecimalConstant, // Числовая десятичная константа
        BinaryConstant, // Числовая двоичная константа
        HexadecimalConstant, // Числовая шестнадцатиричная константа.
        Operator, // Оператор (+-*/%)
        Delimiter, // Разделитель
        PlacingCounter, // Счетчик размещения
        End, // Конец анализа
    };

    LabelContainer *m_labelContainer; // Контейнер меток
    Address m_placingCounter; // Адрес для счетчика размещений

    std::string m_expression; // Математическое выражение в виде строки (пробелы удалены)
    std::string::iterator m_expressionIt; // Итератор по выражению
    TokenType m_tokenType; // Тип токена
    std::string m_token; // Токен

    bool expressionEmpty() const; // Проверяет выражение на пустоту
    bool itAtEnd() const; // Проверяет, дошел ли итератор до конца выражения

    void updateToken(); // Обновляет значения m_token и m_tokenType
    void collectOperator(); // Собирает оператор
    void collectBracket(); // Собирает скобку
    void collectDecimal(); // Собирает десятичную константу
    void collectHexadecimal(); // Собирает шестнадцатиричную константу
    void collectBinary(); // Собирает двоичную константу
    void collectLabel(); // Собирает метку
    void collectPlacingCounter(); // Собирает символ счетчика размещений

    bool isOperator(char c) const; // Проверяет, является ли символ знаком операции
    bool isBracket(char c) const; // Проверяет, является ли символк скобкой
    bool isDecimalDigit(char c) const; // Проверяет, является ли символ цифрой
    bool isDelimiter(char c) const; // Проверяет, является ли символ разделителем (оператором или скобкой)
    bool isX(char c) const; // Проверяет, является ли символ 'x' или 'X'
    bool isB(char c) const; // Проверяет, является ли символ 'b' или 'B'
    bool isAlpha(char c) const; // Проверяет, является ли символ буквой
    bool isBinaryDigit(char c) const; // Проверяет, является ли символ '1' или '0'
    bool isHexadecimalDigit(char c) const; // Проверяет, является ли символ шестнадцатиричной цифрой
    bool isPlacingCounter(char c) const; // Проверяет, что символ является символом '@'
    bool isLabel(char c) const; // Символ относится к имени метки

    void atom(int &value, int &sign);
    void expr(int &value, int &sign);
    void term(int &value, int &sign);
    void factor(int &value, int &sign);
    void val(int &value, int &sign);
};

#endif // MATHEXPRESSIONCALCULATOR_H
