#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        User.Permissions = clsUser::ReadPermissions();
    }

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

    static void ShowAddNewUserScreen()
    {
        system("cls");
        _DrawScreenHeader("\tAdd New User Screen");

        string Username = "";
        cout << "Please enter username : ";
        Username = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(Username))
        {
            cout << "\nUsername Is Already Used, Choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(Username);
        system("cls");
        _DrawScreenHeader("\t Read User Info Screen");
        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;
        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Added Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because Username is used!\n";
            break;

        }
        }

    }
};

