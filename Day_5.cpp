#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


struct range
{
    long long min;
    long long max;
};



int read_file(const string& filename, vector<range>& ranges, vector<long long>& products){
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line) && line != "" ) { 
        //cout << line << endl;
        size_t dash_pos = line.find('-');

        range r = {stoll(line.substr(0, dash_pos)), stoll(line.substr(dash_pos +1))};
        ranges.push_back(r);

    }   

    //cout<< "Prdocuts: "<< endl;

    while (getline(file, line)) { 
        //cout << line << endl;
        products.push_back(stoll(line));
    }

    file.close(); 
    
    return 0;
}



void solution_part1(const vector<range> ranges,const vector<long long>& products){
    
    int count = 0;

    for (size_t i =0; i< products.size(); i++){
        long long product = products[i];
        bool valid = false; 

        for (size_t j=0; j< ranges.size(); j++){
            if (product >= ranges[j].min && product <= ranges[j].max){
                count++; 
                break; 
            }
        }
    }


    cout<< "the count of valid products is: " << count << endl;

}




void solution_part2(vector<range> ranges){
    long long total_valid_ids = 0;
 

    vector<range> unified_ranges;
    vector<size_t> to_erase; 

    for (size_t i =0; i< ranges.size(); i++){
        range current_range = ranges[i];
        bool merged = false;
        vector<size_t> to_erase; 

        for (size_t j=0; j< unified_ranges.size(); j++){
            if (!(current_range.max < unified_ranges[j].min || current_range.min > unified_ranges[j].max)){
                //they overlap
                current_range.min = min(unified_ranges[j].min, current_range.min);
                current_range.max = max(unified_ranges[j].max, current_range.max);
                to_erase.push_back(j);
                merged = true; 
            }
        }

        for (int k = to_erase.size()-1; k>=0; k--){
            unified_ranges.erase(unified_ranges.begin() + to_erase[k]);
        }

        unified_ranges.push_back(current_range);
        
    }


    for (size_t i =0; i< unified_ranges.size(); i++){
        total_valid_ids += (unified_ranges[i].max - unified_ranges[i].min +1);
    }


    cout<< "the total valid IDs is: " << total_valid_ids << endl;
    

}


int main() {

    vector<range> ranges; 
    vector<long long> products;
     
    if (read_file("Day_5_input.txt", ranges, products)){
        return 1;
    }

    solution_part1(ranges, products);   


    solution_part2(ranges);


    return 0;
}