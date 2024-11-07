#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string filename = "";
    cout << "Enter the filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    int* numbers = nullptr;
    int capacity = 10;
    int size = 0;
    numbers = new int[capacity];
    
    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string value = "";
        
        while (getline(ss, value, ',')) {
            if (size == capacity) {
                int* temp = new int[capacity * 2];
                for (int i = 0; i < size; i++) {
                    temp[i] = numbers[i];
                }
                delete[] numbers;
                numbers = temp;
                capacity *= 2;
            }
            numbers[size++] = stoi(value);
        }
    }

    file.close();

    if (size == 0) {
        cout << "No data found in file" << endl;
        delete[] numbers;
        return 1;
    }

    double median = 0.0;
    if (size % 2 == 0) {
        median = (numbers[size/2 - 1] + numbers[size/2]) / 2.0;
    } else {
        median = numbers[size/2];
    }

    cout << "The median is: " << median << endl;

    delete[] numbers;
    return 0;
}
