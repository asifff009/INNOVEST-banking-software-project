#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For sleep function
#include <windows.h>
// Structure for user accounts
struct User
{
    int accountNumber;
    char name[100];
    char password[50];
    double balance;
    char depositHistory[100][50];
    char transferHistory[100][50];
    int depositCount;
    int transferCount;
    int isBlocked; // Added flag for blocked users
};

// Function prototypes
void adminLogin(struct User users[], int numUsers);
void adminInterface(struct User users[], int numUsers);
void userMenu(struct User users[], int *numUsers);
void userLogin(struct User users[], int numUsers);
void userSignUp(struct User users[], int *numUsers);
void userInterface(struct User *user, struct User users[], int numUsers);
void viewBalance(struct User *user);
void depositMoney(struct User *user);
void transferMoney(struct User users[], int numUsers, struct User *user);
void investMoney(struct User *user);
void viewTransactionHistory(struct User *user);
void logTransaction(struct User *user, const char *transactionDetails, const char *transactionType, double amount);
void displayAllUsers(struct User users[], int numUsers);
void displayTotalBalance(struct User users[], int numUsers);
void displayTotalUsers(int numUsers);
void searchUser(struct User users[], int numUsers);
void blockUser(struct User users[], int numUsers);
void unblockUser(struct User users[], int numUsers);

// Constants
#define SYSTEM_IDENTITY 24115

