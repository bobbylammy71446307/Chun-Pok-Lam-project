#ifndef BOOK_H_
#define BOOK_H_
#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
class Book {
private:
	string title;
	string author;
	string isbn;
	string publisher;
	string location;
	int num;
public:

	void getbook(string k);
	void getBook(int k);
	void putbook(int u);
	void putBook(int u);
	void addBook(string& a, int lie1, int f);
	void delBook(string& a);
	void setBook(string& a, int lie1);
	void borrowBook(string& a);
	void returnbookrecord(string& a);
};
#endif
