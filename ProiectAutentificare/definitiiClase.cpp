#include"clase.h"
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<list>

using std::cout; using std::cin; using std::endl; using std::ofstream; using std::ifstream; using std::stringstream;

//Identity
Identity::Identity() { identityConfirmed = false; }

void Identity::confirmIdentity() {

}

bool Identity::getConfirmedIdentity() {
	return 1;
}

Identity::Identity(string userName, string userPassword) {
	this->userName = userName;
	this->userPassword = userPassword;
	identityConfirmed = false;
}
//

//NewUser
NewUser::NewUser() {}

bool NewUser::verifyUserName() { //Returnam true daca numele de utilizator nu e folosit si e valabil, si false in caz contrar
	ifstream fisier;
	string linieFisier, temp;
	string::iterator it;
	for (it = userName.begin(); it != userName.end(); it++) //Verificam ca numele sa nu contina virgula, deoarece ar 
		if ((*it) == ',')                                  //provoca o comportare neasteptata a 
			return false;                                     //programului
	fisier.open("utilizatori.csv");
	if (fisier.is_open()) {
		while (getline(fisier, linieFisier)) {
			stringstream strstream(linieFisier);
			getline(strstream, temp, ',');
			if (userName == temp)
				return false;
		}
		fisier.close();
	}
	else
		cout << "\n\nFisierul nu se poate deschide :((\n\n";
	return true;
}

void NewUser::getNewPassword() {
	RandomPassword pw;
	this->password = pw.getPassword();
}

void NewUser::setSecurityQandA() {
	cout << "\nSET QUESTIONS:\n";
	cout << "Q1: "; cin.ignore(); getline(cin, securityQuestions[0]);
	cout << "Q2: "; getline(cin, securityQuestions[1]);
	cout << "Q3: "; getline(cin, securityQuestions[2]);
	cout << "\nSET ANSWERS:\n";
	cout << securityQuestions[0] << " -> Answer: "; getline(cin, securityAnswers[0]);
	cout << securityQuestions[1] << " -> Answer: "; getline(cin, securityAnswers[1]);
	cout << securityQuestions[2] << " -> Answer: "; getline(cin, securityAnswers[2]);
}

NewUser::NewUser(string userName) {
	this->userName = userName;
	if(verifyUserName() == true)
		getNewPassword();
	else {
		cout << "-- Introduceti un nume de utilizator disponibil --\n";
		do {
			cin >> this->userName;
		} while (!verifyUserName());
		getNewPassword();
	}
	cout << "** PASSWORD: " << password << " **\n";
	setSecurityQandA();
}

void NewUser::createUserProfile() { //Practic, salvam utilizatorul intr-un fisier csv
	ofstream fisier;
	fisier.open("utilizatori.csv", ofstream::app);
	if (fisier.is_open()) {
		fisier << userName << ',' << password << ',' <<
			securityQuestions[0] << ',' << securityAnswers[0] << ',' <<
			securityQuestions[1] << ',' << securityAnswers[1] << ',' <<
			securityQuestions[2] << ',' << securityAnswers[2] << endl;
		fisier.close();
		cout << "\n\nCont creat cu succes\n\n";
	}
	else
		cout << "\n\nFisierul nu a putut fi creat :((\n\n";
}
//

//ResetPassword

//

//RandomPassword
string RandomPassword::genPassword() {
	int passwordLenght;
	char character;
	string generatedPassword = "";
	srand((unsigned)time(NULL));
	//n = offset + (rand() % (range - offset + 1))
	passwordLenght = 4 + (rand() % 12); //Generam un numar random intre 4 si 15
	/*
	*admitem caractere a caror cod ascii e cuprins intre: 33 - 125
	*/
	for (int i = 0; i < passwordLenght; i++) {
		character = (char)(33 + (rand() % 93));
		if (character == ',')
			character = '.';
		generatedPassword = generatedPassword + character;
	}
	return generatedPassword;
}

void animationWaitGenPas() {
	cout << "Generating a password! Please wait . \n";
	Sleep(300);
	cout << "Generating a password! Please wait . . \n";
	Sleep(300);
	cout << "Generating a password! Please wait . . . \n";
	Sleep(400);
}

RandomPassword::RandomPassword() {
	animationWaitGenPas();
	password = genPassword();
}

string RandomPassword::getPassword() {
	return password;
}
//