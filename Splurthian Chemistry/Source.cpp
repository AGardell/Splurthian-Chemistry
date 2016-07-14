/*Taken from Reddit DailyProgrammer Challenge #275:
"The Splurth Council of Atoms and Atom-Related Paraphernalia has decided to keep their current naming conventions, 
as listed in the Easy challenge, but to add a preference system. So while there are still 6 valid symbols for 
the element Iron, the preferred symbol is Ir. The second-most preferred symbol is Io, then In, Ro, Rn, and finally On.
A symbol is preferred based on how early in the element name its first letter is, followed by how early its second 
letter is. In the case of repeated letters like in Neon, Eo is preferred to En, even though an n is closer 
to the beginning of Neon than the o is. This is because it's the second n that's used in the symbol En, 
since the second letter in the symbol must appear after the first. When the Council receives a new element to 
add to the table, it chooses the most preferred valid symbol for that element that's not already taken by another 
element. For instance, if Chlorine were the first element added, then it would get the symbol Ch. 
If Chromium was added later, it would get the symbol Cr. If Cesium and Cerium were then added, they would get the 
symbols Ce and Ci. If there are no valid symbols for the new element.... well, that's why the Council needs you."
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <iterator>

std::multimap <std::string, std::string> elements;

std::string findSymbol(std::string& str) {
	std::string symbol;
	//loop through the string pulling the character at i and the following character to create a symbol.
	for (int i = 0; i < str.length(); ++i) {
		symbol.push_back(str[i]), symbol.push_back(str[i + 1]);
		//if symbol already exists clear the variable and keep looping. Otherwise return the found symbol.
		if (elements.find(symbol) != elements.end()) {
			symbol = "";
		}
		else {
			return symbol;
		}
	}

	if (str.empty()) { //if string is empty return the empty symbol.
		return symbol;
	}
	else { //Otherwise recursivley try finding the symbol again with a shortened string.
		return findSymbol(str.substr(1)); 
	}
}

void process(std::string& str) {
	std::string symbol;

	if (elements.empty()) { //if the elements table is empty just put in the first symbol, element combination.
		symbol = str.substr(0, 2);
		elements.insert({ symbol, str });
	}
	else if (str[0] == toupper(str.back())) { 
		//if the first and last character match. Remove the first character and begin finding the symbol.
		symbol = findSymbol(str.substr(1));
		if (symbol != "") { //push back the symbol, element combination or push back NULL if no symbol could be created.
			elements.insert({ symbol, str });
		}
		else {
			elements.insert({ "NULL!!!!!!!!!!!!!!!!!!!!!!!!!!", str });
		}
	}
	else {
		symbol = findSymbol(str);
		if (symbol != "") {
			elements.insert({ symbol, str });
		}
		else {
			elements.insert({ "NULL!!!!!!!!!!!!!!!!!!!!!!!!!!", str });
		}
	}
}

void printTable() {
	for (auto it : elements) { //range based loop to print contents of the map with some conditional formatting.
		std::cout << std::setw(20) << std::left << it.second << std::setw(15) << std::right << " ->  " << it.first << std::endl;
	}
}

int main() {
	// Create input stream to capture the list of elements from the provided text file.
	std::string str;
	std::ifstream input;
	input.open("Text.txt");

	while (!input.eof()) { //while we're able to pull lines, process them and create the symbol.
		std::getline(input, str);
		process(str);
	}

	printTable();

	return 1;
}