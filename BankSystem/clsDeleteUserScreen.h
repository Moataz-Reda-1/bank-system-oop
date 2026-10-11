#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{

    static void _PrintUser(clsUser& User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUsername    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions  : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:
	static void ShowDeleteUserScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Delete User Screen");

        string Username = "";
        cout << "Please enter Username : ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }
        clsUser User = clsUser::Find(Username);
        _PrintUser(User);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
	}
};

