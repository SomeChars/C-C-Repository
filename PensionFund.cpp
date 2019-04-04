#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "windows.h"

using namespace std;
int currentYear = 2019;
int currentMonth = 1;

class Person {
private:
	string name;
	string sex;
	int birthYear;
	int birthMonth;
	int age;
	int degreeOfDisability;
	bool veteran;
	bool heroOfLabor;
	float salary;
public:
	Person(string name, string sex, int birthYear, int birthMonth, 
		int degreeOfDisability, bool veteran, bool heroOfLabor, float salary) {
		this->name = name;
		this->sex = sex;
		this->birthYear = birthYear;
		this->birthMonth = birthMonth;
		this->age = age;
		this->degreeOfDisability = degreeOfDisability;
		this->veteran = veteran;
		this->heroOfLabor = heroOfLabor;
		this->salary = salary;
		if (birthMonth > currentMonth) this->age = currentYear - birthYear;
		else this->age = currentYear - birthYear - 1;
	}
	//геттеры
	string getName() { return this->name; }
	string getSex() { return this->sex; }
	int getAge() { return this->age; }
	int getBirthYear() { return this->birthYear; }
	int getBirthMonth() { return this->birthMonth; }
	int getDegree() { return this->degreeOfDisability; }
	float getSalary() { return this->salary; }
	bool isVeteran() { return this->veteran; }
	bool isHero() { return this->heroOfLabor; }
	//сеттеры(некоторые)
	void changeAge(int age) {this->age = age;}
	void changeDegree(int degree) { this->degreeOfDisability = degree; }
	void changeVeteran(bool vet) { this->veteran = vet; }
	void changeHero(bool hero) { this->heroOfLabor = hero; }
	void updateAge() {
		if (this->birthMonth > currentMonth) this->age = currentYear - this->birthYear;
		else this->age = currentYear - this->birthYear - 1;
	}
};

class Fund {
private:
	string city;
	float capital;
	float crisis;
	vector<Person*> pensioners;
	vector<Person*> workers;
	float defaultPension;
public:
	Fund(vector<Person*> people,string city,float capital = 1000000,float crisis = 1.0,float defaultPension = 11000) {
		vector<Person*>::iterator it = people.begin();
		for (;it < people.end();it++) {
			if ((*it)->getSex() == "Male") {
				if ((*it)->getAge() >= 65) this->pensioners.push_back((*it));
				else this->workers.push_back((*it));
			}
			else {
				if ((*it)->getAge() >= 60) this->pensioners.push_back((*it));
				else this->workers.push_back((*it));
			}
		}
		this->city = city;
		this->capital = capital;
		this->crisis = crisis;
		this->defaultPension = defaultPension;
	}
	float getCapital() {
		return this->capital;
	}
	string getName() {
		return this->city;
	}
	void personBirth(Person p) {
		cout << p.getName() << " is new here :)" << endl;
		if (p.getSex() == "Male") {
			if (p.getAge() >= 65) this->pensioners.push_back(&p);
			else this->workers.push_back(&p);
		}
		else {
			if (p.getAge() >= 60) this->pensioners.push_back(&p);
			else this->workers.push_back(&p);
		}
		float pen = this->defaultPension;
		if (this->pensioners.size() != 0) {
			if (this->capital > 1000000) {
				if ((capital - 750000) / this->pensioners.size() > 10326) {
					if ((capital - 750000) / this->pensioners.size() < 15000) {
						pen = (capital - 750000) / this->pensioners.size();
					}
					else {
						pen = 15000;
					}
				}
			}
		}
		if (pen > this->defaultPension) this->defaultPension = pen;		
	}
	void personDeath(int num) {
		vector<Person*>::iterator it = this->pensioners.begin();
		for (;it < pensioners.end();it++) {
			if (num == 0) {
				cout << (*it)->getName() << " is dead :(" << endl;
				this->pensioners.erase(it);
				return;
			}
			num--;
		}
		it = this->workers.begin();
		for (;it < workers.end();it++) {
			if (num == 0) {
				cout << (*it)->getName() << " is dead :(" << endl;
				this->workers.erase(it);
				return;
			}
			num--;
		}
	}
	float getCrisis() {
		return this->crisis;
	}
	void givePension() {
		if (pensioners.size() == 0) return;
		if (capital < 10326) { 
			cout << "Oops, collapse in " << this->city << endl;
			return;
		}
		vector<Person*>::iterator it = this->pensioners.begin();
		if (this->pensioners.size() != 0) {
			if (this->capital > 100000) {
				if (capital / defaultPension > 10326) this->defaultPension = (capital - 50000) / pensioners.size();
			}
		}
		while (it <= this->pensioners.begin() && capital >= 10326) {
			float pension = this->defaultPension;
			if ((*it)->isHero()) { pension += 4000; }
			if ((*it)->isVeteran()) { pension += 3000; }
			if ((*it)->getDegree() == 1) { pension += 3000; }
			if ((*it)->getDegree() == 2) { pension += 5000; }
			if ((*it)->getDegree() == 3) { pension += 7000; }
			if (pension > capital) { 
				cout << "Oops, not enough money in " <<this->city<< endl;
				return; 
			}
			pension *= crisis;
			this->capital -= pension;
			it++;
		}
	}
	void moneyStolen(float money) {
		cout << "Money stolen from " << this->city << " fund: " << money << endl;
		this->capital -= money;
	}
	void updateAges() {
		vector<Person*>::iterator it = this->workers.begin();
		for (;it < this->workers.end();it++) {
			(*it)->updateAge();
		}
	}
	float earnings() {
		if (pensioners.size() == 0 || workers.size() == 0) return 0;
		float sum = 0;
		vector<Person*>::iterator it = this->workers.begin();
		for (;it < this->workers.end();it++) {
			this->capital += (*it)->getSalary()*0.25;
			sum += (*it)->getSalary()*0.25;
		}
		cout << "Earnings in " << this->city << ": " << sum << endl;
		return sum;
	}
	int getLen() {
		return this->workers.size() + this->pensioners.size();
	}
	void printInfo() {
		cout << this->city << ": " << this->capital <<"   default pension: "<<this->defaultPension<<"   crisis is: "<<this->crisis<< endl;
	}
	void changeCrisis(float crisis) {
		this->crisis += crisis;
	}
};

