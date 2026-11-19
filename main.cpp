#include "src/Huffman.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    string originalText = "Hello World";

    CompressionResult compressed = compress(originalText);

    cout << "Original text: " << originalText << "\n\n";

    cout << "Huffman Table:\n";

    cout << left
         << setw(12) << "Character"
         << setw(12) << "Frequency"
         << "Code\n";

    cout << "--------------------------------\n";

    vector<char> characters;

    for (auto& entry : compressed.frequencies) {
        characters.push_back(entry.first);
    }

    sort(characters.begin(), characters.end());

    for (char c : characters) {

        string display = (c == ' ') ? "[space]" : string(1, c);

        cout << left
             << setw(12) << display
             << setw(12) << compressed.frequencies[c]
             << compressed.codes[c]
             << endl;
    }

    cout << "\nCompressed string:\n";
    cout << compressed.compressedText << "\n";

    string restoredText = decompress(
        compressed.compressedText,
        compressed.codes
    );

    cout << "\nDecompressed string:\n";
    cout << restoredText << "\n";

    return 0;
}
