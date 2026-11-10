#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class BankAccount
{
private:
    string accNo;
    string name;
    double bal;
    int depCount;
    int withCount;
    int rejCount;
    bool created;

public:
    BankAccount()
    {
        bal = 0;
        depCount = 0;
        withCount = 0;
        rejCount = 0;
        created = false;
    }

    bool createAccount(string a, string n, double b)
    {
        if(b < 0)
        {
            cout << "Invalid opening balance.\n";
            return false;
        }

        accNo = a;
        name = n;
        bal = b;
        created = true;

        cout << "Account created successfully.\n";
        return true;
    }

    void deposit(double amt)
    {
        if(amt <= 0)
        {
            cout << "Invalid deposit amount.\n";
            rejCount++;
            return;
        }

        bal += amt;
        depCount++;

        cout << "Deposit successful.\n";
    }

    void withdraw(double amt)
    {
        if(amt <= 0)
        {
            cout << "Invalid withdrawal amount.\n";
            rejCount++;
            return;
        }

        if(amt > bal)
        {
            cout << "Insufficient balance.\n";
            rejCount++;
            return;
        }

        bal -= amt;
        withCount++;

        cout << "Withdrawal successful.\n";
    }

    void checkBalance()
    {
        cout << fixed << setprecision(2);
        cout << "Available Balance: " << bal << "\n";
    }

    void displayAccount()
    {
        cout << "\nAccount Number: " << accNo;
        cout << "\nCustomer Name: " << name;
        cout << fixed << setprecision(2);
        cout << "\nCurrent Balance: " << bal << "\n";
    }

    void displaySummary()
    {
        cout << "\nTransaction Summary\n";
        cout << "Successful Deposits: " << depCount << "\n";
        cout << "Successful Withdrawals: " << withCount << "\n";
        cout << "Rejected Transactions: " << rejCount << "\n";
        cout << fixed << setprecision(2);
        cout << "Final Balance: " << bal << "\n";
    }

    void rejectTransaction()
    {
        rejCount++;
    }

    bool isCreated()
    {
        return created;
    }
};

int main()
{
    BankAccount b;
    int ch;
    double amt;
    string a, n;

    do
    {
        cout << "\n===== SecureBank =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Balance Enquiry\n";
        cout << "5. Display Account Details\n";
        cout << "6. Display Transaction Summary\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        if(!(cin >> ch))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid menu choice.\n";
            continue;
        }

        switch(ch)
        {
            case 1:
                if(b.isCreated())
                {
                    cout << "Account already exists.\n";
                    break;
                }

                cout << "Enter Account Number: ";
                cin >> a;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Customer Name: ";
                getline(cin, n);

                cout << "Enter Opening Balance: ";

                if(!(cin >> amt))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid balance input.\n";
                    break;
                }

                b.createAccount(a, n, amt);
                break;

            case 2:
                if(!b.isCreated())
                {
                    cout << "Create an account first.\n";
                    break;
                }

                cout << "Enter Deposit Amount: ";

                if(!(cin >> amt))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    b.rejectTransaction();
                    cout << "Invalid amount input.\n";
                    break;
                }

                b.deposit(amt);
                break;

            case 3:
                if(!b.isCreated())
                {
                    cout << "Create an account first.\n";
                    break;
                }

                cout << "Enter Withdrawal Amount: ";

                if(!(cin >> amt))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    b.rejectTransaction();
                    cout << "Invalid amount input.\n";
                    break;
                }

                b.withdraw(amt);
                break;

            case 4:
                if(!b.isCreated())
                    cout << "Create an account first.\n";
                else
                    b.checkBalance();
                break;

            case 5:
                if(!b.isCreated())
                    cout << "Create an account first.\n";
                else
                    b.displayAccount();
                break;

            case 6:
                if(!b.isCreated())
                    cout << "Create an account first.\n";
                else
                    b.displaySummary();
                break;

            case 7:
                cout << "Thank you for using SecureBank.\n";
                break;

            default:
                cout << "Invalid menu choice. Try again.\n";
        }

    } while(ch != 7);

    return 0;
}
