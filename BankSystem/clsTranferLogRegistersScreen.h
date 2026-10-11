#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"

class clsTranferLogRegistersScreen : protected clsScreen
{
private:
    static void _PrintTransferLogRegisterRecordLine(clsBankClient::stTransferLog& TrnasferLogRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(22) << left << TrnasferLogRegisterRecord.DateTime;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.SourceClient;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.DestinationClient;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.SourceClientBalanceAfterOperation;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.DestinationClientBalanceAfterOperation;
        cout << "| " << setw(10) << left << TrnasferLogRegisterRecord.Username;
    }

public:

    static void ShowTransferLogRegistersList()
    {
        vector <clsBankClient::stTransferLog> vTransferLogRegister = clsBankClient::GetTranferLogsList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRegister.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(22) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "d.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRegister.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferLog Record : vTransferLogRegister)
            {

                _PrintTransferLogRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};
