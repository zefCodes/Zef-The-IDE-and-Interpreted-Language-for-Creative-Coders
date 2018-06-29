#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <typeinfo>
#include "../../Lexical_Analysis/tokenizer.h"
#include "../../Lexical_Analysis/lexer.h"
#include "../../Lexical_Analysis/zex.h"
#include "../../Syntax_Analysis/Parsing_Table.h"
#include "../../Syntax_Analysis/RULES.h"
#include "../../Syntax_Analysis/errors.h"
#include "../../Semantic_Analysis/semantic_actions.h"
#include "../../Interpretation/zinterpreter.h"
#include "../../Interpretation/PrimitiveFunctions.h"



//#include "ui_mainwindow.h"
//#include "mainwindow.h"
//#include "QString"
//#include <QTextDocument>
//#include "QKeyEvent"
//#include <QtWidgets>
//#include <string.h>
//#include "QResizeEvent"
//#include "QSize"
//#include <QApplication>

#include <map>

std::vector<int> tokenStack;
std::vector<TOKEN> stack;
vector<string> functionArgs;

void printStack() {
    cout <<"\n"<< std::flush;
    for (int i = 0; i<tokenStack.size(); i++) {
        cout << tokenToString(tokenStack[i])<< " "<<std::flush;
    }
}
bool checkIllegal(TOKEN T) {
    if (T.NAME==UNKNOWN_ILLEGAL || T.NAME==ILL_ID || T.NAME==SPEC_CHAR) {
        return true;
    }
    else {
        return false;
    }
}
void parse () {
    resetTokenBuffer(); //Resets the token pointer to first index.
    bool FAILED=false;
    tokenStack.push_back(EOF_TOKEN);
    //cout << tokenStack.back() << "\n" << std::flush;
    tokenStack.push_back(PROGRAM);
    //cout << tokenStack.back() <<  "\n" << std::flush;

    TOKEN T = nextToken();
    if (checkIllegal(T)) {
        cout << "Syntax error on line " << T.lineNo << ", column " << T.column << " : Illegal token '" << T.lexeme << "', expecting '" << tokenToString(tokenStack.back()) << "'"<<std::flush;
        exit(1);
        FAILED=true;
    }
    else {
        while (1) {
            if (checkIllegal(T)) {
                cout << "Syntax error on line " << T.lineNo << ", column " << T.column << " : Illegal token '" << T.lexeme << "', expecting '" << tokenToString(tokenStack.back()) << "'"<<std::flush;
                exit(1);
                FAILED=true;
                break;
            }
            //cout << "\nLOOKAHEAD: " << tokenToString(T.NAME) << " \n"<< std::flush;
            //printToken(T);
            if (tokenStack.back()==EOF_TOKEN && T.NAME == EOF_TOKEN) {
                break;
            }
            else if ((tokenStack.back() > 199 && tokenStack.back()<300) || tokenStack.back() == EOF_TOKEN) {


                int prediction = tokenStack.back();

                if (T.NAME == prediction) {
                        tokenStack.pop_back();
                        if (insideFunction) {
                                addFuncInstruction(ACTION_PUSH, T);
                        }
                        else {
                            addInstruction(ACTION_PUSH, T);
                        }

                        stack.push_back(T);
                    //cout << "\nMATCH1 " << tokenToString(T.NAME) <<std::flush;
                    T = nextToken();
                }
                else {
                    cout << "Syntax error on line " << T.lineNo << ", column " << T.column << " : Wrong token '" << T.lexeme << "', expecting '" << tokenToString(prediction) << "'"<<std::flush;
                    exit(1);
                    FAILED=true;
                    break;
                }
            }
            else if (tokenStack.back()>299&&tokenStack.back()<500) {
                    int A = tokenStack.back();
                    //cout << "\nTOP OF STACK: "<<stack.back().lexeme<<std::flush;
                    stack = performAction(A,stack);
                    tokenStack.pop_back();
            }
            else {
                int focus = tokenStack.back()-1;

                //cout << "REFERENCING " << "["<< focus << "]" <<  "["<< T.NAME-200 << "]"<< "["<< tokenToString(focus+1) << "]" <<  "["<< tokenToString(T.NAME) << "]"<<std::flush;
                int ENTRY = TABLE[focus][T.NAME-200]-1;
                //cout << "\nENTRY "<<ENTRY;
                if (ENTRY==-3) {
                    cout<< "Syntax error on line " << T.lineNo << ", column " << T.column << " : " << getErrorMessage(focus+1, T) <<"'"<<std::flush;
                    exit(1);
                    FAILED=true;
                    break;
                }
                else if (ENTRY==-2) {
                    cout<< "Syntax error on line " << T.lineNo << ", column " << T.column << " : " << getErrorMessageType2(focus+1, T) <<"'"<<std::flush;
                    exit(1);
                    FAILED=true;
                    break;
                }
                else {
                    tokenStack.pop_back();
                    for(int i=12;i>=0;i--){
                        if (RULES[ENTRY][i]==EPSILON) {
                            //cout<<"\nEPSILON"<<std::flush;
                            //printStack();
                        }
                        if (RULES[ENTRY][i]!=0 && RULES[ENTRY][i]!=EPSILON) {
                            //cout<<"\nPUSHING: " << tokenToString(RULES[ENTRY][i]) <<std::flush;
                            tokenStack.push_back(RULES[ENTRY][i]);
                            //printStack();
                        }
                    }
                }

            }

        }
    }

    if (FAILED) {
        cout << "\nError: Failed to parse program.\n" << std::flush;
    }
}

void logAllTokens(Ui::MainWindow* ui) {
    resetTokenBuffer();
    int i=0;
    while(i<tokenCount+1){
        i++;
        TOKEN T = nextToken();
        printToken(T,ui);
    }
}



int maian(int argc, char* argv[]) {


    //parse();
    //addPrimitiveFunctions();
    //scopeStack.push_back(scope);
    //Items.push_back(interpret(instructions));
    //logAllVariables(var_tab);

    //logInstructions();
    //logFunctions();
}




/*NEED TO DO SEMANTiC CHECKING.
1.CHECK ARRAY STRUCTURE
2.CHECK OPERATIONS WITH NUMBERS GO WITH NUMBERS
3.CHECK INTEGERS ARE RETURNED FOR ARRAY DEFINITION
4.CHECK WHILE, UNTIL AND IF STATEMENTS GET TRUTH VALUES
5.CHECK VARIABLES USED HAVE BEEN DECLARED
6.CHECK FUNCTIONS USED HAVE BEEN DECLARED
7.SCOPE RESOLUTION
8.ARRAY BOUND CHECKING
9.RESERVED IDENTIFIER MISUSE
10.ACCESSING AN OUT OF SCOPE VARIABLES
11.ACTUAL AND FORMAL PARAMETER MISMATCH
*/


#endif // PARSER_H
