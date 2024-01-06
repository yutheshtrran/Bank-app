/*21/ENG/009 A.HARISHAN
  21/ENG/131 S.YUTHESHTRRAN
  21/ENG/131 S.GEERTHIGA*/




//21/ENG/131 S.YUTHESHTRRAN

#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;
class Customer;
class Administrator;
class Transaction;
class Employee;


class Bank
{
public:
    vector < Employee > employeeArray;
    vector < string > employeeNameArray;
    vector < Customer > customerArray;
    vector < string > customerNameArray;
    vector <Transaction> transactions;
    long bank_balance=1000000;
};

class Administrator
{
private:
    string dateToday;
    float annual_saveInterest = 20;
    float overdraft_Charge = 2;
    int Increased_date=0;

public:
    void add_Employee(Bank& bank);
    void set_theDate();
    void increaseDate();
    void set_AnnualSaveInterest();
    void setoverdraft_Charge();
    void updating_CustomerOverdraft(Customer & customer);
    void updating_CustomerInterest(Customer & customer,Bank& bank,ofstream& BankFile);
    string get_NameofEmployee(Bank& bank);
    string get_theDate();
    float get_AnnualSaveInterest();
    float getoverdraft_Charge();
    int employee_No(Bank& bank);
    vector<string> get_NameofEmployeeArray(Bank& bank);
};

class Employee
{
private:
    string employeeName;
    string dateToday;
public:
    void set_theDate(Administrator & Admin);
    void setEmployeeName(string employeeName);
    string get_NameofEmployee();
    void createCustomer(Customer & customerCreated,Bank& bank,ofstream& MyFile);
    void depositMoney(Customer & customer,Bank& bank,ofstream& MyFile,ofstream& BankFile);
    void withDrawMoney(Customer & customer,Bank& bank,ofstream& MyFile,ofstream& BankFile);
    void viewTransactions(Bank& bank);
    void closeCustomerAccount(Customer & customer,ofstream& MyFile);
};

class Customer
{
public:
    string CustomerName;
    string accountType;
    string customerContact;
    long moneyDeposit;
    bool isCurrentAccount = false;
    long overdraftMaximum = 0;
    bool isClosed = false;
    long overDraftNow = 0;
    string dateToday;
    string dateCreated;
    vector <Transaction> transactions;

    void viewTransaction();
    void depositMoneyFun(Bank& bank,ofstream& MyFile,ofstream& BankFile);
    void set_theDate(Administrator& Admin);
    void withdrawMoney(Bank& bank,ofstream& MyFile,ofstream& BankFile);
};

class Transaction
{
private:
    string dateToday;
    string description;
public:

    void setTransactionDate(string dateToday)
    {
        this->dateToday=dateToday;
    }

    void setDescription(string customer_name,string debitOrCredit,long amount)
    {
        this->description=this->dateToday+" - "+customer_name+" : "+debitOrCredit+" : "+to_string(amount)+" Rs.";
    }
    string getDescription()
    {
        return this->description;
    }

};

int Administrator::employee_No(Bank& bank)
{
    return bank.employeeArray.size();
};

vector<string> Administrator::get_NameofEmployeeArray(Bank& bank)
{
    return bank.employeeNameArray;
};

void Administrator::add_Employee(Bank& bank)
{
    string startLetter="";
    if(bank.employeeArray.size()<9)
    {
        startLetter="00";
    }
    else if(bank.employeeArray.size()<99)
    {
        startLetter="0";
    }
    string employeeName=("employee" +startLetter+to_string((bank.employeeArray.size()) + 1));
    Employee employee;
    employee.setEmployeeName(employeeName);
    bank.employeeArray.push_back(employee);
    bank.employeeNameArray.push_back(employeeName);
    Employee lastCreatedEmployee=bank.employeeArray.back();
    cout<<lastCreatedEmployee.get_NameofEmployee()+" : Employee has created successfully"<<endl;;
};

void Administrator::set_theDate()
{
    string dateToday;
    time_t ttime = time(0);
    tm * local_time = localtime( & ttime);
    dateToday = to_string(1900 + local_time -> tm_year) + ":" + to_string(1 + local_time -> tm_mon) + ":" + to_string(local_time -> tm_mday);
    this -> dateToday = dateToday;
};

void Administrator::increaseDate()
{
    this->Increased_date+=1;
    time_t ttime = time(0);
    ttime += (24 * 60 * 60)*(this->Increased_date);
    tm * local_time = localtime( & ttime);
    this->dateToday = to_string(1900 + local_time -> tm_year) + ":" + to_string(1+local_time -> tm_mon) + ":" + to_string(local_time -> tm_mday);
};

