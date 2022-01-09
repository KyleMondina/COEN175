#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

//function to handle simple C keywords
static int isKeyword(std::string s){

	std::unordered_set<std::string> keywords = {
		"auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
		"else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
		"return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
		"unsigned", "void", "volatile", "while"
	};

	if (keywords.find(s) != keywords.end()){
		//is a keyword
		return 1;
	}
	else {
		//is not a keyword
		return 0;
	}

}

static int isWhiteSpace(char character){
	switch(character){
		case ' ':
		case '\t':
		case '\n':
		case '\f':
		case '\v':
		case '\r':
			return 1;
		default:
			return 0;
	}
}

static int isSingleOperator(char c){
	
	std::unordered_set<char> singleOperators = {
		'*',
		'/',
		'%',
		'.',
		'(',
		')',
		'[',
		']',
		'{',
		'}',
		';',
		':',
		','
	};

	if (singleOperators.find(c)!=singleOperators.end()){
		return 1;
	}else{
		return 0;
	}
}

static int isDoubleOperator(std::string s){






int main(){

	std::string cookie = "while";

	int check = isKeyword(cookie);
	if (check ==1){
		std::cout << "iskeyword";
	}else{
		std::cout << "noope";
	}
}
