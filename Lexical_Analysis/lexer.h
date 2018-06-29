#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QString"
#include "tokenIdentifier.h"

bool quit = false;

void lex(string line, int lineNo, Ui::MainWindow* ui) {
	int i = 0;
    if (line!="") {
	  for (i = 0; i<line.length();i++) {
          if(quit) {
              break;
          }
		char c = line[i];

		if (i<line.length()-1) {
		  if (line[i]=='/'&&line[i+1]=='/') {
			break;
		  }
		  if (line[i]=='/'&&line[i+1]=='*') {
			readingComment=true;
			i+=2;
			c = line[i];
		  }
		  if (line[i]=='*'&&line[i+1]=='/') {
			readingComment=false;
			i+=2;
			c = line[i];
		  }
		}
		if (!readingComment) {
            if (c!='\0'&&c!='\t'&&c!='\r') {

				if (readingStrLit) {
				  if(c=='\\') {
					curString+=line[i+1];
					i+=2;
					c=line[i];
				  }
				}
				if (c=='"'&&readingStrLit) {
				  readingStrLit=false;
				  tokenizingString=true;
				  tokenize(curString,lineNo,i);
				  tokenizingString=false;
				  curString="";
				}
				else if (c=='"') {
				  readingStrLit=true;
				}

				if (c=='.'&&isDigit(line[i+1])&&!isLetter(line[i-1])) {
					curString+=c;
				}
				else if (isSym(c)&&!readingStrLit||c=='"') {
				  string str ="";
				  if (c=='.'&&isDigit(line[i-1])) {
					 curString+=c;
				  }
				  else {
					  tokenize(curString,lineNo,i);
					  tokenizingSym=true;
					  str+=c;

					  for (int a=0;a<sizeof(operators)/sizeof(operators[0]);a++) {
						  if (operators[a]==c) {
							foundOp=true;
							break;
						  }
						}
						if (foundOp) {
							for (int k = 0; k<sizeof(dOperators)/sizeof(dOperators[0]);k++) {
								if (str+line[i+1]==dOperators[k]) {
									str+=line[i+1];
									i++;
									break;
								}
							}
						}
					  tokenize(str,lineNo,i);
					  tokenizingSym=false;
					  curString="";
					  str ="";
				  }
				}
				else {
				   curString+=c;
				}
			}
			else {
				tokenize(curString,lineNo,i);
				curString="";
			}
		}
		if (i==line.length()-1) {
			tokenize(curString,lineNo,i);
			curString="";
		}
	  }
	  tokenizingSym=false;
	  tokenizingString=false;
	  curString="";
	}
	if (readingStrLit) {
		cout<<"SYNTAX ERROR ON LINE "<<lineNo<<" ON COLUMN "<<i<<": NO TERMINATING \" CHARACTER\n";
        ui->textBrowser_3->append((QString::fromStdString("Syntax error on line "+to_string(lineNo)+", column "+to_string(i)+": no terminating \" character")));
		readingStrLit=false;
	}
}
