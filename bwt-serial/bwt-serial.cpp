#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Global variable to count comparisons
int comparisonCount = 0;

// Custom comparison function to count comparisons
bool compareChars(const char& a, const char& b) {
    comparisonCount++;
    return a < b; 
}

// Function to perform Burrows-Wheeler Transform
string burrowsWheelerTransform(const string& input) {
    int n = input.size();
    vector<int> rotationIndices(n);

    // Initialize rotation indices
    for (int i = 0; i < n; ++i) {
        rotationIndices[i] = i;
    }

    // Sort rotation indices based on rotations
    sort(rotationIndices.begin(), rotationIndices.end(), [&](int a, int b) {
        for (int i = 0; i < n; ++i) {
            char charA = input[(a + i) % n];
            char charB = input[(b + i) % n];
            if (charA != charB) {
                return compareChars(charA, charB);
            }
        }
        return false; // Should not reach here
    });

    // Construct transformed string
    string transformedString;
    for (int i = 0; i < n; ++i) {
        int index = rotationIndices[i];
        transformedString += input[(index + n - 1) % n]; // Last character of rotation
    }

    return transformedString;
}

int main() {
    string filename="text.txt";

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    string input;
    getline(inFile, input);

    // Reset comparisonCount
    comparisonCount = 0;

    string transformed = burrowsWheelerTransform(input);

    // Print the transformed string
    cout << "Transformed string: " << transformed << endl;

    // Print the number of comparisons made during sorting
    cout << "Number of comparisons: " << comparisonCount << endl;

    return 0;
}

