#include"Menu.h"
using namespace std;
	
void menu::loginmenu() {
		cout << "Please select the service you wish to perform" << endl << endl;
		cout << "[1] Login as User" << endl << endl;
		cout << "[2] Login as Administrator" << endl << endl;
		cout << "[3] Exit System" << endl << endl;
		int command;
	rrre:if (!(cin >> command)) //Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto rrre;
	}
	switch (command) {
	case 1: {
		userlogin();
		break;
	}
	case 2: {
		cout << "Please enter password" << endl;
		string pass;
	rcin:cin >> pass;
		if (pass=="123456") { 
			system("cls");
			Administrator(); 
		}
		else {
			cout << "Incorrect password, please ensure you have entered the correct password" << endl;
			goto rcin;
		}
	break;
	}
	case 3: {
		cout << "Thank you for using this system----exiting system" << endl;;
		system("pause");
		exit(0);
		break;
	}
	default: {
		cout << "Command Error!Please enter command again " << endl;
		goto rrre;
	}
	}
	}
	
void menu::userlogin(){
		string line, Line, k, id, o, t, u, v, password;
		int i, a, c, d, e;
		int flag = 0;
		vector<string>neirong;
		ifstream infile("user.csv");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
		cout << "Please enter your student id:" << endl;
		cin >> id;
		for (i = 0;i < flag;i++) {
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1, 10);//get id
			if (o == id)
			{
				break;
			}
		}
		while (i == flag)//if no match id
		{
			cout << "No such user, please input valid user student id: " << endl;
			cin >> id;
			for (i = 0;i < flag;i++) {
				k = neirong[i];
				a = k.find_first_of(",");
				o = k.substr(a + 1, 10);
				if (o == id) {
					break;
				}
			}
		}
		cout << "Please type in your password: " << endl;
		password = "\n";
		getline(cin, password);
		getline(cin, password);
		k = neirong[i];
		a = k.find_first_of(",");
		o = k.substr(a + 1);
		c = o.find_first_of(",");
		t = o.substr(c + 1);
		d = t.find_first_of(",");
		u = t.substr(d + 1);
		e = u.find_first_of(",");
		v = u.substr(0, e);//get password
		while (v != password) {
			cout << "Incorrect password! Please try again!" << endl;
			getline(cin, password);
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1);
			c = o.find_first_of(",");
			t = o.substr(c + 1);
			d = t.find_first_of(",");
			u = t.substr(d + 1);
			e = u.find_first_of(",");
			v = u.substr(0, e);//get password
		}
		system("cls");
		cout << "You have successfully logged into the system!" << endl;
		useroperator(id);
	}
	
