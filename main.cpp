#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

double findMedian(const vector<int>& numbers) {
    size_t size = numbers.size();
    if (size == 0) {
        throw runtime_error("Empty dataset");
    }
    
    if (size % 2 != 0) {
        return static_cast<double>(numbers[size / 2]);
    }
    
    return (static_cast<double>(numbers[(size - 1) / 2]) + 
            static_cast<double>(numbers[size / 2])) / 2.0;
}

vector<int> readNumbersFromCSV(const string& filename) {
    ifstream file(filename);
    auto numbers = make_unique<vector<int>>();
    
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }
    
    string line;
    if (getline(file, line)) {
        size_t start = 0;
        size_t end = line.find(',');
        
        while (end != string::npos) {
            numbers->push_back(stoi(line.substr(start, end - start)));
            start = end + 1;
            end = line.find(',', start);
        }
        numbers->push_back(stoi(line.substr(start)));
    }
    
    file.close();
    return *numbers;
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);
    
    try {
        auto numbers = make_unique<vector<int>>(readNumbersFromCSV(filename));
        double median = findMedian(*numbers);
        cout << "The median is: " << median << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
