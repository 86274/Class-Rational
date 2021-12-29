#include <iostream>
#include <exception>
#include <numeric>

// Класс рационального цисла
class Rational
{
public:
    Rational(): m_numerator{}, m_denominator{1} {}
    Rational(int numerator, int denominator); // Параметризированный конструктор. В качестве аргументов принимает числитель и знаменатель.

    int Numerator() const; // Метод возвращает числитель
    int Denominator() const; // Метод возвращает знаменатель

    // Перегрузка оператор и их вспомогательные методы
    Rational operator + (const Rational& y);
    Rational sumRational(Rational x, Rational y);
    Rational operator - (const Rational& y);
    Rational diffRational(Rational x, Rational y);
    Rational operator * (const Rational& y);
    Rational Multiplication(Rational x, Rational y);
    Rational operator / (const Rational& y);
    Rational divisionRational(Rational x, Rational y);

    friend bool operator > (const Rational& x, const Rational& y);
    friend bool operator < (const Rational& x, const Rational& y);
    friend bool operator == (const Rational& x, const Rational& y);
    friend std::istream& operator >> (std::istream& is, Rational& x);
    friend std::ostream& operator << (std::ostream& os, Rational x);

private:
    int m_numerator; // Числитель
    int m_denominator; // Знаменатель

    //Проверка положительное число или нет
    //Если дробь p / q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
    void checkZnak();
    //Сокращение дроби
    void reduction();
    //Приведение к общему знаменателю
    void equalDenominator(Rational& x, Rational& y);

};

Rational::Rational(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("invalid argument");
    }
    m_numerator = numerator;
    m_denominator = denominator;
    checkZnak();
    reduction();
}

int Rational::Numerator() const
{
    return m_numerator;
}

int Rational::Denominator() const
{
    return m_denominator;
}

Rational Rational::operator+(const Rational& y)
{
    return sumRational(*this, y);
}

Rational Rational::sumRational(Rational x, Rational y)
{
    Rational temp;
    equalDenominator(x, y);
    temp.m_numerator = x.m_numerator + y.m_numerator;
    temp.m_denominator = x.m_denominator;
    temp.reduction();
    return temp;
}

Rational Rational::operator-(const Rational& y)
{
    return diffRational(*this, y);
}

Rational Rational::diffRational(Rational x, Rational y)
{
    Rational temp;
    equalDenominator(x, y);
    temp.m_numerator = x.m_numerator - y.m_numerator;
    temp.m_denominator = x.m_denominator;
    temp.checkZnak();
    temp.reduction();
    return temp;
}

bool operator == (const Rational& x, const Rational& y)
{
    return x.m_numerator == y.m_numerator && x.m_denominator == y.m_denominator;
}

Rational operator*(const Rational& x, const Rational& y)
{
    return x * y;
}

Rational Rational::operator*(const Rational& y)
{
    return Multiplication(*this, y);
}

Rational Rational::Multiplication(Rational x, Rational y)
{
    Rational temp;
    temp.m_numerator = x.m_numerator * y.m_numerator;
    temp.m_denominator = x.m_denominator * y.m_denominator;
    temp.checkZnak();
    temp.reduction();
    return temp;
}

Rational operator/(const Rational& x, const Rational& y)
{
    return x / y;
}

Rational Rational::operator/(const Rational& y)
{
    if (y.Numerator() == 0)
    {
        throw std::domain_error("");
    }
    return divisionRational(*this, y);
}

Rational Rational::divisionRational(Rational x, Rational y)
{
    Rational temp;
    temp.m_numerator = x.m_numerator * y.m_denominator;
    temp.m_denominator = x.m_denominator * y.m_numerator;
    temp.checkZnak();
    temp.reduction();
    return temp;
    return Rational();
}

bool operator < (const Rational& x, const Rational& y)
{
    if (x.m_numerator * y.m_denominator < y.m_numerator * x.m_denominator)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator > (const Rational& x, const Rational& y)
{
    if (x.m_numerator * y.m_denominator < y.m_numerator * x.m_denominator)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Rational::checkZnak()
{
    if (m_numerator < 0 && m_denominator < 0)
    {
        m_numerator = abs(m_numerator);
        m_denominator = abs(m_denominator);
    }
    else if (m_denominator < 0)
    {
        m_numerator = -m_numerator;
        m_denominator = abs(m_denominator);
    }
}

void Rational::reduction()
{
    int divider = std::gcd(m_numerator, m_denominator);
    if (divider != 1)
    {
        m_numerator = m_numerator / divider;
        m_denominator = m_denominator / divider;
    }
}

void Rational::equalDenominator(Rational& x, Rational& y)
{
    x.m_numerator *= y.m_denominator;
    y.m_numerator *= x.m_denominator;
    x.m_denominator = y.m_denominator = x.m_denominator * y.m_denominator;
}

std::istream& operator >> (std::istream& is, Rational& x)
{
    int buf = 0, buf2 = 0;
    if (is >> buf)
    {
        char c;
        is >> c;
        if (c == '/')
        {
            if (is >> buf2) {
                x.m_numerator = buf;
                x.m_denominator = buf2;
                x.checkZnak();
                x.reduction();
                return is;
            }
            else
            {
                return is;
            }
        }
        else
        {
            return is;
        }
    }
    else
    {
        return is;
    }
}

std::ostream& operator << (std::ostream& os, Rational x)
{
    os << x.m_numerator << "/" << x.m_denominator;
    return os;
}
