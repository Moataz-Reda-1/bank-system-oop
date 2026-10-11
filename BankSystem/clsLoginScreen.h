#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
#include <vector>

class clsLoginScreen : protected clsScreen
{
	static bool _Login()
	{
		short Counter = 3;
		bool LoginFailed = false;
		string Username, Password;
		do
		{
			if (LoginFailed)
			{
				system("color 4F");
				cout << "\n\aInvalid Username/Password! \n";
				--Counter;
				cout << "You have " << Counter << " Trials to login.\n\n";
			}

			if (Counter == 0)
			{
				cout << "\n\aYou are locked after 3 failed trial(s) :( \n";
				return false;
			}

			cout << "Enter Username : ";
			Username = clsInputValidate::ReadString();
			cout << "Enter Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		clsUser User = clsUser::Find(Username, Password);
		User.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;

	}

public:
	static bool ShowLogInScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Login Screen");
		return _Login();
	}

};