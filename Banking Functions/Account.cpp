#include "stdafx.h"
#include "Account.h"

//  Penalty Fee Constant
const double PENALTY_FEE = 5.00;

Account::Account()
{
  first_Name = "Empty";
  last_Name = "Empty";
  client_Group = "Empty";
  ssn = "Empty";
  dob_Month = "1";
  dob_Day = "1";
  dob_Year = "1";
	checking_Balance = 0.00;
  savings_Balance = 0.00;
}

Account::Account(string fname, lname, grp, soc, mnth, day, year, double cmoney, smoney)
{
  first_Name =  fname;
  last_Name = lname;
  client_Group = grp;
  ssn = soc;
  dob_Month = mnth;
  dob_Day = day;
  dob_Year = yr;
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

void Account::setCheckingBalance(double amount)
{
  checking_Balance = amount;
}

void Account::setSavingsBalance(double amount)
{
  savings_Balance = amount;
}

string Account::depositChecking()
{
  string output, confirm;
  double money;
  
  cout << "How much would you like to deposit into this checking account?" << endl;
  cout << "Enter amount in 0.00 format: $";
	
  while( !(cin >> money) )
  {
    cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
    cin.clear();
    cin.ignore(1000, '\n');
  }
      
  cout << "Deposit $" << money << " into checking account for account number" << account_Number << "?\n";
  cout << "[Y]: Yes.\n[N]: No.\n";
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
      
  if(confirm[0] == 'Y' || confirm[0] == 'y')
  {
    checking_Balance += money;
    cout >> "Funds deposited. Your new checking account balance is: $" << checking_Balance;
    output = "Deposit Transaction: $" + money + "deposited into checking account. New Balance: $" + checking_Balance + "\n";
    return output;
  }
  else
  {
    cout << "Deposit cancelled.\n";
    output = "";
    return output;
  }
  
string Account::depositSavings()
{
  string output, confirm;
  double money;
  
  cout << "How much would you like to deposit into this savings account?" << endl;
  cout << "Enter amount in 0.00 format: $";
	
  while( !(cin >> money) )
  {
    cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
    cin.clear();
    cin.ignore(1000, '\n');
  }
       
    cout << "Deposit $" << money << " into savings account for account number" << account_Number << "?\n";
    cout << "[Y]: Yes.\n[N]: No.\n";
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
      
  if(confirm[0] == 'Y' || confirm[0] == 'y')
  {
    savings_Balance += money;
    cout >> "Funds deposited. Your new savings account balance is: $" << savings_Balance;
    output = "Deposit Transaction: $" + money + "deposited into savings account. New Balance: $" + savings_Balance + "\n";
    return output;
  }
  else
  {
    cout << "Deposit cancelled.\n";
    output = "";
    return output;
  }
}

string Account::withdrawChecking()
{
  cout << "How much would you like to withdraw from this checking account?" << endl;
  cout << "Enter amount in 0.00 format: $";
	
  while( !(cin >> money) )
  {
    cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
    cin.clear();
    cin.ignore(1000, '\n');
  }
      
  cout << "Withdraw $" << money << " from checking account for account number" << account_Number << "?\n";
  cout << "Available funds in account: $" << checking_Balance << endl; 
  cout << "[Y]: Yes.\n[N]: No.\n";
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
      
  if(confirm[0] == 'Y' || confirm[0] == 'y')
  {
    if(checking_Balance < money)
    {
      checking_Balance -= (money + PENALTY_FEE);
      cout >> "Funds withdrawn. Your new checking account balance is: $" << checking_Balance;
      cout << "Your account is overdrawn.  You will not be able to make any further withdrawals " << 
           "from this checking account, and you have been charged a fee of $" << PENALTY_FEE << endl; 
      output = "Withdrawal Transaction: $" + money + " withdrawn from checking account. New Balance: $" + checking_Balance + "\n";
      return output;
    }
    else
    {
      checking_Balance -= money;
      cout >> "Funds withdrawn. Your new checking account balance is: $" << checking_Balance;
      output = "Withdrawal Transaction: $" + money + "withdrawn from checking account. New Balance: $" + checking_Balance + "\n";
      return output;
    }
  }
  else
  {
    cout << "Withdrawal cancelled.\n";
    output = "";
    return output;
  }
}

string Account::withdrawSavings()
{
  cout << "How much would you like to withdraw from this savings account?" << endl;
  cout << "Enter amount in 0.00 format: $";
	
  while( !(cin >> money) )
  {
    cout << "Invalid amount.  Please enter an amount in 0.00 format: $";
    cin.clear();
    cin.ignore(1000, '\n');
  }
       
    cout << "Withdraw $" << money << " from savings account for account number" << account_Number << "?\n";
    cout << "[Y]: Yes.\n[N]: No.\n";
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
      
  if(confirm[0] == 'Y' || confirm[0] == 'y')
  {
    if(savings_Balance < money)
    {
      savings_Balance -= (money + PENALTY_FEE);
      cout >> "Funds withdrawn. Your new savings account balance is: $" << savings_Balance;
      cout << "Your account is overdrawn.  You will not be able to make any further withdrawals from this savings account.\n";
      output = "Withdrawal Transaction: $" + money + "withdrawn from savings account. New Balance: $" + savings_Balance + "\n";
      return output;
    }
    else
    {
      savings_Balance -= money;
      cout >> "Funds withdrawn. Your new savings account balance is: $" << savings_Balance;
      output = "Withdrawal Transaction: $" + money + "withdrawn from savings account. New Balance: $" + savings_Balance + "\n";
      return output;
    }
  }
  else
  {
    cout << "Withdrawal cancelled.\n";
    output = "";
    return output;
  }
}


string Account::depositMenu()
{
  string output, account_Choice;
  
  cout << "Would you like to deposit money into your checking or savings account?\n";
  cout << "[C]: Checking.\n[S]: Savings.\n";
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
  
  
  if(account_Choice[0] == 'c' || account_Choice[0] == 'C')
  {
    output = depositChecking();
  }
    
  else if(account_Choice[0] == 's' || account_Choice[0] == 'S')
  {
    output = depositSavings();
  }
  
  return output;
}    

string Account::withdrawMenu()
{
  string output, confirm, account_Choice;
  double money;
  if(savings_Balance < 0 || checking_Balance < 0)
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
  
  if(account_Choice[0] == 'c' || account_Choice[0] == 'C')
  {
    output = withdrawChecking();
  }
    
  else if(account_Choice[0] == 's' || account_Choice[0] == 'S')
  {
    output = withdrawSavings();  
  }
  
  return output;
}

string Account::transferWithinAccount()
{
  string check, output;
  double original_Balance, withdrawn_Amount;
  
  cout << "Would you like to transfer money from your checking account to your savings account,\n";
  cout << "or from your savings account to your checking account?\n";
  cout << "[C]: Checking to Savings.\n[S]: Savings to Checking.\n";
  
  account_Choice = setAccountChoice();
  
  if(account_Choice == 'c' || account_Choice == 'C')
  {
    original_Balance = checking_Balance;
    check = withdrawChecking();
    
    if(checking_Balance < 0.0)
    {
      cout << "You cannot overdraw an account for a transfer.";
      checking_Balance = original_Balance;
      output = "";
      return output;
    }
    
    if check.empty();
      return check;
    
    withdrawn_Amount = original_Balance - checking_Balance;
    
    if (withdrawn_Amount = 0.0) 
    {
      check = "";
      return check;
    }
    
    savings_Balance += withdrawn_Amount;
    
    cout << "$" << withdrawn_Amount << " has been transferred from your checking account " <<
         "into your savings account.\n";
    cout << "New Balances:\n";
    printAccountBalances();    
    output = "Transfer Transaction: $" << withdrawn_Amount << "transferred from checking to savings.\n";
    return output;    
  }
  
  else
  {
    original_Balance = savings_Balance;
    check = withdrawSavings();
    
    if(savings_Balance < 0.0)
    {
      cout << "You cannot overdraw an account for a transfer.";
      savings_Balance = original_Balance;
      output = "";
      return output;
    }
    
    if check.empty();
      return check;
    
    withdrawn_Amount = original_Balance - savings_Balance;
    
    if (withdrawn_Amount = 0.0) 
    {
      check = "";
      return check;
    }
    
    checking_Balance += withdrawn_Amount;
    
    cout << "$" << withdrawn_Amount << " has been transferred from your savings account " <<
         "into your checking account.\n";
    cout << "New Balances:\n";
    printAccountBalances();    
    output = "Transfer Transaction: $" << withdrawn_Amount << "transferred from savings to checking.\n";
    return output;      
  }
  
}
