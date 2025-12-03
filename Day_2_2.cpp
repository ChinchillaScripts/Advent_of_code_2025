#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

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


long long create_pattern(int repetitions, const string& pattern){
    string full_sn = "";
    for (int i = 0; i < repetitions; i++){
        full_sn += pattern;
    }
    return stoll(full_sn);
}


void invalid_sn(long long min, long long max, size_t pattern_len, size_t min_pattern_len, size_t max_pattern_len, set<long long>& invalid_sns){
      //to_string(min).substr(0, pattern_len);
      //to_string(create_pattern(pattern_len,"1"))""
    int repetitions = min_pattern_len / pattern_len;
    if (repetitions == 1) repetitions = 2;
    
    while(repetitions * pattern_len <= max_pattern_len){

        string pattern = "1";

        for (int j = 0; j < pattern_len -1; j++){
            pattern += "0";
        }
        
        long long base_num = create_pattern(repetitions, pattern);

        while(base_num < min){
            pattern = to_string(stoll(pattern) + 1);
            base_num = create_pattern(repetitions, pattern);
        }

        while(base_num <= max){
            invalid_sns.insert(base_num);
            //cout<< base_num << endl;
            pattern = to_string(stoll(pattern) + 1);
            base_num = create_pattern(repetitions, pattern);
        }

        repetitions += 1;         
    }
 
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

        size_t max_len = to_string(end[i]).length()/2;
        if (max_len == 0) max_len = 1;
        set<long long> invalid_sns;

        for(size_t pattern_len = 1; pattern_len <= max_len; pattern_len++){
            invalid_sn(stoll(start[i]), end[i], pattern_len, start[i].length(), to_string(end[i]).length(),invalid_sns);
        }

        for (const auto& sn : invalid_sns){
            cout<< "Invalid SN: " << sn << endl;
            sum += sn;
        }

    }

    cout << "The sum is: " << sum << endl;




    return 0;
}