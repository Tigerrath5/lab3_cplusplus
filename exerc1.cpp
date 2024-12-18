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

    // Step 3: Calculate mean loan and debt amounts
    std::vector<int> loans, debts;
    std::for_each(sortedData.begin(), sortedData.end(), [&](const auto& entry) {
        if (entry.second > 0) {
            loans.push_back(entry.second); // Positive values are loans
        } else if (entry.second < 0) {
            debts.push_back(std::abs(entry.second)); // Negative values are debts
        }
    });

    double meanLoan = loans.empty() ? 0.0 : std::accumulate(loans.begin(), loans.end(), 0.0) / loans.size();
    double meanDebt = debts.empty() ? 0.0 : std::accumulate(debts.begin(), debts.end(), 0.0) / debts.size();

    // Print mean values
    std::cout << "Mean loan amount: " << std::fixed << std::setprecision(2) << meanLoan << std::endl;
    std::cout << "Mean debt amount: " << std::fixed << std::setprecision(2) << meanDebt << std::endl;

    return 0;
}

/*
Comments explaining the code:

1. `#include` statements:
   - Include necessary libraries for input/output, data structures, algorithms, and mathematical functions.

2. `std::map<std::string, int> balances`:
   - A map to store the net balance for each person.

3. Input parsing loop:
   - Reads lines of input in the format `<Payer name> <Receiver name> <price>`.
   - Updates the map: increases the payer's balance and decreases the receiver's balance.

4. `std::vector` and sorting:
   - Copies the map into a vector of pairs for sorting.
   - Sorts by balance in descending order and by name alphabetically for ties.

5. `std::for_each` for categorizing loans and debts:
   - Iterates through the sorted data to separate loans (positive balances) and debts (negative balances).

6. Mean calculation:
   - Uses `std::accumulate` to calculate the sum and divides by the number of elements to get the mean for loans and debts.

7. Output:
   - Prints the sorted data and the calculated mean loan and debt amounts.
*/
