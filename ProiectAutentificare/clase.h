#pragma once
#include<string>

using std::string;

class Identity {
private:
	string userName, userPassword;
	bool identityConfirmed;

	void confirmIdentity();
public:
	Identity();
	Identity(string, string);
	bool getConfirmedIdentity();
};

class NewUser {
private:
	string userName, password, securityQuestions[3], securityAnswers[3];

	void getNewPassword();
	bool verifyUserName();
public:
	NewUser();
	NewUser(string);
	void setSecurityQandA();
	void createUserProfile();
};

class ResetPassword {
private:
	string userName, password, savedSecurityQuestions[3], savedSecurityAnswers[3];
	bool identityConfirmed;

	bool verifyUserName();
	void getSavedSecurityQandA();
	bool getUserSecurityAnswers();
	void getNewPassword();
	void updatePassword();
public:
	ResetPassword();
	ResetPassword(string);
};

class RandomPassword {
private:
	string password;

	string genPassword();
public:
	RandomPassword();
	string getPassword();
};

// clasa utilizata pentru a urmarii exceptii personalizate
class MyException {
public:
	string str_what;
	int what;
	MyException() { str_what = "0"; what = 0; }
	MyException(string s, int e)
	{
		str_what = s;
		what = e;
	}
};