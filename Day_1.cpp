#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int read_file(const string& filename, vector<char>& directions, vector<int>& increment){
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) { 
        char dir = line[0]; 
        int inc = stoi(line.substr(1)); 
        
        directions.push_back(dir); 
        increment.push_back(inc);  
    }   

    file.close(); 
    
    return 0;
}


int main() {

    vector<char> directions; 
    vector<int> increment;
    int new_pos = 50; 
    int count = 0;
    int old_pos = new_pos; 

    if (read_file("Day_1_input.txt", directions, increment)){
        return 1;
    }


    for (size_t i = 0; i< directions.size(); i++){
        /*Solution part 1
        int b = increment[i] * (directions[i]=='L'? -1:1);
        
        start = (start + 100 + b%100) % 100; 
        
        if (start == 0) count ++; 
        */
        
        int b = increment[i] * (directions[i]=='L'? -1:1);
        
        new_pos = (old_pos + b);

        
        if(new_pos*old_pos <0) count++; 
        if(new_pos > 99 ) count += new_pos/100;
        if(new_pos < 0 ) count -= new_pos/100;
        if(new_pos == 0) count++;


        new_pos = (old_pos + 100 + b%100) % 100;
        old_pos = new_pos; 

    }

    cout<< count ; 
}