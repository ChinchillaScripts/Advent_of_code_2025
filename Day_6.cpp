#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;





int read_file(const string& filename, vector<vector<int>>& data, vector<char>& operations) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    for (int i=0; i<4; i++) {
        getline(file, line);
        size_t start = 0;
        vector<int> temp; 
        for (size_t pos = 0; pos < line.length(); pos++) {

            if (line[pos] == ' ') {

                if (line[start] != ' ') {
                    temp.push_back(stoi(line.substr(start, pos - start)));
                    start = pos;
                }
            }

            if (line[start] == ' ') {
                start++;
            }

        }
        data.push_back(temp);

    }

    getline(file, line);
    for (size_t pos = 0; pos < line.length(); pos++) {
        if (line[pos] != ' ') operations.push_back(line[pos]);
    }


    file.close();

    return 0;
}



int read_file_2(const string& filename, vector<vector<int>>& data, vector<char>& operations) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }


    vector<string> lines; 
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
        
    }

    line = lines.back();
  
    vector<int> temp; 
    for (size_t pos = lines[0].length() - 1; pos < lines[0].length(); pos--) {

        int multiplier = 1; 
        int number = 0;

        for (size_t i = lines.size()-2; i< lines.size(); i--) {
            int digit = 0; 
            if (lines[i][pos] != ' ') {
                digit = stoi(lines[i].substr(pos,1));
                number += digit * multiplier;
                multiplier *= 10;
            }
        }


        if (number != 0) { temp.push_back(number); }

        if (line[pos] != ' ') {
            operations.push_back(line[pos]);
            data.push_back(temp);
            temp.clear();
        }

    }

    file.close();

    return 0;
}




int main() {

    vector<vector<int>> data;
    vector<char> operations;


    if (read_file_2("Input.txt", data, operations)) {
        return 1;
    }


    long long result = 0; 

    for (size_t j = 0; j < operations.size(); j++) {
        long long column_res = 0;
        if (operations[j] == '+') {
            for (size_t i = 0; i < data[j].size(); i++) {
                column_res += data[j][i];
            }
        }

        if (operations[j] == '*') {
            column_res = 1;
            for (size_t i = 0; i < data[j].size(); i++) {
                column_res *= data[j][i];
            }
        }
        cout << "The result of column " << j << " is :" << column_res << endl; 
        result += column_res;

    }



    cout << "overall result is: " << result << endl; 


    return 0;
}