
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <algorithm>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void writeToCppFile(std::ofstream& cppFile, const std::string& str){
    cppFile << "\n#include \"" << str << ".hpp\"\n\n";
    cppFile << str << "::" << str << "(){\n";
    cppFile << "}\n\n";
    cppFile << str << "::" << str << "(const " << str << "& other){\n";
    cppFile << "    // copiejjj member\n";
    cppFile << "}\n\n";
    cppFile << str << "::~" << str << "(){\n";
    cppFile << "}\n\n";
    cppFile << str << "& " << str << "::operator=(const " << str << "& other){\n";
    cppFile << "    if (this != &other) {\n";
    cppFile << "        // copie member\n";
    cppFile << "    }\n";
    cppFile << "    return *this;\n";
    cppFile << "}\n";
	std::cout << "✅ " <<GREEN << str << ".cpp complete success\n\n" << RESET;
}

void writeToHppFile(std::ofstream& hppFile, const std::string& str){
	std::string guardName = str;
    std::transform(guardName.begin(), guardName.end(), guardName.begin(), ::toupper);
	hppFile << "#ifndef " << guardName << "_HPP\n";
    hppFile << "#define " << guardName << "_HPP\n\n";
    hppFile << "class " << str << "{\n";
    hppFile << "\n	public:\n";
    hppFile << "		" << str << "();\n";
    hppFile << "    	" << str << "(const " << str << "& other);\n";
    hppFile << "    	~" << str << "();\n";
    hppFile << "		" << str << "& operator=(const " << str << "& other);\n";
    hppFile << "\n	private:\n";
    hppFile << "    	// membres privés\n";
    hppFile << "};\n\n";
    hppFile << "#endif\n";
	std::cout << "✅ " <<GREEN << str << ".hpp complete success\n" << RESET;

}


void	ArgToFile(const std::string& str){

	std::ofstream	cppFile((str + ".cpp"));
	if (!cppFile.is_open()){
		std::cerr << RED << "❌ " << str << ".cpp cannot create correctly" << RESET << std::endl;
		std::exit(1);
	}
	std::cout << "✅ " <<GREEN << str << ".cpp correctly create . . .\n" << RESET;
	writeToCppFile(cppFile, str);
	cppFile.close();

	std::ofstream	hppFile((str + ".hpp"));
	if (!hppFile.is_open()){
		std::cerr << RED << "❌ " << str << ".hpp cannot create correctly" << RESET << std::endl;
		std::exit(1);
	}
	std::cout << "✅ " <<GREEN << str << ".hpp correctly create !\n" << RESET;
	writeToHppFile(hppFile, str);
	hppFile.close();
}

int main(int argc, char **argv){
	if (argc == 1){
		std::cerr << RED << "❌ Enter one or more ClassName in argument\n❌ Usage: " << argv[0] << " ClassName ClassName1 ...\n" << RESET;
		return 1;
	}
	for (int i = 1; argv[i]; i++)
		ArgToFile(std::string (argv[i]));
	return 0;
}
