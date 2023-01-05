#ifndef MENU_H_
#define MENU_H_
#include <iostream>
#include <vector>
#include <fstream>
#include "Book.h"
#include"BorrowRecord.h"
#include"User.h"
using namespace std;
class menu
{
public:
	BorrowRecord br;
	Book bk;
	User us;
	void loginmenu();
	void Administrator(); 
	void useroperator(string iid);
	void userlogin();
};
#endif