class PensionMinistry {
private:
	vector<Fund*> funds;
public:
	PensionMinistry(vector<Fund*> funds, float crisis = 1) {
		this->funds = funds;
	}
	void addFund(Fund* fund) {
		this->funds.push_back(fund);
	}
	float earnings() {
		float earn = 0;
		vector<Fund*>::iterator it = this->funds.begin();
		for (;it < funds.end();it++) {
			earn += (*it)->earnings();
		}
		return earn;
	}
	void givePension() {
		vector<Fund*>::iterator it = this->funds.begin();
		for (;it < funds.end();it++) {
			(*it)->givePension();
		}
	}
	void printInfo() {
		cout << currentMonth << " " << currentYear<<endl;
		vector<Fund*>::iterator it1 = funds.begin();
		for (;it1 < funds.end();it1++) {
			(*it1)->printInfo();
		}
	}
};

class Government {
private:
	vector<Fund*> funds;
public:
	Government(vector<Fund*> funds) {
		this->funds = funds;
	}
	void addFund(Fund* fund) {
		this->funds.push_back(fund);
	}
	float stealMoney() {
		int sumcap = 0;
		vector<Fund*>::iterator it = this->funds.begin();
		for (;it < this->funds.end();it++) {
			sumcap += (*it)->getCapital();
		}
		int stole = 25000 + rand() % 25000;
		for (it = this->funds.begin();it < this->funds.end();it++) {
			(*it)->moneyStolen(stole*((*it)->getCapital() / sumcap));
		}
		return stole;
	}
	void setCrisis() {
		float crisis = rand() % 20;
		crisis -= 10;
		crisis /= 100;
		cout <<"Crisis change is: " <<crisis << endl<<endl;
		vector<Fund*>::iterator it2 = funds.begin();
		for (;it2 < funds.end();it2++) {
			(*it2)->changeCrisis(crisis);
		}
	}
};

