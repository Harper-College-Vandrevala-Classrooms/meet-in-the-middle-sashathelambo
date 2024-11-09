#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

unique_ptr<vector<int>> readNumbersFromCSV(const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return nullptr;
    }
    
    auto numbers = make_unique<vector<int>>();
    string line;
    size_t count = 0;
    if (getline(file, line)) {
        size_t start = 0;
        size_t end = line.find(',');
        
        while (end != string::npos) {
            numbers->push_back(stoi(line.substr(start, end - start)));
            count++;
            start = end + 1;
            end = line.find(',', start);
        }
        numbers->push_back(stoi(line.substr(start)));
        count++;
    }
    
    file.close();
    cout << "Number of data items read: " << count << endl;
    
    sort(numbers->begin(), numbers->end());
    return numbers;
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);
    
    try {
        auto numbersPtr = readNumbersFromCSV(filename);
        if (!numbersPtr) {
            return 1;
        }
        double median = findMedian(*numbersPtr);
        cout << "The median is: " << median << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
