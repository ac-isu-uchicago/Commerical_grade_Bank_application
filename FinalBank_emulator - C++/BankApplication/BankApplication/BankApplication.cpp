// BankApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

//  Penalty Fee Constant
const double PENALTY_FEE = 5.00;

class Account
{
public:
	Account();
	Account(string fname, string lname, string grp, string soc, string mnth, string day, string yr,
		double cmoney, double smoney);

	friend char setAccountChoice();
	friend void updateClientGroup(const vector<Account>& source_Vector, string current_Group);
	friend void updateMultipleGroups(string out_Group_Filename, const vector<Account>& outGroup,
		string in_Group_Filename, const vector<Account>& inGroup);
	friend string loadClientVector(string fileName, vector<Account>& receiving_Vector);
	friend char loadByName(const vector<Account>& source_Vector, Account& activeAccount);
	friend char loadBySSN(const vector<Account>& source_Vector, Account& activeAccount);
	friend char loadByID(const vector<Account>& source_Vector, Account& activeAccount);

	string depositMenu();
	string withdrawMenu();
	string depositChecking();
	string depositSavings();
	string withdrawChecking();
	string withdrawSavings();
	string transferWithinAccount();
	void printAccountBalances();

	void setCheckingBalance(double amount);
	void setSavingsBalance(double amount);
	void setFirstName(string name);
	void setLastName(string name);
	void setClientGroup(string clientGroup);
	void setSSN(string ssn);
	void setDOBMonth(string month);
	void setDOBDay(string day);
	void setDOBYear(string year);
	void setFullDOB();
	void setAccountNumber(int idNumber);
	double getCheckingBalance();
	double getSavingsBalance();
	string getLastName();
	string getFirstName();
	string getFullDOB();
	string getSSN();
	string getGroup();
	int getAccountNumber();

private:
	double checking_Balance, savings_Balance;
	string first_Name, last_Name, client_Group, ssn,
		dob_Month, dob_Day, dob_Year,
		full_DOB;
	int account_Number;

};

// menu function
int menu(string currentAccountString, string currentGroup, Account& activeAccount);
// load list function
string loadClientVector(string fileName, vector<Account>& receiving_Vector);
// load account functions
void loadActiveAccount(const vector<Account>& source_Vector, Account& active_Account);
char loadByName(const vector<Account>& source_Vector, Account& activeAccount);
char loadBySSN(const vector<Account>& source_Vector, Account& activeAccount);
char loadByID(const vector<Account>& source_Vector, Account& activeAccount);
//transfer functions
string transferCtoS(Account& transferOutAccount, Account& transferInAccount);
string transferCtoC(Account& transferOutAccount, Account& transferInAccount);
string transferStoS(Account& transferOutAccount, Account& transferInAccount);
string transferStoC(Account& transferOutAccount, Account& transferInAccount);
string transferWithinGroup(vector<Account>& source_Vector);
string transferBetweenGroups();
// update functions
void updateClientGroup(const vector<Account>& source_Vector, string current_Group);
void updateMultipleHX(Account acct1, Account acct2, string hx);
void updateMultipleGroups(string out_Group_Filename, const vector<Account>& outGroup,
	string in_Group_Filename, const vector<Account>& inGroup);
// create a new account in the current group
void createAccount(Account& newAccount);
// delete account from the current group
void deleteAccount(vector<Account>& source_Vector);
// misc Functions
char setAccountChoice();

