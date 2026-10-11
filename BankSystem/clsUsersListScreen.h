#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include <string>
#include <iomanip>
class clsUsersListScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser& User)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }
public:
    static void ShowUsersList()
    {
        vector <clsUser> vUsers = clsUser::GetUsersList();
        system("cls");
        string Title = "\t  Users List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t____________________________________________________";
        cout << "_________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Username";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________";
        cout << "______________________________________________________\n" << endl;


        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser& User : vUsers)
            {

                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t____________________________________________________";
        cout << "_________________________________________________\n" << endl;


    }
};

