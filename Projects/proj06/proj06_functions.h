#ifndef PROJ06_STEGANOGRAPHY
#define PROJ06_STEGANOGRAPHY

#include<vector>
using std::vector;
#include<string>
using std::string;


vector<vector<int>> read_file(const string &fname);
vector<int> get_row(const vector<vector<int>> &v, int row);
vector<int> get_column(const vector<vector<int>> &v, int col);
string check_column_parity(const vector<vector<int>> &v, int col);
string check_row_parity(const vector<vector<int>> &v, int r);
int col_to_int(const vector<vector<int>> &v, size_t col);
string get_time(const vector<vector<int>> &v);
string get_date(const vector<vector<int>> &v);
string get_serial(const vector<vector<int>> &v);

// Good to have but not tested
int parity(int);
string print_vector(const vector<vector<int>> &v);
#endif
