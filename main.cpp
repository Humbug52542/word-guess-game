
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

string hexToBytes(const string& hex) {
    string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        char byte = (char) stoi(hex.substr(i, 2), nullptr, 16);
        result.push_back(byte);
    }
    return result;
}

string decrypt(const string& data, char key) {
    string decrypted;
    for (char c : data) {
        decrypted.push_back(c ^ key);
    }
    return decrypted;
}

int main() {
    vector<string> encryptedWords = {
        "0b06031f1f0e",   // Encrypted word 1
        "0b0702011c020a", // Encrypted word 2
        "1a0208151a040d", // Encrypted word 3
        "1d0a0004011a",   // Encrypted word 4
        "0d060a1a0f",     // Encrypted word 5
        "0f07041f0a0b",   // Encrypted word 6
        "0a0d1a1a0a"      // Encrypted word 7
    };

    const char key = 0x55; 

    srand(static_cast<unsigned int>(time(nullptr)));

    vector<string> words;
    for (const auto& ew : encryptedWords) {
        string raw = hexToBytes(ew);
        words.push_back(decrypt(raw, key));
    }

    string secretWord = words[rand() % words.size()];

    set<char> guessedLetters;
    int attemptsLeft = 6;

    cout << "Welcome to the Word Guess Game!\n";

    while (attemptsLeft > 0) {
        bool allGuessed = true;

        for (char c : secretWord) {
            if (guessedLetters.count(c)) {
                cout << c << ' ';
            } else {
                cout << "_ ";
                allGuessed = false;
            }
        }

        cout << "\nAttempts left: " << attemptsLeft << "\nGuess a letter: ";

        char guess;
        cin >> guess;
        guess = tolower(guess);

        if (guessedLetters.count(guess)) {
            cout << "Already guessed.\n";
            continue;
        }

        guessedLetters.insert(guess);

        if (secretWord.find(guess) == string::npos) {
            cout << "Wrong!\n";
            attemptsLeft--;
        }

        if (allGuessed) {
            cout << "You won! The word was " << secretWord << "\n";
            break;
        }
    }

    if (attemptsLeft == 0) {
        cout << "You lost! The word was " << secretWord << "\n";
    }

    return 0;
}
