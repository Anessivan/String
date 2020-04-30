#include <iostream>
class String
{
	int size;
	char* data;
private:
	void SetSize(int n);
public:
	String();
	String(const char* s);
	String(const String& s);
	String(String &s, int begin, int end);
	~String();
	int length() const;
	char& operator[] (int number)const;
	String operator+(const String& s)const;
	bool operator==(const String& s) const;
	String& operator=(const String& s);
	bool operator<(const String& s)const;
	bool operator>(const String& s)const;
	friend std::ostream& operator<< (std::ostream& out, const String& s);
	friend std::istream& operator>> (std::istream& in, String& s);
	int posc(const char c);
	int posclast(const char c);
	int pos(const char* s);
	int poscountc(const char c);
	String* part(char c);
	String repeater(String &s, int n);
};
