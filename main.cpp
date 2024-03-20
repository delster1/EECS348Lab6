#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int get_matrix_dimension(){
  string line;
  ifstream myfile ("matrix_input.txt");
  int n = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      if (line.length() < 5) {
        n = stoi(line);
      }
    }
  }
  else {
    cout << "unable to open file";
  }
  return n;
}

std::vector< std::vector <int>> create_matrix(int matrix_size) {
  string line;
  std::vector< std::vector <int> > my_vec;
  ifstream myfile ("matrix_input.txt");
  int n;
  int count = 0;
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
        if (line.length() >= 5) {
            std::vector<int> row; // Create a new row for each line
            std::stringstream ss(line);
            int to_add;
            while (ss >> to_add) { // Read integers separated by spaces
                row.push_back(to_add); // Add integer to the row
            }
            my_vec.push_back(row); // Add row to the matrix
        }
    }
    myfile.close();
  } else {
    cout << "Unable to open file\n";
  }
  return my_vec;
}
void print_matrix(int matrix_size, std::vector<std::vector<int>> my_vec){
  for (int i = 0; i < matrix_size; i++){
    string my_string;

    for (int j = 0; j < matrix_size; j++) {
      my_string+= std::to_string(my_vec[i][j]) + " ";
    }
    cout << my_string << "\n"; 
  }
}
void add_two_matrices(int matrix_size, std::vector<std::vector<int>> matr1, std::vector<std::vector<int>> matr2) {
  std::vector< std::vector <int> > my_vec;

  for (int i = 0; i < matrix_size; i++){
    std::vector<int> row;
    for (int j = 0; j < matrix_size; j++) {
      row.push_back(matr1[i][j] + matr2[i][j]);
    }
    my_vec.push_back(row);
  }
  print_matrix(matrix_size, my_vec);
}
void subtract_two_matrices(int matrix_size, std::vector<std::vector<int>> matr1, std::vector<std::vector<int>> matr2) {
  std::vector< std::vector <int> > my_vec;

  for (int i = 0; i < matrix_size; i++){
    std::vector<int> row;
    for (int j = 0; j < matrix_size; j++) {
      row.push_back(matr1[i][j] - matr2[i][j]);
    }
    my_vec.push_back(row);
  }
  print_matrix(matrix_size, my_vec);
}
std::vector< std::vector <int>> update_matrix(int matrix_size, int row, int col,std::vector<std::vector<int>> to_edit, int new_value ){
  if ((row <= matrix_size && col <= matrix_size) && (row > 0 && col > 0)) {
    to_edit[row-1][col-1] = new_value;
  }
  return to_edit;
}
int find_max(int matrix_size, std::vector<std::vector<int>> search_matrix){
  int max = 0;
  for (int i = 0; i < matrix_size; i++){
    for (int j = 0; j < matrix_size; j++){
      if (search_matrix[i][j] >= max){
        max = search_matrix[i][j];
      }
    }
  }
  cout << max << "\n";
  return max;
}
std::vector< std::vector <int>> transpose_matrix(int matrix_size, std::vector<std::vector<int>> to_edit){
  std::vector< std::vector <int> > my_vec = to_edit;
  for (int i = 0; i < matrix_size; i++){
    for (int j = 0; j < matrix_size; j++){
      my_vec[i][j] = to_edit[j][i];
    }
    
  }

  return my_vec;
}


std::vector<std::vector<int>> multiply_matrices(int matrix_size, std::vector<std::vector<int>> matr1, std::vector<std::vector<int>> matr2){
  // TBD
  std::vector< std::vector <int> > my_vec = matr1;
  for (int i = 0; i < matrix_size; i++) {
    std::vector<int> row = matr1[i];
    for (int j = 0; j < matrix_size; j++) {
      // res = matr1 row obj 
      int sum = 0;
      int b;
      for (int k = 0; k < matrix_size; k++) {
        // matr2 col objs per iteration
        int a = matr1[i][k];

        b = matr2[k][j];
        cout << "\t" << a << " * " << b << "\n";
        sum += a * b;
      }
      cout << sum << "\n";
      my_vec[i][j] = sum;

    }
  }
  return my_vec;
}
int main () {
  // std::vector<int> my_vec = create_matrix();
  int matrix_size = get_matrix_dimension();
  std::vector<std::vector<int>> my_vec = create_matrix(matrix_size);
  print_matrix(matrix_size, my_vec);
  std::vector<std::vector<int>> updated_matrix = update_matrix(matrix_size, 1, 1, my_vec, 15);
  print_matrix(matrix_size, updated_matrix);
  int max = find_max(matrix_size, updated_matrix);
  std::vector<std::vector<int>> transposed = transpose_matrix(matrix_size, my_vec);
  print_matrix(matrix_size, transposed);
  std::vector<std::vector<int>> multiplied = multiply_matrices(matrix_size, my_vec, my_vec);
  print_matrix(matrix_size, multiplied);
  return 0;
}