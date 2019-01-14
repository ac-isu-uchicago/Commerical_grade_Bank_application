#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>      

using namespace std;

class Account
{
public:
	Account();
  Account(string fname, string lname, string grp, string soc, string mnth, string day, string year, 
  double cmoney, double smoney);
  
  friend string setAccountChoice();
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
  double getCheckingBalance();
  double getSavingsBalance();
  

private:
	double checking_Balance, savings_Balance;
  string first_Name, Last_Name, client_Group, ssn,
  dob_Month, dob_Day, dob_Year;
  int account_Number;
  
};