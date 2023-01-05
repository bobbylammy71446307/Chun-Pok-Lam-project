#include "User.h"
using namespace std;
	
void User::getuser(string k) {
	string A, B, C, D, E;
	int a, b, c, d, e, f, g;
	a = k.find_first_of(",");
	A = k.substr(a + 1);
	b = A.find_first_of(",");
	B = A.substr(b + 1);
	c = B.find_first_of(",");
	C = B.substr(c + 1);
	d = C.find_first_of(",");
	D = C.substr(d + 1);
	e = D.find_first_of(",");
	E = D.substr(0, e);//find booknum
	D = C.substr(0, d);//find password
	C = B.substr(0, c);//find name
	B = A.substr(0, b);//find id
	stringstream s(E);
	s >> f;
	stringstream ss;
	ss << B;
	ss >> g;
	    name = C;
		id = g;
		password = D;
		booknum = f;
	}

void User::getUser(int r) {
	string x, y, z, k;
	int i, p;
	switch (r) {
	case 1: {
		cout << "Please enter the Student ID of the User:" << endl;
	nter:if (!(cin >> i))//when cin is not number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto nter;
	}
	if (to_string(i).length() != 10)//when cin non-10-digit number
	{
		cout << "The student ID is a 10-digit number!" << endl;
		goto nter;
	}
	id = i;

		break;
	}
	case 2: {
	cout << "Please enter User name:" << endl;
	x = "/n";
	getline(cin, x);
	getline(cin, x);
	while (x == "") //when no input
	{
		cout << "Do not leave input blank!!" << endl;
		getline(cin, x);
	}
	name = x;

	break;
	}
	case 3: {
		cout << "Please enter the password of the User:" << endl;
		getline(cin, z);
		if (z == "")//if z is not initialized enter again 
		{
			getline(cin, z);
		}
		while (z == "")  //when cin is not number
		{
			cout << "Do not leave input blank!!" << endl;
			getline(cin, z);
		}
		password = z;
		break;
	}
	case 4: {
		cout << "Please enter the no. of books borrowed by the User:" << endl;
	aenter:if (!(cin >> p)) //when cin is not number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto aenter;
	}
	while (p < 0) //when cin is smaller than 0
	{
		cout << "Please enter a valid value!" << endl;
		goto aenter;
	}
	booknum = p;
	break;
	}
	}
}
	
void User::putuser(int u) {
		cout << setw(5) << u << setw(19) << "User Name:" << setw(21 + name.length()) << name << endl << setw(30) << "User Student ID:" << setw(15 + to_string(id).length()) << id << endl;
		cout << setw(28) << "User Password:" << setw(17 + password.length()) << password << endl << setw(39) << "Number of Books borrowed:" << setw(6 + to_string(booknum).length()) << booknum << endl << endl << endl;
	}
	
void User::putUser(int u) {
		cout << "User Code:" << setw(22) << u << endl << "User Name:" << setw(21 + name.length()) << name << endl << "User Student ID:" << setw(15 + to_string(id).length()) << id << endl;
		cout << "User Password:" << setw(17 + password.length()) << password << endl << "Number of Books borrowed:" << setw(6 + to_string(booknum).length()) << booknum << endl << endl << endl;
	}

void User::addUser(string& a, int lie1, int f)
{
	string temp, t, final, newcon;
	int cont = 0, ap, ab;
	vector<string>aa;
	char c[100];
	char delims[] = ",";
	char* result = NULL;
	strcpy(c, a.c_str());
	result = strtok(c, delims);

	switch (lie1) {
	case 1: {
		stringstream s;
		s << f;
		s >> t;
		newcon = t;//input User code
		break;
	}
	case 2: {
		stringstream ss;
		ss << id;
		ss >> newcon;
		break;
	}
	case 3: {
    newcon = name;
	break;
	}
	case 4: {
		newcon = password;
		break;
	}
	case 5: {
		newcon = "0";
		break;
	}
	}
	while (result != NULL)
	{
		cont++;
		temp = result;
		if (cont < 5)
		{
			temp += ',';
		}
		aa.push_back(temp);
		result = strtok(NULL, delims);
	}
	aa[lie1 - 1] = newcon + ',';
	for (int ii = 0;ii < aa.size();ii++)
	{
		final += aa[ii];
	}
	a = final;
	return;
}
	
void User::setUser(string& a, int lie1)
{
	string temp, final, newcon;
	int cont = 0,q;
	vector<string>aa;
	char c[100];
	char delims[] = ",";
	char* result = NULL;
	strcpy(c, a.c_str());
	result = strtok(c, delims);
	switch (lie1-1) {
	case 1: {
		stringstream s;
		s << id;
		s >> newcon;
		break;
	break;
	}
	case 2: {
		newcon = name;
		break;
	}
	case 3: {
		newcon = password;
		break;
	}
	case 4: {
	stringstream s;
	s << booknum;
	s >> newcon;
	break;
	}
	default: {
		newcon = "\n";
		getline(cin, newcon);
		getline(cin, newcon);
	}
	}
	while (result != NULL)
	{
		cont++;
		temp = result;
		if (cont < 5)
		{
			temp += ',';
		}
		aa.push_back(temp);
		result = strtok(NULL, delims);
	}
	aa[lie1 - 1] = newcon + ',';
	for (int ii = 0;ii < aa.size();ii++)
	{
		final += aa[ii];
	}
	a = final;
	return;
}



void User::userborrow(string& a)
	{
	    string temp, final, newcon, d;
		int e, cont = 0;
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		string str = to_string(booknum + 1);
		newcon = str;
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 5)
			{
				temp += ',';
			}
			aa.push_back(temp);
			result = strtok(NULL, delims);
		}
		aa[4] = newcon;
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;
		return;
	}

	
void User::userreturnBook(string& a)
	{
	    string temp, final, newcon, d;
		int cont = 0, e; 
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		string str = to_string(booknum - 1);
		newcon = str;
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 5)
			{
				temp += ',';
			}
			aa.push_back(temp);
			result = strtok(NULL, delims);
		}
		aa[4] = newcon;
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;
		return;
	}