class Processes {
private:
	vector<Fund*> funds;
public:
	Processes(vector<Fund*> funds) {
		this->funds = funds;
	}
	void addFund(Fund* fund) {
		this->funds.push_back(fund);
	}
	void updateAges() {
		vector<Fund*>::iterator it = funds.begin();
		for (;it < funds.end();it++) {
			(*it)->updateAges();
		}
	}
	void birthAndDeath() {
		int numfunds = 0;
		vector<Fund*>::iterator it = funds.begin();
		for (;it < funds.end();it++) {
			numfunds++;
		}
		int birthRate = 1 + rand() % 99;
		int deathRate = 1 + rand() % 99;
		int year = 1970 + rand() % 30;
		int month = 1 + rand() % 11;
		int s = 1 + rand() % 11;
		int dis = 3;
		if (s < 12) dis--;
		if (s < 10) dis--;
		if (s < 7) dis--;
		bool vet = false;
		if (dis % 4 == 1) vet = true;
		bool hero = false;
		if (dis % 5 == 2) hero = true;
		string sex = "Male";
		if (dis % 2 == 1) sex = "Female";
		int salary = 12000 + rand() % 68000;
		int forbirth = rand() % numfunds;
		int fordeath = rand() % numfunds;
		if (birthRate < 5) {
			for (;it < funds.end();it++) {
				if (forbirth == 0) {
					Person *p = new Person(to_string(year) + " " + to_string(deathRate), sex, year, month, dis, vet, hero, salary);
					(*it)->personBirth((*p));
				}
				forbirth--;
			}
		}
		if (deathRate < 5) {
			int len = 0;
			vector<Fund*>::iterator it1 = funds.begin();
			for (;it1 < funds.end();it1++) {
				if (fordeath == 0) {
					int ra = rand() % (*it1)->getLen();
					(*it1)->personDeath(ra);
				}
				fordeath--;
			}
		}
	}
	void changeDate() {
		if (currentMonth == 12) {
			currentMonth = 0;
			currentYear++;
		}
		currentMonth++;
	}
};


int main()
{
	srand(time(0));
	//01.01.2019
	//name,sex,mm,yy,degree,vet,labor,salary
	Person p1("A", "Male", 1950, 9, 0, false, true, 0);
	Person p2("B", "Female", 1958, 3, 0, false, true, 49780);
	Person p3("C", "Male", 1964, 1, 1, false, false, 35000);
	Person p4("D", "Female", 1929, 11, 1, true, false, 0);
	Person p5("E", "Female", 1940, 5, 0, false, true, 45600);
	Person p6("F", "Male", 1961, 7, 0, false, false, 75000);
	Person p7("G", "Female", 1972, 6, 0, false, true, 55600);
	Person p8("H", "Male", 1926, 8, 2, true, false, 0);
	Person p9("I", "Male", 1969, 9, 3, false, true, 20000);
	Person p10("G", "Female", 1967, 12, 0, false, false, 84300);
	Person p11("K", "Female", 1935, 1, 0, false, true, 0);
	Person p12("L", "Female", 1955, 1, 0, false, false, 74000);
	Person p13("M", "Male", 1957, 6, 1, true, false, 16000);
	Person p14("N", "Female", 1963, 10, 0, true, false, 90000);
	Person p15("O", "Female", 1938, 4, 2, false, true, 0);
	Person p16("P", "Male", 1975, 11, 0, false, false, 48500);
	vector<Person*> msk = { &p1,&p2,&p3,&p4 };
	vector<Person*> spb = { &p5,&p6,&p7,&p8 };
	vector<Person*> nsk = { &p9,&p10,&p11,&p12 };
	vector<Person*> ekb = { &p13,&p14,&p15,&p16 };
	Fund fund1(msk, "MSK", 3000000, 1.1);
	Fund fund2(spb, "SPB", 1600000, 1.05);
	Fund fund3(nsk, "NSK", 1200000, 1.0);
	Fund fund4(ekb, "EKB", 1350000, 0.95);
	vector<Fund*> funds = { &fund1,&fund2,&fund3,&fund4 };
	PensionMinistry *pensionMinistry = new PensionMinistry(funds);
	Government *government = new Government(funds);
	Processes *processes = new Processes(funds);
	ofstream outputData;
	vector<Fund*>::iterator it;
	outputData.open("F:\\Data.txt");
	for (int i = 0;i < 120;i++) {
		pensionMinistry->printInfo();
		processes->updateAges();
		pensionMinistry->earnings();
		processes->birthAndDeath();
		pensionMinistry->givePension();
		government->stealMoney();
		government->setCrisis();
		it = funds.begin();
		for (;it < funds.end();it++) {
			outputData << currentMonth << "." << currentYear << " " << (*it)->getName() << " "<< (*it)->getCapital() << " " << (*it)->getCrisis() << endl;
		}
		currentMonth++;
		if (currentMonth == 13) {
			currentYear++;
			currentMonth = 1;
		}
		//Sleep(5000);
	}
}
