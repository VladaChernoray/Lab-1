
#include <iostream>
#include <fstream>
#include <string>
#include<time.h>
#include <random>
#include <cmath>
#include <sstream>
#include <vector>
#include <Windows.h>

using namespace std;

struct tim {
	int day;
	int year;
	int mounth;
	int hour;
	int min;
};   
/**/
struct train {
	int ID;
	int number;
	string name;
	string type;
	tim dep;
	tim arr;
	double popularity;
};
/**/
int getmaxid(vector<train> data);
vector<train> filetovector(fstream& file);
void readvecor(vector<train> data);
vector<train> filetovectorbin(fstream& fil);
tim addrandomtime(tim tr)
{
	tim t = tr;
	random_device rd;
	mt19937 gen(rd());
	int pd, ph, pm;
	t.day += gen() % 5;
	t.hour += gen() % 12;
    t.min += gen() % 60;
	if (t.min > 59) {
		t.min -= 60;
		t.hour += 1;
	}
	if (t.hour > 11) {
		t.hour -= 12;
		t.day += 1;
	}
	switch (t.mounth) {
	case 2:
		if (t.day > 28) {
			t.day -= 28;
			t.mounth++;
		}

		break;
	case 4:
		if (t.day > 30) {
			t.day -= 30;
			t.mounth++;
		}

		break;
	case 6:
		if (t.day > 30) {
			t.day -= 30;
			t.mounth++;
		}

		break;
	case 9:
		if (t.day > 30) {
			t.day -= 30;
			t.mounth++;
		}

		break;
	case 11:
		if (t.day > 30) {
			t.day -= 30;
			t.mounth++;
		}

		break;

	default:
		if (t.day > 31) {
			t.day -= 31;
			t.mounth++;
		}
	}
	if (t.mounth > 12) {
		t.mounth -= 12;
		t.year++;
	}
	return t;
}
/**/

void add(fstream& file, train tr, int id) {
	file.open("fout.txt", ios::in | ios::out | ios::app);
	file.clear();
	file.seekg(0);
	

	file << id << " ";
	if (tr.number < 1000) file << "0";
	if (tr.number < 100) file << "0";
	if (tr.number < 10) file << "0";
	file << tr.number << " ";
	file << tr.name << " ";
	file << tr.type <<" ";
	file << tr.dep.year << " ";
	if (tr.dep.day < 10) file << "0";
	file << tr.dep.day << " ";
	if (tr.dep.mounth < 10) file << "0";
	file << tr.dep.mounth << " "; 
	if (tr.dep.hour <10)file << "0";
	file << tr.dep.hour << " ";
	if (tr.dep.min < 10)file << "0";
	file << tr.dep.min;

	file << " ";
	file << tr.arr.year << " ";
	if (tr.arr.day < 10) file << "0";
	file << tr.arr.day << " ";
	if (tr.arr.mounth < 10) file << "0";
	file << tr.arr.mounth << " ";
	if (tr.arr.hour < 10)file << "0";
	file << tr.arr.hour << " ";
	if (tr.arr.min < 10)file << "0";
	file << tr.arr.min << " "; 
	file << tr.popularity <<endl;
	
};
/**/


