#include "bank_query.h"

// constructor will initialze our vectors. this is the constructor. it will read the txt file to initialize the data vectors
bank_query::bank_query() {
    std::string line;   // string to hold the lines we read
    int index;      // counter to index the line string
    int counter;    // counter to know what data we are on
    std::ifstream infile("BankRecords.txt");    // open text file
    if (!infile)    // if unsuccessful, tell the user
        std::cout << "Unable to open file for reading \n";
    else {
        while (getline(infile, line)) {                 // loop through while we have not reached the end of the file
            index = 0;                                  // init the counter so that we start at beginning of string
            counter = 0;                                // init the counter so that we start with the correct data
            for (int i = 0; i < line.size(); i++) {     // while we have not reached the end of the line do this loop
                if (line[i] == ' ') {                   // if we have reached a space we need to save data to a vector
                    if (counter == 0)                   // if counter is 0 we know that we are getting the account number
                        account_numbers.push_back(std::stoi(line.substr(index, i)));   // add the account number to our vector. need to convert a string to an int 
                    else if (counter == 1)  // if counter is 1 we know that we are going to be getting the account balances info
                        account_balances.push_back(std::stof(line.substr(index, i - index)));  // subtr(start pos, size to take). this gets the balance. std::stof cast a string as a float
                    else if (counter == 2)  // if counter is 2 we know that we are going to be getting the last names info
                        last_names.push_back(line.substr(index, i - index));     // this gets the last names
                    else if (counter == 3) {    // if counter is 3 we know that we are going to be getting the first names info
                        first_names.push_back(line.substr(index, i - index));     // this will get the first names
                    }
                    counter++;  // increment this so we know to move to the next data
                    index = i + 1;  // change index so we know where to start reading from on the next iteration
                }
            }
        }
        infile.close(); // close the file
    }
}

// check if an account number is valid
void bank_query::all_records() {
    drawTable(START);   // draw the top of the table
    // loop through the elements in the vectors and display them
    for (int i = 0; i < (int)first_names.size(); i++) {
        std::cout << "   " << account_numbers[i] << "\t\t|\t" << std::setprecision(2) << std::fixed << account_balances[i]
            << "\t\t|\t" << last_names[i] << ", " << first_names[i] << '\n';
    }
    drawTable(END); // draw the bottom of the table
}   

// add a record
void bank_query::add_record() {
    // declare some variables for data input
    int account_number;
    std::string first_name, last_name;
    float account_balance;

    std::cout << "Enter Account Number: ";          // ask user for an account number
    std::cin >> account_number;
    auto found = std::find(account_numbers.begin(), account_numbers.end(), account_number);  // this will check if the account number already exists

    // do this loop until user enters a new account number
    while (found != account_numbers.end()) {
        std::cout << "\nThe account number you entered already exists.\nPlease enter a new Account Number: "; // ask user for an account number
        std::cin >> account_number;
        found = std::find(account_numbers.begin(), account_numbers.end(), account_number);  // this will check if the account number already exists
    }

    std::cout << "Enter First Name: ";              // ask user for first name
    std::cin >> first_name;
    std::cout << "Enter Last Name: ";               // ask user for last name
    std::cin >> last_name;
    account_balance = EMPTY;

    account_numbers.push_back(account_number);      // add new account number to end of account numbers vector
    first_names.push_back(first_name);              // add new first name to end of first names vector
    last_names.push_back(last_name);                // add new last name to end of last names vector
    account_balances.push_back(account_balance);    // add new account balance to end of account balances vector
    
    std::system("CLS");
    std::cout << "Account added to records!\n";
    std::cout << "================================\n";
}

