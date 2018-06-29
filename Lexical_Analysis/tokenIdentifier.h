#include <fstream>
#include<iostream>
#include <string.h>

#include "tokenizer.h"
#include "token_Buffer.h"

using namespace std;
string curString="";
bool readingComment=false;
string keywords[] = {"if","then","owise","let","in","job","for","step","to","do","import","while","until","return","leave","switch","default","case","from"};
char separators[] = {" {}(),.;[]:"};
string strOperators[] = {"AND", "OR", "ISNOT"};
string dOperators[] = {"+=","-=",">=","<=","^=","++","--","!=","*=","/=","?=","||","&&"};
string bools[] = {"TRUE","FALSE"};
bool isReadingIdentifier=false;
bool isReadingDigit=false;
bool isReadingString=false;
bool readingUnrecognizedToken=false;
char operators[] = "+=*/?&|-!<>^%";
bool foundKeyword;
bool foundOperator;
bool foundSeparator;
bool foundBool;
bool foundstrOperator;
char chr;
bool readingStrLit=false;
bool letterFound=false;
bool tokenizingString;
bool tokenizingSym;
bool foundOp;
string strBuffer="";
int tokenCount=0;

bool isLetter(char chr) {
	bool isLetter=false;
	if ((chr>=65&&chr<=90)||(chr>=97&&chr<=122||chr==95)) {
		isLetter=true;
	}
	return isLetter;
}
bool isDigit(char chr) {
	bool isDigit=false;
	if (chr>=48&&chr<=57) {
		isDigit=true;
	}
	return isDigit;
}
bool isSym(char chr) {
	bool isSym=false;
	if (chr>=40&&chr<=45||chr>=58&&chr<=63||chr>=91&&chr<=94||chr>=123&&chr<=125||chr=='!'||chr=='"'||chr=='/'||chr==' '||chr==37||chr==38) {
		isSym=true;
	}
	return isSym;
}
void appendEOF(string line, int lineNo) {
	TOKEN T = {EOF_T, EOF_TOKEN, line, lineNo, 0, -1};
	pushToken(T);
}
void tokenize(string line, int lineNo, int column) {
    if (line!=""||tokenizingString) {
		strBuffer=line;
    if (strBuffer!=" ") {
		if (tokenizingString) {
			TOKEN T = {STR_LITERAL, STR_LIT, strBuffer, lineNo, column, tokenCount};
			pushToken(T);
		}
		else if (tokenizingSym) {
			for (int i=0;i<sizeof(operators)/sizeof(operators[0]);i++) {
			  if (operators[i]==chr) {
			    foundOperator=true;
			    break;
			  }
			}
			for (int i=0;i<sizeof(separators)/sizeof(separators[0]);i++) {
			  if (separators[i]==chr) {
			    foundSeparator=true;
			    break;
			  }
			  
			}
			if (foundOperator) {
				TOKEN T = {OPERATOR, getToken(strBuffer), strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			}
			else if (foundSeparator) {
				TOKEN T = {SEPARATOR, getToken(strBuffer), strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			}
			else if (strBuffer=="\"") {
				TOKEN T = {SPECIAL_CHAR, QUOT_MARK, strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			}
			else {
				TOKEN T = {SPECIAL_CHAR, SPEC_CHAR, strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			}
		}
		else {
		  
			if (isLetter(strBuffer[0])) {
			  for (int i=0;i<sizeof(keywords)/sizeof(keywords[0]);i++) {
			    if (keywords[i]==strBuffer) {
			      foundKeyword=true;
			      break;
			    }
			  }
			   for (int i=0;i<sizeof(strOperators)/sizeof(strOperators[0]);i++) {
			    if (strOperators[i]==strBuffer) {
			      foundstrOperator=true;
			      break;
			    }
			  }
			  for (int i=0;i<sizeof(bools)/sizeof(bools[0]);i++) {
			    if (bools[i]==strBuffer) {
			      foundBool=true;
			      break;
			    }
			  }
			  if (foundBool) {
				TOKEN T = {BOOL_LITERAL, getToken(strBuffer), strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			  }
			  else if (foundKeyword) {
				TOKEN T = {KEYWORD, getToken(strBuffer), strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			  }
			  else if (foundstrOperator) {
				TOKEN T = {STR_OPERATOR, getToken(strBuffer), strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			  }
			  else {
				TOKEN T = {IDENTIFIER, ID, strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			  }
			  
			}
			else if(isDigit(strBuffer[0])||strBuffer[0]=='.') {
			  for (int i = 0; i<strBuffer.length();i++) {
			    if (isLetter(strBuffer[i])) {
			      letterFound=true;
			      break;
			    }
			  }
			  if (letterFound) {
					TOKEN T = {ILLEGAL_ID, ILL_ID, strBuffer, lineNo, column, tokenCount};
					pushToken(T);
			  }
			  else {
				  int pointCnt=0;
				  for (int i = 0; i<strBuffer.length();i++) {
					if (strBuffer[i]=='.') {
					  pointCnt++;
					} 
				  }
				  if (pointCnt>1) {
					 TOKEN T = {ILLEGAL_ID, ILL_ID, strBuffer, lineNo, column, tokenCount};
						pushToken(T);
				 }
				  else {
                        TOKEN T = {CONSTANT, CONST_K, strBuffer, lineNo, column, tokenCount};
						pushToken(T);
				  }
			  }
			}
			else if(strBuffer!="\0") {
				TOKEN T = {ILLEGAL, UNKNOWN_ILLEGAL, strBuffer, lineNo, column, tokenCount};
				pushToken(T);
			}
		}
		tokenCount++;
	}
	foundOperator=false;
	foundSeparator=false;
	foundstrOperator=false;
	foundBool=false;
	foundKeyword=false;
	letterFound=false;
	strBuffer="";
    }
}