void addbin(fstream& fil, train tr, int id)
{
	fil.open("foutbin.txt", ios::in | ios::out | ios::app|ios::binary);
	fil.clear();
	fil.seekg(0);
	fil.write((char*)& id, sizeof(int));
	fil.write((char*)& tr.number, sizeof(int));
	int a= tr.name.length();
	fil.write((char*)& a, sizeof(int));
	fil << tr.name;
	int b = tr.type.length();
	fil.write((char*)& b, sizeof(int));
	fil << tr.type;
	fil.write((char*)& tr.dep.year, sizeof(int));
	fil.write((char*)& tr.dep.day, sizeof(int));
	fil.write((char*)& tr.dep.mounth, sizeof(int));
	fil.write((char*)& tr.dep.hour, sizeof(int));
	fil.write((char*)& tr.dep.min, sizeof(int));

	fil.write((char*)& tr.arr.year, sizeof(int));
	fil.write((char*)& tr.arr.day, sizeof(int));
	fil.write((char*)& tr.arr.mounth, sizeof(int));
	fil.write((char*)& tr.arr.hour, sizeof(int));
	fil.write((char*)& tr.arr.min, sizeof(int));

	fil.write((char*)& tr.popularity, sizeof(double));
	
};
void readbin(fstream& fil) {
	fil.clear();
	fil.seekg(0);
	vector<train> data;
	while (!fil.eof())
	{

		//std::cout << fil.tellg() << endl;

		train tr;
		fil.read((char*)& tr.ID, sizeof(int));
		fil.read((char*)& tr.number, sizeof(int));
		//cout << fil.tellg() << endl;
		int a;
		char ch;
		fil.read((char*)& a, sizeof(int));
		for (int i = 0;i <= a - 1;i++) {
			fil.get(ch);
			tr.name += ch;
		}
		int b;
		fil.read((char*)& b, sizeof(int));
		for (int i = 0;i <= b - 1;i++) {
			fil.get(ch);
			tr.type += ch;
		}

		fil.read((char*)& tr.dep.year, sizeof(int));
		fil.read((char*)& tr.dep.day, sizeof(int));
		fil.read((char*)& tr.dep.mounth, sizeof(int));
		fil.read((char*)& tr.dep.hour, sizeof(int));
		fil.read((char*)& tr.dep.min, sizeof(int));

		fil.read((char*)& tr.arr.year, sizeof(int));
		fil.read((char*)& tr.arr.day, sizeof(int));
		fil.read((char*)& tr.arr.mounth, sizeof(int));
		fil.read((char*)& tr.arr.hour, sizeof(int));
		fil.read((char*)& tr.arr.min, sizeof(int));

		fil.read((char*)& tr.popularity, sizeof(double));
		cout << tr.ID << " ";
	if (tr.number < 1000) cout << "0";
		if (tr.number < 100) cout << "0";
		if (tr.number < 10) cout << "0";
		cout << tr.number << " ";
		cout << tr.name << " ";
		cout << tr.type << " ";
		cout << tr.dep.year << " ";
		if (tr.dep.day < 10) cout << "0";
		cout << tr.dep.day << " ";
		if (tr.dep.mounth < 10) cout << "0";
		cout << tr.dep.mounth << " ";
		if (tr.dep.hour < 10)cout << "0";
		cout << tr.dep.hour << " ";
		if (tr.dep.min < 10)cout << "0";
		cout << tr.dep.min;

		cout << " ";
		cout << tr.arr.year << " ";
		if (tr.arr.day < 10) cout << "0";
		cout << tr.arr.day << " ";
		if (tr.arr.mounth < 10) cout << "0";
		cout << tr.arr.mounth << " ";
		if (tr.arr.hour < 10)cout << "0";
		cout << tr.arr.hour << " ";
		if (tr.arr.min < 10)cout << "0";
		cout << tr.arr.min << " ";
		cout << tr.popularity << endl;
		
	}
	
}
void readall(fstream& fie) {
	fie.clear();
	fie.seekg(0);
	
	 string ss = "";
	 while (!fie.eof())
	 {
		 string s;
		 getline(fie, s);
		 cout << s << endl;

	 }
	fie.seekg(0);
};
/**/
string numtocity(int n) {
	switch (n) {
	case 1:
		return "Cherkassy";
		break;
	case 2:
		return"Chernigov";
		break;
	case 3:
		return"Chernovtsy";
		break;
	case 4:
		return"Crimea";
		break;
	case 5:
		return"Dnepropetrovsk";
		break;
	case 6:
		return"Donetsk";
		break;
	case 7:
		return"Ivano-Frankivsk";
		break;
	case 8:
		return"Kharkov";
		break;
	case 9:
		return"Kherson";
		break;
	case 10:
		return "Khmelnitsky";
		break;
	case 11:
		return "Kiev";
		break;
	case 12:
		return"Kirovograd";
		break;
	case 13:
		return"Lugansk";
		break;
	case 14:
		return"Lviv";
		break;
	case 15:
		return"Nikolaev";
		break;
	case 16:
		return"Odessa";
		break;
	case 17:
		return"Poltava";
		break;
	case 18:
		return"Rivne";
		break;
	case 19:
		return"Sumy";
		break;
	case 20:
		return"Ternopil";
		break;
	case 21:
		return"Vinnitsa";
		break;
	case 22:
		return"Volyn";
		break;
	case 23:
		return"Zakarpattia";
		break;
	case 24:
		return"Zaporozhye";
		break;
	case 25:
		return"Zhitomir";
		break;
	}
};
/**/
train randomtrain()
{
	random_device rd;
	mt19937 gen(rd());
	train tr;
	tr.number = gen() % 9999+1;
	int m = gen() % 4 + 1;
	switch (m)
	{
	case 1: tr.type = "international";
		break;
	case 2: tr.type = "fast";
		break;
	case 3: tr.type = "suburban";
		break;
	case 4: tr.type = "default";
		break;

	}
	tr.dep.day = gen() % 31 + 1;
	tr.dep.mounth = gen() % 12 + 1;
	tr.dep.hour = gen() % 23;
	tr.dep.min = gen() % 59;
	tr.dep.year = gen() % 5 + 2019;
	switch (tr.dep.mounth)
	{
	case 2:
		if (tr.dep.day > 28)
			tr.dep.day = tr.dep.day - 3 - gen() % 28;
		break;
	case 4:
		if (tr.dep.day > 30)
			tr.dep.day = tr.dep.day - 1 - gen() % 30;
		break;
	case 6:
		if (tr.dep.day > 30)
			tr.dep.day = tr.dep.day - 1 - gen() % 30;
		break;
	case 9:
		if (tr.dep.day > 30)
			tr.dep.day = tr.dep.day - 1 - gen() % 30;
		break;
	case 11:
		if (tr.dep.day > 30)
			tr.dep.day = tr.dep.day - 1 - gen() % 30;
		break;
	}
	tr.arr = addrandomtime(tr.dep);
	int a = gen();
	
		double pop = (double)(abs(a)%100+1)/50 ;
		tr.popularity = pop;
		int d = gen();
		a = abs(d) % 25 + 1;
		int c=0;	
		int f = gen();
		c = abs(f) % 25 + 1;
		while (a == c)
		{
			int f = gen();
			c = abs(f) % 25 + 1;
		}
	
		tr.name = numtocity(c) + "--"+numtocity(a);
	
	
	return tr;
}
/**/
train strtotrn(string str)
{
	train tr;
	stringstream st;
	st << str;
	st >>tr.ID>> tr.number>>tr.name>> tr.type>>tr.dep.year>>tr.dep.mounth>>tr.dep.day>>tr.dep.hour>>tr.dep.min >> tr.arr.year >> tr.arr.mounth >> tr.arr.day 
		>>tr.arr.hour>> tr.arr.min>>tr.popularity;
	return tr;
};
/**/
void inputtrain(fstream& file, fstream& fileb)
{

	train tr;
	cout << "Input train number:";
	cin >> tr.number;
	cout << "Input train name:";
	cin >> tr.name;
	cout << "Input train type:";
	cin >> tr.type;
	cout << "Input train departure year:";
	cin >> tr.dep.year;
	cout << "Input train departure mounth:";
	cin >> tr.dep.mounth;
	cout << "Input train departure day:";
	cin >> tr.dep.day;
	cout << "Input train departure hour:";
	cin >> tr.dep.hour;
	cout << "Input train departure min:";
	cin >> tr.dep.min;
	cout << "Input train arrival year:";
	cin >> tr.arr.year;
	cout << "Input train arrival mounth:";
	cin >> tr.arr.mounth;
	cout << "Input train arrival day:";
	cin >> tr.arr.day;
	cout << "Input train arrival hour:";
	cin >> tr.arr.hour;
	cout << "Input train arrival min:";
	cin >> tr.arr.min;
	cout << "Input train popularity:";
	cin >> tr.popularity;
	int a = getmaxid(filetovector(file)) + 1;
	int b = getmaxid(filetovectorbin(fileb)) + 1;
	add(file, tr,a);
	addbin(fileb, tr,b );
	
}
/**/
bool isbigger(tim t1, tim t2) {
	if (t1.year > t2.year) return true;
	if (t1.year < t2.year) return false;
	if (t1.mounth > t2.mounth) return true;
	if (t1.mounth < t2.mounth) return false;
	if (t1.day > t2.day) return true;
	if (t1.day < t2.day) return false;
	if (t1.hour > t2.hour) return true;
	if (t1.hour < t2.hour) return false;
	if (t1.min > t2.min) return true;
	if (t1.min < t2.min) return false;
	return true;
}
/**/
void inputvec (vector<train>& data) {
	train tr;
	cout << "Input train number:";
	cin >> tr.number;
	cout << "Input train name:";
	cin >> tr.name;
	cout << "Input train type:";
	cin >> tr.type;
	cout << "Input train departure year:";
	cin >> tr.dep.year;
	cout << "Input train departure mounth:";
	cin >> tr.dep.mounth;
	cout << "Input train departure day:";
	cin >> tr.dep.day;
	cout << "Input train departure hour:";
	cin >> tr.dep.hour;
	cout << "Input train departure min:";
	cin >> tr.dep.min;
	cout << "Input train arrival year:";
	cin >> tr.arr.year;
	cout << "Input train arrival mounth:";
	cin >> tr.arr.mounth;
	cout << "Input train arrival day:";
	cin >> tr.arr.day;
	cout << "Input train arrival hour:";
	cin >> tr.arr.hour;
	cout << "Input train arrival min:";
	cin >> tr.arr.min;
	cout << "Input train popularity:";
	cin >> tr.popularity;
	data.push_back(tr);
};
/**/
void readvecor(vector<train> data)
{
	int z = data.size() - 1;
	for (int i = 0;i <= z;i++)
	{
		
		if (data[i].number < 1000) cout << "0";
		if (data[i].number < 100) cout << "0";												
		if (data[i].number < 10) cout << "0";
		cout << data[i].number << " ";
		cout << data[i].name << " ";
		cout << data[i].type << " ";
		cout << data[i].dep.year << " ";
		if (data[i].dep.day < 10) cout << "0";
		cout << data[i].dep.day << " ";
		if (data[i].dep.mounth < 10) cout << "0";
		cout << data[i].dep.mounth << " ";
		if (data[i].dep.hour < 10) cout<< "0";
		cout << data[i].dep.hour << " ";
		if (data[i].dep.min < 10) cout<< "0";
		cout << data[i].dep.min;

		cout << " ";
		cout << data[i].arr.year << " ";
		if (data[i].arr.day < 10) cout << "0";
		cout << data[i].arr.day << " ";
		if (data[i].arr.mounth < 10) cout << "0";
		cout << data[i].arr.mounth << " ";
		if (data[i].arr.hour < 10)cout << "0";
		cout << data[i].arr.hour << " ";
		if (data[i].arr.min < 10)cout << "0";
		cout << data[i].arr.min << " ";
		cout << data[i].popularity << endl;
	}
};
/**/
vector<train> filetovector(fstream& fil) {
	fil.open("fout.txt", ios::in | ios::out | ios::app);
	fil.clear();
	fil.seekg(0, ios::end);
	int file_size = fil.tellg();
	if (file_size == 0) return{};
	string line;
	vector<train> res;
	fil.clear();
	fil.seekg(0);
	while (!fil.eof()) {
		getline(fil, line);
		train tr = strtotrn(line);
		res.push_back(tr);
	}
	res.pop_back();
	return res;
};
vector<train> filetovectorbin(fstream& fil) {
	//fil.open("foutbin.txt", ios::in | ios::out | ios::app|ios::binary);
	fil.clear();
	fil.seekg(0, ios::end);
	int file_size = fil.tellg();
	if (file_size == 0) return{};
	fil.clear();
	fil.seekg(0);
	train tr;
	vector<train> res;
	while (!fil.eof())
	{

		//std::cout << fil.tellg() << endl;

		train tr;
		fil.read((char*)& tr.ID, sizeof(int));
		fil.read((char*)& tr.number, sizeof(int));
		//cout << fil.tellg() << endl;
		int a;
		char ch;
		fil.read((char*)& a, sizeof(int));
		for (int i = 0;i <= a - 1;i++) {
			fil.get(ch);
			tr.name += ch;
		}
		int b;
		fil.read((char*)& b, sizeof(int));
		for (int i = 0;i <= b - 1;i++) {
			fil.get(ch);
			tr.type += ch;
		}

		fil.read((char*)& tr.dep.year, sizeof(int));
		fil.read((char*)& tr.dep.day, sizeof(int));
		fil.read((char*)& tr.dep.mounth, sizeof(int));
		fil.read((char*)& tr.dep.hour, sizeof(int));
		fil.read((char*)& tr.dep.min, sizeof(int));

		fil.read((char*)& tr.arr.year, sizeof(int));
		fil.read((char*)& tr.arr.day, sizeof(int));
		fil.read((char*)& tr.arr.mounth, sizeof(int));
		fil.read((char*)& tr.arr.hour, sizeof(int));
		fil.read((char*)& tr.arr.min, sizeof(int));

		fil.read((char*)& tr.popularity, sizeof(double));
		res.push_back(tr);
	}
	res.pop_back();
	return res;
}
bool mode1(string searc, train tr) {
	if (tr.name.length() < searc.length()) return false;
	for (int i = 0; i <= searc.length() - 1;i++)
		if (searc[searc.length() - 1 - i] != tr.name[tr.name.length() - 1 - i]) return false;
	return true;
}
bool mode2(string searc,int searc2,int searc3, train tr) {
	if (searc == tr.type && searc2 <= tr.number && searc3 > tr.number) return true;
	return false;
}
tim stringtotime(string ss) {
	tim t;
	stringstream s;
	s << ss;
	s >> t.year >> t.mounth >> t.day >> t.hour >> t.min;
	return t;
}
bool mode3(string searc, train tr) {
	if (isbigger(tr.dep, stringtotime(searc))) return false;
	
	else return true;
}
void addnrand(fstream& fil,int n) {
	fil.clear();
	fil.seekg(0);
	int curr = getmaxid(filetovector(fil))+2;
	train tr;
	for (int i = 1;i <= n;i++) {
		tr = randomtrain();
		add(fil, tr,curr);
		curr++;
	}
}
void addnrandbin(fstream& fil, int n) {
	fil.clear();
	fil.seekg(0);
	int curr = getmaxid(filetovectorbin(fil)) + 2;
	train tr;
	for (int i = 1;i <= n;i++) {
		tr = randomtrain();
		addbin(fil, tr, curr);
		curr++;
	}
}
int getmaxid(vector<train> data) {

	if (data.empty()) return 0;
	
	int i = data[data.size() - 2].ID;
	return i;

	}