int main()
{
	int choice = 0;
	Account account_To_Access, newAccount;
	ifstream input_File;
	ofstream output_File;
	vector<Account> account_List;
	string temp, current_Group, current_Account, transactionHX, account_Hx_Filename, loadTest;

	current_Account = "No Account has been loaded yet.";
	current_Group = "No file has been successfully loaded.\n";
	cout << "Welcome to J.I.A. Bank" << endl;
	cout << "Please enter the filename for the Client Group (including suffix) you wish to load: ";
	cin >> temp;

	loadTest = loadClientVector(temp, account_List);
	if (loadTest != "FAIL")
	{
		current_Group = temp;
	}
	else
	{
		;
	}

	/*for (int i = 0; i < account_List.size(); i++)
	{
		cout << setw(20) << account_List[i].getLastName() << '|' << setw(20) << account_List[i].getFirstName()
			<< '|' << setw(10) << account_List[i].getSSN() << '|' << setw(11) << account_List[i].getFullDOB()
			<< '|' << setw(25) << account_List[i].getGroup() << '|' << setw(7)
			<< account_List[i].getAccountNumber() << '|' << setw(17) << account_List[i].getCheckingBalance()
			<< '|' << setw(17) << account_List[i].getSavingsBalance() << '|' << endl;
	}
	cout << "Size of Vector = " << account_List.size();
	*/

	cout << endl;
	while (choice != 11)
	{
		choice = menu(current_Account, current_Group, account_To_Access);

		switch (choice)
		{
		case 1: // Load an account
		{
			loadActiveAccount(account_List, account_To_Access);
      
      stringstream sstrm;
      sstrm << account_To_Access.getAccountNumber();
      string acctNumber = sstrm.str();
      sstrm.str("");
      sstrm.clear();
			
      current_Account = "LastName: " + account_To_Access.getLastName() + " FirstName: " + account_To_Access.getFirstName()
				+ " DOB: " + account_To_Access.getFullDOB() + " Account ID# " + acctNumber;

		    account_Hx_Filename = account_To_Access.getLastName() + account_To_Access.getSSN() + ".txt";

			break;
		}
		case 2: // Withdraw funds from an account
		{
			transactionHX = account_To_Access.withdrawMenu();
			if ( !(transactionHX.empty()) )
			{
				output_File.open(account_Hx_Filename, ios::app);
				output_File.setf(ios::fixed);
				output_File.setf(ios::showpoint);
				output_File.precision(2);
				output_File << transactionHX << endl;
				output_File.close();
				cout << "Account History file updated.\n";

				for (int i = 0; i < account_List.size(); i++)
				{
					if (account_To_Access.getAccountNumber() == account_List[i].getAccountNumber())
					{
						account_List[i] = account_To_Access;
						break;
					}
					if (i == account_List.size())
					{
						cout << "No matches found in currently loaded Client List! Unable to update.";
					}
				}
				
				updateClientGroup(account_List, current_Group);
				break;
			}
			else
			{
				break;
			}
		}

		case 3: // Deposit funds to an account
		{
			transactionHX = account_To_Access.depositMenu();
			if ( !(transactionHX.empty()) )
			{
				output_File.open(account_Hx_Filename, ios::app);
				output_File << transactionHX << endl;
				output_File.close();
				cout << "Account History file updated.\n";

				for (int i = 0; i < account_List.size(); i++)
				{
					if (account_To_Access.getAccountNumber() == account_List[i].getAccountNumber())
					{
						account_List[i] = account_To_Access;
						break;
					}
					if (i == account_List.size())
					{
						cout << "No matches found in currently loaded Client List! Unable to update.";
					}
				}
				
				updateClientGroup(account_List, current_Group);
				break;
			}
			else
			{
				break;
			}
		}

		case 4: // Transfer funds between checking and savings accounts of the same client
		{
			transactionHX = account_To_Access.transferWithinAccount();
			if ( !(transactionHX.empty()) )
			{
				output_File.open(account_Hx_Filename, ios::app);
				output_File << transactionHX << endl;
				output_File.close();
				cout << "Account History file updated.\n";

				for (int i = 0; i < account_List.size(); i++)
				{
					if (account_To_Access.getAccountNumber() == account_List[i].getAccountNumber())
					{
						account_List[i] = account_To_Access;
						break;
					}
					if (i == account_List.size())
					{
						cout << "No matches found in currently loaded Client List! Unable to update.";
					}
				}
				updateClientGroup(account_List, current_Group);
				break;
			}
			else
			{
				break;
			}
		}

		case 5: // Transfer funds between clients in the same Group
		{
			transactionHX = transferWithinGroup(account_List);
			if ( !(transactionHX.empty()) )
			{
				output_File.open("transferHistory.txt", ios::app);
				output_File << transactionHX << endl;
				output_File.close();
				cout << "Account History file updated.\n";
				updateClientGroup(account_List, current_Group);
				break;
			}
			else
			{
				break;
			}
		}

		case 6: // Transfer funds between clients in different Groups
		{
			transactionHX = transferBetweenGroups();
			if ( !(transactionHX.empty()) )
			{
				output_File.open("transferHistory.txt", ios::app);
				output_File << transactionHX << endl;
				output_File.close();

				cout << "Account History file updated.\n";
				break;
			}
			else
			{
				break;
			}
		}

		case 7: // Display current account balances for the active account
		{
			cout << endl;
			account_To_Access.printAccountBalances();
			cout << endl;
			break;
		}
		case 8: // Create a new client account and add it to the current group
		{
			createAccount(newAccount);
			account_List.push_back(newAccount);
			updateClientGroup(account_List, current_Group);
			break;
		}
		case 9: // Delete a client account from the current group
		{
			deleteAccount(account_List);
			updateClientGroup(account_List, current_Group);
			break;
		}
		case 10: // Load a new client group into the main vector
		{
			cout << "Please enter the filename for the Client Group (including suffix) you wish to load: ";
			cin >> temp;

			loadTest = loadClientVector(temp, account_List);
			if (loadTest != "FAIL")
			{
				current_Group = temp;
			}
			else
			{
				;
			}
			break;
		}
		case 11: // Exit the program
			cout << "Good Bye!";
			break;

		default:
			cout << "Invalid Option." << endl;
			break;
		}
	}
	return 0;
}

//        Function Definitions


int menu(string currentAccountString, string currentGroup, Account& activeAccount)
{
	int choice;
	cout << endl << endl << "What actions would you like to take now?" << endl;
	cout << "1. Select or change the active account. " << endl;
	cout << "2. Withdraw funds from current account. " << endl;
	cout << "3. Deposit funds into current account. " << endl;
	cout << "4. Make a transfer within the current account." << endl;
	cout << "5. Make a transfer between accounts in the same Client Group." << endl;
	cout << "6. Make a transfer between accounts in different Client Groups." << endl;
	cout << "7. View account balances for active account." << endl;
	cout << "8. Create New Account in current Client Group." << endl;
	cout << "9. Delete Account from current Client Group." << endl;
	cout << "10. Load New Client Group." << endl;
	cout << "11. Exit" << endl << endl;
	cout << "Current active account: " << currentAccountString << endl;
	cout << "Checking Balance: $" << activeAccount.getCheckingBalance() << endl;
	cout << "Savings Balance: $" << activeAccount.getSavingsBalance() << endl;
	cout << "Current active Client Group: " << currentGroup << endl;

	while (!(cin >> choice))
	{
		cout << "Invalid choice, please choose an option from the menu.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter your selection: ";
	}

	return choice;
}

char setAccountChoice()
{
	string account_Choice;
	cin.ignore(1000, '\n');
	getline(cin, account_Choice);

	while
	(
		(account_Choice[0] != 'c' && account_Choice[0] != 'C')
		&&
		(account_Choice[0] != 's' && account_Choice[0] != 'S')
	)
	{
		cout << "Invalid option.  Please try again.\n";
		cout << "[C]: Checking.\n[S]: Savings.\n";
		getline(cin, account_Choice);
	}

	return account_Choice[0];
}

Account::Account()
{
	first_Name = "Empty";
	last_Name = "Empty";
	client_Group = "Empty";
	ssn = "Empty";
	dob_Month = "1";
	dob_Day = "1";
	dob_Year = "1111";
	full_DOB = dob_Month + '/' + dob_Day + '/' + dob_Year;
	checking_Balance = 0.00;
	savings_Balance = 0.00;
	account_Number = 0;
}

Account::Account(string fname, string lname, string grp, string soc, string mnth, string day, string yr, double cmoney, double smoney)
{
	first_Name = fname;
	last_Name = lname;
	client_Group = grp;
	ssn = soc;
	dob_Month = mnth;
	dob_Day = day;
	dob_Year = yr;
	full_DOB = mnth + '/' + day + '/' + yr;
	checking_Balance = cmoney;
	savings_Balance = smoney;
}

void Account::printAccountBalances()
{
	cout << "Checking Account Balance: $" << checking_Balance << endl << "Savings Account Balance: $" <<
		savings_Balance << endl;
}

double Account::getCheckingBalance()
{
	return checking_Balance;
}

