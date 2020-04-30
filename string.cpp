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
	if (data == nullptr)
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
	size = end - begin + 2;
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
	res.SetSize(size + s.length() - 1);
	for (int i = size - 1; i < res.length(); i++)
	{
		res[i] = s[i - size + 1];
	}
	return res;
}

bool String::operator==(const String& s) const
{
	if (size == s.length())
	{
		int i = 0;
		while (data[i] == s[i])
		{
			i++;
		}
		if (i == size - 1)
			return true;
	}
	return false;
}
String& String::operator=(const String& s)
{
	if (*this == s) return *this;
	if (data != nullptr)
		delete[] data;
	size = s.length();
	data = nullptr;
	data = new char[size];
	if (data == nullptr)
		throw "Memmory generation error";
	for (int i = 0; i < size; i++)
		data[i] = s[i];
	return *this;
}

bool String::operator<(const String& s) const
{
	for (int i = 0; i < (size < s.length() ? size : s.length()); i++)
	{
		if (data[i] < s[i]) return true;
		else if (data[i] > s[i]) return false;
	}
	return false;
}

bool String::operator>(const String& s) const
{
	for (int i = 0; i < (size < s.length() ? size : s.length()); i++)
	{
		if (data[i] > s[i]) return true;
		else if (data[i] < s[i]) return false;
	}
	return false;
}
int String::posc(const char c)
{
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			return i;
	return 0;
}
int String::posclast(const char c)
{
	int last = 0;
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			last = i;
	return last;
}
int String::pos(const char* s)
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
int String::poscountc(const char c)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (data[i] == c)
			count++;
	return count;
}
String* String::part(char c) // Доделать
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
String String::repeater(String &s, int n)
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
void String::SetSize(int n)
{
	int copysize = size;
	char* copy = data;
	size = n;
	data = nullptr;
	data = new char[size];
	if (data == nullptr)
		throw "Memmory generation error";
	if (n >= copysize)
	{
		for (int i = 0; i < copysize; i++)
			data[i] = copy[i];
		data[n - 1] = 0;
	}
	else
	{
		for (int i = 0; i < n; i++)
			data[i] = copy[i];
		data[n - 1] = 0;
	}
	delete[] copy;
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