int main()
{
    struct User users[100];
    int numUsers = 0;
    int choice;

    while (1)
    {
        printf("\n\t\t\t\t\t\t === Innovest Bank System ===\n");
        printf("\t\t\t\t\t\t\t1. Admin Panel\n");
        printf("\t\t\t\t\t\t\t2. User Panel\n");
        printf("\t\t\t\t\t\t\t3. Exit\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            adminLogin(users, numUsers);
            break;
        case 2:
            userMenu(users, &numUsers);
            break;
        case 3:
            printf("\t\t\t\t\t\t Thank you for using Innovest. As-salamu alaykum!\n");
            exit(0);
        default:
            printf("\t\t\t\t\t\t Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Admin login function
void adminLogin(struct User users[], int numUsers)
{
    char uname[100], pword[50];
    printf("\t\t\t\t\t\t Enter admin username: ");
    scanf("%s", uname);
    printf("\t\t\t\t\t\t Enter admin password: ");
    scanf("%s", pword);

    if (strcmp(uname, "Admin") == 0 && strcmp(pword, "#ad12#") == 0)
    {
        printf("\t\t\t\t\t\t Admin login successful!\n");
        adminInterface(users, numUsers);
    }
    else
    {
        printf("\t\t\t\t\t\t Invalid Admin credentials.\n");
    }
}

// Admin interface function
void adminInterface(struct User users[], int numUsers)
{
    int choice;
    do
    {
        printf("\n\t\t\t\t\t\t === Admin Panel ===\n");
        printf("\t\t\t\t\t\t 1. Display All Users\n");
        printf("\t\t\t\t\t\t 2. Display Total Balance\n");
        printf("\t\t\t\t\t\t 3. Display Total Users\n");
        printf("\t\t\t\t\t\t 4. Search User\n");
        printf("\t\t\t\t\t\t 5. Block User\n");
        printf("\t\t\t\t\t\t 6. Unblock User\n");
        printf("\t\t\t\t\t\t 7. Exit to Main Menu\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayAllUsers(users, numUsers);
            break;
        case 2:
            displayTotalBalance(users, numUsers);
            break;
        case 3:
            displayTotalUsers(numUsers);
            break;
        case 4:
            searchUser(users, numUsers);
            break;
        case 5:
            blockUser(users, numUsers);
            break;
        case 6:
            unblockUser(users, numUsers);
            break;
        case 7:
            printf("\t\t\t\t\t\t Exiting Admin Panel...\n");
            return;
        default:
            printf("\t\t\t\t\t\t Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

// User menu function
void userMenu(struct User users[], int *numUsers)
{
    int choice;
    printf("\n\t\t\t\t\t\t === User Panel ===\n");
    printf("\t\t\t\t\t\t 1. Login as User\n");
    printf("\t\t\t\t\t\t 2. Sign Up as New User\n");
    printf("\t\t\t\t\t\t Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        userLogin(users, *numUsers);
        break;
    case 2:
        userSignUp(users, numUsers);
        break;
    default:
        printf("\t\t\t\t\t\t Invalid choice. Returning to main menu.\n");
    }
}

// User login function
void userLogin(struct User users[], int numUsers)
{
    int accountNumber;
    char password[50];

    printf("\t\t\t\t\t\t Enter your account number: ");
    scanf("%d", &accountNumber);
    printf("\t\t\t\t\t\t Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].accountNumber == accountNumber && strcmp(users[i].password, password) == 0)
        {
            if (users[i].isBlocked)
            {
                printf("\t\t\t\t\t\t Your account is blocked. Contact admin for assistance.\n");
                return;
            }
            printf("\t\t\t\t\t\t Login successful! Welcome, %s!\n", users[i].name);
            userInterface(&users[i], users, numUsers);
            return;
        }
    }
    printf("\t\t\t\t\t\t Invalid credentials.\n");
}

// User sign-up function
void userSignUp(struct User users[], int *numUsers)
{
    struct User newUser;
    newUser.accountNumber = SYSTEM_IDENTITY * 1000 + (*numUsers + 1);
    printf("\t\t\t\t\t\t Enter your name: ");
    scanf("%s", newUser.name);
    printf("\t\t\t\t\t\t Enter password: ");
    scanf("%s", newUser.password);
    newUser.balance = 0.0;
    newUser.depositCount = 0;
    newUser.transferCount = 0;
    newUser.isBlocked = 0;

    users[*numUsers] = newUser;
    (*numUsers)++;
    printf("\t\t\t\t\t\t Account created successfully!\n\t\t\t\t\t\t Your account number is %d\n", newUser.accountNumber);
}

// User interface function
void userInterface(struct User *user, struct User users[], int numUsers)
{
    int choice;
    do
    {
        printf("\n\t\t\t\t\t\t === User Menu ===\n");
        printf("\t\t\t\t\t\t 1. View Balance\n");
        printf("\t\t\t\t\t\t 2. Deposit Money\n");
        printf("\t\t\t\t\t\t 3. Transfer Money\n");
        printf("\t\t\t\t\t\t 4. Invest Money\n");
        printf("\t\t\t\t\t\t 5. View Transaction History\n");
        printf("\t\t\t\t\t\t 6. Exit to Main Menu\n");
        printf("\t\t\t\t\t\t Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            viewBalance(user);
            break;
        case 2:
            depositMoney(user);
            break;
        case 3:
            transferMoney(users, numUsers, user);
            break;
        case 4:
            investMoney(user);
            break;
        case 5:
            viewTransactionHistory(user);
            break;
        case 6:
            printf("\t\t\t\t\t\t Exiting to main menu...\n");
            return;
        default:
            printf("\t\t\t\t\t\t Invalid choice. Try again.\n");
        }
    } while (choice != 6);
}

// Admin functions
void displayAllUsers(struct User users[], int numUsers)
{
    if (numUsers == 0)
    {
        printf("\t\t\t\t\t\t No users available.\n");
        return;
    }
    for (int i = 0; i < numUsers; i++)
    {
        printf("\t\t\t\t\t\t Account Number: %d, Name: %s, Balance: $%.2f, Blocked: %s\n",
               users[i].accountNumber, users[i].name, users[i].balance,
               users[i].isBlocked ? "Yes" : "No");
    }
}

void displayTotalBalance(struct User users[], int numUsers)
{
    double total = 0;
    for (int i = 0; i < numUsers; i++)
    {
        total += users[i].balance;
    }
    printf("\t\t\t\t\t\t Total balance in the system: $%.2f\n", total);
}

void displayTotalUsers(int numUsers)
{
    printf("\t\t\t\t\t\t Total number of users: %d\n", numUsers);
}

void searchUser(struct User users[], int numUsers)
{
    int accountNumber;
    printf("\t\t\t\t\t\t Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].accountNumber == accountNumber)
        {
            printf("\t\t\t\t\t\t Account Number: %d, Name: %s, Balance: $%.2f\n",
                   users[i].accountNumber, users[i].name, users[i].balance);
            return;
        }
    }
    printf("\t\t\t\t\t\t User not found.\n");
}

void blockUser(struct User users[], int numUsers)
{
    int accountNumber;
    printf("\t\t\t\t\t\t Enter account number to block: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].accountNumber == accountNumber)
        {
            users[i].isBlocked = 1;
            printf("\t\t\t\t\t\t User %d has been blocked.\n", accountNumber);
            return;
        }
    }
    printf("\t\t\t\t\t\t User not found.\n");
}

void unblockUser(struct User users[], int numUsers)
{
    int accountNumber;
    printf("\t\t\t\t\t\t Enter account number to unblock: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].accountNumber == accountNumber)
        {
            users[i].isBlocked = 0;
            printf("\t\t\t\t\t\t User %d has been unblocked.\n", accountNumber);
            return;
        }
    }
    printf("\t\t\t\t\t\t User not found.\n");
}

// User functions
void viewBalance(struct User *user)
{
    printf("\t\t\t\t\t\t Your balance is: $%.2f\n", user->balance);
}

void depositMoney(struct User *user)
{
    double amount;
    printf("\t\t\t\t\t\t Enter the amount to deposit: $");
    scanf("%lf", &amount);
    if (amount <= 0)
    {
        printf("\t\t\t\t\t\t Invalid amount. Please try again.\n");
        return;
    }
    printf("\n\t\t\t\t\t\t Processing your transaction.\n\t\t\t\t\t\t Please hold while we complete the verification process...\n");
    for (int i = 3; i > 0; i--)
    {
        printf("\t\t\t\t\t\t %d...\n", i);
        sleep(1);
    }
    user->balance += amount;
    printf("\n\t\t\t\t\t\t Deposit successful. New balance: $%.2f\n", user->balance);

    // Log the deposit in transaction history
    char transactionDetails[100];
    snprintf(transactionDetails, 100, "Deposited ");
    logTransaction(user, transactionDetails, "deposit", amount);
}

void transferMoney(struct User users[], int numUsers, struct User *user)
{
    int recipientAccount;
    double amount;
    printf("\t\t\t\t\t\t Enter recipient account number: ");
    scanf("%d", &recipientAccount);
    printf("\t\t\t\t\t\t Enter the amount to transfer: $");
    scanf("%lf", &amount);
    printf("\n\t\t\t\t\t\t Initiating funds transfer.\n\t\t\t\t\t\t Please wait while we process your request....\n");
    for (int i = 3; i > 0; i--)
    {
        printf("\t\t\t\t\t\t %d...\n", i);
        sleep(1);
    }
    if (amount <= 0 || amount > user->balance)
    {
        printf("\t\t\t\t\t\t Invalid amount. Please try again.\n");
        return;
    }

    // Loop through the users to find the recipient account
    for (int i = 0; i < numUsers; i++)
    {
        if (users[i].accountNumber == recipientAccount)
        {
            if (users[i].isBlocked)
            {
                printf("\t\t\t\t\t\t Recipient account is blocked. Transfer not allowed.\n");
                return;
            }

            // Perform the transfer
            user->balance -= amount;
            users[i].balance += amount;

            printf("\n\t\t\t\t\t\t Transfer successful! You sent $%.2f to account %d.\n", amount, recipientAccount);
            printf("\t\t\t\t\t\t Your new balance: $%.2f\n", user->balance);

            // Log the transfer in both sender and recipient histories
            char senderTransaction[100], recipientTransaction[100];
            snprintf(senderTransaction, 100, "Transferred to %d", recipientAccount);
            snprintf(recipientTransaction, 100, "Received from %d", user->accountNumber);

            logTransaction(user, senderTransaction, "transfer", amount);
            logTransaction(&users[i], recipientTransaction, "transfer", amount);

            return;
        }
    }
    printf("\t\t\t\t\t\t Recipient account not found or blocked.\n");
}

void investMoney(struct User *user)
{
    double amount;
    int choice;
    printf("\n\t\t\t\t\t\t Please wait!\n\t\t\t\t\t\t while we verify the available\n\t\t\t\t\t\t investment opportunities\n");
    for (int i = 3; i > 0; i--)
    {
        printf("\t\t\t\t\t\t %d...\n", i);
        sleep(1);
    }

    printf("\n\t\t\t\t\t\t To invest,\n\t\t\t\t\t\t you need to pay a fee of $5.\n\n");

    printf("\t\t\t\t\t\tToday's Investment Options:\n");
    printf("\t\t\t\t\t\t 1. Tech Company A\n");
    printf("\t\t\t\t\t\t 2. Tech Company B\n");
    printf("\t\t\t\t\t\t 3. Tech Company C\n");
    printf("\t\t\t\t\t\t 4. Tech Company D\n");
    printf("\t\t\t\t\t\t 5. Tech Company E\n");

    printf("\n\t\t\t\t\t\t Please choose\n\t\t\t\t\t\t your desired investment option:");
    scanf("%d", &choice);

    // Handle investment options with a switch statement
    switch (choice)
    {
    case 1:
        printf("\n\t\t\t\t\t\t You have selected to invest in Tech Company A.\n");
        break;
    case 2:
        printf("\n\t\t\t\t\t\t You have selected to invest in Tech Company B.\n");
        break;
    case 3:
        printf("\n\t\t\t\t\t\t You have selected to invest in Tech Company C.\n");
        break;
    case 4:
        printf("\n\t\t\t\t\t\t You have selected to invest in Tech Company D.\n");
        break;
    case 5:
        printf("\n\t\t\t\t\t\t You have selected to invest in Tech Company E.\n");
        break;
    default:
        printf("\t\t\t\t\t\t Invalid option selected. Returning to the main menu.\n");
        return;
    }

    // Prompt the user for the investment amount
    printf("\n\t\t\t\t\t\t Enter the amount to invest \n\t\t\t\t\t\t(excluding the fee): $");
    scanf("%lf", &amount);

    printf("\n\t\t\t\t\t\t Please wait");
    for (int i = 4; i > 0; i--)
    {
        printf(".", i);
        sleep(1);
    }

    if ((amount <= 0 || amount > user->balance) || (amount <= 5))
    {
        printf("\n\t\t\t\t\t\t Invalid amount. Please try again.\n");
        return;
    }

    user->balance -= (amount + 200);

    printf("\n\t\t\t\t\t\t Investment successful.\n\t\t\t\t\t\t Your new balance is: $%.2f\n", user->balance);

    // Log the investment as a deposit for record keeping
    logTransaction(user, "Investment", "deposit", amount); // Investment is logged under deposits
}

void viewTransactionHistory(struct User *user)
{
    printf("\n\t\t\t\t\t\t Transaction History for %s:\n", user->name);

    printf("\n\t\t\t\t\t\t Deposits:\n");
    if (user->depositCount == 0)
    {
        printf("\t\t\t\t\t\t No deposit history available.\n");
    }
    else
    {
        for (int i = 0; i < user->depositCount; i++)
        {
            printf("\t\t\t\t\t\t %s\n", user->depositHistory[i]);
        }
    }

    printf("\n\t\t\t\t\t\t Transfers:\n");
    if (user->transferCount == 0)
    {
        printf("\t\t\t\t\t\t No transfer history available.\n");
    }
    else
    {
        for (int i = 0; i < user->transferCount; i++)
        {
            printf("\t\t\t\t\t\t %s\n", user->transferHistory[i]);
        }
    }
}

// Log a transaction (deposit or transfer)
void logTransaction(struct User *user, const char *transactionDetails, const char *transactionType, double amount)
{
    char transactionRecord[100];
    snprintf(transactionRecord, 100, "%s - $%.2f", transactionDetails, amount);

    if (strcmp(transactionType, "deposit") == 0)
    {
        snprintf(user->depositHistory[user->depositCount++], 50, "%s", transactionRecord);
    }
    else if (strcmp(transactionType, "transfer") == 0)
    {
        snprintf(user->transferHistory[user->transferCount++], 50, "%s", transactionRecord);
    }
}
