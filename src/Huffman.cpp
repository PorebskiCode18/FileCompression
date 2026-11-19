#include "Huffman.hpp"

#include <memory>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    char character;
    int frequency;

    Node* left;
    Node* right;

    Node(char c, int f) {
        character = c;
        frequency = f;
        left = nullptr;
        right = nullptr;
    }

    Node(Node* l, Node* r) {
        character = '\0';
        // The frequency of the parent node is the sum of the frequencies of its children
        frequency = l->frequency + r->frequency;
        left = l;
        right = r;
    }

    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
};
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};
Node* buildTree(const unordered_map<char,int>& frequencies){
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    // Create a leaf node for each character with (char,frequency) and add it to the priority queue
    for (auto& pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }
    if (minHeap.empty()) {
        return nullptr;
    }
    //retrieve two nodes with the lowest frequency from the priority queue,
    //create a new parent node with these two nodes as children, and add
    //the new node back to the priority queue. Repeat this process until
    //there is only one node left in the priority queue, which will be the
    //root of the Huffman tree.
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        Node* parent = new Node(left, right);
        minHeap.push(parent);
    }
    return minHeap.top();
}
//pre-order depth-first traversal
void generateCodes(Node* node, const string& prefix, unordered_map<char, string>& codes) {
    if (node == nullptr) {
        return;
    }
    if (node->isLeaf()) {
        //once we reach a leaf node, assign the prefix in codes map.
        codes[node->character] = prefix.empty() ? "0" : prefix;
    } else {
        generateCodes(node->left, prefix + "0", codes);
        generateCodes(node->right, prefix + "1", codes);
    }
}
CompressionResult compress(const string& plaintext) {
    CompressionResult result;
    //count frequencies
    for (char c : plaintext) {
        result.frequencies[c]++;
    }
    //build tree off frequencies and generate codes
    Node* root = buildTree(result.frequencies);
    //use the Huffman tree to generate the codes for each character and
    //store them in the codes map.
    generateCodes(root, "", result.codes);
    //Loop through original text and replace each char with corresponding code
    for (char c : plaintext) {
        result.compressedText += result.codes[c];
    }
    return result;
}
string decompress(const string& compressedText, const unordered_map<char, string>& codes) {
    //swap key/value pairs to create a reverse mapping from codes to characters
    unordered_map<string, char> reverseCodes;
    for (const auto& pair : codes) {
        reverseCodes[pair.second] = pair.first;
    }
    string currentCode;
    string decompressedText;
    for (char bit : compressedText) {
        currentCode += bit;
        //check if currentCode matches any code in reverseCodes
        if (reverseCodes.count(currentCode)) {
            decompressedText += reverseCodes[currentCode];
            //reset currentCode for next character
            currentCode.clear();
        }
    }
    return decompressedText;
}