void Administrator::set_AnnualSaveInterest()
{
    float annual_saveInterest;
    cout << "Please enter the new annual saving interest : ";
    cin >> annual_saveInterest;
    this -> annual_saveInterest = annual_saveInterest;
    cout<<"New annual savings interest is "<< annual_saveInterest<<endl;
};

void Administrator::setoverdraft_Charge()
{
    float overdraft_Charge;
    cout << "Please enter the new overdraft charge(% per day) : ";
    cin >> overdraft_Charge;
    this -> overdraft_Charge = overdraft_Charge;
    cout<<"New overdraft charge is "<< overdraft_Charge<<endl;
};

void Administrator::updating_CustomerOverdraft(Customer & customer)
{
    if (customer.overDraftNow > 0)
    {
        customer.overDraftNow += ((this -> overdraft_Charge) / 100) * (customer.overDraftNow);
        customer.moneyDeposit=(customer.overDraftNow)*(-1);

    }
}

void Administrator::updating_CustomerInterest(Customer & customer,Bank& bank,ofstream& BankFile)
{
    float dailyInterest = (this -> annual_saveInterest) / 365;
    if (customer.moneyDeposit > 0)
    {
        cout<<"line-1"<<endl;
        customer.moneyDeposit += ((dailyInterest) / 100) * (customer.moneyDeposit);
        bank.bank_balance-=((dailyInterest) / 100) * (customer.moneyDeposit);
        BankFile<<this->dateToday<<" - "<<customer.CustomerName<<" : Interest debited to bank account is : "<<to_string(((dailyInterest) / 100) * (customer.moneyDeposit))<<" Rs."<<endl;
        BankFile<<this->dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
        Transaction transaction_now;
        transaction_now.setTransactionDate(this->dateToday);
        transaction_now.setDescription(customer.CustomerName,"Interest credited to customer account is",((dailyInterest) / 100) * (customer.moneyDeposit));
        bank.transactions.push_back(transaction_now);
        customer.transactions.push_back(transaction_now);

    }
}

string Administrator::get_NameofEmployee(Bank& bank)
{
    return bank.employeeArray.back().get_NameofEmployee();
}

string Administrator::get_theDate()
{
    return this->dateToday;
}

float Administrator::get_AnnualSaveInterest()
{
    return (this->annual_saveInterest);
};

float Administrator::getoverdraft_Charge()
{
    return (this->overdraft_Charge);
};


void Customer::viewTransaction()
{
    int numberOfTransactions=this->transactions.size();
    for(int i=0; i<numberOfTransactions; i++)
    {
        cout<<this->transactions[i].getDescription()<<endl;
    }
};

void Customer::depositMoneyFun(Bank& bank,ofstream& MyFile,ofstream& BankFile)
{
    int moneyAdded;
    cout << "Please enter the amount of money to deposit: ";
    cin >> moneyAdded;
    this -> moneyDeposit += moneyAdded;
    MyFile<<this->dateToday<<" - "<<this->CustomerName<<" : deposited "<<to_string(moneyAdded)<<endl;
    Transaction transaction_now_1;
    transaction_now_1.setTransactionDate(this->dateToday);
    transaction_now_1.setDescription(this->CustomerName,"Money credited to the customer account",moneyAdded);
    this->transactions.push_back(transaction_now_1);

    if (this -> moneyDeposit >= 0)
    {
        bank.bank_balance+=overDraftNow;
        BankFile<<this->dateToday<<" - "<<this->CustomerName<<" : overdraft credited to bank account : "<<to_string(overDraftNow)<<" Rs."<<endl;
        BankFile<<this->dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
        Transaction transaction_now_2;
        transaction_now_2.setTransactionDate(this->dateToday);
        transaction_now_2.setDescription(this->CustomerName,"overdraft credited to bank account",overDraftNow);
        bank.transactions.push_back(transaction_now_2);
        this -> overDraftNow = 0;
    }
    else
    {
        bank.bank_balance+=moneyAdded;
        BankFile<<this->dateToday<<" - "<<this->CustomerName<<" : overdraft credited to bank account : "<<to_string(moneyAdded)<<" Rs."<<endl;
        BankFile<<this->dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
        this -> overDraftNow -= moneyAdded;
        Transaction transaction_now_2;
        transaction_now_2.setTransactionDate(this->dateToday);
        transaction_now_2.setDescription(this->CustomerName,"overdraft credited to bank account",moneyAdded);
        bank.transactions.push_back(transaction_now_2);
    }
    for(int i=0; i<=bank.customerNameArray.size(); i++)
    {
        if(this->CustomerName==bank.customerNameArray[i])
        {
            bank.customerArray[i].moneyDeposit=this->moneyDeposit;
            bank.customerArray[i].overDraftNow=this->overDraftNow;
        }
    }
}

