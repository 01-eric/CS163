#include <cstring>
#include <vector>
using namespace std;

int indexOf(char c, char* cstr, int occurrence) {
    int count = 0;
    for (int i = 0; i < strlen(cstr); i++) if (cstr[i] == c && ++count == occurrence) return i;
    return -1;
}

// similar syntax as substring in java
char* substr(char* cstr, int start, int end) {
    char* substr = new char[end - start + 1]; // +1 for null char
    for (int i = 0; i < end - start; i++) substr[i] = cstr[start + i]; // making copy char by char
    substr[end - start] = '\0'; // why do i have to do this
    return substr;
}

// splits cstr by a delim character and returns vector of all tokens
vector<char*>* split(char* cstr, char delim) {
    vector<char*>* tokens = new vector<char*>();
    int count = 0; // keep track of which token we are on
    do { // 0th occurence in indexOf returns -1 so we use do while
        int endIndex = indexOf(delim, cstr, count + 1) == -1 ? strlen(cstr) : indexOf(delim, cstr, count + 1); // exclusive; end before next space, end of string if -1
        int startIndex = indexOf(delim, cstr, count) + 1; // inclusive, start after current space
        if (startIndex != endIndex) tokens->push_back(substr(cstr, startIndex, endIndex)); // prevent empty string
    } while (indexOf(delim, cstr, ++count) != -1); // while there are more tokens
    return tokens;
}
