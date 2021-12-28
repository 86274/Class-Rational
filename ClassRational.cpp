#include <iostream>
#include <exception>
#include <numeric>

using namespace std;

// Класс рационального цисла
class Rational
{
public:
	Rational();
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
	friend bool operator== (const Rational& x, const Rational& y);
	friend std::istream& operator >> (std::istream& is, Rational& x);
	friend std::ostream& operator << (std::ostream& os, Rational x);

private:
	int p; // Числитель
	int q; // Знаменатель 

	//Проверка положительное число или нет
	//Если дробь p / q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
	void checkZnak();
	//Сокращение дроби 
	void reduction();
	//Приведение к общему знаменателю
	void equalDenominator(Rational& x, Rational& y);

};


Rational::Rational()
{
	p = 0;
	q = 1;
}

Rational::Rational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument("invalid argument");
	}
	p = numerator;
	q = denominator;
	checkZnak();
	reduction();
}

int Rational::Numerator() const
{
	return p;
}

int Rational::Denominator() const
{
	return q;
}

Rational Rational::operator+(const Rational& y)
{
	return sumRational(*this, y);
}

Rational Rational::sumRational(Rational x, Rational y)
{
	Rational temp;
	equalDenominator(x, y);
	temp.p = x.p + y.p;
	temp.q = x.q;
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
	temp.p = x.p - y.p;
	temp.q = x.q;
	temp.checkZnak();
	temp.reduction();
	return temp;
}

bool operator == (const Rational& x, const Rational& y)
{
	return x.p == y.p && x.q == y.q;
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
	temp.p = x.p * y.p;
	temp.q = x.q * y.q;
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
		throw domain_error("");
	}
	return divisionRational(*this, y);
}

Rational Rational::divisionRational(Rational x, Rational y)
{
	Rational temp;
	temp.p = x.p * y.q;
	temp.q = x.q * y.p;
	temp.checkZnak();
	temp.reduction();
	return temp;
	return Rational();
}

bool operator < (const Rational& x, const Rational& y)
{
	if (x.p * y.q < y.p * x.q)
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
	if (x.p * y.q < y.p * x.q)
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
	if (p < 0 && q < 0)
	{
		p = abs(p);
		q = abs(q);
	}
	else if (q < 0)
	{
		p = -p;
		q = abs(q);
	}
}

void Rational::reduction()
{
	int divider = std::gcd(p, q);
	if (divider != 1)
	{
		p = p / divider;
		q = q / divider;
	}
}

void Rational::equalDenominator(Rational& x, Rational& y)
{
	x.p *= y.q;
	y.p *= x.q;
	x.q = y.q = x.q * y.q;
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
				x.p = buf;
				x.q = buf2;
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
	os << x.p << "/" << x.q;
	return os;
}
