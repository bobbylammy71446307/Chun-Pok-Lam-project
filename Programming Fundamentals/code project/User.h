#ifndef USER_H_
#define USER_H_
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
class User {
private:
	string name;
	int id;
	string password;
	int booknum;
public:
	void getuser(string k);
	void getUser(int r);
	void putuser(int i);
	void putUser(int u);
	void addUser(string& a, int lie1, int f);
	void setUser(string& a, int lie1);
	void userborrow(string& a);
	void userreturnBook(string& a);
};
#endif
