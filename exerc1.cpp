/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/
 
 /*
AE EM 102
AN PS 190
EM BD 23
CK EM 15
FF CK 17
AE CK 9
PS FF 50
DH FF 35
DH EM 65
PS AN 75
FF CK 18
AE EM 91
JP FF 203
*/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

// Function to print the summary
void printSummary(const std::vector<std::pair<std::string, int>>& data, const std::string& label) {
    std::cout << label << std::endl;
    for (const auto& entry : data) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

int main() {
    std::map<std::string, int> balances; // Stores the net balance for each person

    // Step 1: Read loans from std::cin
    std::string payer, receiver;
    int amount;

    std::cout << "Enter loans in the format: <Payer> <Receiver> <Amount> (e.g., AE EM 102)." << std::endl;
    std::cout << "To finish, press Ctrl+D (Linux/Mac) or Ctrl+Z (Windows) and Enter." << std::endl;

    while (std::cin >> payer >> receiver >> amount) {
        balances[payer] += amount;    // Increment payer's balance
        balances[receiver] -= amount; // Decrement receiver's balance
    }

    // Step 2: Prepare data for sorting
    std::vector<std::pair<std::string, int>> sortedData(balances.begin(), balances.end());

    std::sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second; // Sort by balance descending
        }
        return a.first < b.first; // Sort alphabetically for ties
    });

    printSummary(sortedData, "Name Balance");
    
    // Extract only the 'second' values into a new vector
    std::vector<int> balancesOnly;
    std::transform(sortedData.begin(), sortedData.end(), std::back_inserter(balancesOnly),
                   [](const std::pair<std::string, int>& entry) {
                       return entry.second;
                   });

    // Step 3: Calculate mean loan and debt amounts using copy_if
    std::vector<int> loans, debts;

    // Copy positive values (loans)
    std::copy_if(balancesOnly.begin(), balancesOnly.end(), std::back_inserter(loans),
                 [](const int& entry) {
                     return entry > 0;
                 });

    // Copy negative values (debts)
    std::copy_if(balancesOnly.begin(), balancesOnly.end(), std::back_inserter(debts),
                 [](const int& entry) {
                     return entry < 0;
                 });

    // Convert debts to absolute values
    std::transform(debts.begin(), debts.end(), debts.begin(), [](int value) {
        return std::abs(value);
    });

    // Calculate mean loan and debt amounts
    int meanLoan = loans.empty() ? 0.0 : std::accumulate(loans.begin(), loans.end(), 0.0) / loans.size();
    int meanDebt = debts.empty() ? 0.0 : std::accumulate(debts.begin(), debts.end(), 0.0) / debts.size();

    // Print mean values
    std::cout << "Mean loan amount: " << std::fixed << std::setprecision(2) << meanLoan << std::endl;
    std::cout << "Mean debt amount: " << std::fixed << std::setprecision(2) << meanDebt << std::endl;

    return 0;
}

