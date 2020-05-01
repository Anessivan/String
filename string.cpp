#include "String.h"
#include <iostream>
String::String()
{
	data = new char[1];
	data[0] = 0;
	size = 1;
}

String::String(const char* s)
{
	data = nullptr;
	size = strlen(s) + 1;
	data = new char[size + 1];
	if (data == nullptr) //проверка выделения памяти
		throw "Memmory generation error";
	for (int i = 0; i < size; i++)
	{
		data[i] = s[i];
	}
	data[size] = 0;
}

String::String(const String& s)
{
	data = nullptr;
	size = s.length();
	data = new char[size];
	if (data == nullptr)
		throw "Memmory generation error";
	for (int i = 0; i < size; i++)
		data[i] = s[i];
}
String::String(String& s, int begin, int end)
{
	data = nullptr;
	size = end - begin + 2;// рассчет нового размера строки(из последнего номера начальный + последний символ + место для 0)
	data = new char[size];
	if (data == nullptr)
		throw "Memmory generation error";
	for (int i = 0; i < size; i++)
		data[i] = s[begin + i];
	data[size] = 0;
}
String::~String()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	size = 0;
}

int String::length() const
{
	return size;
}

char& String::operator[](int number) const
{
	return data[number];
}

String String::operator+(const String& s) const
{
	String res(*this);
	res.SetSize(size + s.length() - 1);//изменение размера объекта на необходимый
	for (int i = size - 1; i < res.length(); i++)
	{
		res[i] = s[i - size + 1];//К изначальному объекту приписывается строка s
	}
	return res;
}

bool String::operator==(const String& s) const
{
	if (size == s.length())// сравнение размеров
	{
		int i = 0;
		while (data[i] == s[i])//поэлементное сравнение
		{
			i++;
		}
		if (i == size - 1) //Если счетчик совпавших подряд символов совпал с размером строк, то выражение истинно
			return true;
	}
	return false;
}
String& String::operator=(const String& s)
{
	if (*this == s) return *this;// проверка на самокопирование
	if (data != nullptr)//очистка памяти изначального объекта
		delete[] data;
	size = s.length();
	data = nullptr;
	data = new char[size]; // выделение необходимого количества памяти для новых данных
	if (data == nullptr)
		throw "Memmory generation error";
	for (int i = 0; i < size; i++)
		data[i] = s[i];
	return *this;
}

bool String::operator<(const String& s) const
{
	for (int i = 0; i < (size < s.length() ? size : s.length()); i++) // сравнение символов с нулевого по размер наименьшей строки
	{
		if (data[i] < s[i]) return true;
		else if (data[i] > s[i]) return false;
	}
	return false;
}

bool String::operator>(const String& s) const
{
	for (int i = 0; i < (size < s.length() ? size : s.length()); i++) //сравнение символов с нулевого по размер наименьшей строки
	{
		if (data[i] > s[i]) return true;
		else if (data[i] < s[i]) return false;
	}
	return false;
}
int String::posc(const char c) // Поиск первого вхождения символа в строку, возвращает номер этого символа
{
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			return i;
	return 0;
}
int String::posclast(const char c)//Поиск последнего вхождения символа в строке возвращает номер этого символа
{
	int last = 0;
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			last = i;
	return last;
}
int String::pos(const char* s) //Поиск первого вхождения подстроки в строку
{
	int sizechar = strlen(s);
	int count = 0;
	int i;
	for (i = sizechar; i < size; i++)
	{
		if (data[i] == s[i])
			count++;
		else
			count = 0;
		if (count == sizechar)
			break;
	}
	if (count == sizechar)
		return i - count;
	return 0;
}
int String::poscountc(const char c) // Поиск количества вхождений символа в строку
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			count++;
	return count;
}
String* String::part(char c) // Разбиение строки на подстроки по символу. Возвращает массив строк
{
	int count = this->poscountc(c);
	String* res = new String[count + 1];
	res[0] = *this;
	for (int i = 1; i < count; i++)
	{
		String s(res[i - 1], res[i - 1].posc(c) + 1, res[i - 1].posclast(c));
		res[i] = s;
		res[i - 1].SetSize(res[i - 1].posc(c));
	}
	return res;
}
String String::repeater(String &s, int n)// Метод, дублирующий строку n раз
{
	if (s.length() == 0)
		throw "Length = 0";
	String res(s);
	for (int i = 0; i < n - 1; i++)
	{ 
		res = res + s;
	}
	return res;
}
void String::SetSize(int n)// Метод изменения размера объекта
{
	if(size != n)
	{
	int copysize = size; 
	char* copy = data; // сохранение изначальных данных
	size = n;
	data = nullptr;
	data = new char[size];
	if (data == nullptr)
		throw "Memmory generation error";
	if (n >= copysize) //Случай, когда мы меняем размер памяти на больший
	{
		for (int i = 0; i < copysize; i++)
			data[i] = copy[i];
		data[n - 1] = 0;
	}
	else //Случай, когда мы изменям размер на меньший
	{
		for (int i = 0; i < n; i++)
			data[i] = copy[i];
		data[n - 1] = 0;
	}
	delete[] copy;
	}
	else 
		std::cout << "Same size" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.data << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, String& s)
{
	char get[256];
	in.getline(get, 256);
	String right(get);
	s = right;
	return in;
}
