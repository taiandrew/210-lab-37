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
void print_hash_table(const map<int, list<string>> &hash_table, int top_n);
int user_menu();
int search_key(const map<int, list<string>> &hash_table, const string &key);
void user_search_key(const map<int, list<string>> &hash_table);
void user_add_key(map<int, list<string>> &hash_table);
void user_remove_key(map<int, list<string>> &hash_table);

// Constants
const int HASH_MOD = 1009; // Large prime number
const string FILENAME = "/Users/andrewtai/Desktop/COMSC_210/projects/210-lab-37/lab-37-data.txt";

// -------------------------------------------
// Main
// -------------------------------------------
int main() {

    // Create hash table with of lists
    map<int, list<string>> hash_table;

    // Loop through file
    int sum = 0;
    ifstream infile(FILENAME);
    if (!infile) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    string line;
    while (infile >> line) {
        int hash_index = gen_hash_index(line);      // Get hash index
        hash_table[hash_index].push_back(line);     // Insert into hash table at index; initializes list if not already
    }
    infile.close();

    // Menu loop
    int choice = 0;
    while (choice!=6) {
        choice = user_menu();
        switch (choice) {
            case 1:
                print_hash_table(hash_table, 100);
                break;
            case 2: {
                user_search_key(hash_table);
                break;
            }
            case 3: {
                user_add_key(hash_table);
                break;
            }
            case 4: {
                user_remove_key(hash_table);
                break;
            }
                
        }
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

void print_hash_table(const map<int, list<string>> &hash_table, int top_n) {
    // Prints the first top_n entries in the hash table (strings, not indexes)
    // Arg: hash_table to print
    // Arg: top_n number of entries to print
    
    int count = 0;
    for (const auto &entry : hash_table) {      // Loop through entries -- note: one entry is an index and its list of strings
        cout << "Index " << entry.first << ": " << endl;  // index
        for (const auto &str : entry.second) {   // Strings stored at this index
            cout << "\t" << str << endl;
            count++;
            if (count >= top_n) return;
        }
        cout << endl;
    }
}

int user_menu() {
    // Implements user menu; returns selection

    int choice;
    cout << "Menu:\n"
         << "1. Print first 100 entries\n"
         << "2. Search for a key\n"
         << "3. Add a key\n"
         << "4. Remove a key\n"
         << "5. Modify a key\n"
         << "6. Exit\n"
         << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int search_key(const map<int, list<string>> &hash_table, const string &key) {
    // Args:
    // - hash_table to search
    // - key to search for
    // Returns: index if key found, -1 if not

    int hash_index = gen_hash_index(key);
    auto it = hash_table.find(hash_index);
    if (it != hash_table.end()) {       // If index exists, check contained list for key
        const list<string> &keys = it->second;
        for (const auto &str : keys) {
            if (str == key) {
                return hash_index;
            }
        }
    }
    return -1; // Not found
}

void user_search_key(const map<int, list<string>> &hash_table) {
    // Implements user search key

    string key;
    cout << "Enter key to search for: ";
    cin >> key;
    int index = search_key(hash_table, key);
    if (index != -1) {
        cout << "Key '" << key << "' found at index " << index << "." << endl;
    } else {
        cout << "Key '" << key << "' not found in hash table." << endl;
    }
    cout << endl;
}


void user_add_key(map<int, list<string>> &hash_table) {
    // Implements user add key

    string key;
    cout << "Enter key to add: ";
    cin >> key;
    int hash_index = gen_hash_index(key);
    hash_table[hash_index].push_back(key);
    cout << "Key '" << key << "' added at index " << hash_index << "." << endl;
    cout << endl;
}

void user_remove_key(map<int, list<string>> &hash_table) {
    // Implements user remove key

    string key;
    cout << "Enter key to remove: ";
    cin >> key;
    int index = search_key(hash_table, key);
    if (index != -1) {
        hash_table[index].remove(key);
        cout << "Key '" << key << "' removed from index " << index << "." << endl;
    } else {
        cout << "Key '" << key << "' not found in hash table." << endl;
    }
    cout << endl;
}