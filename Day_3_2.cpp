#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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





int find_max_joltage(const string& battery_bank, size_t digits_left, size_t& index){
    int max_joltage = -1;
    int size_bat = battery_bank.size();

    for (size_t j = index; j< battery_bank.size()-digits_left + 1; j++){
        int joltage = stoi(battery_bank.substr(j,1));
        if (joltage > max_joltage){
            max_joltage = joltage;
            index = j; 
        }
        if (joltage == 9) break; 
    }      
    return max_joltage;  
}






int main() {

    vector<string> battery_banks;
    long long total_joltage = 0;  
    
     

    //if (read_file("Day_3_input_example.txt", battery_banks)){
    if (read_file("Day_3_input.txt", battery_banks)){
        return 1;
    }


    for (size_t i = 0; i< battery_banks.size(); i++){
        size_t current_index = 0;
        long long joltage = 0;
        for (int digits = 12; digits>0; digits--){
            joltage += find_max_joltage(battery_banks[i], digits, current_index) * pow(10, digits-1);
            current_index ++;
        }
        //cout<< joltage << endl;
        total_joltage += joltage;    
    }
    cout<< "Day 3 part 2:"<< endl;
    cout<< "The answer is:"<< total_joltage ; 

    return 0;
}