#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

//function to handle simple C keywords

enum {
	NUMBER,STRING,CHARACTER,IDENTIFIER,KEYWORD,OPERATOR,DONE,
};

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
	std::unordered_set<std::string> doubleOperators = {
		"||",
		"&&",
		"==",
		"!=",
		"<=",
		">=",
		"++",
		"--",
		"->"
	};

	if (doubleOperators.find(s)!=doubleOperators.end()){
		return 1;
	}else{
		return 0;
	}
}

static int isPotentialDoubleOperator(char c){
	std::unordered_set<char> potentialDouble = {
		'<',
		'>',
		'!',
		'&',
		'=',
		'+',
		'-',
		'|'

	};
	if (potentialDouble.find(c) != potentialDouble.end()){
		return 1;
	}else{
		return 0;
	}
}

static int lexan(std::string& lexbuff){

	char input = std::cin.peek();

	//for dealing with operators
	char xbuff;
	char ybuff;
	std::string opbuff;

	while (!std::cin.eof()){

		lexbuff.clear();

		//1.) White Space
		if(isWhiteSpace(input)){
			do{
				std::cin.get();
				input = std::cin.peek();
			}while(isWhiteSpace(input));
		}

		//2.) Integers
		if(std::isdigit(input)){
			do{
				lexbuff += input;
				std::cin.get();
				input = std::cin.peek();
			}
			while(isdigit(input));
			return NUMBER;
		}

		
	}
	return DONE;
}















int main(){


}

