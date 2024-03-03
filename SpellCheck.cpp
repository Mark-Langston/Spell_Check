#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <cctype> // for isalpha function

int main() {

    // Initaite necessary variable for program loop
    std::string answer;
    
    // Open words file/ Unix words
    std::ifstream words_file("words.txt");

    // Check if words.txt exists
    if (!words_file.is_open()) {
        std::cerr << "Error: 'words.txt' file not found in the same directory as the program.\n";
        return 1;
    }

    // Set to store words from words.txt
    std::set<std::string> word_set;
    std::string word;

    // Read words from words.txt and store them in the set
    while (words_file >> word) {
        word_set.insert(word);
    }

    // Close words file
    words_file.close();

    do {
        // Prompt user for the file name
        std::string file_name;
        std::cout << "Enter the file name to check spelling (you can enter test_file.txt): ";
        std::cin >> file_name;

        // Open user-provided file
        std::ifstream user_file(file_name);

        // Check if user-provided file exists
        if (!user_file.is_open()) {
            std::cerr << "Error: Unable to open file, terminating program! [" << file_name << "].\n";
            return 1;
        }

        // Check spelling and print words not found in the word list
        std::cout << "Words not found in the word list:\n";
        while (user_file >> word) {
            // Check if word only contains letters
            bool only_letters = true;
            for (char ch : word) {
                if (!isalpha(ch)) {
                    only_letters = false;
                    break;
                }
            }

            // Check if the word is not in the word list and only contains letters
            if (word_set.find(word) == word_set.end() && only_letters) {
                std::cout << word << std::endl;
            }
        }
        
        // Close user file
        user_file.close();

        // Ask the user if they want to spellcheck another file, after response is entered system clears screen
        std::cout << "\nDo you want to spellcheck another file? (yes/no): ";
        std::cin >> answer;
        system("cls");

        // Convert the answer to lowercase for case-insensitive comparison
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    } while (answer == "yes" || answer == "y");

    // Terminates program
    return 0;
}