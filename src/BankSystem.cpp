// BankSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "bank_query.h"

void drawTable(bool begin) {
    if (begin) {
        std::cout << "Bank Record(s) \n";
        std::cout << "====================================================================\n";
        std::cout << "  Account #     |   Account Balance ($) |   Last Name, First Name   \n";
        std::cout << "--------------------------------------------------------------------\n";
    }
    else
        std::cout << "====================================================================\n";
}

int main()
{
    bank_query handler;     // handler is our bank_query class object
    std::uint16_t choice; 

    while (true)
    {
        std::cout << "Select one option below ";                // display all the options
        std::cout << "\n1-Add Record";
        std::cout << "\n2-Display All Records";
        std::cout << "\n3-Search Records";
        std::cout << "\n4-Update Record";
        std::cout << "\n5-Delete Record";
        std::cout << "\n6-Save & Exit\n";
        std::cout << "================================\n"; 
        std::cout << "Select option >> ";
        std::cin >> choice;
        std::cout << '\n';

        switch (choice)
        {
        case 1:                     // add a record
            handler.add_record();
            break;
        case 2:                     // show all records to user
            std::system("CLS");
            handler.all_records();
            break;
        case 3:                     // search for a specific record
            handler.search_record();
            break;
        case 4:                     // update a record
            handler.update_record();
            break;
        case 5:                     // delete a record
            handler.delete_record();
            break;
        case 6:                     // quit the program
            handler.SaveAndExit();
            exit(0);
            break;
        default:
            std::cout << "Invalid option\n";
            std::cout << "================================\n";
            break;
        }
    }
}