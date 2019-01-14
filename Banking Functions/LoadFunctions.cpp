// Load functions

void loadClientVector(string fileName, vector<Account>& receiving_Vector)
{
  ifstream input_File;
  Account intake_Account;
  string trash;
  char ch;
  int dates;
  
  cout << "Retrieving Account List From Source File: " << fileName << endl;
  input_File.open(fileName);
	if(input_File.fail())                     //Testing for successful file opening
	{
		cout << "Failed to open file.\n";
		return;
	}
	else
	{
		cout << "File opened successfully. Loading Accounts..." << endl;
	}
  
  // Skip first two lines of file
  for(int i = 0 ; i < 2 ; i++)
    getline(input_File, trash);
  
  while( !input_File.eof() ) 
  {
    getline(input_File, intake_Account.last_Name, |);
    getline(input_File, intake_Account.first_Name, |);
    getline(input_File, intake_Account.ssn, |);
    getline(input_File, intake_Account.dob_Month, /);
    getline(input_File, intake_Account.dob_Day, /);
    getline(input_File, intake_Account.dob_Year, |);
    getline(input_File, intake_Account.client_Group, |);
    input_File >> intake_Account.account_Number;
    getline(input_File, trash);
    
    receiving_Vector.pushback(intake_Account);
  }
  
  input_File.close();
}

void loadActiveAccount(vector<Account> source_Vector, Account& active_Account)
{
  char menuLooper;
  string choice;
  
  do
  {
    cout << "Would you like to search for an account by Last Name, SSN, or Account Number?" << endl;
    cout << "1. Last Name\n2. SSN\n3. Account #\n4. Cancel" << endl;

    getline(cin, choice);
    while( !isdigit(choice[0]) )
    {
      cout << "Invalid option, try again."
      getline(cin, choice);
    }
    
    switch (choice[0])
    {
      case '1' :
        menuLooper = loadByName(source_Vector, active_Account);
        break;
      case '2' :
        menuLooper = loadBySSN(source_Vector, active_Account);
        break;
      case '3' : 
        menuLooper = loadByID(source_Vector, active_Account);
        break;
      case '4' :
        menuLooper = '0';
        break;
      
      default : 
        cout << "Invalid option, try again.\n";
        menuLooper = '1';
        break;
    }
  }while(menuLooper == '1');
  
}

char loadByName(const vector<Account>& source_Vector, Account& activeAccount)
{
  string name, lastNm input;
  vector<Account> matchedAccounts;
  cout << "Enter the Last Name of the Client: ";
  getline(cin, name); 
      
  for(int i = 0 ; i < source_Vector.size() ; i++)
  {
    lastNm = source_Vector[i].last_Name.substr( 0, name.length() )
    if(name == lastNm)
    {
      matchedAccounts.push_back(source_Vector[i]);
    }
  }
  
  if(matchedAccounts.empty())
  {
    cout << "There were no Accounts that matched that name.  Please try your search again." << endl;
    return '1'; // continues menu loop in loading function
  }
  
  for(i = 0 ; i < matchedAccounts.size() ; i++)
  {
    cout << "#" << i+1 << matchedAccounts[i].last_Name << ' ' << matchedAccounts[i].first_Name << ' ' <<
    matchedAccounts[i].dob_Month << '/' << matchedAccounts[i].dob_Day << '/' << 
    matchedAccounts[i].dob_Year << "Account Number: " << matchedAccounts[i].account_Number 
    << endl;
  }
    
  cout << "Enter the number following the '#' sign that corresponds to the account you wish to access, "
  << "or enter 0 to perform a new search.\n";
  
  getline(cin, input);
  
  while(!isdigit(input[0]))
  {
    cout << "That is not a valid option, try again.\n";
    getline(cin, input[0]);
  }
  
  while(input[0] < 1 && input[0] > matchedAccounts.size())
  {
    cout << "That is not a valid option, try again.\n";
    getline(cin, input[0]);
  }
  
  int c = input[0] - '0';
  activeAccount = matchedAccounts[c];
  return '0'; // terminates menu loop in loading function
}

char loadBySSN(const vector<Account>& source_Vector, Account& activeAccount)
{
  string ssn, input;
  vector<Account> matchedAccounts;
  cout << "Enter the Social Security Number of the Client, with no dashes or spaces: ";
  getline(cin, ssn); 
      
  for(int i = 0 ; i < source_Vector.size() ; i++)
  {
    if(ssn == source_Vector[i].ssn)
    {
      matchedAccounts.push_back(source_Vector[i]);
    }
  }
  
  if(matchedAccounts.empty())
  {
    cout << "There were no Accounts with that Soc. Sec. Number.  Please try your search again." << endl;
    return '1'; // continues menu loop in loading function
  }
  
  for(i = 0 ; i < matchedAccounts.size() ; i++)
  {
    cout << "#" << i+1 << matchedAccounts[i].last_Name << ' ' << matchedAccounts[i].first_Name << ' ' <<
    matchedAccounts[i].dob_Month << '/' << matchedAccounts[i].dob_Day << '/' << 
    matchedAccounts[i].dob_Year << "Account Number: " << matchedAccounts[i].account_Number 
    << endl;
  }
    
  cout << "Enter the number following the '#' sign that corresponds to the account you wish to access, "
  << "or enter 0 to perform a new search.\n";
  
  getline(cin, input);
  
  while(!isdigit(input[0]))
  {
    cout << "That is not a valid option, try again.\n";
    getline(cin, input[0]);
  }
  
  while(input[0] < 1 && input[0] > matchedAccounts.size())
  {
    cout << "That is not a valid option, try again.\n";
    getline(cin, input[0]);
  }
  
  int c = input[0] - '0';
  activeAccount = matchedAccounts[c];
  return '0'; // terminates menu loop in load function
} 

char loadByID(const vector<Account>& source_Vector, Account& activeAccount)
{
  string input;
  
  cout << "Enter the Account ID Number of the account you wish to access.\n";
  getline(cin, input);
  
  for(int i = 0 ; i < input.length() ; i++)
  {
    if( !isdigit(input[i]) )
      {
        cout << "You must enter a valid Account Number! Try again.\n";
        cout << "Enter the Account Number: ";
        getline(cin, input);
        i=0;
        continue;
      }  
  }
  
  for(i = 0 ; i < source_Vector.size() ; i++)
  {
    if(input == source_Vector[i].account_Number)
    {
      activeAccount = source_Vector[i];
      return '0'; //terminates menu loop in loading function
    }
  }
  
  cout << "No accounts found with that ID Number. Please try another search.\n";
  return '1'; // continues the menu loop in loading fuction
}

