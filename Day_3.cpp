#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int read_file(const string& filename, vector<string>& battery_banks){
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) { 
        battery_banks.push_back(line); 
    }   

    file.close(); 
    
    return 0;
}


int main() {

    vector<string> battery_banks;
    int total_joltage = 0;  
    
     

    //if (read_file("Day_3_input_example.txt", battery_banks)){
    if (read_file("Day_3_input.txt", battery_banks)){
        return 1;
    }


    for (size_t i = 0; i< battery_banks.size(); i++){
        size_t index_tens = 0;
        size_t index_units = 0;
        int max_joltage = 0;
        for (size_t j = 0; j< battery_banks[i].size()-1; j++){
            int joltage = stoi(battery_banks[i].substr(j,1));
            if (joltage > max_joltage){
                max_joltage = joltage;
                index_tens = j; 
            }
            if (joltage == 9) break; 
        }         

        max_joltage = 0;
        for (size_t j = index_tens+1; j< battery_banks[i].size(); j++){
            int joltage = stoi(battery_banks[i].substr(j,1));
            if (joltage > max_joltage){
                max_joltage = joltage;
                index_units = j;
            }
            if (joltage == 9) break; 
        }

        
        int temp = stoi(battery_banks[i].substr(index_tens,1))*10 +stoi(battery_banks[i].substr(index_units,1));

        cout<< "battery bank "<< endl << battery_banks[i] << " -> max joltage digits: " << battery_banks[i].substr(index_tens,1) << " " << battery_banks[i].substr(index_units,1) << " -> max joltage: " << temp << endl;

        total_joltage += stoi(battery_banks[i].substr(index_tens,1))*10 +stoi(battery_banks[i].substr(index_units,1));

    }

    cout<< total_joltage ; 
}