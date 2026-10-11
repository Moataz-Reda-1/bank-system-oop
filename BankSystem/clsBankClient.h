#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	struct stTransferLog;

	static stTransferLog _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLog TransferLog;
		vector<string> vTransferLogDataLine = clsString::Split(Line, Separator);

		TransferLog.DateTime = vTransferLogDataLine[0];
		TransferLog.SourceClient = vTransferLogDataLine[1];
		TransferLog.DestinationClient = vTransferLogDataLine[2];
		TransferLog.Amount = stod(vTransferLogDataLine[3]);
		TransferLog.SourceClientBalanceAfterOperation = stod(vTransferLogDataLine[4]);
		TransferLog.DestinationClientBalanceAfterOperation = stod(vTransferLogDataLine[5]);
		TransferLog.Username =vTransferLogDataLine[6];

		return TransferLog;
	}


	string _PrepareTransferLogRecord(clsBankClient DestinationClient, double Amount, string Separator = "#//#")
	{
		string TransferLog = "";
		TransferLog += clsDate::GetSystemDateTimeString() + Separator;
		TransferLog += AccountNumber() + Separator;
		TransferLog += DestinationClient.AccountNumber() + Separator;
		TransferLog += to_string(Amount) + Separator;
		TransferLog += to_string(AccountBalance) + Separator;
		TransferLog += to_string(DestinationClient.AccountBalance) + Separator;
		TransferLog += CurrentUser.UserName;
		return TransferLog;
	}


	void _RegisterTransferLog(clsBankClient DestinationClient, double Amount, string Separator = "#//#")
	{
		string DataLine = _PrepareTransferLogRecord(DestinationClient, Amount);
		fstream File;
		File.open("TransferLog.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << DataLine << endl;
			File.close();
		}
	}


	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stof(vClientData[6]));

	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += clsUtil::EncryptText(Client.PinCode) + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}

	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}



public:

	struct stTransferLog
	{
		string DateTime;
		string SourceClient;
		string DestinationClient;
		double Amount;
		double SourceClientBalanceAfterOperation;
		double DestinationClientBalanceAfterOperation;
		string Username;
	};


	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n______________________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance << "$";
		cout << "\n______________________________\n";
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream File;
		File.open("Clients.txt", ios::in);
		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					File.close();
					return Client;
				}

			}

			File.close();

		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector < clsBankClient> vClients;
		fstream File;
		File.open("Clients.txt", ios::in);
		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					File.close();
					return Client;
				}

			}

			File.close();

		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 3 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return svFaildEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (IsClientExist(AccountNumber()))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;

	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();
		float TotalBalances = 0;
		for (clsBankClient& C : vClients)
		{
			if (C.MarkedForDelete() == false)
			{
				TotalBalances += C.AccountBalance;
			}
		}
		return TotalBalances;
	}


	void Deposite(double Amount)
	{

		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient)
	{

		if (Amount > AccountBalance)
		{
			return false;
		}
		Withdraw(Amount);
		DestinationClient.Deposite(Amount);
		_RegisterTransferLog(DestinationClient, Amount);
		return true;
	}

	static vector<stTransferLog> GetTranferLogsList()
	{
		vector <stTransferLog> vTransferRegisters;
		fstream File;
		File.open("TransferLog.txt", ios::in);
		if (File.is_open())
		{
			string Line;
			stTransferLog TransferLogRecord;
			while (getline(File, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferRegisters.push_back(TransferLogRecord);
			}
			File.close();
		}
		return vTransferRegisters;
	}

};