// search for a specific bank record
int bank_query::search_record() {
    int account_number;
    std::cout << "Enter account number: ";  // ask user for an account number
    std::cin >> account_number;             // store the account number in a variable
    std::system("CLS");                     // clear the screen

    drawTable(START);   // draw the top part of the table

    auto found = std::find(account_numbers.begin(), account_numbers.end(), account_number);  // this will get us an iterator to the correct index if it exists

    if (found == account_numbers.end()) {             // if the iterator is at the end of the vector, we could not find the account number
        std::cout << "   Account number '" << account_number << "' not found!\n";    // tell user that the account number doesnt exist
        drawTable(END);     // draw the bottom part of the table
        return -1;
    }
    else {
        int index = std::distance(account_numbers.begin(), found);                  // this will get the index of the account number in the vector
        std::cout << "   " << account_numbers[index] << "\t\t|\t" << std::setprecision(2) << std::fixed << account_balances[index]
            << "\t\t|\t" << last_names[index] << ", " << first_names[index] << '\n';
        drawTable(END);     // draw the bottom part of the table
        return index;
    }
}

// update our records
void bank_query::update_record() {
    int choice;     // this will be used to check what command the user wants to do 
    float money;    // this will be used if the user wants to withdraw or deposit money
    int index = search_record();
    if (index != -1) {      // if we received a valid account number we will show them the options to update the record
        std::cout << "Select field you would like to update ";
        std::cout << "\n1-Update First Name";
        std::cout << "\n2-Update Last Name";
        std::cout << "\n3-Make a deposit";
        std::cout << "\n4-Make a withdrawl\n";
        std::cout << "================================\n";
        std::cout << "Select option >> ";
        std::cin >> choice;
        std::cout << '\n';
        switch (choice)
        {
        case 1: // user can change first name
            std::cout << "Enter new First Name: ";
            std::cin >> first_names[index]; // put the new first name in the correct index of the first names vector
            break;
        case 2: // user can change last name
            std::cout << "Enter new Last Name: ";
            std::cin >> last_names[index];  // put the new last name in the correct index of the last names vector
            break;
        case 3: // user can deposit money
            std::cout << "Enter deposit value: $";
            std::cin >> money;                  // put the money to deposit into a float variable
            account_balances[index] += money;   // add the deposit money to the current amount of money in the account
            break;
        case 4: // user can withdraw money
            std::cout << "Enter withdraw value: $";
            std::cin >> money;                  // put the money to withdraw into a float variable
            account_balances[index] -= money;   // subtract the withdraw money from the current amount of money in the account
            break;
        default:
            std::cout << "Invalid option\n";
            std::cout << "================================\n";
            break;
        }
        std::system("CLS"); // clear screen
        std::cout << "Account updated!\n";
        std::cout << "================================\n";
    }

}

// we will use this method to delete a record
void bank_query::delete_record() {
    int index = search_record();
    if (index != -1) {
        first_names.erase(first_names.begin() + index);             // erase the first name from the vector
        last_names.erase(last_names.begin() + index);               // erase the last name from the vector
        account_balances.erase(account_balances.begin() + index);   // erase the account balance from the vector
        account_numbers.erase(account_numbers.begin() + index);     // erase the account number from the vector

        std::cout << "Record has been erased!\n";
        std::cout << "================================\n";
    }
}

// this method will save records to a txt file
void bank_query::SaveAndExit() {
    std::ofstream outf;
    outf.open("BankRecords.txt");    // we will open file "BankRecords.txt" for writing
    if (!outf) {    // check if we are able to open the file for writing
        std::cout << "unable to open up the txt file for writing\n";

        std::system("CLS");
        std::cout << "Unable to save records to database!\n";
        std::cout << "================================\n";
    }
    else {

        for (int i = 0; i < (int)first_names.size(); i++) {
            outf << account_numbers[i] << ' ' << std::setprecision(2) << std::fixed << account_balances[i]
                << ' ' << last_names[i] << ' ' << first_names[i] << " \n";
        }
        outf.close();   // close the file we are writing to

        std::system("CLS"); 
        std::cout << "Records have been saved to database!\n";
        std::cout << "====================================\n";
    }
}