#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen : protected clsScreen
{
private:
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
    static void ShowFindUserScreen()
    {
        system("cls");
        _DrawScreenHeader("\t Find User Screen");

        string UserName = "";
        cout << "Please enter username : ";
        UserName = clsInputValidate::ReadString();
        while(!clsUser::IsUserExist(UserName))
        {
            cout << "\nUsername was Not found!, Choose another one : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        if (!User.IsEmpty())
        {
            cout << "\nUser Found Successfully :-)\n";
            _PrintUser(User);
        }
        else
        {
            cout << "\nUser was not found !";
        }

    }

};