void Customer::set_theDate(Administrator & Admin)
{
    this -> dateToday = Admin.get_theDate();
};

void Customer::withdrawMoney(Bank& bank,ofstream& MyFile,ofstream& BankFile)
{
    int moneyToWithdraw;
    cout << "Enter the amount of money to withdraw: ";
    cin >> moneyToWithdraw;
    if (this -> isCurrentAccount == false && moneyToWithdraw > this -> moneyDeposit)
    {
        cout << "Sorry insufficient balance" << endl;
    }
    else if (this -> isCurrentAccount == false && moneyToWithdraw <= this -> moneyDeposit)
    {
        this -> moneyDeposit -= moneyToWithdraw;
        cout << "It is a successful withdrawal" << endl;
        MyFile<<this->dateToday<<" - "<<this->CustomerName<<" : Withdrawn "<<to_string(moneyToWithdraw)<<endl;
        Transaction transaction_now_1;
        transaction_now_1.setTransactionDate(this->dateToday);
        transaction_now_1.setDescription(this->CustomerName,"Money withdrawn from customer account",moneyToWithdraw);
        this->transactions.push_back(transaction_now_1);
    }
    else if (this -> isCurrentAccount == true && moneyToWithdraw > this -> moneyDeposit)
    {
        if (((this -> moneyDeposit - moneyToWithdraw) * (-1)) <= this -> overdraftMaximum && ((this -> moneyDeposit - moneyToWithdraw) * (-1)) <= bank.bank_balance )
        {
            this -> overDraftNow = moneyToWithdraw - (this -> moneyDeposit);
            bank.bank_balance-=this->overDraftNow;
            this -> moneyDeposit -= moneyToWithdraw;
            cout << "It is a successful withdrawal" << endl;
            BankFile<<this->dateToday<<" - "<<this->CustomerName<<" : overdraft debited to bank account : "<<to_string(this->overDraftNow)<<" Rs."<<endl;
            BankFile<<this->dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
            MyFile<<this->dateToday<<" - "<<this->CustomerName<<" : Withdrawn "<<to_string(moneyToWithdraw)<<endl;
            Transaction transaction_now_2;
            Transaction transaction_now_3;
            transaction_now_2.setTransactionDate(this->dateToday);
            transaction_now_3.setTransactionDate(this->dateToday);
            transaction_now_2.setDescription(this->CustomerName,"Money withdrawn from customer account",moneyToWithdraw);
            transaction_now_3.setDescription(this->CustomerName,"overdraft debited to bank account",this->overDraftNow);
            this->transactions.push_back(transaction_now_2);
            bank.transactions.push_back(transaction_now_3);
        }
        else if(((this -> moneyDeposit - moneyToWithdraw) * (-1)) <= this -> overdraftMaximum && ((this -> moneyDeposit - moneyToWithdraw) * (-1)) > bank.bank_balance)
        {
            cout << "We are really sorry. Cannot withdraw amount higher than balance in the bank.";
        }
        else
        {
            cout << "We are really sorry. Cannot withdraw amount higher than maximum overdraft.";
        }
    }
    else if (this -> isCurrentAccount == true && moneyToWithdraw <= this -> moneyDeposit)
    {
        this -> moneyDeposit -= moneyToWithdraw;
        cout << "It is a successful withdrawal" << endl;
        MyFile<<this->dateToday<<" - "<<this->CustomerName<<" : Withdrawn "<<to_string(moneyToWithdraw)<<endl;
        Transaction transaction_now_4;
        transaction_now_4.setTransactionDate(this->dateToday);
        transaction_now_4.setDescription(this->CustomerName,"Money withdrawn from customer account",moneyToWithdraw);
        this->transactions.push_back(transaction_now_4);
    }
    for(int i=0; i<=bank.customerNameArray.size(); i++)
    {
        if(this->CustomerName==bank.customerNameArray[i])
        {
            bank.customerArray[i].moneyDeposit=this->moneyDeposit;
            bank.customerArray[i].overDraftNow=this->overDraftNow;
        }
    }

};



//21/ENG/132 S.GEERTHIGA

void Employee::set_theDate(Administrator & Admin)
{
    this -> dateToday = Admin.get_theDate();
};

void Employee::setEmployeeName(string employeeName)
{
    this->employeeName = employeeName;
};