void menu::Administrator() {
	amenu:string line, Line, id, K, k, O, o, T, t, U, u, V, v, P, p, S, password, info, temp, j;
		int col, row, i, com, A, a, C, c, D, d, E, e, F, f, G, g, H, flag = 0, Flag = 0, comma = 0, I = 0, l = 0;
		vector<string>neirong;
		vector<string>Neirong;
		ifstream infile("book.csv");
		ifstream iinfile("user.csv");
		cout << "Please select the service you wish to perform" << endl << endl;
		cout << "[1] Add new book to database" << endl << endl;
		cout << "[2] Delete book in database" << endl << endl;
		cout << "[3] Find book in database" << endl << endl;
		cout << "[4] Edit book in database" << endl << endl;
		cout << "[5] Create User" << endl << endl;
		cout << "[6] Search User" << endl << endl;
		cout << "[7] Edit user" << endl << endl;
		cout << "[8] Logout System" << endl << endl;
		cout << "[9] Exit System" << endl << endl;
		int command;
	cincom:if (!(cin >> command)) //Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto cincom;
	}
	switch (command) {
	case 1: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;//count for the new book code
			neirong.push_back(line);
		}
		infile.close();
		cout << "Book Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			bk.getbook(k);
			bk.putbook(i+1);//display book info
		}
		neirong.pop_back();
		neirong.push_back("  ,  ,  ,  ,  ,  ,  ");
		for (int k = 1;k <= 7;k++) {
			bk.getBook(k);
			bk.addBook(neirong[flag - 1], k, flag);//add book record
		}
		ofstream onfile("book.csv");
		for (int l = 0;l < neirong.size();l++)
		{
			onfile << neirong[l] << endl;
		}
		onfile.close();
		cout << "The book has been successfully added!" << endl;
		system("pause");
		system("cls");
		goto amenu;
		break;
	}
	case 2: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
	go:cout << "Book Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			bk.getbook(k);
			bk.putbook(i+1);//display book info
		}
		cout << "Please enter the Book Code of the book you wish to delete: " << endl;
	iter: if (!(cin >> col))//Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto iter;
	}
	while (col >= flag || col <= 0) {
		cout << "Please enter valid input!" << endl;
		cin >> col;
	}
	system("cls");
	cout << "Book Code:" << endl;
	k = neirong[col - 1];
	bk.getbook(k);
	bk.putbook(col);//display info of book to be deleted 
	cout << "You will be deleting the book shown above " << endl;
	cout << "[1] Choose another book" << endl;
	cout << "[2] Continue" << endl;
iiter: if (!(cin >> row))//Input must be number
{
	cout << "Please enter numbers only." << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	goto iiter;
}
if (row == 1) {
	system("cls");
	goto go;
}
neirong.erase(neirong.begin() + col - 1);
for (int r = col;r < flag - 1;r++) {
	bk.delBook(neirong[r - 1]);//Change book code
}
ofstream onfile("book.csv");
neirong.pop_back();
for (int l = 0;l < neirong.size();l++)
{
	onfile << neirong[l] << endl;
}
onfile.close();
cout << "You have successfully delete the record!" << endl;
system("pause");
system("cls");
goto amenu;
break;
	}
	case 3: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
	search:cout << "Please select your serch type:" << endl;
		cout << "[1]Search by book title" << endl;
		cout << "[2]Search by author name" << endl;
		cout << "[3]Return to last page" << endl;
	reenter:if (!(cin >> com))//Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto reenter;
	}
	switch (com) {
	case 1: {
		cout << "Please enter the book title:" << endl;
		k = "\n";
		getline(cin, k);
	reeenter:getline(cin, k);
		if (k == "") //Input cannot be empty
		{
			cout << "Do not leave input blank!!" << endl;
			goto reeenter;
		}
		cout << endl << endl;
		int I = 0;
		char in_array[100];
		strcpy(in_array, k.c_str());
		for (i = 0;i < flag - 1;i++) {
			o = neirong[i];
			a = o.find_first_of(",");
			t = o.substr(a + 1);
			c = t.find_first_of(",");
			u = t.substr(0, c);//get book title
			char out_array[100];
			strcpy(out_array, u.c_str());
			if (strstr(out_array, in_array) != NULL)//check whether the title match
			{
				bk.getbook(o);
				bk.putBook(i+1);
				I++;
			}
		}
		if (I == 0) //When no suitable title
		{
			cout << "No results found, please check to see if you have enter the correct spelling" << endl;
			goto reeenter;
		}
		system("pause");
		system("cls");
		goto search;
		break;
	}
	case 2: {
		cout << "Please enter the name of the Author:" << endl;
		k = "\n";
		getline(cin, k);
	reeeenter:getline(cin, k);
		if (k == "") //Input cannot be empty
		{
			cout << "Do not leave input blank!!" << endl;
			goto reeeenter;
		}
		int I = 0;
		char in_array[100];
		strcpy(in_array, k.c_str());
		for (i = 0;i < flag - 1;i++) {
			o = neirong[i];
			a = o.find_first_of(",");
			t = o.substr(a + 1);
			c = t.find_first_of(",");
			u = t.substr(c + 1);
			d = u.find_first_of(",");
			v = u.substr(0, d);//get author
			char out_array[100];
			strcpy(out_array, v.c_str());
			if (strstr(out_array, in_array) != NULL)//check whether the author match
			{
				bk.getbook(o);
				bk.putBook(i+1);
				I++;
			}
		}
		if (I == 0) // When no suitable author
		{
			cout << "No results found, please check to see if you have enter the correct spelling" << endl;
			goto reeeenter;
		}
		system("pause");
		system("cls");
		goto search;
		break;
	}
	case 3: {
		system("cls");
		goto amenu;
		break;
	}
	default: {
		cout << "Command Error!!PLease enter again" << endl;
		goto reenter;
	}
	}
	}
	case 4: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
		cout << "Book Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			bk.getbook(k);
			bk.putbook(i+1);
		}
		cout << "Please enter the Book Code of the book you wish to edit" << endl;
	cim:if (!(cin >> col)) // Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto cim;
	}
	if (col >= flag || col <= 0)//check whether input is valid
	{
		cout << "Please enter valid input!" << endl;
		goto cim;
	}
	system("cls");
	k = neirong[col - 1];
	bk.getbook(k);
	bk.putBook(col);
	cout << "Please enter the variables u wish to change:" << endl;
	cout << "[1] Book Title" << endl;
	cout << "[2] Author " << endl;
	cout << "[3] ISBN " << endl;
	cout << "[4] Publisher " << endl;
	cout << "[5] Location" << endl;
	cout << "[6] Number of Books " << endl;
