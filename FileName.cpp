/*
Mohamed Elmarzougui
10/15/2023

*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class InventoryAnalyzer {
public:
    InventoryAnalyzer(const string& inputFilename, const string& outputFilename);
    void run();

private:
    map<string, int> itemFrequency;
    string inputFilename;
    string outputFilename;

    void loadItemFrequencies();
    void printHistogram();
    void saveDataToFile();
};

InventoryAnalyzer::InventoryAnalyzer(const string& inputFilename, const string& outputFilename) :
    inputFilename(inputFilename), outputFilename(outputFilename) {
    loadItemFrequencies();
}

void InventoryAnalyzer::loadItemFrequencies() {
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the input file." << endl;
        return;
    }

    string item;
    while (inputFile >> item) {
        itemFrequency[item]++;
    }

    inputFile.close();
}

void InventoryAnalyzer::printHistogram() {
    cout << "Item Histogram:" << endl;
    for (const auto& entry : itemFrequency) {
        cout << entry.first << " ";
        for (int i = 0; i < entry.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}

void InventoryAnalyzer::saveDataToFile() {
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the output file for data backup." << endl;
        return;
    }

    for (const auto& entry : itemFrequency) {
        outputFile << entry.first << " " << entry.second << endl;
    }

    outputFile.close();
    cout << "Data has been backed up to '" << outputFilename << "'" << endl;
}

void InventoryAnalyzer::run() {
    saveDataToFile(); // Save data to the backup file at the beginning

    while (true) {
        cout << "Menu Options:" << endl;
        cout << "1. Look up the frequency of a specific word" << endl;
        cout << "2. Print the list of items with their frequencies" << endl;
        cout << "3. Print a histogram of item frequencies" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1/2/3/4): ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string searchWord;
            cout << "Enter the word you wish to look for: ";
            cin.ignore(); // Clear the newline character from the input buffer
            getline(cin, searchWord);

            if (itemFrequency.find(searchWord) != itemFrequency.end()) {
                int frequency = itemFrequency[searchWord];
                cout << "The word '" << searchWord << "' appears " << frequency << " times." << endl;
            }
            else {
                cout << "The word '" << searchWord << "' does not appear in the records." << endl;
            }
        }
        else if (choice == 2) {
            cout << "Item Frequencies:" << endl;
            for (const auto& entry : itemFrequency) {
                cout << entry.first << " " << entry.second << endl;
            }
        }
        else if (choice == 3) {
            printHistogram();
        }
        else if (choice == 4) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please select 1, 2, 3, or 4." << endl;
        }
    }
}

int main() {
    InventoryAnalyzer analyzer("inventory.txt", "frequency.dat");
    analyzer.run();
    return 0;
}