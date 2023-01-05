#ifndef BORROWRECORD_H_
#define BORROWRECORD_H_
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#pragma warning(disable : 4996)
using namespace std;
class BorrowRecord {
private:
	int id;
	string title;
	string borrowdate;
	string returndate;
public:
	void getrecord(string k);
	void getRecord(string d,string t);
	void putrecord();
	void putRecord(int u);
	void userborrowupdate(string& a, int lie1, int f, int col);
	void returnbook(string& a);
	string getTime();
	string getreturndate();
};
#endif