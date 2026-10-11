#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTranferLogRegistersScreen.h"
class clsTransationsScreen :protected clsScreen
{
private:
    enum enTransChoices {
        eDiposite = 1,
        eWithDraw = 2,
        eBalances = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eMainMenue = 6
    };

    static short _ReadTransactionsMenuOption()
    {
        cout << setw(37) << left << "" << "What do you want to do [1 to 6] ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6);
        return Choice;
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\033[36m\n\nPress any key to go back to transactions menu...\033[0m";        system("pause>0");
        ShowTransactionsScreen();
    }

    static void _ShowDepositeScreen()
    {
        clsDepositeScreen::ShowDepositeScreen();
    }

    static void _ShowWithDrawScreen()
    {
        clsWithdrawScreen::ShowWithDrawcreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogRegisters()
    {
        clsTranferLogRegistersScreen::ShowTransferLogRegistersList();
    }

    static void _PerformTransactionsOptions(enTransChoices Choice)
    {


        switch (Choice)
        {
        case eDiposite:
        {
            system("cls");
            _ShowDepositeScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case eWithDraw:
        {
            system("cls");
            _ShowWithDrawScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case eBalances:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case eTransfer:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case eTransferLog:
        {
            system("cls");
            _ShowTransferLogRegisters();
            _GoBackToTransactionsMenu();
            break;
        }
        case eMainMenue:
        {

        }
        }
    }
public:
    static void ShowTransactionsScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }


        system("cls");
        _DrawScreenHeader("\tTransactions Menu");
        cout << setw(37) << left << "" << "===========================================" << endl;
        cout << setw(37) << left << "" << "             Transcations Screen          " << endl;
        cout << setw(37) << left << "" << "===========================================" << endl;
        cout << setw(37) << left << "" << "\t[1] Deposite. " << endl;
        cout << setw(37) << left << "" << "\t[2] WithDraw. " << endl;
        cout << setw(37) << left << "" << "\t[3] Total Balances. " << endl;
        cout << setw(37) << left << "" << "\t[4] Transfer." << endl;
        cout << setw(37) << left << "" << "\t[5] Transfer Log." << endl;
        cout << setw(37) << left << "" << "\t[6] MainMenue." << endl;
        cout << setw(37) << left << "" << "===========================================" << endl;
        _PerformTransactionsOptions(enTransChoices(_ReadTransactionsMenuOption()));
    }

};

