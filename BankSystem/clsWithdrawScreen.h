#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsWithdrawScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient& Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number? ";
        AccountNumber = clsInputValidate::ReadString();
        return AccountNumber;
    }

    static void _ReadWithdrawAmount(clsBankClient& Client)
    {
        system("cls");
        cout << "-----------------------------------------" << endl;
        cout << "           WithDraw Screen        " << endl;
        cout << "-----------------------------------------\n" << endl;
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Withdraw amount ? ";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount > Client.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance, You can withdraw upto : " << Client.AccountBalance << endl;
            cout << "\nPlease Enter another amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }

        char Answer = 'N';
        cout << "\nAre You Sure You Want To Perform this Transaction ? (Y / N) ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrawed Succssefully.\n";
                cout << "\nNew Balance Is : " << Client.AccountBalance << endl;
            }
        }
        else
        {
            cout << "\nOperation Was Cancelled\n";
        }
    }

    static void _PerformWithdrawOperation()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string AccountNumber = _ReadAccountNumber();
        while (!(clsBankClient::IsClientExist(AccountNumber)))
        {
            cout << "\nClient With [" << AccountNumber << "] does not exist ." << endl;
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _ReadWithdrawAmount(Client);
    }


public:
    static  void ShowWithDrawcreen()
    {
        _DrawScreenHeader("\t Withdraw Screen");
        _PerformWithdrawOperation();
    }

};



