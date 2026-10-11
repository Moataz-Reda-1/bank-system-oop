#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsUpdateUserScreen :protected clsScreen

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

public:

    static void ShowUpdateUserScreen()
    {
        system("cls");
        _DrawScreenHeader("\t Update User Screen");

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

            system("cls");
            _PrintUser(User);
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;

            SaveResult = User.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }

            }

        }
    }
};