double Account::getSavingsBalance()
{
	return savings_Balance;
}

string Account::getLastName()
{
	return last_Name;
}

string Account::getFirstName()
{
	return first_Name;
}

string Account::getSSN()
{
	return ssn;
}

string Account::getGroup()
{
	return client_Group;
}

string Account::getFullDOB()
{
	return full_DOB;
}

int Account::getAccountNumber()
{
	return account_Number;
}

void Account::setCheckingBalance(double amount)
{
	checking_Balance = amount;
}

void Account::setSavingsBalance(double amount)
{
	savings_Balance = amount;
}

void Account::setFirstName(string name)
{
	first_Name = name;
}

void Account::setLastName(string name)
{
	last_Name = name;
}

void Account::setClientGroup(string clientGroup)
{
	client_Group = clientGroup;
}

void Account::setSSN(string soc)
{
	ssn = soc;
}

void Account::setDOBMonth(string month)
{
	dob_Month = month;
}

void Account::setDOBDay(string day)
{
	dob_Day = day;
}

void Account::setDOBYear(string year)
{
	dob_Year = year;
}

void Account::setFullDOB()
{
	full_DOB = dob_Month + '/' + dob_Day + '/' + dob_Year;
}

void Account::setAccountNumber(int idNumber)
{
	account_Number = idNumber;
}

