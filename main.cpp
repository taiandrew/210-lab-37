// COMSC 210 | Lab 37 | 2 DEC 2025
// IDE: VS Code

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

// Fn prototypes
int sum_ascii(const string &str);
void tester();

// -------------------------------------------
// Main
// -------------------------------------------
int main() {

    tester();

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

void tester() {
    cout << "A" << sum_ascii("A") << endl; // 65
    cout << "AB" << sum_ascii("AB") << endl; // 65 + 66 = 131
    cout << "q!" << sum_ascii("q!") << endl; // 33 + 113 = 146
}