void Employee::createCustomer(Customer & customerCreated,Bank& bank,ofstream& MyFile)
{
    string startLetter="";
    if(bank.customerArray.size()<9)
    {
        startLetter="00";
    }
    else if(bank.customerArray.size()<99)
    {
        startLetter="0";
    }
    string customer_contact;
    int account_type;
    customerCreated.dateCreated = dateToday;
    string customerName= "customer" +startLetter+to_string((bank.customerArray.size()) + 1);
    cout << "Customer name : " << "customer" +startLetter+to_string((bank.customerArray.size()) + 1)<<endl;
    cout << "Please enter mobile number : ";
    cin >> customer_contact;
    customerCreated.CustomerName=customerName;
    customerCreated.customerContact = customer_contact;
    cout << "Please select the account type : " << endl;
    cout << "1) Current account" << endl;
    cout << "2) Saving account" << endl;
    cin >> account_type;

    while (account_type < 0 || account_type > 3)
    {
        cout << "Incorrect input! Select a correct account";
        cout << "Select the account type : " << endl;
        cout << "1) Current account" << endl;
        cout << "2) Saving account" << endl;
        cin >> account_type;
    }

    if (account_type == 1)
    {
        customerCreated.accountType = "Current";
        customerCreated.isCurrentAccount = true;
        cout << "Enter the overdraft limit : ";
        cin >> customerCreated.overdraftMaximum;
    }
    else if (account_type == 2)
    {
        customerCreated.accountType = "Saving";
    }

    long moneyDepositNow;
    cout << "Enter the initial amount deposited : ";
    cin>>moneyDepositNow;
    customerCreated.moneyDeposit=moneyDepositNow;
    bank.customerNameArray.push_back(customerName);
    bank.customerArray.push_back(customerCreated);
    MyFile<<customerCreated.dateToday<<" - "<<customerCreated.CustomerName<<" : Account created."<<endl;
    MyFile<<customerCreated.dateToday<<" - "<<customerCreated.CustomerName<<" : Deposited "<<moneyDepositNow<<endl;
    Transaction transaction_now_1;
    transaction_now_1.setTransactionDate(customerCreated.dateToday);
    transaction_now_1.setDescription(customerCreated.CustomerName,"Money credited to customer account",moneyDepositNow);
    customerCreated.transactions.push_back(transaction_now_1);

};

void Employee::depositMoney(Customer& customer,Bank& bank,ofstream& MyFile,ofstream& BankFile)
{
    if (customer.isClosed == false)
    {
        long account_balance = customer.moneyDeposit;
        long now_deposited;
        cout << "Enter the amount to be deposited: ";
        cin >> now_deposited;
        customer.moneyDeposit = account_balance + now_deposited;
        MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Deposited "<<now_deposited<<endl;
        Transaction transaction_now_1;
        transaction_now_1.setTransactionDate(customer.dateToday);
        transaction_now_1.setDescription(customer.CustomerName,"Money credited to customer account",now_deposited);
        customer.transactions.push_back(transaction_now_1);

        if (customer.moneyDeposit >= 0)
        {
            bank.bank_balance+=customer.overDraftNow;
            BankFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : overdraft credited to bank account : "<<to_string(customer.overDraftNow)<<" Rs."<<endl;
            BankFile<<customer.dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.dateToday);
            transaction_now_2.setDescription(customer.CustomerName,"overdraft credited to bank account",customer.overDraftNow);
            bank.transactions.push_back(transaction_now_2);
            customer.overDraftNow = 0;

        }
        else
        {
            bank.bank_balance+=now_deposited;
            customer.overDraftNow -= now_deposited;
            BankFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : overdraft credited to bank account : "<<to_string(now_deposited)<<" Rs."<<endl;
            BankFile<<customer.dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.dateToday);
            transaction_now_2.setDescription(customer.CustomerName,"overdraft credited to bank account",now_deposited);
            bank.transactions.push_back(transaction_now_2);
        }
    }
    else
    {
        cout << "Sorry. Account is already closed" << endl;
    }
};

