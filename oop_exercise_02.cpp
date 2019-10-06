/*
Вариант 3
Рациональная (несократимая) дробь представляется парой целых чисел (a, b), где a — числитель, b — знаменатель. Создать класс Rational для работы с рациональными дробями. Обязательно должны быть реализованы операции:
-       сложения add, (a, b) + (c, d) = (ad + bc, bd);
-       вычитания sub, (a, b) – (c, d) = (ad – bc, bd);
-       умножения mul, (a, b) ´ (c, d) = (ac, bd);
-       деления div, (a, b) / (c, d) = (ad, bc);
-       операции сравнения.
Должна быть реализована функция сокращения дроби reduce(), которая обязательно вызывается при выполнении арифметических операций.
Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа Rational.
Кулагин Даниил Николаевич
М8О-201Б-18
*/

#include <iostream>
#include <cstdlib>
class Rational
{
private:
	int chisl; //числитель Рациональной Дроби
	int znamen; //знаменатель Рациональной Дроби
public:
	Rational()
	{
		chisl = 0;
		znamen = 1;
	}

	Rational(int chislitel, int znamenatel)
	{
		set(chislitel, znamenatel);
	}

	Rational operator+(Rational b) //Оператор сложения
	{
		Rational c(chisl * b.znamen + znamen * b.chisl, znamen * b.znamen);
		return c;
	}

	Rational operator-(Rational b) //Оператор вычитания
	{
		Rational c(chisl * b.znamen - znamen * b.chisl, znamen * b.znamen);
		return c;
	}

	Rational operator*(Rational b) //Оператор умножения
	{
		Rational c(chisl * b.chisl, znamen * b.znamen);
		return c;
	}

	Rational operator/(Rational b) //Оператор деления
	{
		if (b.chisl)
		{
			Rational c(chisl * b.znamen, znamen * b.chisl);
			return c;
		}
		else {
			std::cout << "Деление на ноль.\n";
			return Rational();
		}
	}

	int operator==(Rational b) //Оператор равенства
	{
		if (chisl == b.chisl && znamen == b.znamen) return 1;
		else return 0;
	}

	int operator>(Rational b) //Оператор "Больше"
	{
		if (chisl * b.znamen - znamen * b.chisl > 0) return 1;
		else return 0;
	}

	int operator<(Rational b) //Оператор "Меньше"
	{
		if (chisl * b.znamen - znamen * b.chisl < 0) return 1;
		else return 0;
	}

	int get_chisl()
	{
		return chisl;
	}

	int get_znamen()
	{
		return znamen;
	}

	void set(int chislitel, int znamenatel)
	{
		chisl = chislitel;
		if (znamenatel)
			znamen = znamenatel;
		else
		{
			std::cout << "Введённый знаменатель равен нулю.\n";
			chisl = 0;
			znamen = 1;
		}
	}

	int EuclideanAlgorithm(int a, int b) //алгоритм Евклида (поиск НОК)
	{
		if (b == 0)
			return a;
		return EuclideanAlgorithm(b, a % b);
	}

	void reduce() //Сокращение дроби до рациональной
	{
		if (znamen == 1) return;
		int NOK = EuclideanAlgorithm(chisl, znamen);
		while (true)
		{
			if (NOK == 1) break; //Если общих делителей больше нет
			chisl /= NOK;
			znamen /= NOK;
			NOK = EuclideanAlgorithm(chisl, znamen);
		}
		if (znamen < 0) //Если знаменатель отрицателен, то "отправляем" минус в числитель
		{
			chisl *= -1;
			znamen *= -1;
		}
	}
};

Rational operator "" _frac(long double a) { //Реализация пользовательского литерала,
	int test = (int)a;						 //переводящего десятичное число 
	int count = 1;							 //в дробь
	while (test != a) {
		count *= 10;
		a *= 10;
		test = (int)a;
	}
	return Rational((int)a, count);
}



void cout_menu()
{
	std::cout << "Меню команд\n";
	std::cout << "0. Выход\n";
	std::cout << "1. Печать меню\n";
	std::cout << "2. Ввести значение дроби a\n";
	std::cout << "3. Ввести значение дроби b\n";
	std::cout << "4. Сложение дробей a и b\n";
	std::cout << "5. Разность дробей a и b\n";
	std::cout << "6. Произведение дробей a и b\n";
	std::cout << "7. Частное дробей a и b\n";
	std::cout << "8. a == b ???\n";
	std::cout << "9. a > b ???\n";
	std::cout << "10. a < b ???\n";
	std::cout << "11. Пример использования пользовательских литералов\n";
}


int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Программа для работы с рациональной (несократимой) дробью.\n" <<
		"Числа a и b вводит пользователь, число c - результат применения оператора над a и b." << std::endl;
	Rational a, b, c, example1(12.5_frac), example2(1412.25_frac), example3(524.125_frac);
	int action = 1, num, den;
	while (action != 0)
	{
		switch (action)
		{
		case 1: cout_menu(); break;
		case 2: std::cout << "Числитель = "; std::cin >> num;
			std::cout << "Знаменатель = "; std::cin >> den;
			a.set(num, den);
			break;
		case 3:
			std::cout << "Числитель = "; std::cin >> num;
			std::cout << "Знамнатель = "; std::cin >> den;
			b.set(num, den);
			break;
		case 4: c = a + b; break;
		case 5: c = a - b; break;
		case 6: c = a * b; break;
		case 7: c = a / b; break;
		case 8: c.set(a == b, 1); break;
		case 9: c.set(a > b, 1); break;
		case 10: c.set(a < b, 1); break;
		case 11:
			example1.reduce(); example2.reduce(); example3.reduce();
			std::cout << "12.5 = " << example1.get_chisl() << "/" << example1.get_znamen() << " \n";
			std::cout << "1412.25 = " << example2.get_chisl() << "/" << example2.get_znamen() << " \n";
			std::cout << "524.125 = " << example3.get_chisl() << "/" << example3.get_znamen() << " \n"; break;
		default: break;
		}
		a.reduce(); b.reduce(); c.reduce();
		std::cout << "a=" << a.get_chisl() << "/" << a.get_znamen() << " ";
		std::cout << "b=" << b.get_chisl() << "/" << b.get_znamen() << " ";
		std::cout << "c=" << c.get_chisl() << "/" << c.get_znamen() << " \n====>";
		std::cin >> action;
	}
	return 0;
}