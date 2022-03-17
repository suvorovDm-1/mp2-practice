#include <cstdio>
#include <string>

#include <iostream>
#include "polinom.h"
#include "monom.h"

int main() {
	setlocale(LC_ALL, "Russian");
	TPolinom result;
	std::string s1, s2;
	std::cout << "Введите 1-й полином. Пример - 3х^5y^2z^5-5x^4y^3z^3+7x^3y^5z" << std::endl;
	std::cin >> s1;
	std::cout << "Введите 2-й полином. Пример - 4x^3y^2z^6-6x^2yz^8" << std::endl;
	std::cin >> s2;
	TPolinom p1(s1);
	TPolinom p2(s2);
	int menu = 1;
	std::cout << "Меню:" << endl;
	std::cout << "1. Сумма полиномов" << endl;
	std::cout << "2. Разность полиномов" << endl;
	std::cout << "3. Умножение 1-го полинома на число" << endl;
	std::cout << "4. Умножение 2-го полинома на число" << endl;
	std::cout << "5. Произведение полиномов" << endl;
	std::cout << "6. Вывести результат" << endl;
	std::cout << "7. Удалить результат" << endl;
	std::cin >> menu;
	while (menu < 7 && menu > 0)
	{
		switch (menu)
		{
		case 1:
		{
			result = p1 + p2;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 2:
		{
			result = p1 - p2;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 3:
		{
			double b1;
			std::cout << "Введите число, на которые Вы хотите умножить полином" << std::endl;
			std::cin >> b1;
			result = p1 * b1;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 4:
		{
			double b2;
			std::cout << "Введите число, на которые Вы хотите умножить полином" << std::endl;
			std::cin >> b2;
			result = p2 * b2;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 5:
		{
			result = p1 * p2;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 6:
		{
			std::cout << result;
			std::cout << "3x^5y^2z^5 - 5x^4y^3z^3 + 7x^3y^5z + 4x^3y^2z^6 - 6x^2yz^8 = 1-й + 2-й" << endl;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		case 7:
		{
			string s = "0xyz";
			TPolinom Null(s);
			result = Null;
			std::cout << "Меню:" << endl;
			std::cout << "1. Сумма полиномов" << endl;
			std::cout << "2. Разность полиномов" << endl;
			std::cout << "3. Умножение 1-го полинома на число" << endl;
			std::cout << "4. Умножение 2-го полинома на число" << endl;
			std::cout << "5. Произведение полиномов" << endl;
			std::cout << "6. Вывести результат" << endl;
			std::cout << "7. Удалить результат" << endl;
			std::cin >> menu;
			break;
		}
		default:exit(1);
		}
	}
	return 0;
}