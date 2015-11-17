#include <sstream>

#include "Helpers.h"

// Split a string into a vector on the char delim
std::vector<std::string> SplitString(const std::string& string, char delim)
{
	std::istringstream stream(string);
	std::string tempLine;
	std::vector<std::string> tokens;

	while (std::getline(stream, tempLine, delim))
	{
		if (!tempLine.empty())
		{
			tokens.push_back(tempLine);
		}
	}

	return tokens;
}

// convert a number string to an integer
int ToInt(const std::string& string)
{
	std::stringstream stream(string);
	int returnInt;

	stream >> returnInt;
	return returnInt;
}

// builds a vector from an input stream
void BuildVector(std::vector<std::string>& vector, std::istream& stream)
{
	std::string line;

	while(std::getline(stream, line))
	{
		vector.push_back(line);
	}
}