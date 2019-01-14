#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "Account.h"

using namespace std;

//menu function
char menu(string currentAccountString);

//load list function
void loadClientVector(ifstream& input_File, vector<Account>& receiving_Vector);

//--load account function
void loadActiveAccount(const vector<Account>& source_Vector, Account& active_Account);

//transfer from outside accounts function

int main()
{
  char choice = '0';
  Account account_To_Access;
  ifstream input_File;
  ofstream output_File;
  vector<Account> account_List;
  string current_Account, withdrawalTransaction, depositTransaction, transferTransaction;
  
  current_Account = "No Account has been loaded yet.\n";
  
  cout << "    Welcome to XXX Bank" << endl; 
  loadClientVector(input_File, account_List);  
  
  while(choice != 'exit character')
  {
    choice = menu(current_Account);

    switch (choice)
    { //all cases will have a function writing the transaction event to the history file before the break
      case '1' :
        loadActiveAccount(account_List, account_To_Access);
        current_Account = account_To_Access.last_Name + ", " + account_To_Access.first_Name + " " 
        + account_To_Access.dob_Month + "/" + account_To_Access.dob_Day + "/" + account_To_Access.dob_Year;
        break;
      case '2' :
        withdrawalTransaction = account_To_Access.withdrawMenu();
        break;
      case '3' : 
        depositTransaction = account_To_Access.depositMenu();
        break;
      case '4' : 
        transferTransaction = transferWithinAccount();
        break;
      case '5' :
        transferTransaction = transferWithinGroup(account_List);
        break;
      case '6' :
      /*load two vectors from DB files
        load account from group 1, load account from group 2
        withdraw from acct 1, deposit to acct 2
        */
        break;
      case '7' : 
        account_To_Access.printAccountBalances();
        break;
      case 8 : //exit
    }
  }
    
    
    return 0;
}

//        Function Definitions

// Menu Function:

char menu(string currentAccountString)
{
  string choice;
  cout << "What actions would you like to take now?" << endl;
  cout << "1. Select or change the active account. " << endl;
  cout << "2. Withdraw funds from current account. " << endl;
  cout << "3. Deposit funds into current account. " << endl;
  cout << "4. Make a transfer within the current account." << endl;
  cout << "5. Make a transfer between accounts in the same Client Group." << endl;
  cout << "6. Make a transfer between accounts in different Client Groups." << endl;
  cout << "7. View account balances for active account." << endl;
  cout << "8. Exit." << endl;
  cout << "Current active account: " << currentAccountString;
  
  
  do{
      getline(cin, choice);
      if (!isdigit(choice[0]))
      {
        cout << "You must enter a valid number from the menu.  Try again." << endl;
        continue;
      }
      else if(choice[0] < '1' || choice[0] > '9')
      {
        cout << "That is not a valid menu option. Try again." << endl;
      }
    }while(choice[0] < '1' || choice[0] > '4');
  
  return choice[0];
}

string setAccountChoice()
{
  string account_Choice;
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
  
  return account_Choice;
}
/*string withdraw(double& balance)
{
	double withdrawal;
	string withdrawalRecord;
    cout << "Withdraw how much?: ";
    cin >> withdrawal;
     
    if (withdrawal < balance)   
	{
	    balance -= withdrawal;
    }
    else                  
    {
	    cout << "You a broke boy" << endl;
    }
	 
	 return withdrawalRecord;
}

string deposit(double amount, string account)
{
	Account savings, checking;

	if (account == "S" || account == "s")
		savings.Add(amount);
	else
		checking.Add(amount);
}

string withdraw(double amount, string account)
{
	Account savings, checking;

	if (account == "S" || account == "s")
		savings.Withdraw(amount);
	else
		checking.Withdraw(amount);
}

string transfer(double amount, string account)
{
	Account savings, checking;

	if (account == "S" || account == "s")
	{
		savings.Withdraw(amount);
		checking.Add(amount);
	}
	else
	{
		checking.Withdraw(amount);
		savings.Add(amount);
	}
}

void printBalances()
{
	Account savings, checking;

	cout << "The current balance in savings is: " << savings.GetBalance() << endl;
	cout << "The current balance in checking is: " << checking.GetBalance() << endl << endl;
}*/

