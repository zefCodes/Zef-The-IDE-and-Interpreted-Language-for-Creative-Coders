#include <fstream>
#include<iostream>
#include <string.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QString"
#include <QTextDocument>
#include "QKeyEvent"
#include <QtWidgets>
using namespace std;
int maxPrints=10000;
int noPrints=0;
string line;
int lineNo=0;
bool reachedEnd=false;

void showError(Ui::MainWindow* ui, string err) {
    if (noPrints>maxPrints) {
        ui->textBrowser_3->clear();
        noPrints=0;
    }
    noPrints++;
    ui->textBrowser_3->setTextColor(QColor(184, 59, 47));
    ui->textBrowser_3->append(QString::fromStdString(err));
    ui->textBrowser_3->append("Error: Failed to Execute program!");
    ui->textBrowser_3->verticalScrollBar()->setValue(ui->textBrowser_3->verticalScrollBar()->maximum());
    qApp->processEvents();
}


void collectTokens(string zef_file, Ui::MainWindow* ui) {
    clearTokens();
	int lineNo=0; //Initialize line number as 0
	ifstream script; //create ifstream object
	string fileName = (zef_file+".zef");
	script.open(fileName.c_str()); //open script file.
	if (script.is_open()) {
        //cout+"SUCCESSFULLY OPENED FILE!\n";
		while(getline(script,line)) { //while there is another line in the text file,
            if(quit) {
                break;
            }
			lineNo++; //update line number
            lex(line,lineNo, ui); //pass this line to the lex function
		}
		lineNo++;
		appendEOF("End of file",lineNo);
	}
	else {
	  cout<<"Could not find \""<<fileName<<"\"\n"; //report failure if cannot open
	  exit(1);
	}

}

void printToken(TOKEN T, Ui::MainWindow* ui) {
    string str = "ID: ";
    str+=to_string(T.tokenID);
	switch(T.TYPE) {
        case CONSTANT :    str+=("              CONSTANT | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case STR_LITERAL : str+=("           STR_LITERAL | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case BOOL_LITERAL: str+=("          BOOL_LITERAL | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case IDENTIFIER :  str+=("            IDENTIFIER | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case ILLEGAL_ID :  str+=("            ILLEGAL_ID | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case OPERATOR :    str+=("              OPERATOR | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case SPECIAL_CHAR :str+=("          SPECIAL_CHAR | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case SEPARATOR :   str+=("             SEPARATOR | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case STR_OPERATOR :str+=("          STR_OPERATOR | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case KEYWORD :     str+=("               KEYWORD | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case ILLEGAL :     str+=("               ILLEGAL | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
        case EOF_T :       str+=("                   EOF | "+tokenToString(T.NAME)+" ("+T.lexeme+")\n"); break;
	}
    QString qstr = QString::fromStdString(str);
    ui->textBrowser_3->setText(ui->textBrowser_3->toPlainText()+qstr);
}