vector<train> search(int mode, vector<train> data, string searc1, int searc2, int searc3) {
	train tr;
	vector<train> res;
	int i = 0;
	int k = data.size() - 1;
	switch (mode) {
	case 1:
		for (i; i <= k; i++) {
			if (mode1(searc1, data[i]))
				res.push_back(data[i]);
	                         }
			  
		break;

	case 2:
		for (i; i <= k; i++) {
			if (mode2(searc1, searc2, searc3, data[i]))
				res.push_back(data[i]);
		}


		break;
	case 3:
		for (i; i <= k; i++) {
			if (mode3(searc1,data[i]))
				res.push_back(data[i]);
		}

		break;
	}
	return res;
}
void benchmarc(fstream& bench, string name) {
	
	

	cout << "Choose search mode:" << endl;
	cout << "1-End of name" << endl << "2-Type and number diapazon" << endl << "3-Time" << endl;
	int n;
	cin >> n;

	int m = 10;
	int start = 0;

	int end = 0;
	

	while (end - start < 3000) 
	{

		remove("bench.txt");
		bench.open(name, ios::in | ios::out | ios::app);

		start = clock();
		addnrand(bench, m);
		search(m, filetovector(bench), "tsk", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m *= 1.5;
		bench.close();

	}
         while (end - start < 10000) {

		remove("bench.txt");
		bench.open(name, ios::in | ios::out | ios::app);

		start = clock();
		addnrand(bench, m);
		search(m, filetovector(bench), "tsk", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m += 5000;
		bench.close();

	}
		 cout << "number of trains:" << m<<endl;
		 bench.open(name, ios::in | ios::out | ios::app);
		 bench.seekg(0, ios::end);
		 cout << "file size:" << bench.tellg() << "bytes";
		 bench.close();
}

void benchmarcbin(fstream& bench, string name) {



	cout << "Choose search mode:" << endl;
	cout << "1-End of name" << endl << "2-Type and number diapazon" << endl << "3-Time" << endl;
	int n;
	cin >> n;

	int m = 10;
	int start = 0;

	int end = 0;


	while (end - start < 3000)
	{

		remove("benchbin.txt");
		bench.open(name, ios::in | ios::out | ios::app | ios::binary);

		start = clock();
		addnrandbin(bench, m);
		search(m, filetovectorbin(bench), "tsk", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m *= 1.5;
		bench.close();

	}
	while (end - start < 10000) {

		remove("bench.txt");
		bench.open(name, ios::in | ios::out | ios::app | ios::binary);

		start = clock();
		addnrandbin(bench, m);
		search(m, filetovectorbin(bench), "sad", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m += 5000;
		bench.close();
		
	}
	cout << "number of trains:" << m << endl;
	bench.open(name, ios::in | ios::out | ios::app|ios::binary);
	bench.seekg(0, ios::end);
	cout << "file size:" << bench.tellg() << "bytes";
	bench.close();
}
void benchmarcvector() {
	vector<train> data;
	cout << "Choose search mode:" << endl;
	cout << "1-End of name" << endl << "2-Type and number diapazon" << endl << "3-Time" << endl;
	int n;
	cin >> n;

	int m = 10;
	int start = 0;

	int end = 0;


	while (end - start < 5000)
	{

		data.clear();
		

		start = clock();
		for (int i = 1;i <= m;i++) {
			train t = randomtrain();
			data.push_back(t);
		}
		search(m, data, "sad", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m *= 1.5;
		

	}
	while (end - start < 10000) {
		data.clear();


		start = clock();
		for (int i = 1;i <= m;i++) {
			train t = randomtrain();
			data.push_back(t);
		}
		search(m, data, "sad", 10, 1000);
		end = clock();
		cout << "time:" << end - start << endl;
		m += 10000;



	}
	cout << "number of trains:" << m << endl;
	
	

}

int main()
{
	random_device rd;
	mt19937 gen(rd());
	string  ss;
	string path = "fout.txt";
	string pathbin = "foutbin.txt";
	fstream bench;

	string pathbench= "bench.txt";
	fstream filbin;
	fstream fil;
	fstream benchbin;
	fil.open(path,ios::in | ios::out | ios::app);
	
	filbin.open(pathbin, fstream::in | fstream::out | fstream::app | fstream::binary);
    vector <train> data1;
    cout << "Choose program mode: " << endl << "1-Interactive mode" << endl << "2-Demonstration mode" << endl << "3-Benchmark mode" << endl;
	int m;
	cin >> m;
	system("cls");
	switch (m) {
	case 1: {
		int cur = -1;
		while (cur != 0) {
			cout << "1-Add new train to file" << endl << "2-Add n random trains to file" << endl << "3-Show all current trains in file"
				<< endl << "4-Search train " << endl << "5-Add new train to vector" << endl << "6-Add n random trains to vector" << endl <<
				"7-Show all trains in vector" << endl << "8-Read from binary"<<endl
				
				<< "0-Exit" << endl;
			cin >> cur;
			vector<train> searchres;
			string line;
			tim t;
			
			int a, b;
			switch (cur)
			{
			case 1:
				inputtrain(fil,filbin);
				break;

			case 2:
				cout << "Input n" << endl;
				int n;
				cin >> n;
				addnrand(fil, n);
				addnrandbin(filbin, n);
				break;
			case 3:
				readall(fil);
				system("pause");
				break;
			case 4:
				cout << "1-End of name" << endl << "2-Type and number diapazon" << endl << "3-Time" << endl;
				int mode;
				
				cin >> mode;
				switch (mode) {
				case 1:
					cout << "Input end of name:" << endl;
					cin >> line;
					searchres = search(1, filetovector(fil), line , 0, 0);
					readvecor(searchres);
					system("pause");
					break;
				case 2:
					cout << "Input train type:"<<endl;
					cin >> line;
					cout << endl << "Input down law:" << endl;
					cin >> a;
					cout << endl << "Input up law:" << endl;
					cin >> b;
					searchres = search(2, filetovector(fil), line, a, b);
					readvecor(searchres);
					system("pause");
					break;
				case 3:
					cout << "Input departure year:" << endl;
					cin >> t.year;
					cout << "Input departure mounth:" << endl;
					cin >> t.mounth;
					cout << "Input departure day:" << endl;
					cin >> t.day;
					cout << "Input departure hour:" << endl;
					cin >> t.hour;
					cout << "Input departure min:" << endl;
					cin >> t.min;
					line = to_string(t.year)+" "+ to_string(t.mounth) + " " + to_string(t.day) + " " + to_string(t.hour) + " " + to_string(t.min);
					cout << line << endl;
					searchres = search(3, filetovector(fil), line, 0, 0);
					readvecor(searchres);
					system("pause");
					break;
				}

				break;
			case 5:
				inputvec(data1);
				break;
			case 6:
				cout << "Input n" << endl;
				int k;
				cin >> k;
				for (int i = 1;i <= k;i++) {
					train t = randomtrain();
					data1.push_back(t);
				}
				
				break;

				
			case 7:
				readvecor(data1);
				system("pause");
				break;
			case 8:
				readbin(filbin);
				system("pause");
				break;
			}
			system("cls");

		}
		
		break;
	}
	case 2:
		cout << "Current txt file:" << endl;
		Sleep(2000);
		readall(fil);
		Sleep(2000);
		system("cls");
		cout << "Adding 10 trains to txt file:" << endl;
		addnrand(fil, 10);
		Sleep(2000);
		cout << "Current txt file:" << endl;
		Sleep(2000);
		readall(fil);
		Sleep(2000);
		system("cls");
		cout << "Current binary file:" << endl;
		Sleep(2000);
		readbin(filbin);
		Sleep(2000);
		system("cls");
		cout << "Adding 10 trains to binary file:" << endl;
		Sleep(2000);
		addnrandbin(filbin, 10);
		
		system("cls");
		cout << "Current binary file:" << endl;
		Sleep(2000);
		readbin(filbin);
		Sleep(2000);
		system("cls");
		cout << "Adding 10 trains to vector:" << endl;
		Sleep(2000);
		
		for (int i = 1;i <= 10;i++) {
			train t = randomtrain();
			data1.push_back(t);
		}
		cout << "Current vector:" << endl;
		Sleep(2000);
		readvecor(data1);
		system("pause");

		break;
	case 3:
		
		cout << "1-txt file" << endl << "2-binary file" << endl << "3-vector" << endl;
		int k;
		cin >> k;
		switch (k)
		{
		case 1:
			benchmarc(bench, "bench.txt");
			break;
			case 2:
				benchmarcbin(benchbin, "benchbin.txt");
				break;
			case 3:
				benchmarcvector();
				break;
		}
		break;
	}
	fil.close();
}
