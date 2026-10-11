#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsDepositeScreen : protected clsScreen
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

    static void _ReadDepositeAmount(clsBankClient& Client)
    {
        system("cls");
        cout << "-----------------------------------------" << endl;
        cout << "            Deposite Screen        " << endl;
        cout << "-----------------------------------------" << endl;
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Deposite amount ? ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'N';
        cout << "\nAre You Sure You Want To Perform this Transaction ? (Y / N) ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            Client.Deposite(Amount);
            cout << "\nAmount Deposited Succssefully.\n";
            cout << "\nNew Balance Is : " << Client.AccountBalance << endl;
        }
        else
        {
            cout << "\nOperation Was Cancelled\n";
        }
    }

    static void _PerformDepositeOperation()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        string AccountNumber = _ReadAccountNumber();
        while(!(clsBankClient::IsClientExist(AccountNumber)))
        {
                cout << "\nClient With [" << AccountNumber << "] does not exist ." << endl;
                AccountNumber = _ReadAccountNumber();
        } 

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _ReadDepositeAmount(Client);

    }


public:
    static  void ShowDepositeScreen()
    {
        _DrawScreenHeader("\tDeposite Screen");
        _PerformDepositeOperation();
    }

};

