#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen :clsScreen
{
    enum enUsersMenuChoices
    {
        eListUsers = 1,
        eAddUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenu = 6
    };

    static short _ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToManageUsersMenu()
    {
        cout << setw(37) << left << "" << "\033[36m\nPress any key to go back to Manage Users Menu...\n\033[0m";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowUsersListScreen()
    {
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersMenuOption(enUsersMenuChoices Choice)
    {
        switch (Choice)
        {
        case clsManageUsersScreen::eListUsers:
        {
            system("cls");
            _ShowUsersListScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eAddUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }
        case clsManageUsersScreen::eMainMenu:
        {

        }
        }
    }


public :
	static void ShowManageUsersMenu()
	{
        system("cls");
        _DrawScreenHeader("\t  Manage Users Screen");
        cout << setw(37) << left << "" << "===========================================" << endl;
        cout << setw(37) << left << "" << "             Manage Users Menue " << endl;
        cout << setw(37) << left << "" << "===========================================" << endl;
        cout << setw(37) << left << "" << "\t[1] List Users. " << endl;
        cout << setw(37) << left << "" << "\t[2] Add New User. " << endl;
        cout << setw(37) << left << "" << "\t[3] Delete User. " << endl;
        cout << setw(37) << left << "" << "\t[4] Update User. " << endl;
        cout << setw(37) << left << "" << "\t[5] Find User. " << endl;
        cout << setw(37) << left << "" << "\t[6] Main Menu. " << endl;
        cout << setw(37) << left << "" << "===========================================" << endl;
        _PerformManageUsersMenuOption((enUsersMenuChoices)_ReadManageUsersMenuOption());
	}
};

