#ifndef BANK_QUERY_H
#define BANK_QUERY_H

#define EMPTY 0.00
#define START true
#define END false

#include <iostream>
#include <iomanip>      // this is for decimal precision
#include <fstream>      // this is so we can work with files
#include <string>
#include <vector>
#include <algorithm>

void drawTable(bool begin);

class bank_query {
private:
    std::vector<std::string> first_names;
    std::vector<std::string> last_names;
    std::vector<int> account_numbers;
    std::vector<float> account_balances;
public:
    bank_query();
    void add_record();          // method to add a records 
    int search_record();        // method to search for a record
    void update_record();       // method to update a record
    void delete_record();       // method to delete a record
    void all_records();         // method to display all records
    void SaveAndExit();         // save records and exit system
};
#endif