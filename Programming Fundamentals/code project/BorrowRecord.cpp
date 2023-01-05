#include"BorrowRecord.h"
using namespace std;

void BorrowRecord::getrecord(string k) {
	string A, B, C, D, E, F;
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
	E = D.substr(e + 1);
	f = E.find_first_of(",");
	F = E.substr(0, f);//get return date
	E = D.substr(0, e);//get borrow date
	D = C.substr(0, d);//get book title
	B = A.substr(0, b);//get id
	stringstream ss;
	ss << B;
	ss >> g;
		id = g;
		title = D;
		borrowdate = E;
		returndate = F;
	}
void BorrowRecord::getRecord(string d, string t) {
	int a;
	stringstream s;
	s << d;
	s >> a;
	id = a;
	title = t;

}
void BorrowRecord::putrecord() {
		cout << title << setw(59 - title.length()) << borrowdate << setw(22) << returndate << endl << endl;
	}

void BorrowRecord::putRecord(int u) {
		cout << setw(5) << u << setw(19) << "Book Title:" << setw(16 + title.length()) << title << endl << setw(25) << "Borrow Date:" << setw(15 + borrowdate.length()) << borrowdate << endl << setw(25) << "Return Date:" << setw(15 + returndate.length()) << returndate << endl << endl;
	}

void BorrowRecord::userborrowupdate(string& a, int lie1, int f, int col)
{
	string temp, final, newcon;
	int cont = 0, var = 0;
	vector<string>aa;
	char b[100], c[100];
	strcpy(b, a.c_str());
	char delims[] = ",";
	char* result = NULL;
	char* func = NULL;
	func = strtok(b, delims);
	while (func != NULL)
	{
		var++;//record number of commas
		func = strtok(NULL, delims);
	}
	strcpy(c, a.c_str());
	result = strtok(c, delims);
	string str = to_string(f);
	string sstr = to_string(col);
	switch (lie1) {
	case 1: {
		newcon = str;//put borrow code
		break;
	}
	case 2: {
		stringstream s;
		s << id;
		s >> newcon;
		break;
	}
	case 3: {
		newcon = sstr;//put book code
		break;
	}
	case 4: {
		newcon = title;//put book title
		break;
	}
	case 5: {
		cout << "The Date of Borrow is:" << endl;
		newcon = getTime();//get today's date
		break;
	}
	case 6: {
		cout << "The Date of Return is:" << endl;
		newcon = getreturndate();//get date 2 months later

		break;
	}
	}
	while (result != NULL)
	{
		cont++;
		temp = result;
		if (cont < var)
		{
			temp += ',';
		}
		aa.push_back(temp);// put the "," into every vector
		result = strtok(NULL, delims);
	}
	switch (lie1) {
	case 6: {
		aa[lie1 - 1] = newcon;//for .csv file no ","for the final input
		break;
	}
	default: {
		aa[lie1 - 1] = newcon + ',';
		break;
	}
	}
	for (int ii = 0;ii < aa.size();ii++)
	{
		final += aa[ii];
	}
	a = final;//Change the input into the changed string
	return;
}

void BorrowRecord::returnbook(string& a) {
	string temp, final, newcon, d;
	int e, cont = 0, var = 0;
	vector<string>aa;
	char b[100];
	char c[100];
	strcpy(b, a.c_str());
	char delims[] = ",";
	char* result = NULL;
	char* func = NULL;
	func = strtok(b, delims);
	while (func != NULL)
	{
		var++;
		func = strtok(NULL, delims);
	}
	strcpy(c, a.c_str());
	result = strtok(c, delims);
	d = a;
	stringstream s(d);
	s >> e;
	string str = to_string(e - 1);////The borrow records move up by a place and book code-1
	newcon = str;
	while (result != NULL)
	{
		cont++;
		temp = result;
		if (cont < var)
		{
			temp += ',';
		}
		aa.push_back(temp);
		result = strtok(NULL, delims);
	}
	aa[0] = newcon + ',';
	for (int ii = 0;ii < aa.size();ii++)
	{
		final += aa[ii];
	}
	a = final;//Change the input into the changed string
	return;
}
string BorrowRecord::getTime() {
	time_t t = time(NULL);
	char tmp[11];
	struct tm* ptr;
	ptr = localtime(&t);//get today's date
	strftime(tmp, 11, "%F", ptr);
	puts(tmp);
	return tmp;
}

string BorrowRecord::getreturndate() {
	time_t now = time(NULL);
	char tmp[11];
	struct tm* tm = localtime(&now);
	tm->tm_mon += 2;//get date 2 months later
	strftime(tmp, 11, "%F", tm);
	puts(tmp);
	return tmp;
}