string Account::depositChecking()
{
	string output, confirm, money_String, checking_Bal_String;
	double money;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "How much would you like to deposit into this checking account?" << endl;
	cout << "Current Checking Balance: $" << checking_Balance << endl;
	cout << "Enter amount in 0.00 format: $";

	while (!(cin >> money))
	{
		cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << money;
	money_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	cout << endl << "Deposit $" << money << " into checking account for account number " << account_Number << "?\n";
	cout << "[Y]: Yes.\n[N]: No.\n";
	cin.ignore(1000, '\n');
	getline(cin, confirm);

	while
	(
		(confirm[0] != 'y' && confirm[0] != 'Y')
		&&
		(confirm[0] != 'n' && confirm[0] != 'N')
	)
	{
		cout << "Invalid option.  Please try again.\n";
		cout << "[Y]: Yes.\n[N]: No.\n";
		getline(cin, confirm);
	}

	if (confirm[0] == 'Y' || confirm[0] == 'y')
	{
		checking_Balance += money;
		
		sstrm << fixed << setprecision(2) << checking_Balance;
		checking_Bal_String = sstrm.str();
		sstrm.str("");
		sstrm.clear();

		cout << endl << "Funds deposited. Your new checking account balance is: $" << checking_Balance << endl;
		output = "Deposit Transaction: $" + money_String + " deposited into checking account. New Balance: $" + checking_Bal_String + "\n";
		return output;
	}
	else
	{
		cout << endl << "Deposit cancelled.\n\n";
		output = "";
		return output;
	}
}

string Account::depositSavings()
{
	string output, confirm, money_String, savings_Bal_String;
	double money;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "How much would you like to deposit into this savings account?" << endl;
	cout << "Current Savings Balance: $" << savings_Balance << endl;
	cout << "Enter amount in 0.00 format: $";

	while (!(cin >> money))
	{
		cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << money;
	money_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	cout << endl << "Deposit $" << money << " into savings account for account number " << account_Number << "?\n";
	cout << "[Y]: Yes.\n[N]: No.\n";
	cin.ignore(1000, '\n');
	getline(cin, confirm);

	while
	(
		(confirm[0] != 'y' && confirm[0] != 'Y')
		&&
		(confirm[0] != 'n' && confirm[0] != 'N')
	)
	{
		cout << "Invalid option.  Please try again.\n";
		cout << "[Y]: Yes.\n[N]: No.\n";
		getline(cin, confirm);
	}

	if (confirm[0] == 'Y' || confirm[0] == 'y')
	{
		savings_Balance += money;
		
		sstrm << fixed << setprecision(2) << savings_Balance;
		savings_Bal_String = sstrm.str();
		sstrm.str("");
		sstrm.clear();

		cout << endl << "Funds deposited. Your new savings account balance is: $" << savings_Balance << endl;
		output = "Deposit Transaction: $" + money_String + " deposited into savings account. New Balance: $" + savings_Bal_String + "\n";
		return output;
	}
	else
	{
		cout << endl << "Deposit cancelled.\n\n";
		output = "";
		return output;
	}
}

string Account::withdrawChecking()
{
	double money;
	string confirm, output, money_String, checking_Bal_String;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "How much would you like to withdraw from this checking account?" << endl;
	cout << "Current Checking Balance: $" << checking_Balance << endl;
	cout << "Enter amount in 0.00 format: $";

	while (!(cin >> money))
	{
		cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << money;
	money_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	cout << endl << "Withdraw $" << money << " from checking account for account number " << account_Number << "?\n";
	cout << "Available funds in account: $" << checking_Balance << endl;
	cout << "[Y]: Yes.\n[N]: No.\n";
	cin.ignore(1000, '\n');
	getline(cin, confirm);

	while
	(
		(confirm[0] != 'y' && confirm[0] != 'Y')
		&&
		(confirm[0] != 'n' && confirm[0] != 'N')
	)
	{
		cout << "Invalid option.  Please try again.\n";
		cout << "[Y]: Yes.\n[N]: No.\n";
		getline(cin, confirm);
	}

	if (confirm[0] == 'Y' || confirm[0] == 'y')
	{
		if (checking_Balance < money)
		{
			checking_Balance -= (money + PENALTY_FEE);
			
			sstrm << fixed << setprecision(2) << checking_Balance;
			checking_Bal_String = sstrm.str();
			sstrm.str("");
			sstrm.clear();

			cout << endl << "Funds withdrawn. Your new checking account balance is: $" << checking_Balance << endl;
			cout << "Your account is overdrawn.  You will not be able to make any further withdrawals " <<
				"from this account, and you have been charged a fee of $" << PENALTY_FEE << endl;
			output = "Withdrawal Transaction: $" + money_String + " withdrawn from checking account. New Balance: $" + checking_Bal_String + "\n";
			return output;
		}
		else
		{
			checking_Balance -= money;
			
			sstrm << fixed << setprecision(2) << checking_Balance;
			checking_Bal_String = sstrm.str();
			sstrm.str("");
			sstrm.clear();
			
			cout << endl << "Funds withdrawn. Your new checking account balance is: $" << checking_Balance << endl;
			output = "Withdrawal Transaction: $" + money_String + " withdrawn from checking account. New Balance: $" + checking_Bal_String + "\n";
			return output;
		}
	}
	else
	{
		cout << endl << "Withdrawal cancelled.\n\n";
		output = "";
		return output;
	}
}

string Account::withdrawSavings()
{
	double money;
	string confirm, output, money_String, savings_Bal_String;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "How much would you like to withdraw from this savings account?" << endl;
	cout << "Current Savings Balance: $" << savings_Balance << endl;
	cout << "Enter amount in 0.00 format: $";

	while (!(cin >> money))
	{
		cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << money;
	money_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	cout << endl << "Withdraw $" << money << " from savings account for account number " << account_Number << "?\n";
	cout << "[Y]: Yes.\n[N]: No.\n";
	cin.ignore(1000, '\n');
	getline(cin, confirm);

	while
	(
		(confirm[0] != 'y' && confirm[0] != 'Y')
		&&
		(confirm[0] != 'n' && confirm[0] != 'N')
	)
	{
		cout << "Invalid option.  Please try again.\n";
		cout << "[Y]: Yes.\n[N]: No.\n";
		getline(cin, confirm);
	}

	if (confirm[0] == 'Y' || confirm[0] == 'y')
	{
		if (savings_Balance < money)
		{
			savings_Balance -= (money + PENALTY_FEE);
			
			sstrm << fixed << setprecision(2) << savings_Balance;
			savings_Bal_String = sstrm.str();
			sstrm.str("");
			sstrm.clear();

			cout << endl << "Funds withdrawn. Your new savings account balance is: $" << savings_Balance << endl;
			cout << "Your account is overdrawn.  You will not be able to make any further withdrawals from this account, and you have been charged a fee of $" << PENALTY_FEE << endl;
			output = "Withdrawal Transaction: $" + money_String + " withdrawn from savings account. New Balance: $" + savings_Bal_String + "\n";
			return output;
		}
		else
		{
			savings_Balance -= money;

			sstrm << fixed << setprecision(2) << savings_Balance;
			savings_Bal_String = sstrm.str();
			sstrm.str("");
			sstrm.clear();
			
			cout << endl << "Funds withdrawn. Your new savings account balance is: $" << savings_Balance << endl;
			output = "Withdrawal Transaction: $" + money_String + " withdrawn from savings account. New Balance: $" + savings_Bal_String + "\n";
			return output;
		}
	}
	else
	{
		cout << endl << "Withdrawal cancelled.\n\n";
		output = "";
		return output;
	}
}

string Account::depositMenu()
{
	string output;
	char account_Choice;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Would you like to deposit money into your checking or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";
	
	account_Choice = setAccountChoice();

	if (account_Choice == 'c' || account_Choice == 'C')
	{
		output = depositChecking();
	}

	else if (account_Choice == 's' || account_Choice == 'S')
	{
		output = depositSavings();
	}

	return output;
}

string Account::withdrawMenu()
{
	string output;
	char account_Choice;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);
	
	if (savings_Balance < 0 || checking_Balance < 0)
	{
		cout << "One of your accounts is overdrawn.  You may not make withdrawals at this time.\n";
		cout << "Make a deposit or a transfer to put the overdrawn account back into good standing.\n";
		cout << "Checking Account balance: $" << checking_Balance << endl;
		cout << "Savings Account balance: $" << savings_Balance << endl;
		output = "";
		return output;
	}
	cout << "Would you like to withdraw money from your checking or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";

	account_Choice = setAccountChoice();

	if (account_Choice == 'c' || account_Choice == 'C')
	{
		output = withdrawChecking();
		return output;
	}
	else if (account_Choice == 's' || account_Choice == 'S')
	{
		output = withdrawSavings();
		return output;
	}
}

string Account::transferWithinAccount()
{
	char account_Choice;
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Would you like to transfer money from your checking account to your savings account,\n";
	cout << "or from your savings account to your checking account?\n";
	cout << "[C]: Checking to Savings.\n[S]: Savings to Checking.\n";

	account_Choice = setAccountChoice();

	if (account_Choice == 'c' || account_Choice == 'C')
	{
		original_Balance = checking_Balance;
		check = withdrawChecking();

		if (checking_Balance < 0.0)
		{
			cout << "You cannot overdraw an account for a transfer.";
			checking_Balance = original_Balance;
			output = "";
			return output;
		}

		if (check.empty())
			return check;

		withdrawn_Amount = original_Balance - checking_Balance;

		if (withdrawn_Amount == 0.0)
		{
			check = "";
			return check;
		}

		stringstream sstrm;
		sstrm << fixed << setprecision(2) << withdrawn_Amount;
		withdrawn_String = sstrm.str();
		sstrm.str("");
		sstrm.clear();

		savings_Balance += withdrawn_Amount;

		cout << "$" << withdrawn_Amount << " has been transferred from your checking account into your savings account.\n";
		cout << "New Balances:\n\n";
		printAccountBalances();
		cout << endl;
		output = "Transfer Transaction: $" + withdrawn_String + " transferred from checking to savings.\n";
		return output;
	}

	else
	{
		original_Balance = savings_Balance;
		check = withdrawSavings();

		if (savings_Balance < 0.0)
		{
			cout << "You cannot overdraw an account for a transfer.";
			savings_Balance = original_Balance;
			output = "";
			return output;
		}

		if (check.empty())
			return check;

		withdrawn_Amount = original_Balance - savings_Balance;

		stringstream sstrm;
		sstrm << fixed << setprecision(2) << withdrawn_Amount;
		withdrawn_String = sstrm.str();
		sstrm.str("");
		sstrm.clear();

		if (withdrawn_Amount == 0.0)
		{
			check = "";
			return check;
		}

		checking_Balance += withdrawn_Amount;

		cout << "$" << withdrawn_Amount << " has been transferred from your savings account into your checking account.\n";
		cout << "New Balances:\n\n";
		printAccountBalances();
		cout << endl;
		output = "Transfer Transaction: $" + withdrawn_String + " transferred from savings to checking.\n";
		return output;
	}

}

string loadClientVector(string fileName, vector<Account>& receiving_Vector)
{
	ifstream input_File;
	Account intake_Account;
	string trash;

	cout << endl << "Retrieving Account List From Source File: " << fileName << endl;
	input_File.open(fileName);
	if (input_File.fail())                     //Testing for successful file opening
	{
		cout << endl << "Failed to open file.\n\n";
		trash = "FAIL";
		return trash;
	}
	else
	{
		cout << "File opened successfully. Loading Accounts..." << endl << endl;
	}

	receiving_Vector.clear();

	// Skip first two lines of file
	for (int i = 0; i < 2; i++)
		getline(input_File, trash);

	while (!input_File.eof())
	{
		input_File >> intake_Account.last_Name;
		getline(input_File, trash, '|');
		
		input_File >> intake_Account.first_Name;
		getline(input_File, trash, '|');
		
		input_File >> intake_Account.ssn;
		getline(input_File, trash, '|');

		getline(input_File, intake_Account.dob_Month, '/');

		getline(input_File, intake_Account.dob_Day, '/');

		getline(input_File, intake_Account.dob_Year, '|');
		
		intake_Account.setFullDOB();
		
		input_File >> intake_Account.client_Group;
		getline(input_File, trash, '|');
		input_File >> intake_Account.account_Number;
		getline(input_File, trash, '|');
		input_File >> intake_Account.checking_Balance;
		getline(input_File, trash, '|');
		input_File >> intake_Account.savings_Balance;
		getline(input_File, trash);

		receiving_Vector.push_back(intake_Account);
		
		if (input_File.peek() == EOF)
			break;
	}

	input_File.close();
	return "SUCCESS";
}

void loadActiveAccount(const vector<Account>& source_Vector, Account& active_Account)
{
	char menuLooper;
	int choice;

	do
	{
		cout << "Would you like to search for an account by Last Name, SSN, or Account Number?" << endl;
		cout << "1. Last Name\n2. SSN\n3. Account #\n4. Cancel" << endl;

		while (!(cin >> choice))
		{
			cout << "That is not a valid option, try again.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Enter the number: ";
		}


		switch (choice)
		{
		case 1:
			menuLooper = loadByName(source_Vector, active_Account);
			break;
		case 2:
			menuLooper = loadBySSN(source_Vector, active_Account);
			break;
		case 3:
			menuLooper = loadByID(source_Vector, active_Account);
			break;
		case 4:
			menuLooper = '0';
			break;

		default:
			cout << "Invalid option, try again.\n";
			menuLooper = '1';
			break;
		}
	} while (menuLooper == '1');

}

char loadByName(const vector<Account>& source_Vector, Account& activeAccount)
{
	string name, trash, lastNm;
	int input;
	vector<Account> matchedAccounts;
	cout << "Enter the Last Name of the Client: ";
	getline(cin, trash, '\n');
	getline(cin, name);

	for (int i = 0; i < source_Vector.size(); i++)
	{
		lastNm = source_Vector[i].last_Name.substr(0, name.length());
		if (name == lastNm)
		{
			matchedAccounts.push_back(source_Vector[i]);
		}
	}

	if (matchedAccounts.empty())
	{
		cout << "There were no Accounts that matched that name.  Please try your search again." << endl << endl;
		return '1'; // continues menu loop in loading function
	}

	cout << endl;

	for (int i = 0; i < matchedAccounts.size(); i++)
	{
		cout << "#" << i + 1 << " " << matchedAccounts[i].last_Name << ", " << matchedAccounts[i].first_Name << " -- " <<
			"DOB: " << matchedAccounts[i].full_DOB << " -- " << "Account Number: " << matchedAccounts[i].account_Number
			<< endl;
	}

	cout << endl << "Enter the number following the '#' sign that corresponds to the account you wish to access, "
		<< "or enter 0 to perform a new search.\n";

	while (!(cin >> input))
	{
		cout << "That is not a valid option, try again.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter the number: ";
	}

	while (input < 0 || input > matchedAccounts.size())
	{
		cout << "That is not a valid option, try again.\n";
		cout << "Enter the number: ";
		while (!(cin >> input))
		{
			cout << "That is not a valid option, try again.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Enter the number: ";
		}
	}

	if (input == 0)
	{
		return '1';
	}

	activeAccount = matchedAccounts[input-1];
	return '0'; // terminates menu loop in loading function
}

char loadBySSN(const vector<Account>& source_Vector, Account& activeAccount)
{
	string ssn, trash;
	int input;
	vector<Account> matchedAccounts;
	cout << "Enter the Social Security Number of the Client, with no dashes or spaces: ";
	getline(cin, trash, '\n');
	getline(cin, ssn);

	for (int i = 0; i < source_Vector.size(); i++)
	{
		if ( ssn == source_Vector[i].ssn.substr(0, ssn.length()) )
		{
			matchedAccounts.push_back(source_Vector[i]);
		}
	}

	if (matchedAccounts.empty())
	{
		cout << "There were no Accounts with that Soc. Sec. Number.  Please try your search again." << endl << endl;
		return '1'; // continues menu loop in loading function
	}

	cout << endl;

	for (int i = 0; i < matchedAccounts.size(); i++)
	{
		cout << "#" << i + 1 << " " << matchedAccounts[i].last_Name << ", " << matchedAccounts[i].first_Name << " -- " <<
			"DOB: " << matchedAccounts[i].full_DOB << " -- " << "Account Number: " << matchedAccounts[i].account_Number
			<< endl;
	}

	cout << endl << "Enter the number following the '#' sign that corresponds to the account you wish to access, "
		<< "or enter 0 to perform a new search.\n";

	while (!(cin >> input))
	{
		cout << "That is not a valid option, try again.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter the number: ";
	}

	while (input < 0 || input > matchedAccounts.size())
	{
		cout << "That is not a valid option, try again.\n";
		cout << "Enter the number: ";
		while (!(cin >> input))
		{
			cout << "That is not a valid option, try again.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Enter the number: ";
		}
	}

	if (input == 0)
	{
		return '1';
	}

	activeAccount = matchedAccounts[input - 1];
	return '0'; // terminates menu loop in loading function
}

char loadByID(const vector<Account>& source_Vector, Account& activeAccount)
{
	int input;

	cout << "Enter the Account ID Number of the account you wish to access: ";
	
	while (!(cin >> input))
	{
		cout << "That is not a valid option, try again.\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter the number: ";
	}


	for (int i = 0; i < source_Vector.size(); i++)
	{
		if (input == source_Vector[i].account_Number)
		{
			activeAccount = source_Vector[i];
			return '0'; //terminates menu loop in loading function
		}
	}

	cout << "No accounts found with that ID Number. Please try another search." << endl << endl;
	return '1'; // continues the menu loop in loading fuction
}

string transferCtoS(Account& transferOutAccount, Account& transferInAccount)
{
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	original_Balance = transferOutAccount.getCheckingBalance();
	check = transferOutAccount.withdrawChecking();

	if (transferOutAccount.getCheckingBalance() < 0.0)
	{
		cout << "You cannot overdraw an account for a transfer." << endl;
		transferOutAccount.setCheckingBalance(original_Balance);
		output = "";
		return output;
	}

	if (check.empty())
	return check;

	withdrawn_Amount = original_Balance - transferOutAccount.getCheckingBalance();

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << withdrawn_Amount;
	withdrawn_String = sstrm.str();

	if (withdrawn_Amount == 0.0)
	{
		check = "";
		return check;
	}

	transferInAccount.setSavingsBalance(transferInAccount.getSavingsBalance() + withdrawn_Amount);
	
	output = "Transferred $" + withdrawn_String + " from " + transferOutAccount.getFirstName() +
		"'s checking account to " + transferInAccount.getFirstName() + "'s savings account.\n";
	
	updateMultipleHX(transferInAccount, transferOutAccount, output);
	return output;
}

string transferCtoC(Account& transferOutAccount, Account& transferInAccount)
{
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	original_Balance = transferOutAccount.getCheckingBalance();
	check = transferOutAccount.withdrawChecking();

	if (transferOutAccount.getCheckingBalance() < 0.0)
	{
		cout << "You cannot overdraw an account for a transfer.";
		transferOutAccount.setCheckingBalance(original_Balance);
		output = "";
		return output;
	}

	if (check.empty())
		return check;

	withdrawn_Amount = original_Balance - transferOutAccount.getCheckingBalance();

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << withdrawn_Amount;
	withdrawn_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	if (withdrawn_Amount == 0.0)
	{
		check = "";
		return check;
	}

	transferInAccount.setCheckingBalance(transferInAccount.getCheckingBalance() + withdrawn_Amount);
	
	output = "Transferred $" + withdrawn_String + " from " + transferOutAccount.getFirstName() +
		"'s checking account to " + transferInAccount.getFirstName() + "'s checking account.\n";
	
	updateMultipleHX(transferInAccount, transferOutAccount, output);
	return output;
}

string transferStoS(Account& transferOutAccount, Account& transferInAccount)
{
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	original_Balance = transferOutAccount.getSavingsBalance();
	check = transferOutAccount.withdrawSavings();

	if (transferOutAccount.getSavingsBalance() < 0.0)
	{
		cout << "You cannot overdraw an account for a transfer.";
		transferOutAccount.setSavingsBalance(original_Balance);
		output = "";
		return output;
	}

	if (check.empty())
	return check;

	withdrawn_Amount = original_Balance - transferOutAccount.getSavingsBalance();

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << withdrawn_Amount;
	withdrawn_String = sstrm.str();

	if (withdrawn_Amount == 0.0)
	{
		check = "";
		return check;
	}

	transferInAccount.setSavingsBalance(transferInAccount.getSavingsBalance() + withdrawn_Amount);
	
	output = "Transferred $" + withdrawn_String + " from " + transferOutAccount.getFirstName() +
		"'s savings account to " + transferInAccount.getFirstName() + "'s savings account.\n";
	
	updateMultipleHX(transferInAccount, transferOutAccount, output);
	return output;
}

string transferStoC(Account& transferOutAccount, Account& transferInAccount)
{
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	original_Balance = transferOutAccount.getSavingsBalance();
	check = transferOutAccount.withdrawSavings();

	if (transferOutAccount.getSavingsBalance() < 0.0)
	{
		cout << "You cannot overdraw an account for a transfer.";
		transferOutAccount.setSavingsBalance(original_Balance);
		output = "";
		return output;
	}

	if (check.empty())
	return check;

	withdrawn_Amount = original_Balance - transferOutAccount.getSavingsBalance();

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << withdrawn_Amount;
	withdrawn_String = sstrm.str();

	if (withdrawn_Amount == 0.0)
	{
		check = "";
		return check;
	}

	transferInAccount.setCheckingBalance(transferInAccount.getCheckingBalance() + withdrawn_Amount);
	
	output = "Transferred $" + withdrawn_String + " from " + transferOutAccount.getFirstName() +
		"'s savings account to " + transferInAccount.getFirstName() + "'s checking account.\n";
	
	updateMultipleHX(transferInAccount, transferOutAccount, output);
	return output;
}

string transferWithinGroup(vector<Account>& source_Vector)
{
	Account transferOutAccount, transferInAccount;
	char in_Account_Choice, out_Account_Choice;
	string  output;

	cout << "Please select the account from which you wish to withdraw funds.\n";
	loadActiveAccount(source_Vector, transferOutAccount);
	cout << "Please select the account into which you wish to transfer funds.\n";
	loadActiveAccount(source_Vector, transferInAccount);

	cout << "Would you like to transfer money out of " << transferOutAccount.getFirstName() <<
		"'s checking account or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";

	out_Account_Choice = setAccountChoice();

	cout << "Would you like to transfer money into " << transferInAccount.getFirstName() <<
		"'s checking account or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";

	cin.ignore(1000, '\n');
	in_Account_Choice = setAccountChoice();

	if
	(
		(out_Account_Choice == 'c' || out_Account_Choice == 'C')
		&&
		(in_Account_Choice == 's' || in_Account_Choice == 'S')
	)
	{
		output = transferCtoS(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		
		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferOutAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferOutAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}
		
		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferInAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferInAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}
		
		return output;
	}
	else if
	(
		(out_Account_Choice == 'c' || out_Account_Choice == 'C')
		&&
		(in_Account_Choice == 'c' || in_Account_Choice == 'C')
	)
	{
		output = transferCtoC(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		
		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferOutAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferOutAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}

		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferInAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferInAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}
		return output;
	}
	else if
	(
		(out_Account_Choice == 's' || out_Account_Choice == 'S')
		&&
		(in_Account_Choice == 's' || in_Account_Choice == 'S')
	)
	{
		output = transferStoS(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		
		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferOutAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferOutAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}

		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferInAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferInAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}
		
		return output;

	}
	else if
	(
		(out_Account_Choice == 's' || out_Account_Choice == 'S')
		&&
		(in_Account_Choice == 'c' || in_Account_Choice == 'C')
	)
	{
		output = transferStoC(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		
		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferOutAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferOutAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}

		for (int i = 0; i < source_Vector.size(); i++)
		{
			if (transferInAccount.getAccountNumber() == source_Vector[i].getAccountNumber())
			{
				source_Vector[i] = transferInAccount;
				break;
			}
			if (i == source_Vector.size())
			{
				cout << "No matches found in currently loaded Client List! Unable to update.";
			}
		}

		return output;
	}
}

