#ifndef PROJ05_PLAYFAIR
#define PROJ05_PLAYFAIR

#include<string>
using std::string;
#include<cctype>

// playfair from
// http://practicalcryptography.com/ciphers/classical-era/playfair/

const string alphabet_minus_j = "abcdefghiklmnopqrstuvwxyz";
const int dim = 5;

string prepare_plaintext(const string &s);
string create_encoding(const string &key);
string encode_pair(const string &pr, const string &key);
string decode_pair(const string &pr, const string &key);
string encode(const string &plaintxt, const string &key);
string decode(const string &encodedtxt, const string &key);

#endif
