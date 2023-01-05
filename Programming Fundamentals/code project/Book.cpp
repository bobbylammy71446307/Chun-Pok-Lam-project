#include"Book.h"
using namespace std;

	void Book::getbook(string k)
	{
		string A, B, C, D, E, F, G, H;
		int a, b, c, d, e, f, g;
			A = k;
			a = A.find_first_of(",");
			B = A.substr(a + 1);
			b = B.find_first_of(",");
			C = B.substr(b + 1);
			c = C.find_first_of(",");
			D = C.substr(c + 1);
			d = D.find_first_of(",");
			E = D.substr(d + 1);
			e = E.find_first_of(",");
			F = E.substr(e + 1);
			f = F.find_first_of(",");
			G = F.substr(f + 1);
			g = G.find_first_of(",");
			H = G.substr(0, g);//get num
			G = F.substr(0, f);//get location
			F = E.substr(0, e);//get publisher
			E = D.substr(0, d);//get isbn
			D = C.substr(0, c);//get author
			C = B.substr(0, b);//get title
			stringstream s;
			s << H;
			s >> a;
		title = C;
		author = D;
		isbn = E;
		publisher = F;
		location = G;
		num = a;
	}

	void Book::getBook(int r) {
		string x, y, z, k, i;
		int p;
		switch (r) {
		case 1: {
			cout << "Please enter Book Title:" << endl;
			x = "/n";
			getline(cin, x);
			getline(cin, x);
			while (x == "") //The input cannot be empty
			{
				cout << "Do not leave input blank!!" << endl;
				getline(cin, x);
			}
			title = x;
			break;
		}
		case 2: {
			cout << "Please enter the Author of the Book:" << endl;
			getline(cin, y);
			if (y == "") //in case y hasnt been initialized
			{
				getline(cin, y);
			}
			while (y == "")  //The input cannot be empty
			{
				cout << "Do not leave input blank!!" << endl;
				getline(cin, y);
			}
			author = y;
			break;
		}
		case 3: {
			cout << "Please enter the ISBN code of the Book:" << endl;
			getline(cin, i);
			if (i == "") //in case z hasnt been initialized
			{
				getline(cin, i);
			}
			while (i == "")  //The input cannot be empty
			{
				cout << "Do not leave input blank!!" << endl;
				getline(cin, i);
			}
			isbn = i;
		    break;
		}
		case 4: {
			cout << "Please enter the publisher of the book:" << endl;
			getline(cin, z);
			if (z == "") //in case z hasnt been initialized
			{
				getline(cin, i);
			}
			while (z == "")  //The input cannot be empty
			{
				cout << "Do not leave input blank!!" << endl;
				getline(cin, z);
			}
			publisher = z;
			break;
		}
		case 5: {
			cout << "Please enter the location of the book:" << endl;
			getline(cin, k);
			if (k == "")//in case k hasnt been initialized
			{
				getline(cin, k);
			}
			while (k == "") //The input cannot be empty
			{
				cout << "Do not leave input blank!!" << endl;
				getline(cin, k);
			}
			location = k;
			break;
		}
		case 6: {
			cout << "Please enter the no. of books on shelf:" << endl;
		aenter:if (!(cin >> p)) //The input must be a number
		{
			cout << "Please enter numbers only." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			goto aenter;
		}
		while (p < 0) //The input must be non-negative
		{
			cout << "Please enter a valid value!" << endl;
			goto aenter;
		}
		num = p;
		break;
		}
		}
	}
	
	void Book::putbook(int u)
	{
		cout << setw(5) << u << setw(19) << "Book Title:" << setw(16 + title.length()) << title << endl << setw(25) << "Book Author:" << setw(15 + author.length()) << author << endl << setw(28) << "Book ISBN code:" << setw(12 + isbn.length()) << isbn << endl;
		cout << setw(28) << "Book Publisher:" << setw(12 + publisher.length()) << publisher << endl << setw(27) << "Book Location:" << setw(13 + location.length()) << location << endl << setw(35) << "No. of Books on shelf:" << setw(5 + to_string(num).length()) << num << endl << endl << endl;
	}
	
	void Book::putBook(int u) 
	{
		cout << "Book Code:" << setw(18) << u << endl << "Book Title:" << setw(16 + title.length()) << title << endl << "Book Author:" << setw(15 + author.length()) << author << endl << "Book ISBN code:" << setw(12 + isbn.length()) << isbn << endl;
		cout << "Book Publisher:" << setw(12 + publisher.length()) << publisher << endl << "Book Location:" << setw(13 + location.length()) << location << endl << "No. of Books on shelf:" << setw(5 + to_string(num).length()) << num << endl << endl << endl;
	}

	void Book::addBook(string& a, int lie1, int f)
	{
		string temp, t, final, newcon;
		int as, cont = 0;
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		stringstream s;
		s << f;
		s >> t;
		switch (lie1) {
		case 1: {
			newcon = t;//Input book code
			break;
		}
		case 2: {
			newcon = title;
			
			break;
		}
		case 3: {
			newcon = author;
			break;
		}
		case 4: {
			newcon = isbn;
		break;
		}
		case 5: {
			newcon = publisher;
			break;
		}
		case 6: {
			newcon = location;
			break;
		}
		case 7: {
		stringstream er;
		er << num;
		er >> newcon;
		break;
		}
		}
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 7)
			{
				temp += ',';
			}
			aa.push_back(temp);//put the "," into every vector
			result = strtok(NULL, delims);
		}
		aa[lie1 - 1] = newcon + ',';
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;//Change the input into the changed string
		return;
	}

	void Book::delBook(string& a)
	{
		string temp, final, newcon, d;
		int cont = 0, e;
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		d = a;
		stringstream s(d);
		s >> e;
		string str = to_string(e - 1);//The book code move up by a place and book code-1
		newcon = str;
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 7)
			{
				temp += ',';
			}
			aa.push_back(temp);//put the "," into every vector
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

	void Book::setBook(string& a, int lie1)
	{
		string temp, final, newcon;
		int r, cont = 0;
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		switch (lie1-1) {
		case 1: {
			newcon = title;
			break;
		}
		case 2: {
			newcon = author;
			break;
		}
		case 3: {
			newcon = isbn;
			break;
		}
		case 4: {
			newcon = publisher;
			break;
		}
		case 5: {
			newcon = location;
			break;
		}
		case 6: {
			stringstream s;
			s << num;
			s >> newcon;
			break;
		}
		}
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 7)
			{
				temp += ',';
			}
			aa.push_back(temp);//put the "," into every vector
			result = strtok(NULL, delims);
		}
		aa[lie1 - 1] = newcon + ',';
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;//Change the input into the changed string
		return;
	}

	void Book::borrowBook(string& a)
	{
		string temp, final, newcon;
		int cont = 0, var = 0;
		vector<string>aa;
		char c[100];
		char delims[] = ",";
		char* result = NULL;
		strcpy(c, a.c_str());
		result = strtok(c, delims);
		string str = to_string(num - 1);
		newcon = str;
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < 7)
			{
				temp += ',';
			}
			aa.push_back(temp);//put the "," into every vector
			result = strtok(NULL, delims);
		}
		aa[6] = newcon;
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;//Change the input into the changed string
		return;
	}
	void Book::returnbookrecord(string& a)
	{
		string temp, final, newcon, d;
		int cont = 0, var = 0, e;
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
		string str = to_string(num + 1);
		newcon = str;
		while (result != NULL)
		{
			cont++;
			temp = result;
			if (cont < var)
			{
				temp += ',';
			}
			aa.push_back(temp);//put the "," into every vector
			result = strtok(NULL, delims);
		}
		aa[6] = newcon;
		for (int ii = 0;ii < aa.size();ii++)
		{
			final += aa[ii];
		}
		a = final;//Change the input into the changed string
		return;
	}