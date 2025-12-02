// COMSC 210 | Lab 37 | 2 DEC 2025
// IDE: VS Code

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <fstream>

using namespace std;

// Fn prototypes
int sum_ascii(const string &str);
void ascii_tester();
int gen_hash_index(const string &str);

// Constants
const int HASH_MOD = 1009; // Large prime number
const string FILENAME = "/Users/andrewtai/Desktop/COMSC_210/projects/210-lab-37/lab-37-data.txt";

// -------------------------------------------
// Main
// -------------------------------------------
int main() {

    // Create hash table
    map<int, list<string>> hash_table;

    // Loop through file -- Edit once you have the file
    ifstream infile(FILENAME);
    if (!infile) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    string line;
    while (infile >> line) {
        int hash_index = gen_hash_index(line);
        hash_table[hash_index].push_back(line);
    }

    return 0;
}

// -------------------------------------------
// Programmer fns
// -------------------------------------------

int sum_ascii(const string &str) {
    // Arg: str to convert to ASCII sum
    // Ret: int: sum of ASCII values of all chars in str

    int sum = 0;
    for (char ch : str) {
        sum += (int) ch;
    }
    return sum;
}

void ascii_tester() {
    // Tests the sum_ascii fn

    cout << "A" << sum_ascii("A = ") << endl; // 65
    cout << "AB" << sum_ascii("AB = ") << endl; // 65 + 66 = 131
    cout << "q!" << sum_ascii("q! = ") << endl; // 33 + 113 = 146
}

int gen_hash_index(const string &str) {
    // Arg: str to hash
    // Ret: int: hash index for str

    int ascii_sum = sum_ascii(str);
    int hash_index = ascii_sum % HASH_MOD;
    return hash_index;
}