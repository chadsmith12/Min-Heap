#ifndef HELPERS_H_
#define HELPERS_H_

#include <vector>
#include <string>

// SplitString - Splits a string based on a character delim into a vector of strings
// string - the string to split. Passed by const reference to avoid copying and modifying it
// delim - the character delim to split on
// Returns - vector<string> - all the strings/tokens that were found
std::vector<std::string> SplitString(const std::string& string, char delim);

// ToDouble - Converts a string into a double
// string - the string to convert to a double. Passed by const reference to avoid copying and modifying
double ToDouble(const std::string& string);

// ToInt - Converts a string into an integer
// string - the string to convert to a double. Passed by const reference to avoid copying and modifying
int ToInt(const std::string& string);

// BuildVector - Builds a vector from an input stream given
// vector - the vector to build. Passed by reference to modify it.
// stream - the inputstream to use
void BuildVector(std::vector<std::string>& vector, std::istream& stream);

#endif

