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

	while (!(std::cin.eof())){

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

		//3.) Strings
		if(input=='"'){
			//start of a string
			do{
				lexbuff += input;
				std::cin.get();
				input = std::cin.peek();

				//handle backslash escaping
				if(input == '\\'){
					lexbuff+=input;
					std::cin.get();
					lexbuff+=std::cin.peek();
					std::cin.get();
					input = std::cin.peek();
				}

			}while(input!='"');
			//handle the next "
			lexbuff += input;
			std::cin.get();
			return STRING;
		}

		//4.) Handle Characters: Exact same logic with strings
		if(input=='\''){
			//start of the chracter
			do{
				lexbuff += input;
				std::cin.get();
				input = std::cin.peek();

				//handle backslashing escaping
				if(input == '\\'){
					lexbuff+=input;
					std::cin.get();
					lexbuff+=std::cin.peek();
					std::cin.get();
					input = std::cin.peek();
				}
			}while(input!='\'');
			//handle the next '
			lexbuff+=input;
			std::cin.get();
			return CHARACTER;
		}


		//5.) Handle identifiers and keywords
		//First Case: When they start with _
		
		if(input == '_'){
			do {
				lexbuff+=input;
				std::cin.get();
				input = std::cin.peek();
			}while( std::isalpha(input) || std::isdigit(input) || input == '_');
			return IDENTIFIER;
		}

		//Second case: when they could potentially be keywords
		
		if(std::isalpha(input)){
			do{
				lexbuff+=input;
				std::cin.get();
				input = std::cin.peek();
			}while(input == '_' || std::isalpha(input) || std::isdigit(input));
			
			if(isKeyword(lexbuff)){
				return KEYWORD;
			}else{
				return IDENTIFIER;
			}
		}
		
		//6.) Handle Comments
		
		if (input == '/'){
			std::cin.get();
			input = std::cin.peek();
			
			if(input == '*'){
				do {
					//process the contents
					std::cin.get();
					input = std::cin.peek();
PROCESS: /*wow i hate c++ took me a while to figure this out*/ ;

				}while(input != '*');
				//process the star
				std::cin.get();
				input = std::cin.peek();
				if(input != '/'){
					goto PROCESS;
				}
				//finish processing the comment
				std::cin.get();
				input = std::cin.peek();
			}else{
				std::cin.putback('/');
				input = '/';
			}

		}


		
	}
	return DONE;
}




int main(){
	int token;
	std::string lexbuff, type;
	//NUMBER,STRING,CHARACTER,IDENTIFIER,KEYWORD,OPERATOR,DONE,

	while ((token = lexan(lexbuff))!=DONE){
		switch(token){
			case NUMBER:
				type = "number";
				break;
			case STRING:
				type = "string";
				break;
			case CHARACTER:
				type = "character";
				break;
			case IDENTIFIER:
				type = "identifier";
				break;
			case KEYWORD:
				type = "keyword";
				break;

		}	
		std::cout << type << " : " << lexbuff << std::endl;
	}
	std::cout << "hello is this program even working?" << std::endl;
	return 0;


}