void Employee::withDrawMoney(Customer& customer,Bank& bank,ofstream& MyFile,ofstream& BankFile)
{
    if (customer.isClosed == false)
    {
        //long account_balance=customer.moneyDeposit;
        long now_withdraw;
        cout << "Enter the amount to be withdrawed: ";
        cin >> now_withdraw;
        //customer.moneyDeposit=account_balance-now_withdraw;

        if (customer.isCurrentAccount == false && now_withdraw > customer.moneyDeposit)
        {
            cout << "Sorry insufficient balance" << endl;
        }
        else if (customer.isCurrentAccount == false && now_withdraw <= customer.moneyDeposit)
        {
            customer.moneyDeposit -= now_withdraw;
            cout << "Successful withdrawal" << endl;
            MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Withdrawn "<<now_withdraw<<endl;
            Transaction transaction_now_1;
            transaction_now_1.setTransactionDate(customer.dateToday);
            transaction_now_1.setDescription(customer.CustomerName,"Money debited from customer account",now_withdraw);
            bank.transactions.push_back(transaction_now_1);
        }
        else if (customer.isCurrentAccount == true && now_withdraw > customer.moneyDeposit)
        {
            if (((customer.moneyDeposit - now_withdraw) * (-1)) <= customer.overdraftMaximum && ((customer.moneyDeposit - now_withdraw) * (-1)) <= bank.bank_balance )
            {
                customer.overDraftNow = now_withdraw - (customer.moneyDeposit);
                bank.bank_balance-=customer.overDraftNow;
                customer.moneyDeposit -= now_withdraw;
                cout << "Successful withdrawal" << endl;
                BankFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : overdraft debited to bank account : "<<to_string(customer.overDraftNow)<<" Rs."<<endl;
                BankFile<<customer.dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
                MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Withdrawn "<<now_withdraw<<endl;
                Transaction transaction_now_2;
                Transaction transaction_now_3;
                transaction_now_2.setTransactionDate(customer.dateToday);
                transaction_now_3.setTransactionDate(customer.dateToday);
                transaction_now_2.setDescription(customer.CustomerName,"Money withdrawn from customer account",now_withdraw);
                transaction_now_3.setDescription(customer.CustomerName,"overdraft debited to bank account",customer.overDraftNow);
                customer.transactions.push_back(transaction_now_2);
                bank.transactions.push_back(transaction_now_3);
            }
            else if(((customer.moneyDeposit - now_withdraw) * (-1)) <= customer.overdraftMaximum && ((customer.moneyDeposit - now_withdraw) * (-1)) > bank.bank_balance)
            {
                cout << "Sorry. Cannot withdraw amount greater than balance in bank.";
            }
            else
            {
                cout << "Sorry. Cannot withdraw amount greater than maximum overdraft.";
            }
        }
        else if (customer.isCurrentAccount == true && now_withdraw <= customer.moneyDeposit)
        {
            customer.moneyDeposit -= now_withdraw;
            cout << "Successful withdrawal" << endl;
            MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Withdrawn "<<now_withdraw<<endl;
            Transaction transaction_now_4;
            transaction_now_4.setTransactionDate(customer.dateToday);
            transaction_now_4.setDescription(customer.CustomerName,"Money debited from customer account",now_withdraw);
            customer.transactions.push_back(transaction_now_4);
        }
    }
    else
    {
        cout << "Sorry. Account is already closed" << endl;
    }
};

void Employee::viewTransactions(Bank& bank)
{
    int numberOfBankTransactions=bank.transactions.size();
    cout<<"Transaction related with money owned by bank"<<endl<<endl;
    for(int i=0; i<numberOfBankTransactions; i++)
    {
        cout<<bank.transactions[i].getDescription()<<endl;
    }
    for(int i=0; i<bank.customerArray.size(); i++)
    {
        cout<<"Transaction related with "+bank.customerArray[i].CustomerName<<endl;
        for(int j=0; j<bank.customerArray[i].transactions.size(); j++)
        {
            cout<<bank.customerArray[i].transactions[j].getDescription()<<endl;
        }
    }
};

string Employee::get_NameofEmployee()
{
    return this->employeeName;
};

void Employee::closeCustomerAccount(Customer& customer,ofstream& MyFile)
{
    if (customer.moneyDeposit == 0)
    {
        customer.isClosed = true;
        cout << "Account closed successfully." << endl;
        MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Account closed."<<endl;
    }
    else if (customer.moneyDeposit > 0)
    {
        string userInputCloseAcc;
        cout << "Do you want to withdraw the remaining amount of " << customer.moneyDeposit << " and close the account." << endl;
        cout << "press 1 for yes \nPress 2 for no" << endl; ////////////////////////////////////////////////////////////////
        cin >> userInputCloseAcc;
        if (userInputCloseAcc == "1")
        {
            customer.moneyDeposit == 0;
            customer.isClosed = true;
            cout << "Account closed successfully." << endl;
            MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : remaining amount of"<<customer.moneyDeposit <<" is taken and Account is closed."<<endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.dateToday);
            transaction_now_2.setDescription(customer.CustomerName,"Money debited from customer account",customer.moneyDeposit);
            customer.transactions.push_back(transaction_now_2);

        }
        else if (userInputCloseAcc == "2")
        {
            cout << "Account not closed." << endl;
        }
    }
    else if (customer.moneyDeposit < 0)
    {
        cout << "There is an overdraft in this account. So account cannot be closed." << endl;
    }

};

