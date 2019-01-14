// Transfer Functions

string transferCtoS(Account& transferOutAccount, Account& transferInAccount)
{
  string check, output;
  double original_Balance, withdrawn_Amount;
  
  original_Balance = transferOutAccount.getCheckingBalance();
  check = transferOutAccount.withdrawChecking();
    
  if(transferOutAccount.getCheckingBalance() < 0.0)
  {
    cout << "You cannot overdraw an account for a transfer.";
    transferOutAccount.setCheckingBalance(original_Balance);
    output = "";
    return output;
  }
    
  if check.empty();
    return check;
  
  withdrawn_Amount = original_Balance - transferOutAccount.getCheckingBalance();
  
  if (withdrawn_Amount = 0.0) 
  {
    check = "";
    return check;
  }
  
  transferInAccount.setSavingsBalance(transferInAccount.getSavingsBalance() + withdrawn_Amount);
  output = "Transferred $" + withdrawn_Amount + " from " + transferOutAccount.getFirstName() + 
             "'s checking account to " + transferInAccount.getFirstName() + "'s savings account.\n";
  return output;
}

string transferCtoC(Account& transferOutAccount, Account& transferInAccount)
{
  string check, output;
  double original_Balance, withdrawn_Amount;
  
  original_Balance = transferOutAccount.getCheckingBalance();
  check = transferOutAccount.withdrawChecking();
    
  if(transferOutAccount.getCheckingBalance() < 0.0)
  {
    cout << "You cannot overdraw an account for a transfer.";
    transferOutAccount.setCheckingBalance(original_Balance);
    output = "";
    return output;
  }
    
  if check.empty();
    return check;
  
  withdrawn_Amount = original_Balance - transferOutAccount.getCheckingBalance();
  
  if (withdrawn_Amount = 0.0) 
  {
    check = "";
    return check;
  }
  
  transferInAccount.setCheckingBalance(transferInAccount.getCheckingBalance() + withdrawn_Amount);
  output = "Transferred $" + withdrawn_Amount + " from " + transferOutAccount.getFirstName() + 
             "'s checking account to " + transferInAccount.getFirstName() + "'s checking account.\n";
  return output;
}


string transferStoS(Account& transferOutAccount, Account& transferInAccount)
{
  string check, output;
  double original_Balance, withdrawn_Amount;
  
  original_Balance = transferOutAccount.getSavingsBalance();
  check = transferOutAccount.withdrawSavings();
    
  if(transferOutAccount.getSavingsBalance() < 0.0)
  {
    cout << "You cannot overdraw an account for a transfer.";
    transferOutAccount.setSavingsBalance(original_Balance);
    output = "";
    return output;
  }
    
  if check.empty();
    return check;
  
  withdrawn_Amount = original_Balance - transferOutAccount.getSavingsBalance();
  
  if (withdrawn_Amount = 0.0) 
  {
    check = "";
    return check;
  }
  
  transferInAccount.setSavingsBalance(transferInAccount.getSavingsBalance() + withdrawn_Amount);
  output = "Transferred $" + withdrawn_Amount + " from " + transferOutAccount.getFirstName() + 
             "'s savings account to " + transferInAccount.getFirstName() + "'s savings account.\n";
  return output;
}


string transferStoC(Account& transferOutAccount, Account& transferInAccount)
{
  string check, output;
  double original_Balance, withdrawn_Amount;
  
  original_Balance = transferOutAccount.getSavingsBalance();
  check = transferOutAccount.withdrawSavings();
    
  if(transferOutAccount.getSavingsBalance() < 0.0)
  {
    cout << "You cannot overdraw an account for a transfer.";
    transferOutAccount.setSavingsBalance(original_Balance);
    output = "";
    return output;
  }
    
  if check.empty();
    return check;
  
  withdrawn_Amount = original_Balance - transferOutAccount.getSavingsBalance();
  
  if (withdrawn_Amount = 0.0) 
  {
    check = "";
    return check;
  }
  
  transferInAccount.setCheckingBalance(transferInAccount.getCheckingBalance() + withdrawn_Amount);
  output = "Transferred $" + withdrawn_Amount + " from " + transferOutAccount.getFirstName() + 
             "'s savings account to " + transferInAccount.getFirstName() + "'s checking account.\n";
  return output;
}

string transferWithinGroup(vector<Account>& source_Vector)
{
  Account transferOutAccout, transferInAccount;
  double original_Balance;
  string in_Account_Choice, out_Account_Choice, output;
  
  cout << "Please select the account from which you wish to withdraw funds.\n";
  loadActiveAccount(source_Vector, transferOutAccout);
  cout << "Please select the account into which you wish to transfer funds.\n";
  loadActiveAccount(source_Vector, transferInAccount);
  
  cout << "Would you like to transfer money out of " << transferOutAccount.first_Name << 
       "'s checking account or savings account?\n";
  cout << "[C]: Checking.\n[S]: Savings.\n";
  
  out_Account_Choice = setAccountChoice();  
  
  cout << "Would you like to transfer money into " << transferInAccount.first_Name << 
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
    return output;
  }
}

string transferBetweenGroups()
{
  Account transferOutAccout, transferInAccount;
  double original_Balance;
  string in_Group_Filename, out_Group_Filename, in_Account_Choice, out_Account_Choice, output;
  vector<Account> outGroup, inGroup;
  
  do
  {
    cout << "Enter the filename (including suffix) for the Group supplying the account to transfer funds from: ";
    cin >> out_Group_Filename;
    
    loadClientVector(out_Group_Filename, outGroup);
  
  }while(outGroup.empty());
  
  do
  {
    cout << "Enter the filename (including suffix) for the Group supplying the account to transfer funds into: ";
    cin >> in_Group_Filename;
    
    loadClientVector(in_Group_Filename, inGroup);
  
  }while(inGroup.empty());
  
  cout << "Please select the account from which you wish to withdraw funds.\n";
  loadActiveAccount(outGroup, transferOutAccout);
  cout << "Please select the account into which you wish to transfer funds.\n";
  loadActiveAccount(inGroup, transferInAccount);
  
  cout << "Would you like to transfer money out of " << transferOutAccount.first_Name << 
       "'s checking account or savings account?\n";
  cout << "[C]: Checking.\n[S]: Savings.\n";
  
  out_Account_Choice = setAccountChoice();  
  
  cout << "Would you like to transfer money into " << transferInAccount.first_Name << 
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
    return output;
  }
}


