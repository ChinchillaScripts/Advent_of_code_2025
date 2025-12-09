#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>


using namespace std;





int read_file(const string& filename, vector<string>& lab_map) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }


    lab_map.clear();


    string line;
    while (getline(file, line)) {
        lab_map.push_back(line);
    }
 

    file.close();

    return 0;
}


size_t find_start(vector<string>& lab_map) {
    return lab_map[0].find('S');
}


vector<size_t> find_spliters(string line) {
    vector<size_t> spliters;

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '^') spliters.push_back(i);
    }

    return spliters;
}


void update_lab_map(vector<string>& lab_map, size_t l, set<size_t> lazers) {
    for (size_t i: lazers) {
        lab_map[l][i] = '|';
    }
}



void update_lab_map(vector<string>& lab_map, size_t l, map<size_t, long long>lazers) {

    for (const auto & p : lazers) {
        lab_map[l][p.first] = '|';
    }

}


void print_lab_map(const vector<string> lab_map) {
    cout << endl;
    for (size_t i = 0; i < lab_map.size(); i++) {
        cout << lab_map[i] << endl;
    }
    cout << endl;
}


int main() {


    //Solution to part 1 
    /*
    vector<string> lab_map;
    int splits_count = 0; 

    if (read_file("Input.txt", lab_map)) {
        return 1;
    }
    set<size_t> lazers;
    vector<int> time_dimensions;

    lazers.insert(find_start(lab_map));
    time_dimensions.push_back(1);

    update_lab_map(lab_map, 1, lazers);

    for (size_t row = 2; row < lab_map.size(); row += 2) {
        set<size_t> new_lazers;
        vector<int> new_time_dimensions;
        for (size_t lazer : lazers) {
            if(lab_map[row][lazer] == '^') {
                splits_count++;
                new_lazers.insert(lazer - 1);
                new_lazers.insert(lazer + 1);
            }else {
                new_lazers.insert(lazer);
            }   
        }
        update_lab_map(lab_map, row, new_lazers);
        update_lab_map(lab_map, row + 1, new_lazers);
        lazers = new_lazers;

        //print_lab_map(lab_map);
          
    }

    print_lab_map(lab_map);



    cout << "the number of lazers is: " << lazers.size() << endl;
    cout << "the number of splits is: " << splits_count << endl;

    */

    
    vector<string> lab_map;
    int splits_count = 0;
    long long time_splits_count = 0;

    if (read_file("Input.txt", lab_map)) {
        return 1;
    }
    map<size_t,long long> lazers;
    

    lazers.insert({find_start(lab_map),1 });
    update_lab_map(lab_map, 1, lazers);

    for (size_t row = 2; row < lab_map.size(); row += 2) {
        map<size_t, long long> new_lazers;

        for (const auto& p : lazers) {
            if (lab_map[row][p.first] == '^') {
                splits_count++;
                auto result = new_lazers.insert({ p.first - 1, p.second });
                if (!result.second) {
                    new_lazers[p.first - 1] += p.second;
                }
                result = new_lazers.insert({ p.first + 1, p.second });
                if (!result.second) {
                    new_lazers[p.first + 1] += p.second;
                }
            }
            else {
                auto result = new_lazers.insert({ p.first, p.second });
                if (!result.second) {
                    new_lazers[p.first] += p.second;
                }
            }
        }
        update_lab_map(lab_map, row, new_lazers);
        update_lab_map(lab_map, row + 1, new_lazers);
        lazers = new_lazers;

        //print_lab_map(lab_map);


        //if (row == 10) break; 

    }

    print_lab_map(lab_map);

    for (const auto& p : lazers) {
        cout << "lazer " << p.first << " Count: " << p.second << endl; 


        time_splits_count += p.second; 
    }

    cout << "the number of lazers is: " << lazers.size() << endl;
    cout << "the number of used spliters is: " << splits_count << endl;
    cout << "the number of time splits is: " << time_splits_count << endl;




    return 0;
}