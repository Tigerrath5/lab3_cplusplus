/**************************
 * Lab 3: exercise 3      *
 **************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main (){
    std::ifstream file("/Users/romeodahlstrom/Documents/lab3/code/uppgift3_kort.txt");
        if (!file) {
            std::cerr << "Error: Could not open file." << std::endl;
            return 1;
        }
    
    std::ofstream outputFile("/Users/romeodahlstrom/Documents/lab3/code/output.txt");
        if (!outputFile) {
            std::cerr << "Error: Could not open output file." << std::endl;
            return 1;
        }

    std::string line, word;
    std::map<std::string, std::vector<std::string>> anagrams; // Map to group words by their subject

    // Read words from file
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        // Read each word in the line
        while (ss >> word) {
            // Sort the characters in the word to compute its "subject"
            std::string subject = word;
            std::sort(subject.begin(), subject.end());

            // Group the word by its subject in the map
            if(anagrams.find(subject) != anagrams.end()){
                std::vector<std::string>& vec = anagrams[subject];

               // Check if the value already exists in the vector
                if (std::find(vec.begin(), vec.end(), word) == vec.end()) {
                    vec.push_back(word); // Add the value if not found
                }
                //anagrams[subject].push_back(word);
            }
            else{
                anagrams[subject].push_back(word);
            }
        
        }
    }

    // Debug: Check if words were found
    if (anagrams.empty()) {
        std::cerr << "Error: No words found in the file." << std::endl;
        return 1;
    }


// Write anagrams to the output file
    for (std::map<std::string, std::vector<std::string>>::iterator it = anagrams.begin(); it != anagrams.end(); ++it) {
        if (it->second.size() > 1) { // Only write groups with 2 or more anagrams
            outputFile << "Anagram group (" << it->second.size() << " words): ";
            for (std::vector<std::string>::iterator wordIt = it->second.begin(); wordIt != it->second.end(); ++wordIt) {
                outputFile << *wordIt << " ";
            }
            outputFile << std::endl;
        }
    }
}