com:if (!(cin >> row))//Input must be number
{
	cout << "Please enter numbers only." << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	goto com;
}
if (row < 1 || row>6) //Check for valid input
{
	cout << "Please enter valid input!" << endl;
	goto com;
}
cout << "Input new data!" << endl;
bk.getBook(row);
bk.setBook(neirong[col - 1], row + 1);//input changed data 
neirong.pop_back();
ofstream onfile("book.csv");
for (int l = 0;l < neirong.size();l++)
{
	onfile << neirong[l] << endl;
}
onfile.close();
cout << "You have successfully changed the record!" << endl;
system("pause");
system("cls");
goto amenu;
break;
	}
	case 5: {
		system("cls");
		while (iinfile.good())
		{
			getline(iinfile, line);
			flag++;
			neirong.push_back(line);
		}
		iinfile.close();
		cout << "User Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			us.getuser(k);
			us.putuser(i+1);
		}
		neirong.pop_back();
		neirong.push_back("  ,  ,  ,  ,  ");
		for (int k = 1;k <= 5;k++) {
			if (k != 4) {
				us.getUser(k);
			}
			us.addUser(neirong[flag - 1], k, flag);//create new record
		}
		ofstream onfile("user.csv");
		for (int l = 0;l < neirong.size();l++)
		{
			onfile << neirong[l] << endl;
		}
		onfile.close();
		cout << "You have successfully added the user!" << endl;
		system("pause");
		system("cls");
		goto amenu;
		break;
	}
	case 6: {
		system("cls");
		while (iinfile.good())
		{
			getline(iinfile, line);
			flag++;
			neirong.push_back(line);
		}
		iinfile.close();
		ifstream Infile("userborrow.csv");
		while (Infile.good())
		{
			getline(Infile, Line);
			Flag++;
			Neirong.push_back(Line);
		}
		Infile.close();
	ssearch:cout << "Please seclect your search type" << endl << endl;
		cout << "[1]Search by id" << endl;
		cout << "[2]Search by name" << endl;
		cout << "[3]Return to last page" << endl;
	rreenter:if (!(cin >> com))//Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto rreenter;
	}
	switch (com) {
	case 1: {
		cout << "Please enter the student ID of the user:" << endl;
		cin >> id;
		for (i = 0;i < flag;i++) {
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1, 10);//get id
			if (o == id) {
				break;
			}
		}
		while (i == flag) //no match id
		{
			cout << "No such user, please input valid user student id: " << endl;
			cin >> id;
			for (i = 0;i < flag;i++) {
				k = neirong[i];
				a = k.find_first_of(",");
				o = k.substr(a + 1, 10);//get id
				if (o == id) {
					break;
				}
			}
		}
		cout << endl << endl;
		k = neirong[i];
		a = k.find_first_of(",");
		o = k.substr(a + 1);
		c = o.find_first_of(",");
		t = o.substr(c + 1);
		d = t.find_first_of(",");
		u = t.substr(d + 1);
		e = u.find_first_of(",");
		v = u.substr(e + 1);
		f = v.find_first_of(",");
		p = v.substr(0, f);//get booknum
		t = o.substr(0, c);//get id
		stringstream s(p);
		s >> g;
		us.getuser(k);
		us.putUser(i+1);
		if (g == 0)//if no borrow record
		{
			cout << "He/She have no borrow records..." << endl << endl;
		}
		else {
			cout << "His/Her borrow records: " << endl << endl;
			cout << "Book Title" << setw(50) << "Borrow Date" << setw(20) << "Return Date" << endl << endl;
			for (I = 0;I < Flag;I++) {
				K = Neirong[I];
				A = K.find_first_of(",");
				O = K.substr(A + 1);
				C = O.find_first_of(",");
				T = O.substr(C + 1);
				D = T.find_first_of(",");
				U = T.substr(D + 1);
				E = U.find_first_of(",");
				V = U.substr(E + 1);
				F = V.find_first_of(",");
				P = V.substr(F + 1);
				H = P.find_first_of(",");
				T = O.substr(0, C);//get id
				if (T == t) {
					br.getrecord(K);
					br.putrecord();
				}
			}
		}
		system("pause");
		system("cls");
		goto ssearch;
		break;
	}
	case 2: {
		cout << "Please enter the name of the user:" << endl;
		id = "\n";
		getline(cin, id);
	again:getline(cin, id);
		if (id == "") //Input cannot be blank
		{
			cout << "Do not leave input blank!!" << endl;
			goto again;
		}
		char in_array[100];
		strcpy(in_array, id.c_str());
		cout << endl;
		for (i = 0;i < flag;i++) {
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1);
			c = o.find_first_of(",");
			t = o.substr(c + 1);
			d = t.find_first_of(",");
			u = t.substr(d + 1);
			e = u.find_first_of(",");
			v = u.substr(e + 1);
			f = v.find_first_of(",");
			p = v.substr(0, f);
			u = t.substr(0, d);//get name
			t = o.substr(0,c);//get id
			stringstream s;
			s << p;
			s >> g;
			char out_array[100];
			strcpy(out_array, u.c_str());
			if (strstr(out_array, in_array) != NULL) {
				us.getuser(k);
				us.putUser(i+1);
				if (g == 0) //when the user do hv borrow record
				{
					cout << "He/she has no borrow records..." << endl << endl;
				}
				else {
					cout << "His/Her borrow records: " << endl << endl;
					cout << "Book Title" << setw(50) << "Borrow Date" << setw(20) << "Return Date" << endl << endl;
					for (I = 0;I < Flag;I++) {
						K = Neirong[I];
						A = K.find_first_of(",");
						O = K.substr(A + 1);
						C = O.find_first_of(",");
						T = O.substr(0, C);//get id
						if (T == t) {
							br.getrecord(K);
							br.putrecord();
						}
					}
				}
				l++;
			}
		}
		if (l == 0) //When no suitable records
		{
			cout << "No results found, please check to see if you have enter the correct spelling" << endl;
			goto again;
		}
		system("pause");
		system("cls");
		goto ssearch;
		break;
	}
	case 3: {
		cout << "Redirecting..." << endl;
		system("cls");
		goto amenu;
		break;
	}
	default: {
		cout << "Command Error!!Please enter again" << endl;
		goto rreenter;
		break;
	}
	}
	}
	case 7: {
		system("cls");
		while (iinfile.good())
		{
			getline(iinfile, line);
			flag++;
			neirong.push_back(line);
		}
		iinfile.close();
		cout << "User Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			us.getuser(k);
			us.putuser(i+1);
		}
		cout << "Please enter the user code of the user you wish to edit" << endl;
	cm:if (!(cin >> col))//Input must be number
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto cm;
	}
	if (col >= flag || col <= 0) //Check for valid input
	{
		cout << "Please enter the correct user code" << endl;
		goto cm;
	}
	system("cls");
	k = neirong[col - 1];
	us.getuser(k);
	us.putuser(col);
	cout << "Please enter the variables u wish to change :" << endl;
	cout << "[1] Student id" << endl;
	cout << "[2] Student name " << endl;
	cout << "[3] Password " << endl;
	cout << "[4] Number of books borrowed " << endl;
