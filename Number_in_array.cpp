/* Напишите программу, которая проверяет, находится ли введенное с клавиатуры число в массиве. 
Массив вводит пользователь во время выполнения программы. */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>  // для превращения строки в число
#include <cctype>   // для посимвольной валидации пользовательского ввода

using std::cout; using std::cin; using std::endl;
using std::vector; using std::string;

// пытается превратить строку в число, выдаёт false, если не получилось
inline bool is_number(const string& str, int& number)
{
	std::istringstream istream(str);
	return (istream >> number) ? true : false;
}

// получаем от пользователя число
int get_number()
{
	cout << "Введите целое число, чтобы проверить, есть ли оно в полученном массиве: ";
	int answer;
	cin >> answer;
	while(cin.fail())
	{
		cout << "Вы ввели не число, попробуйте ещё раз: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> answer;
	}
	return answer;
}

// создаёт массив (точнее вектор) целых чисел из строки, введённой пользователем
vector<int> create_array_from_string(const string& users_input)
{
	vector<int> array{};
	string future_number{}; // будущее число в виде строки
	// будем собирать каждое число по символам-цифрам, каждый пробел добавляем число в массив и начинаем заново
	for (unsigned int i = 0; i < users_input.length(); i++)
	{
		// если после пробела знак минус или просто число
		if (((future_number=="") && (users_input[i]=='-')) || (isdigit(users_input[i])))
			future_number.push_back(users_input[i]);
		// если пробел или конец строки
		if ((users_input[i] == ' ')||(i== (users_input.length()-1)))
		{
			int one_more_number{0};
			if (is_number(future_number, one_more_number))
				array.push_back(one_more_number);
			future_number = "";
		}
	}
	return array;
}

// получаем от пользователя последовательность чисел и, возможно, не только числа в виде строки
string get_users_input()
{
	cout << "Вводите последовательность целых чисел через пробел (прочие знаки будут проигнорированы),\n"
		 << "для окончания ввода нажмите enter: " << endl;
	string input;
	getline(cin,input);
	return input;
}

// проверочная функция печати массива, точнее вектора
void print_array(const vector<int>& array)
{
	if (array.size() == 0)
		cout << "В массиве нет чисел";
	else 
	{
		cout << "Вот, что в массиве: ";
		for (const auto& one_number : array)
			cout << one_number << " ";
	}
	cout << endl;
}

// возвращает истину, если число есть в массиве и ложь - если нет
bool is_number_in_array(const vector<int>& array, const int number_to_find)
{
	for (const auto& number_from_array : array)
		if (number_from_array == number_to_find)
			return true;
	return false;
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // подключаем кириллицу:

	// создаём вектор (массив чисел) по введённым пользователем данным
	vector<int> array = create_array_from_string(get_users_input());

	// проверяем есть ли число от пользователя в массиве, пока ему не надоест
	while (true)
	{ 
		const int number_to_check = get_number();
		if (is_number_in_array(array, number_to_check))
			cout << "Число " << number_to_check << " есть в массиве!" << endl;
		else cout << "Числа " << number_to_check << " в массиве нет!" << endl;
	}
}