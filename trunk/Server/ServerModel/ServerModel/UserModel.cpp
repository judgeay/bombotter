#include "UserModel.h"

UserModel::UserModel()
{
	/*Trololo */
}

UserModel::UserModel(string log, string pwd)
{
	this->login = log;
	this->password = pwd;
}

UserModel* UserModel::Connect(string login, string password)
{
	UserModel* user = NULL;
	bool badLogin = false, badPwd = false;
	/* Rechercher dans la base de donn�es */
	if (badLogin)
		throw Bomberloutre::BadLoginException("BOLOSS");
	if (badPwd)
		throw Bomberloutre::BadPasswordException("Retente ta chance");
	
	return user;
}

UserModel* UserModel::CreateUser(string login, string password)
{
	UserModel* user = NULL;
	bool userExist = false;
	/* Si l'utilisateur existe deja : */
	if (userExist)
		throw Bomberloutre::UserException("L'utilisateur existe d�j� : sois cr�atif et trouve un autre pseudo.... VICTIME!");

	/* Maj de la bdd : cr�ation du user avec des params par d� */
	return user;
}
