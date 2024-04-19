#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string runLengthEncode(const string& input) {
    string encoded;
    int count = 1;
    for (size_t i = 1; i <= input.size(); ++i) {
        if (i == input.size() || input[i] != input[i - 1]) {
            encoded += to_string(count) + input[i - 1];
            count = 1;
        } else {
            ++count;
        }
    }
    return encoded;
}

int main() {
    string filename = "gpu_output.txt"; // Specify the GPU output file name here
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return 1;
    }

    // Read content from the input file
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Close the input file
    inputFile.close();

    // Perform run-length encoding
    string encodedContent = runLengthEncode(content);

    // Write the encoded content to a file
    string outputFilename = "rle_output.txt";
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file " << outputFilename << endl;
        return 1;
    }
    outputFile << encodedContent;
    outputFile.close();
    cout << "Run-length encoded content written to " << outputFilename << endl;

    // Count characters before and after encoding
    size_t beforeEncoding = content.size();
    size_t afterEncoding = encodedContent.size();

    // Print the counts
    cout << "Number of characters before encoding: " << beforeEncoding << endl;
    cout << "Number of characters after encoding: " << afterEncoding << endl;

    return 0;
}
