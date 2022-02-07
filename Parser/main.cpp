#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <memory>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std; 

enum tokenType {
	LEFT_PAREN,RIGHT_PAREN,
	ID,STRLIT,
	DOT,
	ERROR,
	KNOWNYET
};

struct token {
	string lexeme;
	tokenType type;
} ;

string nextL;
string NextG = "\0";
bool lambda = false;
vector <token> TokList;
token stayTok;

bool getLexeme() {
	string stayL = "\0";
	string tok = "\0";
	char stay1 = '\0';
	int i = 0, GLen = 0, lPNum = 0;  
	stay1 = cin.peek();
	
	if ( NextG != "\0" ) {
		NextG = "\0";
	} // if
	
	while ( stay1 == '\n' ) {
		scanf( "%c", & stay1 );
		stay1 = cin.peek();
		return false;
	} // while
	
	while ( stay1 != EOF && stay1 != '\n' ) {		
		if ( stay1 == '(' || stay1 == ')' || stay1 == '\"' || stay1 =='.' ) {
			stay1 = '\n';
		} // if
		else {
			scanf( "%c", & stay1 );
			NextG = NextG + stay1;
			stay1 = cin.peek();
		} // else
	} // while
	
	while ( NextG[0] == ' ' || NextG[0] == '\t' || NextG[0] == '\n' ) {
		if ( NextG[0] == ' ' || NextG[0] == '\t' || NextG[0] == '\n' ) {
			NextG.erase( 0, 1 );
		} // if 
	} // while
	
	stay1 = cin.peek();
	if ( stay1 == '(' || stay1 == ')' || stay1 == '\"' || stay1 =='.' ) {
		if ( NextG == "\0" ) {
			scanf( "%c", & stay1 );
			NextG = NextG + stay1;
			stay1 = cin.peek();
		} // if
	} // if
	
	if ( stay1 == EOF ) { 
		return true;
	} // if
	else {
		return false;
	} // else
} // getLexeme ()
	
void whatToken() {
	char stay2 = '\0';
	bool isID = false;
	string stayL = "\0";
	token nT;
	int i = 1, GLen = NextG.size(), lPNum = 0;
	
	stayTok.lexeme = "\0";
	stayTok.type = KNOWNYET;
	
	if ( NextG == "(" ) {
		stayTok.lexeme = NextG;
		stayTok.type = LEFT_PAREN;
	} // if
	else if ( NextG == ")" ) {
		stayTok.lexeme = NextG;
		stayTok.type = RIGHT_PAREN;
	} // else if 
	else if ( NextG == "\"" ) {
		stay2 = cin.peek();
		while ( stay2 != EOF && stay2 != '\n' && stay2 != '\"' ) {
			scanf( "%c", & stay2 );
			NextG = NextG + stay2;
			stay2 = cin.peek();
		} // while
		
		if ( stay2 == '\"' ) {
			scanf( "%c", & stay2 );
			NextG = NextG + stay2;
			stayTok.lexeme = NextG;
			stayTok.type = STRLIT;
		} // if
		else {
			stayTok.lexeme = NextG;
			stayTok.type = ERROR;
		} // else
		
	} // else if
	else if ( NextG == "." ) {
		stayTok.lexeme = NextG;
		stayTok.type = DOT;
	} // else if
	else if ( NextG == "\0" ) {
		
	} // else if
	else { // 剩ID
		stay2 = NextG[0]; // 確定開頭符合規矩 
		
		if ( stay2 >= 'A' && stay2 <= 'Z' ) {
			while ( i < GLen ) {
				stay2 = NextG[i];
				if ( stay2 >= 'A' && stay2 <= 'Z' ) {
					isID = true;
				} // if
				else if ( stay2 >= 'a' && stay2 <= 'z' ) {
					isID = true;
				} // else if
				else if ( stay2 >= '0' && stay2 <= '9' ) {
					isID = true;
				} // else
				else if ( stay2 == '_' ) {
					isID = true;
				} // else
				else {
					isID = false;
					i = GLen;
				} // else
				
				i++;
			} // while
		} // if
		else if ( stay2 >= 'a' && stay2 <= 'z' ) {
			while ( i < GLen ) {
				stay2 = NextG[i];
				if ( stay2 >= 'A' && stay2 <= 'Z' ) {
					isID = true;
				} // if
				else if ( stay2 >= 'a' && stay2 <= 'z' ) {
					isID = true;
				} // else if
				else if ( stay2 >= '0' && stay2 <= '9' ) {
					isID = true;
				} // else
				else if ( stay2 == '_' ) {
					isID = true;
				} // else
				else {
					i = GLen;
					isID = false;
				} // else
				
				i++;
			} // while
		} // else if
		else if ( stay2 == '_' ) {
			while ( i < GLen ) {
				stay2 = NextG[i];
				if ( stay2 >= 'A' && stay2 <= 'Z' ) {
					isID = true;
				} // if
				else if ( stay2 >= 'a' && stay2 <= 'z' ) {
					isID = true;
				} // else if
				else if ( stay2 >= '0' && stay2 <= '9' ) {
					isID = true;
				} // else
				else if ( stay2 == '_' ) {
					isID = true;
				} // else
				else {
					i = GLen ;
					isID = false;
				} // else
				
				i++;
			} // while
		} // else
		else {
			isID = false;
		} // else
		
		if ( isID ) {
			stayTok.lexeme = NextG;
			stayTok.type = ID;
		} // if
		else {
			stayTok.lexeme = NextG;
			stayTok.type = ERROR;
		} // else
		
	} // else if
			
} // whatToken()