void depositFromOutside(Bank& bank,Customer& customer,ofstream& MyFile,ofstream& BankFile)
{
    if (customer.isClosed == false)
    {
        long account_balance = customer.moneyDeposit;
        long now_deposited;
        cout << "Enter the amount to be deposited: ";
        cin >> now_deposited;
        customer.moneyDeposit = account_balance + now_deposited;
        Transaction transaction_now_1;
        transaction_now_1.setTransactionDate(customer.dateToday);
        transaction_now_1.setDescription(customer.CustomerName,"Money credited to customer account",now_deposited);
        customer.transactions.push_back(transaction_now_1);

        if (customer.moneyDeposit >= 0)
        {
            bank.bank_balance+=customer.overDraftNow;
            BankFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : overdraft credited to bank account : "<<to_string(customer.overDraftNow)<<" Rs."<<endl;
            BankFile<<customer.dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.dateToday);
            transaction_now_2.setDescription(customer.CustomerName,"overdraft credited to bank account",customer.overDraftNow);
            bank.transactions.push_back(transaction_now_2);
            customer.overDraftNow = 0;
        }
        else
        {
            bank.bank_balance+=now_deposited;
            customer.overDraftNow -= now_deposited;
            BankFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : overdraft credited to bank account : "<<to_string(now_deposited)<<" Rs."<<endl;
            BankFile<<customer.dateToday<<" - "<<"Bank balance : "<<bank.bank_balance<<endl;
            Transaction transaction_now_2;
            transaction_now_2.setTransactionDate(customer.dateToday);
            transaction_now_2.setDescription(customer.CustomerName,"overdraft credited to bank account",now_deposited);
            bank.transactions.push_back(transaction_now_2);

        }

        for(int i=0; i< bank.customerArray.size(); i++)
        {
            if(customer.CustomerName==bank.customerArray[i].CustomerName)
            {
                bank.customerArray[i].moneyDeposit=customer.moneyDeposit;
                bank.customerArray[i].overDraftNow=customer.overDraftNow;
                break;
            }
        }
        cout<<"Money successfully deposited"<<endl;
        MyFile<<customer.dateToday<<" - "<<customer.CustomerName<<" : Deposited "<<now_deposited<<endl;
    }
    else
    {
        cout << "Sorry. Account is already closed" << endl;
    }
}

string getPassword()
{
    cout << "Enter password: ";

    string password;
    char ch;
    while (true)
    {
        ch = _getch(); // Read a single character without echoing
        if (ch == '\r') // '\r' corresponds to Enter key
        {
            cout << endl;
            break;
        }
        password += ch;
        cout << '*'; // Show asterisk instead of the actual character
    }

    return password;
}


//21/ENG/009 A.HARISHAN 

