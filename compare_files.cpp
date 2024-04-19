#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool compareFiles(const string& filename1, const string& filename2) {
    ifstream file1(filename1), file2(filename2);
    if (!file1.is_open() || !file2.is_open()) {
        cerr << "Error opening files." << endl;
        return false;
    }

    string content1((istreambuf_iterator<char>(file1)), (istreambuf_iterator<char>()));
    string content2((istreambuf_iterator<char>(file2)), (istreambuf_iterator<char>()));

    file1.close();
    file2.close();

    return content1 == content2;
}

int main() {
    string gpuFilename = "gpu_output.txt";
    string decodeFilename = "rle_decode_output.txt";

    if (compareFiles(gpuFilename, decodeFilename)) {
        cout << "Files are the same." << endl;
    } else {
        cout << "Files are different." << endl;
    }

    return 0;
}
