
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <algorithm>
#include <filesystem>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

std::string generateHeader(const std::string& filename) {
    std::string header;

    header += "╔═════════════════════════════════════════════╗\n";
    header += "	Class: " + filename+ "\n";
    header += "╚═════════════════════════════════════════════╝\n\n";

    return header;
}

void moveFile(const std::string& fileName, const std::string& fileName2, const std::string& destination) {
    std::string command = "mv " + fileName + " " + fileName2 + " " + destination;
    int result = std::system(command.c_str());
    if (result != 0)
        std::cerr << RED << "❌ Error moving " << fileName << " && "<< fileName2 << " to " << destination << "\n\n" << RESET;
    else
        std::cout << GREEN << "✅ File successfully moved from " << fileName << " && "<< fileName2 << " to " << destination << "\n\n" <<RESET;
}

void writeToCppFile(std::ofstream& cppFile, const std::string& str){
    cppFile << "#include \"" << str << ".hpp\"\n\n";
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
	std::cout << "✅ " <<GREEN << str << ".cpp complete success\n" << RESET;
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


void	ArgToFile(const std::string& str, const std::string& destination){

	std::cout << YELLOW << generateHeader(str) << RESET;
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
		cppFile.close();
		std::exit(1);
	}
	std::cout << "✅ " <<GREEN << str << ".hpp correctly create . . .\n" << RESET;
	writeToHppFile(hppFile, str);
	hppFile.close();

	if (std::filesystem::current_path() != destination)
    	moveFile((str + ".cpp"), (str + ".hpp"), destination);
}

int main(int argc, char **argv){
	if (argc < 3){
		std::cerr << RED << "❌ Enter one or more ClassName in argument\n❌ Usage: " << argv[0] << " /path ClassName ClassName1 ...\n" << RESET;
		return 1;
	}
	std::string destination = argv[1];
	if (destination.empty() || destination == "." || destination == "./") {
        destination = std::filesystem::current_path();
    }
	if (!std::filesystem::exists(destination) || !std::filesystem::is_directory(destination)) {
		std::cerr << RED << "❌ " << destination << " doesn't exist. Do you want to create it?\n(yes/no): " << RESET << std::endl;
		std::string userResponse;
		std::getline(std::cin, userResponse);
		if (userResponse == "yes"){
			if (std::filesystem::create_directory(destination))
				std::cout << GREEN << "✅ Directory created successfully." << RESET << std::endl;
			else{
				std::cerr << RED << "❌ Failed to create directory." << RESET << std::endl;
				return 1;
			}
    	}
		else
			return 1;
	}
	for (int i = 2; argv[i]; i++)
		ArgToFile(std::string (argv[i]), destination);
	return 0;
}