string transferBetweenGroups()
{
	Account transferOutAccount, transferInAccount;
	string in_Group_Filename, out_Group_Filename, output;
	char in_Account_Choice, out_Account_Choice;
	vector<Account> outGroup, inGroup;

	do
	{
		cout << "Enter the filename (including suffix) for the Group supplying the account to transfer funds from: ";
		cin >> out_Group_Filename;

		loadClientVector(out_Group_Filename, outGroup);

	} while (outGroup.empty());

	do
	{
		cout << "Enter the filename (including suffix) for the Group supplying the account to transfer funds into: ";
		cin >> in_Group_Filename;

		loadClientVector(in_Group_Filename, inGroup);

	} while (inGroup.empty());

	cout << "Please select the account from which you wish to withdraw funds.\n";
	loadActiveAccount(outGroup, transferOutAccount);
	cout << "Please select the account into which you wish to transfer funds.\n";
	loadActiveAccount(inGroup, transferInAccount);

	cout << "Would you like to transfer money out of " << transferOutAccount.getFirstName() <<
		"'s checking account or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";

	out_Account_Choice = setAccountChoice();

	cout << "Would you like to transfer money into " << transferInAccount.getFirstName() <<
		"'s checking account or savings account?\n";
	cout << "[C]: Checking.\n[S]: Savings.\n";

	in_Account_Choice = setAccountChoice();

	if
		(
		(in_Account_Choice == 'c' || in_Account_Choice == 'C')
			&&
			(out_Account_Choice == 's' || out_Account_Choice == 'S')
			)
	{
		output = transferCtoS(transferOutAccount, transferInAccount);		
	string check, output, withdrawn_String;
	double original_Balance, withdrawn_Amount;

	original_Balance = transferOutAccount.getCheckingBalance();
	check = transferOutAccount.withdrawChecking();

	if (transferOutAccount.getCheckingBalance() < 0.0)
	{
		cout << "You cannot overdraw an account for a transfer.";
		transferOutAccount.setCheckingBalance(original_Balance);
		output = "";
		return output;
	}

	if (check.empty())
		return check;

	withdrawn_Amount = original_Balance - transferOutAccount.getCheckingBalance();

	stringstream sstrm;
	sstrm << fixed << setprecision(2) << withdrawn_Amount;
	withdrawn_String = sstrm.str();
	sstrm.str("");
	sstrm.clear();

	if (withdrawn_Amount == 0.0)
	{
		check = "";
		return check;
	}

	transferInAccount.setCheckingBalance(transferInAccount.getCheckingBalance() + withdrawn_Amount);
	
	output = "Transferred $" + withdrawn_String + " from " + transferOutAccount.getFirstName() +
		"'s checking account to " + transferInAccount.getFirstName() + "'s checking account.\n";
	
	updateMultipleHX(transferInAccount, transferOutAccount, output);
		
		
		
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		updateMultipleGroups(out_Group_Filename, outGroup, in_Group_Filename, inGroup);
		return output;
	}
	else if
		(
		(in_Account_Choice == 'c' || in_Account_Choice == 'C')
			&&
			(out_Account_Choice == 'c' || out_Account_Choice == 'C')
			)
	{
		output = transferCtoC(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		updateMultipleGroups(out_Group_Filename, outGroup, in_Group_Filename, inGroup);
		return output;
	}
	else if
		(
		(in_Account_Choice == 's' || in_Account_Choice == 'S')
			&&
			(out_Account_Choice == 's' || out_Account_Choice == 'S')
			)
	{
		output = transferStoS(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		updateMultipleGroups(out_Group_Filename, outGroup, in_Group_Filename, inGroup);
		return output;
	}
	else if
		(
		(in_Account_Choice == 's' || in_Account_Choice == 'S')
			&&
			(out_Account_Choice == 'c' || out_Account_Choice == 'C')
			)
	{
		output = transferStoC(transferOutAccount, transferInAccount);
		updateMultipleHX(transferInAccount, transferOutAccount, output);
		updateMultipleGroups(out_Group_Filename, outGroup, in_Group_Filename, inGroup);
		return output;
	}
}

void createAccount(Account& newAccount)
{
	ifstream infile;
	ofstream outfile;
	string stringVariable;
	double doubleVariable;
	int intVariable;

	// Assign First Name
	cout << "Enter new client's first name: ";
	cin.ignore(1000,'\n');
	getline(cin, stringVariable, '\n');

	if (stringVariable.size() > 20)
		stringVariable.resize(20);

	newAccount.setFirstName(stringVariable);

	// Assign Last Name
	cout << "Enter new client's last name: ";
	getline(cin, stringVariable, '\n');

	if (stringVariable.size() > 20)
		stringVariable.resize(20);

	newAccount.setLastName(stringVariable);

	// Assign SSN
	cout << "Enter the client's SSN with no dashes: ";
	getline(cin, stringVariable, '\n');

	while (stringVariable.size() != 9)
	{
		cout << "That is not a valid SSN, try another. Remember not to use dashes.\n";
		cout << "Enter filename for Client's Group (including suffix): ";
		getline(cin, stringVariable);
	}

	newAccount.setSSN(stringVariable);

	// Assign Group Filename
	cout << "Enter filename for Client's Group (including suffix): ";
	getline(cin, stringVariable, '\n');

	while (stringVariable.size() > 20)
	{
		cout << "That filename is too large, try another.\n";
		cout << "Enter filename for Client's Group (including suffix): ";
		getline(cin, stringVariable, '\n');
	}

	newAccount.setClientGroup(stringVariable);

	// Assign DOB month
	cout << "Enter the Client's month of birth as a number (1-12): ";
	getline(cin, stringVariable, '\n');

	while (stringVariable.size() < 1 || stringVariable.size() > 2)
	{
		cout << "That is not a valid month, try another.\n";
		cout << "Enter month: ";
		getline(cin, stringVariable, '\n');
	}

	newAccount.setDOBMonth(stringVariable);

	// Assign DOB day
	cout << "Enter the Client's day of birth as a number (1-31): ";
	getline(cin, stringVariable, '\n');

	while (stringVariable.size() < 1 || stringVariable.size() > 2)
	{
		cout << "That is not a valid day, try another.\n";
		cout << "Enter day: ";
		getline(cin, stringVariable, '\n');
	}

	newAccount.setDOBDay(stringVariable);

	// Assign DOB Year
	cout << "Enter the Client's year of birth as a 4-digit number: ";
	getline(cin, stringVariable, '\n');

	while (stringVariable.size() != 4)
	{
		cout << "That is not a valid year, try another.\n";
		cout << "Enter year (4-digit number): ";
		getline(cin, stringVariable, '\n');
	}

	newAccount.setDOBYear(stringVariable);

	// Assign Full DOB string
	newAccount.setFullDOB();

	// Assign initial Checking Balance
	cout << "Enter the Client's starting Checking Account Balance, using 0.00 format: $";
	while (!(cin >> doubleVariable))
	{
		cout << "That is not a valid amount, try again.";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	newAccount.setCheckingBalance(doubleVariable);

	// Assign initial Savings Balance
	cout << "Enter the Client's starting Savings Account Balance, using 0.00 format: $";
	while (!(cin >> doubleVariable))
	{
		cout << "That is not a valid amount, try again.";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	newAccount.setSavingsBalance(doubleVariable);

	// Assign Account Number
	cout << "Assigning Account Number.";
		infile.open("numberOfAccounts.txt");
	if (infile.fail())                     //Testing for successful file opening
	{
		cout << "Failed to retrieve running total of Accounts. Unable to assign account ID number.\n";
		return;
	}
	else
	{
		;
	}

	infile >> intVariable;
	intVariable++;
	newAccount.setAccountNumber(intVariable);
	infile.close();

	outfile.open("numberOfAccounts.txt");
	outfile << intVariable;
	outfile.close();
}

void deleteAccount(vector<Account>& source_Vector)
{}

void updateClientGroup(const vector<Account>& source_Vector, string current_Group)
{
	ofstream outFile;

	outFile.open(current_Group, ios::trunc);
	outFile.setf(ios::left);
	outFile.setf(ios::showpoint);
	outFile.setf(ios::fixed);
	outFile.precision(2);

	outFile << "Last Name           |First Name          |SSN       |DOB        |Client Group Filename    |Acct # |Checking Balance |Savings Balance  |" << endl;
	outFile << "=======================================================================================================================================" << endl;

	for (int i = 0; i < source_Vector.size(); i++)
	{
		outFile << setw(20) << source_Vector[i].last_Name << '|' << setw(20) << source_Vector[i].first_Name
			<< '|' << setw(10) << source_Vector[i].ssn << '|' << setw(11) << source_Vector[i].full_DOB
			<< '|' << setw(25) << source_Vector[i].client_Group << '|' << setw(7)
			<< source_Vector[i].account_Number << '|' << setw(17) << source_Vector[i].checking_Balance
			<< '|' << setw(17) << source_Vector[i].savings_Balance << '|' << endl;
	}

	outFile.close();
	return;
}

void updateMultipleHX(Account acct1, Account acct2, string hx)
{
	string first_Account_Filename = acct1.getLastName() + acct1.getSSN() + ".txt";
	string second_Account_Filename = acct2.getLastName() + acct2.getSSN() + ".txt";
	ofstream outfile;

	outfile.open(first_Account_Filename, ios::app);
	
	outfile << hx << endl;
	outfile.close();

	outfile.open(second_Account_Filename, ios::app);
	outfile << hx << endl;
	outfile.close();
}

void updateMultipleGroups(string out_Group_Filename, const vector<Account>& outGroup,
	string in_Group_Filename, const vector<Account>& inGroup)
{
	ofstream outFile;

	outFile.open(out_Group_Filename, ios::trunc);
	outFile.setf(ios::left);
	outFile.setf(ios::showpoint);
	outFile.setf(ios::fixed);
	outFile.precision(2);

	outFile << "Last Name           |First Name          |SSN       |DOB        |Client Group Filename    |Acct # |" << endl;
	outFile << "===================================================================================================" << endl;

	for (int i = 0; i < outGroup.size(); i++)
	{
		outFile << setw(20) << outGroup[i].last_Name << '|' << setw(20) << outGroup[i].first_Name
			<< '|' << setw(10) << outGroup[i].ssn << '|' << setw(11) << outGroup[i].full_DOB
			<< '|' << setw(25) << outGroup[i].client_Group << '|' << setw(7)
			<< outGroup[i].account_Number << '|' << endl;
	}
	outFile.close();

	outFile.open(in_Group_Filename, ios::trunc);
	outFile.setf(ios::left);
	outFile.setf(ios::showpoint);
	outFile.setf(ios::fixed);
	outFile.precision(2);

	outFile << "Last Name           |First Name          |SSN       |DOB        |Client Group Filename    |Acct # |" << endl;
	outFile << "===================================================================================================" << endl;

	for (int i = 0; i < outGroup.size(); i++)
	{
		outFile << setw(20) << inGroup[i].last_Name << '|' << setw(20) << inGroup[i].first_Name
			<< '|' << setw(10) << inGroup[i].ssn << '|' << setw(11) << inGroup[i].full_DOB
			<< '|' << setw(25) << inGroup[i].client_Group << '|' << setw(7)
			<< inGroup[i].account_Number << '|' << endl;
	}
	outFile.close();

	return;
}