int main()
{
    Bank bank;
    vector<string> employeeNameArray;
    vector<string> customerNameArray;

    ofstream BankFile("Bank.txt");
    ofstream CustomerFile("Customer_details.txt");
    fstream BankFile_handler;
    fstream CustomerFile_handler;

    BankFile_handler.open("Bank.txt", ios:: in | ios::out);
    CustomerFile_handler.open("Customer_details.txt", ios:: in | ios::out);

    if (!BankFile_handler)
    {
        cout << "Bank File did not open!";
        exit(1);
    }

    if (!CustomerFile_handler)
    {
        cout << "Customer details File did not open!";
        exit(1);
    }

    int input=1,user_input_1, user_input_2,user_input_3;
    Administrator Admin;
    Admin.set_theDate();
    string username, password;
    while(input!=0)
    {
        cout << "Please select an option here : " << endl;
        cout << "1. Deposit as an outside source." << endl;
        cout << "2. Login." << endl;
        cin >> user_input_1;
        if (user_input_1 == 2)
        {
            int login_checker=0;
            while(login_checker!=1)
            {
                cout << "Select an option below : " << endl;
                cout << "1. Enter as administrator ." << endl;
                cout << "2. Enter as customer ." << endl;
                cout << "3. Enter as employee ." << endl;
                cout<<"4. Back"<<endl;

                cin >> user_input_2;
                if (user_input_2 == 1)
                {
                    cout << "Enter the user name : ";
                    cin >> username;
                    cout << endl;
                    password = getPassword();

                    while (username != "Admin" || password != "Password@1234")
                    {
                        cout << "Incorrect credentials. Please try again.." << endl;
                        cout << "Enter the user name : ";
                        cin >> username;
                        cout << endl;
                        password = getPassword();
                    }
                    cout << "Successful login" << endl<<endl;
                    int checker_admin=0;
                    while(checker_admin!=1)
                    {
                        cout<<"\ndate : "<<Admin.get_theDate()<<endl;
                        float annualInterest=Admin.get_AnnualSaveInterest();
                        float overdraft_Charge=Admin.getoverdraft_Charge();
                        cout<<"Annual interest rate is "<<annualInterest<<endl;
                        cout<<"Overdraft charge is "<<overdraft_Charge<<endl;
                        cout<<"Bank balance now :  "<<bank.bank_balance<<endl<<endl;
                        // cout<<"Overdraft charge per day is " <<" % "<<end;
                        cout<<"1. Create an employee"<<endl;
                        cout<<"2. Increase the date"<<endl;
                        cout<<"3. Change overdraft charge"<<endl;
                        cout<<"4. Change annual savings interest"<<endl;
                        cout<<"5. Logout"<<endl;
                        cout <<"Select an option above"<<endl;
                        cin>>user_input_3;
                        switch(user_input_3)
                        {
                        case 1:
                        {
                            Admin.add_Employee(bank);
                            Employee employee;
                            break;
                        }
                        case 2:
                        {
                            Admin.increaseDate();
                            if(bank.customerArray.size()>0)
                            {
                                for(int i=0; i<bank.customerArray.size(); i++)
                                {
                                    Admin.updating_CustomerInterest(bank.customerArray[i],bank,BankFile);
                                    Admin.updating_CustomerOverdraft(bank.customerArray[i]);
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            Admin.setoverdraft_Charge();
                            break;
                        }
                        case 4:
                        {
                            Admin.set_AnnualSaveInterest();
                            break;
                        }
                        case 5:
                        {
                            input=0;
                            checker_admin=1;
                            break;
                        }
                        default:
                        {}
                        }
                    }
                }
                else if(user_input_2==4)
                {
                    login_checker=1;
                    input=1;
                    break;
                }
                else if(user_input_2==3)
                {
                    cout << "Enter the employee user name : ";
                    cin >> username;
                    cout << endl;
                    password = getPassword();
                    employeeNameArray=bank.employeeNameArray;
                    Employee employeeNow;
                    for(int i=0; i<employeeNameArray.size(); i++)
                    {
                        if(username==employeeNameArray[i] && password =="Password@1234")
                        {
                            employeeNow=bank.employeeArray[i];
                            login_checker=0;
                            break;
                        }
                        login_checker=1;
                    }
                    if(login_checker==1)
                    {
                        cout<<"Login unsuccessful";
                        login_checker=0;
                    }
                    else
                    {
                        cout << "Successful login" << endl<<endl;
                        int checker_employee=0;
                        while(checker_employee!=1)
                        {
                            cout<<"\ndate : "<<Admin.get_theDate()<<endl;
                            float annualInterest=Admin.get_AnnualSaveInterest();
                            float overdraft_Charge=Admin.getoverdraft_Charge();
                            cout<<"Annual interest rate is "<<annualInterest<<endl;
                            cout<<"Overdraft charge is "<<overdraft_Charge<<endl;
                            // cout<<"Overdraft charge per day is " <<" % "<<end;
                            cout<<"1. Create a customer account"<<endl;
                            cout<<"2. Close the customer account"<<endl;
                            cout<<"3. Deposit money in account"<<endl;
                            cout<<"4. Withdraw money from account"<<endl;
                            cout<<"5. View transactions"<<endl;
                            cout<<"6. Logout"<<endl;
                            cout <<"Select an option above"<<endl;
                            cin>>user_input_3;
                            switch(user_input_3)
                            {
                            case 1:
                            {
                                Customer customerCreated;
                                customerCreated.set_theDate(Admin);
                                employeeNow.createCustomer(customerCreated,bank,CustomerFile);
                                break;
                            }
                            case 2:
                            {
                                string customerName;
                                cout<<"Enter the name of the customer: ";
                                cin>>customerName;
                                for(int i=0; i<bank.customerArray.size(); i++)
                                {
                                    if(customerName==bank.customerArray[i].CustomerName)
                                    {
                                        bank.customerArray[i].set_theDate(Admin);
                                        employeeNow.closeCustomerAccount(bank.customerArray[i],CustomerFile);
                                        break;
                                    }
                                }
                                break;
                            }
                            case 3:
                            {
                                string customerName;
                                cout<<"Enter the name of the customer: ";
                                cin>>customerName;
                                for(int i=0; i<bank.customerArray.size(); i++)
                                {
                                    if(customerName==bank.customerArray[i].CustomerName)
                                    {
                                        bank.customerArray[i].set_theDate(Admin);
                                        employeeNow.depositMoney(bank.customerArray[i],bank,CustomerFile,BankFile);
                                        break;
                                    }
                                }
                                break;
                            }
                            case 4:
                            {
                                string customerName;
                                cout<<"Enter the name of the customer: ";
                                cin>>customerName;
                                for(int i=0; i<bank.customerArray.size(); i++)
                                {
                                    if(customerName==bank.customerArray[i].CustomerName)
                                    {
                                        bank.customerArray[i].set_theDate(Admin);
                                        employeeNow.withDrawMoney(bank.customerArray[i],bank,CustomerFile,BankFile);
                                        break;
                                    }
                                }
                                break;
                            }
                            case 5:
                            {
                                employeeNow.viewTransactions(bank);
                                break;
                            }
                            case 6:
                            {
                                input=0;
                                checker_employee=1;
                                break;
                            }
                            default:
                            {}
                            }
                        }
                    }


                }
                else if(user_input_2==2)
                {
                    int customerArrayElement;
                    cout << "Enter the customer user name : ";
                    cin >> username;
                    cout << endl;
                    password = getPassword();
                    customerNameArray=bank.customerNameArray;
                    Customer customer;
                    for(int i=0; i<customerNameArray.size(); i++)
                    {
                        cout<<customerNameArray[i]<<endl;
                    }
                    for(int i=0; i<customerNameArray.size(); i++)
                    {
                        if(username==customerNameArray[i] && password =="Password@1234")
                        {
                            customer=bank.customerArray[i];
                            customerArrayElement=i;
                            login_checker=0;
                            break;
                        }
                        login_checker=1;
                    }
                    if(login_checker==1)
                    {
                        cout<<"Login unsuccessful";
                        login_checker=0;
                    }
                    else
                    {
                        cout << "Successful login" << endl<<endl;
                        int checker_customer=0;
                        while(checker_customer!=1)
                        {
                            cout<<"\ndate : "<<Admin.get_theDate()<<endl;
                            float annualInterest=Admin.get_AnnualSaveInterest();
                            float overdraft_Charge=Admin.getoverdraft_Charge();
                            cout<<"Annual interest rate is "<<annualInterest<<endl;
                            cout<<"Overdraft charge is "<<overdraft_Charge<<endl<<endl;
                            cout<<"Account name : "<<customer.CustomerName<<endl;
                            cout<<"Account type : "<<customer.accountType<<endl;
                            cout<<"Account Contact details : "<<customer.customerContact<<endl<<endl;
                            cout<<"Account balance : "<<customer.moneyDeposit<<endl<<endl;
                            cout<<"Account overdraft : "<<customer.overDraftNow<<endl<<endl;
                            // cout<<"Overdraft charge per day is " <<" % "<<end;
                            cout<<"1. Deposit money in account"<<endl;
                            cout<<"2. Withdraw money from account"<<endl;
                            cout<<"3. View transactions"<<endl;
                            cout<<"4. Logout"<<endl;
                            cout <<"Select an option above"<<endl;
                            cin>>user_input_3;
                            switch(user_input_3)
                            {
                            case 1:
                            {
                                if(customer.isClosed==false)
                                {
                                    customer.set_theDate(Admin);
                                    customer.depositMoneyFun(bank,CustomerFile,BankFile);
                                    bank.customerArray[customerArrayElement]=customer;
                                }
                                else
                                {
                                    cout<<"Account closed already."<<endl;
                                }
                                break;
                            }
                            case 2:
                            {
                                if(customer.isClosed==false)
                                {
                                    customer.set_theDate(Admin);
                                    customer.withdrawMoney(bank,CustomerFile,BankFile);
                                    bank.customerArray[customerArrayElement]=customer;
                                }
                                else
                                {
                                    cout<<"Account closed already."<<endl;
                                }
                                break;
                            }
                            case 3:
                            {
                                customer.viewTransaction();
                                break;
                            }
                            case 4:
                            {
                                input=0;
                                checker_customer=1;
                                break;
                            }
                            default:
                            {}
                            }
                        }
                    }
                }

            }
        }
        else if(user_input_1==1)
        {
            string customerUserName;
            int isSuccess=0;
            cout<<"Enter the customer name : ";
            cin>>customerUserName;
            for(int i=0; i<bank.customerArray.size(); i++)
            {
                if(customerUserName==bank.customerNameArray[i])
                {
                    bank.customerArray[i].set_theDate(Admin);
                    depositFromOutside(bank,bank.customerArray[i],CustomerFile,BankFile);
                    isSuccess=1;
                    break;
                }
            }
            if(isSuccess==0)
            {
                cout<<"Transaction unsuccessful"<<endl;
            }
        }
    }
    return 0;
}
