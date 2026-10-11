#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient& Client)
	{
		cout << "\nClient Card : \n";
		cout << "________________________\n";
		cout << "\nFullName   : " << Client.FullName();
		cout << "\nAcc.Number : " << Client.AccountNumber();
		cout << "\nBalance    : " << Client.AccountBalance;
		cout << "\n________________________\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber = "";
		cout << "\nPlease Enter Account Number? ";
		AccountNumber = clsInputValidate::ReadString();
		while (!(clsBankClient::IsClientExist(AccountNumber)))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient& SourceClient)
	{
		double Amount;

		cout << "\nEnter Transfer Amount? ";

		Amount = clsInputValidate::ReadDblNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

	static void _Transfer()
	{
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientCard(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClientCard(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'N';
		cout << "\nAre You Sure You Want To Perform this Operation ? (Y / N) ? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			SourceClient.Transfer(Amount, DestinationClient);
			cout << "\nTransfer Done Successfully :) \n";
			_PrintClientCard(SourceClient);
			_PrintClientCard(DestinationClient);
		}
		else
		{
			cout << "\nOperation Was Cancelled :( \n";
		}
	}

public :

	static void ShowTransferScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Transfer Screen ");
		_Transfer();
	}

};