dm:if (!(cin >> row)) //Input must be number
{
	cout << "Please enter numbers only." << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	goto dm;
}
if (row <= 0 || row > 4)//Check for valid input
{
	cout << "Please enter valid commands" << endl;
	goto dm;
}
cout << "Input new data!" << endl;
us.getUser(row);
us.setUser(neirong[col - 1], row + 1);//update data
neirong.pop_back();
ofstream onfile("user.csv");
for (int l = 0;l < neirong.size();l++)
{
	onfile << neirong[l] << endl;
}
onfile.close();
cout << "You have successfully changed the profile of the user" << endl;
system("pause");
system("cls");
goto amenu;
break;
	}
	case 8: {
		cout << "Logging out..." << endl;
		system("pause");
		system("cls");
		loginmenu();
		break;
	}
	case 9: {
		cout << "Thank you for using this system----exiting system" << endl;
		system("pause");
		exit(0);
		break;
	}
	default: {
		cout << "Command Error?Please try again" << endl;
		goto cincom;
	}
	}
	}
	
void menu::useroperator(string iid) {
	umenu:string line, Line, lline, id, k, kk, K, O, o, oo, tt, t, T, U, u, V, v, P, p, S, password, info;
		int col, row, com, command,i, A, a, aa, b, bb, s, z, ii, uu, C, c, D, d, E, e, F, f, G, g, H, flag = 0, Flag = 0, fflag = 0, q = 0, l = 0, I = 0;
		vector<string>neirong;
		vector<string>Neirong;
		vector<string>nneirong;
		ifstream iinfile("userborrow.csv");
		ifstream infile("book.csv");
		ifstream innfile("user.csv");
		cout << "Please select the service you wish to perform" << endl << endl;
		cout << "[1] Borrow a book" << endl << endl;
		cout << "[2] Return a book" << endl << endl;
		cout << "[3] Find book in database" << endl << endl;
		cout << "[4] Show user" << endl << endl;
		cout << "[5] Edit user information" << endl << endl;
		cout << "[6] Logout System" << endl << endl;
		cout << "[7] Exit System" << endl << endl;
	rreenter:if (!(cin >> command))
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto rreenter;
	}
	switch (command) {
	case 1: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
		while (innfile.good())
		{
			getline(innfile, Line);
			Flag++;
			Neirong.push_back(Line);
		}

		innfile.close();
		for (I = 0;I < Flag;I++) {
			K = Neirong[I];
			A = K.find_first_of(",");
			O = K.substr(A + 1, 10);
			if (O == iid) {
				break;
			}
		}
		cout << "Book Code:" << endl;
		for (i = 0;i < flag - 1;i++) {
			k = neirong[i];
			bk.getbook(k);
			bk.putbook(i+1);
		}
		cout << "Please enter the Book Code of the book you wish to borrow: " << endl;
	tr:if (!(cin >> col)) //Input numbers only
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto tr;
	}
	while (col >= flag || col <= 0) {
		cout << "Your entry is invalid, please enter again:" << endl;
		goto tr;
	}
	k = neirong[col - 1];
	a = k.find_last_of(",");
	o = k.substr(a + 1);

	while (o == "0") {
		cout << "The Library currently does not have the book you wish to borrow, please choose another book" << endl;
		goto tr;
	}
	bk.getbook(k);
	bk.borrowBook(neirong[col - 1]);
	neirong.pop_back();
	ofstream onfile("book.csv");
	for (int l = 0;l < neirong.size();l++)
	{
		onfile << neirong[l] << endl;
	}
	onfile.close();
	K = Neirong[I];
	us.getuser(K);
	us.userborrow(Neirong[I]);
	Neirong.pop_back();
	ofstream outfile("user.csv");
	for (int l = 0;l < Neirong.size();l++)
	{
		outfile << Neirong[l] << endl;
	}
	outfile.close();

	while (iinfile.good())
	{
		getline(iinfile, lline);
		fflag++;
		nneirong.push_back(lline);
	}
	iinfile.close();
	nneirong.pop_back();
	nneirong.push_back("  ,  ,  ,  ,  ,  ,  ");
	kk = neirong[col - 1];
	aa = kk.find_first_of(",");
	oo = kk.erase(0, aa + 1);
	bb = oo.find_first_of(",");
	tt = oo.substr(0, bb);	
	br.getRecord(iid, tt);
	for (int k = 1;k <= 6;k++) {
		br.userborrowupdate(nneirong[fflag - 1], k, fflag, col);//Compile borrow records
	}
	ofstream oonfile("userborrow.csv");
	for (int l = 0;l < nneirong.size();l++)
	{
		oonfile << nneirong[l] << endl;
	}
	oonfile.close();
	cout << "You have successfully borrowed the book!" << endl;
	system("pause");
	system("cls");
	goto umenu;
	break;
	}
	case 2: {
		system("cls");
		while (iinfile.good())
		{
			getline(iinfile, line);
			flag++;
			neirong.push_back(line);
		}
		iinfile.close();
		for (s = 0;s < flag; s++) {
			k = neirong[s];
			a = k.find_first_of(",");
			o = k.substr(a + 1, 10);
			if (o == iid) {
				break;
			}
		}
		if (s == flag) {
			cout << "You do not have a borrow record, you will be directed back to the previous page " << endl;
			goto umenu;
		}
		cout << "Borrow Code:" << endl;
		while (q < flag) {
			k = neirong[q];
			a = k.find_first_of(",");
			o = k.substr(a + 1);
			c = o.find_first_of(",");
			t = o.substr(0, c);
			if (t == iid) {
				br.getrecord(k);
				br.putRecord(q+1);//display borrow records of student
			}
			q++;
		}
		cout << "Please enter the borrow code of the book you wish to return: " << endl;
	rr:if (!(cin >> col)) {
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto rr;
	}
	if (col >= flag) {
		cout << "Invalid code! Please enter again!" << endl;
		goto rr;
	}
	k = neirong[col - 1];
	a = k.find_first_of(",");
	o = k.substr(a+1);
	c = o.find_first_of(",");
	u = o.substr(c + 1);
	d = u.find_first_of(",");
	v = u.substr(0, d);
	u = o.substr(0, c);
	o = k.substr(0, a);
	stringstream sss;
	sss << v;
	sss >> uu;
	if (u != iid) {
		cout << "The code does not sync your borrow record, please enter again" << endl;
		goto rr;
	}
	if (col >= flag) {
		cout << "Invalid code! Please enter again!" << endl;
		goto rr;
	}
	while (infile.good())
	{
		getline(infile, lline);
		fflag++;
		nneirong.push_back(lline);
	}
	infile.close();
	neirong.erase(neirong.begin() + col - 1);
	for (int r = col;r < flag - 1;r++) {
		br.returnbook(neirong[r - 1]);//update borrow records borrow codes
	}
	ofstream onfile("userborrow.csv");
	neirong.pop_back();
	for (int l = 0;l < neirong.size();l++)
	{
		onfile << neirong[l] << endl;
	}
	onfile.close();

	ifstream innfile("user.csv");
	while (innfile.good())
	{
		getline(innfile, Line);
		Flag++;
		Neirong.push_back(Line);
	}

	innfile.close();

	for (I = 0;I < Flag;I++) {
		K = Neirong[I];
		A = K.find_first_of(",");
		O = K.substr(A + 1, 10);
		if (O == iid) {
			break;
		}
	}

	K = Neirong[I];
	us.getuser(K);
	us.userreturnBook(Neirong[I]);//change user booknum
	Neirong.pop_back();
	ofstream onnfile("user.csv");
	for (int l = 0;l < Neirong.size();l++)
	{
		onnfile << Neirong[l] << endl;
	}
	onnfile.close();
	k = nneirong[uu - 1];
	bk.getbook(k);
	bk.returnbookrecord(nneirong[uu - 1]);//change book avaliable number
	nneirong.pop_back();
	ofstream oonfile("book.csv");
	for (int l = 0;l < nneirong.size();l++)
	{
		oonfile << nneirong[l] << endl;
	}
	oonfile.close();
	cout << "You have successfully returned the book!" << endl;
	system("pause");
	system("cls");
	goto umenu;
	break;
	}
	case 3: {
		system("cls");
		while (infile.good())
		{
			getline(infile, line);
			flag++;
			neirong.push_back(line);
		}
		infile.close();
	search:cout << "Please select your serch type:" << endl;
		cout << "[1]Search by book title" << endl;
		cout << "[2]Search by author name" << endl;
		cout << "[3]Return to last page" << endl;
	reenter:if (!(cin >> com))//Input must be numbers
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto reenter;
	}
	switch (com) {
	case 1: {
		cout << "Please enter the book title:" << endl;
		k = "\n";
		getline(cin, k);
	reeenter:getline(cin, k);
		if (k == "") {
			cout << "Do not leave input blank!!" << endl;
			goto reeenter;
		}
		int I = 0;
		char in_array[100];
		strcpy(in_array, k.c_str());
		for (i = 0;i < flag - 1;i++) {
			o = neirong[i];
			a = o.find_first_of(",");
			t = o.substr(a + 1);
			c = t.find_first_of(",");
			u = t.substr(0, c);//get book title
			char out_array[100];
			strcpy(out_array, u.c_str());
			if (strstr(out_array, in_array) != NULL) {
				bk.getbook(o);
				bk.putBook(i+1);
				I++;
			}
		}
		if (I == 0) {
			cout << "No results found, please check to see if you have enter the correct spelling" << endl;
			goto reeenter;
		}
		system("pause");
		system("cls");
		goto search;
		break;
	}
	case 2: {
		cout << "Please enter the name of the Author:" << endl;
		k = "\n";
		getline(cin, k);
	reeeenter:getline(cin, k);
		if (k == "") {
			cout << "Do not leave input blank!!" << endl;
			goto reeeenter;
		}
		int I = 0;
		char in_array[100];
		strcpy(in_array, k.c_str());
		for (i = 0;i < flag - 1;i++) {
			o = neirong[i];
			a = o.find_first_of(",");
			t = o.substr(a + 1);
			c = t.find_first_of(",");
			u = t.substr(c + 1);
			d = u.find_first_of(",");
			v = u.substr(0, d);
			char out_array[100];
			strcpy(out_array, v.c_str());
			if (strstr(out_array, in_array) != NULL) {
				bk.getbook(o);
				bk.putBook(i+1);//display book info
				I++;
			}
		}
		if (I == 0) {
			cout << "No results found, please check to see if you have enter the correct spelling" << endl;
			goto reeeenter;
		}
		system("pause");
		system("cls");
		goto search;
		break;
	}
	case 3: {
		system("cls");
		goto umenu;
		break;
	}
	default: {
		cout << "Command Error!!PLease enter again" << endl;
		goto reenter;
	}
	}
	}
	case 4: {
		system("cls");
		while (innfile.good())
		{
			getline(innfile, line);
			flag++;//???? 
			neirong.push_back(line);
		}
		innfile.close();
		for (i = 0;i < flag;i++) {
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1, 10);
			if (o == iid) {
				break;
			}
		}
		k = neirong[i];
		a = k.find_first_of(",");
		u = k.substr(a + 1);
		b = u.find_first_of(",");
		v = u.substr(b + 1);
		c = v.find_first_of(",");
		oo = v.substr(c + 1);
		d = oo.find_first_of(",");
		kk = oo.substr(d + 1);
		e = kk.find_first_of(",");
		K = kk.substr(0, e);//get booknum
		us.getuser(k);
		us.putUser(i+1);
		stringstream s;
		s << K;
		s >> g;
		ifstream Infile("userborrow.csv");
		while (Infile.good())
		{
			getline(Infile, Line);
			Flag++;
			Neirong.push_back(Line);
		}
		Infile.close();
		cout << "Your borrow records are: " << endl << endl;
		if (g == 0) {
			cout << "You have no borrow records..." << endl;
		}
		else {
			cout << "Book Title" << setw(50) << "Borrow Date" << setw(20) << "Return Date" << endl << endl;
			for (I = 0;I < Flag;I++) {
				K = Neirong[I];
				A = K.find_first_of(",");
				O = K.substr(A + 1);
				C = O.find_first_of(",");
				T = O.substr(0, C);
				if (T == iid) {
					br.getrecord(K);
					br.putrecord();//display borrow records
				}
			}
		}
		system("pause");
		system("cls");
		goto umenu;
		break;
	}
	case 5: {
		system("cls");
		while (innfile.good())
		{
			getline(innfile, line);
			flag++;
			neirong.push_back(line);
		}
		innfile.close();
		for (i = 0;i < flag;i++) {
			k = neirong[i];
			a = k.find_first_of(",");
			o = k.substr(a + 1, 10);
			if (o == iid) {
				break;
			}
		}
		k = neirong[i];
		a = k.find_first_of(",");
		o = k.substr(0, a);
		stringstream s(o);
		s >> col;
		cout << "Please enter the information you wish to edit" << endl;
		cout << "[1] Student Name " << endl;
		cout << "[2] Password " << endl;
	rrr:if (!(cin >> row)) //input must be numbers
	{
		cout << "Please enter numbers only." << endl;
		cin.clear();
		cin.ignore(10000, '\n');
		goto rrr;
	}
	if (row < 1 || row>2)
	{
		cout << "Command Error! Please enter again!" << endl;
		goto rrr;
	}	
	cout << "input new data!" << endl;
	us.getUser(row+1);
	us.setUser(neirong[col - 1], row + 2);//change data
	neirong.pop_back();
	ofstream onfile("user.csv");
	for (int l = 0;l < neirong.size();l++)
	{
		onfile << neirong[l] << endl;
	}
	onfile.close();
	cout << "You have successfully edited your profile!" << endl;
	system("pause");
	system("cls");
	goto umenu;
	break;
	}
	case 6: {
		cout << "Logging out..." << endl;
		system("pause");
		system("cls");
		loginmenu();
		break;
	}
	case 7: {
		cout << "Thank you for using this system----exiting system" << endl;
		system("pause");
		exit(0);
		break;
	}
	default: {
		cout << "Command Error!Please try again" << endl;
		goto rreenter;
	}
	}
	}

