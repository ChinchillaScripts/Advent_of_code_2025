#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int read_file(const string& filename, vector<string>& start, vector<long long>& end){
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line);

    size_t pos = 0, comma_pos, dash_pos;
        
    while(pos < line.length()) {
        comma_pos = line.find(',', pos);
        dash_pos = line.find('-', pos);
        
        string s = line.substr(pos, dash_pos - pos);

        size_t temp = (comma_pos == string::npos ? line.length() : comma_pos) - dash_pos - 1;
        
        string p = line.substr(dash_pos + 1, (comma_pos == string::npos ? line.length() : comma_pos) - dash_pos - 1);

        long long e = stoll(p);
        
        start.push_back(s);
        end.push_back(e);
        
        if (comma_pos == string::npos) {
            break;
        }
        pos = comma_pos + 1;
    }

    file.close(); 
    
    return 0;
}


int main() {

    vector<string> start; 
    vector<long long> end;

    long long sum = 0; 


    if (read_file("Day_2_input.txt", start, end)){
        return 1;
    }


    for (size_t i = 0; i< start.size(); i++){
        cout<< start[i] << " " << end[i] << endl;

        size_t max_len = start[i].length()/2;
        if (max_len == 0) max_len = 1;

        string pattern = start[i].substr(0, max_len);

        long long base_num = stoll(pattern + pattern);

        long long min_num = stoll(start[i]);

        while(base_num < min_num){
            pattern = to_string(stoll(pattern) + 1);
            base_num = stoll(pattern + pattern);
        }


        while(base_num <= end[i]){
            sum +=  base_num;
            cout<< base_num << endl;
            pattern = to_string(stoll(pattern) + 1);
            base_num = stoll(pattern + pattern);
        }

    }

    cout << "The sum is: " << sum << endl;






    return 0;
}