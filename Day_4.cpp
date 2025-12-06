#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


vector<vector<int>> directions = {
       {0,1},  // Rigth 
       {1,0},  // Up
       {0,-1}, // Left
       {-1,0},  // Down
       { 1,1 }, // Up, Rigth
       {1,-1},  // Up, Left
       {-1,-1}, // Down Left
       {-1,1}  // Down Rigth
};

size_t max_row = 0; 
size_t max_column = 0;  



int read_file(const string& filename, vector<string>& map) {
    ifstream file(filename); // Open the file
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        map.push_back(line);
    }

    file.close();

    return 0;
}



bool valid_coordinate(size_t x, size_t max) {
    return x < max; 
}


int neighbors(size_t row, size_t column, vector<string>& map) {


    int neighbors_count = 0; 

    for (int i = 0; i < 8; i++) {

        size_t n_column = column + directions[i][0];
        size_t n_row = row + directions[i][1];


        if (valid_coordinate(n_column, max_column) && valid_coordinate(n_row, max_row)) {
            neighbors_count += map[n_row][n_column] == '@';
        }


    }

    return neighbors_count;
};



int main() {

    vector<string> map;


    if (read_file("Day4_input.txt", map)) {
        return 1;
    }


    max_row = map.size();
    max_column = map[0].size();


   
    int count = 0;
    int old_count = -1;

    for (size_t row = 0; row < max_row; row++) {
        cout << map[row] << endl; 
    }

   



    while (old_count != count) {
        old_count = count; 
        for (size_t row = 0; row < max_row; row++) {

            for (size_t column = 0; column < max_column; column++) {

                if (map[row][column] == '@') {
                    if (neighbors(row, column, map) < 4) {
                        map[row][column] = '.';
                        count++;
                    }
                }

            }


        }

        //cout << count << endl; 

    }


    cout << "The number of valid positions is: " << count << endl;



    for (size_t row = 0; row < max_row; row++) {
        cout << map[row] << endl;
    }



    return 0; 
}