bool stmt();

bool primary_tail() {
	char next = '\0';
	
	if ( lambda ) {
		return true;
	} // if
	else if ( stayTok.type == DOT ) {
		TokList.push_back(stayTok);
		next = cin.peek();
		
		if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
			lambda = true;
		} // if
		
		getLexeme();
		whatToken();
		
		if ( stayTok.type == ID ) {
			TokList.push_back(stayTok);
			next = cin.peek();
			
			if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
				lambda = true;
			} // if
		
			getLexeme();
			whatToken();
			
			if ( primary_tail() ) {
				return true;
			} // if
			else {
				return false;
			} // else
		} // if
		else {
			return false;
		} // else
	} // else if
	else if ( stayTok.type == LEFT_PAREN ){
		TokList.push_back(stayTok);
		next = cin.peek();
		
		if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
			lambda = true;
		} // if
		
		getLexeme();
		whatToken();
		
		if ( stmt() ) {
			if ( stayTok.type == RIGHT_PAREN ) {
				TokList.push_back(stayTok);
				next = cin.peek();
		
				if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
					lambda = true;
				} // if
				
				getLexeme();
				whatToken();
				
				if ( primary_tail() ) 
					return true;
				else
					return false;
			} // if
			else
				return false;
		} // if
		else if ( stayTok.type == RIGHT_PAREN ) {
			TokList.push_back(stayTok);
			next = cin.peek();
		
			if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
				lambda = true;
			} // if
	
			getLexeme();
			whatToken();
				
			if ( primary_tail() ) 
				return true;
			else
				return false;
		} // else if
		else 
			return false;
	} // else if
	else {
		return false;
	} // else
} // primary_tail() 

bool primary() {
	char next = '\0';
	
	if ( stayTok.type == ID ) {
		TokList.push_back(stayTok);
		next = cin.peek();
		
		if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
			lambda = true;
		} // if
		
		getLexeme();
		whatToken();
		
		if ( primary_tail() ) {
			return true;
		} // if
	} // if
	else {
		return false;
	} // else
} // primary()

bool stmt() {
	char next = '\0';
	if ( lambda ) {
		return true;
	} // if
	else if ( primary() ) {
		return true;
	} // else if 
	else if ( stayTok.type == STRLIT ) {
		TokList.push_back(stayTok);
		next = cin.peek();
		
		if ( next == ' ' || next == '\t' || next == '\0' || next == '\n' || next == EOF ) {
			lambda = true;
		} // if
		
		getLexeme();
		whatToken();
		return true;
	}  // else
	else {
		return false;
	} // else
} // stmt

bool stmts() {
	if ( lambda ) {
		return true;
	} // if
	else if ( stmt() ) {
  		if ( stmts() ) 
  			return true;
		else 
			return false;
	} // else if 
	else {
		return false;
	} // else
} // Program()

bool program() {
	if ( stmts() ) {
		return true;
	} // if
	else {
		return false;
	} // else
} // Program()

void parserPrint () {
	int i = 0 , GLen = TokList.size();
	
	while ( i < GLen ) {
		if ( TokList[i].type == LEFT_PAREN ) {
			cout << "LBR " << TokList[i].lexeme << "\n";
		} // if
		else if ( TokList[i].type == RIGHT_PAREN ) {
			cout << "PBR " << TokList[i].lexeme << "\n";;
		} // else if 
		else if ( TokList[i].type == ID ) {
			cout << "ID "<< TokList[i].lexeme << "\n";
		} // else if
		else if ( TokList[i].type == STRLIT ) {
			cout << "STRLIT "<< TokList[i].lexeme << "\n";
		} // else if
		else if ( TokList[i].type == DOT ) {
			cout << "DOT "<< TokList[i].lexeme << "\n";
		} // else if
		else if ( TokList[i].type == KNOWNYET ) { // do nothing 
		} // else if
		else { // 剩 ERROR 
			cout << "invalid input\n";
		} // else if
		
		i++;
	} // while
	
} // parserPrint()

int main() {
	
	char getIn = '\0';
	bool toStop = false;
	
	
	while ( !toStop ) {
		toStop = getLexeme();
		whatToken();
		//cout << stayTok.lexeme << " " << stayTok.type << "\n";
		
		if ( program() ) {
			parserPrint();
		} // if
	    else {
	    	if ( stayTok.type == ERROR ) {
	    		cout << "invalid input\n";
			} // if
		} // else
		
		TokList.clear();
		lambda = false;
	} // while
    
	return 0;
} // main()
