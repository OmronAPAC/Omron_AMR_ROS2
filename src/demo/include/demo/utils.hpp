#include <string>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;


// Utility function to split string based on a delimiter
template <typename T>
void split(const basic_string<T>& s, T c, vector<basic_string<T>>& v) {
    auto i = 0;
    auto j = s.find(c);

    while (j != basic_string<T>::npos) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);

        if (j == basic_string<T>::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

// Utility function to extract macro name 
template<typename T>
basic_string<T> extract_macro_name(const basic_string<T>& s) {
    return s.substr(7);
}