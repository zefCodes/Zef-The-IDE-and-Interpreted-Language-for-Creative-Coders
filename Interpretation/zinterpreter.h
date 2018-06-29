#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <string>
#include <stdio.h>
#include <deque>
#include "zefopengl.h"
#include <math.h>

#define _USE_MATH_DEFINES

Ui::MainWindow* ui;
float inc = 0.7;
int getmousey();
int getmousex();
void movesquare(float f);
void drawArc(float x, float y, float radius1, float radius2, float start, float end, float segments);
void fillArc(float x, float y, float radius1, float radius2, float start, float end, float segments);
void drawOval(float x, float y ,float width, float height, float segments);
void fillOval(float x, float y ,float width, float height, float segments);
void drawLine(float startx, float starty, float endx, float endy);
void setBackground(float r, float g, float b, float a);
void fillRect(float x,float y, float width, float height);
void drawRect(float x,float y, float width, float height);
void setPaintColor(float r, float g, float b);
void setLineWeight(float w);
void translate(float x, float y);
void scale(float x, float y);
void rotate(float r);
void clearScreen();
int NO=0;
int noOfnl = 0;
static char * _topOfStack;
static int _maxAllowedStackUsage;
bool prepared = false;
deque<ELEMENT> EMPTYL;
bool STOP = false;
int loops = 0;
int numwhiles;

void printListE(ELEMENT V) {
    cout<<"[";
    std::deque<ELEMENT> list = V.list;
    for (int i = 0; i<list.size(); i++) {
        if (i!=list.size()-1) {
                if (list[i].TYPE==DATAL) {
                    printListE(list[i]);
                }
                else {
                     cout<<list[i].lexeme<<", ";
                }
           }
           else {
                if (list[i].TYPE==DATAL) {
                    printListE(list[i]);
                    cout<<"]";
                }
                else {
                    cout<<list[i].lexeme<<"]";
                }

           }
    }
}

void printList(VARIABLE V) {

    cout<<"\n[";
    deque<ELEMENT> list = V.list;
    for (int i = 0; i<list.size(); i++) {
        if (i!=list.size()-1) {
                if (list[i].TYPE==DATAL) {
                    printListE(list[i]);
                }
                else {
                     cout<<list[i].lexeme<<", ";
                }
           }
           else {
                if (list[i].TYPE==DATAL) {
                    printListE(list[i]);
                    cout<<"]";
                }
                else {
                    cout<<list[i].lexeme<<"]";
                }

           }
    }
}

void logInstructions() {
    for (int j = 0; j<instructions.size();j++) {
        std::cout << "\n[ instruction: " << j << " : " << tokenToString(instructions[j].i) <<" : "<< (instructions[j].a.lexeme) <<" : "<< (instructions[j].b.lexeme) <<']'<<std::flush;
    }
}


//void logRenderInstructions() {
//  for (std::map<int,instruction>::iterator it=render_instructions.begin(); it!=render_instructions.end(); ++it) {
//    std::cout << "\n[ RENDER instruction: " << it->first << " : " << tokenToString(it->second.i) <<" : "<< (it->second.a.lexeme) <<" : "<< (it->second.b.lexeme) <<']'<<std::flush;
//    int InstrucitonID = it->first;
//    ACTION i = it->second.i;
//  }
//}


int GetCurrentStackSize()
{
   char localVar;
   int curStackSize = (&localVar)-_topOfStack;
   if (curStackSize < 0) curStackSize = -curStackSize;  // in case the stack is growing down
   return curStackSize;
}


struct FunctionData {
    string arguments[50];
    int noArgs;
};
deque<ELEMENT> Items;

std::map<string,FunctionData> funcData;



deque<int> instrucID;

struct scopeVar {
  int tableIndex;
  ELEMENT T;
};

void ouch(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
}

std::ostringstream oss;

bool func=false;
bool debugging=false;
bool failedSoFar=false;

TOKENS OR[2][2] = {
    {TRUE_K,TRUE_K},
    {TRUE_K,FALSE_K},
};

TOKENS AND[2][2] = {
    {TRUE_K,FALSE_K},
    {FALSE_K,FALSE_K},
};

void initializeElements(Ui::MainWindow* u) {
    ui=u;
}
void logFunctions() {

  cout<<"\nFUNCTIONS: ===========";
    for (std::unordered_map<std::string,deque<instruction>>::iterator i=functions.begin(); i!=functions.end(); ++i) {
        std::cout<<"\n FUNCTION: "<<i->first;
        for (int j = 0; j<i->second.size();j++) {
            std::cout << "\n[ instruction: " << j << " : " << tokenToString(i->second[j].i) <<" : "<< (i->second[j].a.lexeme) <<" : "<< (i->second[j].b.lexeme) <<']'<<std::flush;
        }
      }
}

void printScope(int i) {
    std::cout <<"\nVARIABLES :: "<< scopeStack[i].vars.size() <<std::flush;
    for (std::unordered_map<string,VARIABLE>::iterator it=scopeStack[i].vars.begin(); it!=scopeStack[i].vars.end(); ++it) {
      std::cout << "\n[" << it->first << " : " << it->second.val <<" : "<< typeToString(it->second.T) <<']'<<std::flush;
    }
    std::cout <<"\n"<<std::flush;
}

void printItems() {
  cout <<"\n\n"<< std::flush;
  for(int i=0; i<Items.size(); i++) {
    cout<<Items[i].lexeme<<" :: ";
  }
  cout <<"\n\n"<< std::flush;
}

float strToFloat(string str) {
//    NO++;
//    if (noPrints>maxPrints) {
//        ui->textBrowser_3->clear();
//        noPrints=0;
//    }
//    noPrints++;
//     ui->textBrowser_3->append("CONVERTGING TO FLOAT" + QString::number(NO));
    const char* p = str.c_str();
    float r = 0.0;
        bool neg = false;
        if (*p == '-') {
            neg = true;
            ++p;
        }
        while (*p >= '0' && *p <= '9') {
            r = (r*10.0) + (*p - '0');
            ++p;
        }
        if (*p == '.') {
            float f = 0.0;
            int n = 0;
            ++p;
            while (*p >= '0' && *p <= '9') {
                f = (f*10.0) + (*p - '0');
                ++p;
                ++n;
            }
            r += f / std::pow(10.0, n);
        }
        if (neg) {
            r = -r;
        }
        return r;
}
string convToString(float num) {
//    NO++;
//    if (noPrints>maxPrints) {
//        ui->textBrowser_3->clear();
//        noPrints=0;
//    }
//    noPrints++;
//     ui->textBrowser_3->append("CONVERTGING TO STRING "+ QString::number(NO));
    //THIS FUNCTION CONVERTS A STRING TO AN INTEGER VALUE.
    //IT IS USED TO READ THE HIGHSCORE FROM THE TEXT FILE

    return std::to_string(num);
}

TOKENS andV(ELEMENT A, ELEMENT B) {
        return AND[A.NAME-241][B.NAME-241];

}

TOKENS orV(ELEMENT A, ELEMENT B) {
        return OR[A.NAME-241][B.NAME-241];
}

bool exists(ELEMENT T, Scope scope) {
    string value = T.lexeme;
    bool found=false;
        for (std::unordered_map<string,VARIABLE>::iterator it=scope.vars.begin(); it!=scope.vars.end(); ++it) {
                if (it->first==value) {
                        return true;
                }
        }
    return false;
}

bool checkRenderFunction(Ui::MainWindow* ui) {
    for (std::unordered_map<std::string,deque<instruction>>::iterator it=functions.begin(); it!=functions.end(); ++it) {
        if (it->first=="render") {
            return true;
        }
    }
    failedSoFar=true;
   // cout<< "\nVariable use error on line " << lineNo << ", column " << column << " : " << "'"<<value<<"' "<<"has not been declared."<<std::flush;
    oss<< "Missing the render function";
    showError(ui, oss.str());
}

bool checkPrepareFunction(Ui::MainWindow* ui) {
    for (std::unordered_map<std::string,deque<instruction>>::iterator it=functions.begin(); it!=functions.end(); ++it) {
        if (it->first=="prepare") {
            return true;
        }
    }
    failedSoFar=true;
   // cout<< "\nVariable use error on line " << lineNo << ", column " << column << " : " << "'"<<value<<"' "<<"has not been declared."<<std::flush;
    oss<< "Missing the prepare function";
    showError(ui, oss.str());
}

scopeVar searchFor(ELEMENT T, Ui::MainWindow* ui) {
    TOKEN_TYPE_T Type;
    TOKENS name = T.NAME;
    string value = T.lexeme;
    int lineNo = T.lineNo;
    int column = T.column;
    deque<ELEMENT> list = T.list;
    bool found=false;
  int tableIndex;
  //cout<<"\n Searching for: "<<T.lexeme<<" :: "<<scopeStack.size()<<std::flush;
  for (int i = scopeStack.size()-1 ; i>=0; i--) {
    Scope s = scopeStack[i];
    //printScope(i);
    for (std::unordered_map<string,VARIABLE>::iterator it=s.vars.begin(); it!=s.vars.end(); ++it) {
      //if (debugging) {cout<<"\n COMPARING"<<it->first<<"?="<<value<<std::flush;}
                if (it->first==value) {
                        Type=it->second.T;
                        value=it->second.val;
                        name=it->second.name;
                        lineNo=it->second.lineNo;
                        column=it->second.column;
                        list=it->second.list;
                        found=true;
                        tableIndex=i;
                        break;
                }
        }
    if (found) {
      break;
    }
  }

        if (!found) {
            cout<< "\nVariable use error on line " << lineNo << ", column " << column << " : " << "'"<<value<<"' "<<"has not been declared."<<std::flush;
            oss<< "\nVariable use error on line " << lineNo << ", column " << column << " : " << "'"<<value<<"' "<<"has not been declared.";
            showError(ui, oss.str());
            failedSoFar=true;
        }

        //if (debugging) {cout<<"GOTR "<<tokenToString(name)<<std::flush;}
        ELEMENT newT = {Type,name,value,lineNo,column,list};
    scopeVar newVar = {tableIndex, newT};
        return newVar;
}

ELEMENT retrieveData(ELEMENT REF) {
    Items.pop_back();
    ELEMENT STORE = Items.back();
    int lineNo = STORE.lineNo;
    int column = STORE.column;
    ELEMENT RES;
//cout<<"\nRETRIEVING: " <<STORE.lexeme<<flush;
    if (STORE.TYPE==IDENTIFIER) {
        STORE = searchFor(STORE,ui).T;
    }
    else {
        cout<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": Expecting an expression, got "<<tokenToString(STORE.NAME);
        oss<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": Expecting an expression, got "<<tokenToString(STORE.NAME);
        showError(ui, oss.str());
        failedSoFar=true;
    }

    if (STORE.TYPE!=DATAL) {
        cout<< "\nOperation error on line " << STORE.lineNo <<" column "<< STORE.column <<" : Attempt to index from non list '"<<STORE.lexeme<<"'"<<std::flush;
        oss<< "\nOperation error on line " << STORE.lineNo <<" column "<< STORE.column <<" : Attempt to index from non list '"<<STORE.lexeme<<"'"<<std::flush;
        showError(ui, oss.str());
        failedSoFar=true;
    }

    //printListE(REF);

    if (!failedSoFar) {
        int size = REF.list.size();

        if (size==0) {
            //cout<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": ZERRO SIZE, got "<<tokenToString(STORE.NAME);
            oss<<"\nError on line "<<lineNo<<" column "<<  column<<": Expecting expression, got ']'";
            showError(ui, oss.str());
            failedSoFar=true;
        }

        int i = 0;
        while(i<size) {
                int index = (int)strToFloat(REF.list[i].lexeme);
                int s = STORE.list.size();
                if (index>=s || index<0) {
                    //cout<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": ZERRO SIZE, got "<<tokenToString(STORE.NAME);
                    oss<<"\nError on line "<<REF.list[i].lineNo<<" column "<<REF.list[i].column<<": list indexing is out of bounds by "<<index-s+1;
                    showError(ui, oss.str());
                    failedSoFar=true;break;
                }
                RES = STORE.list[index];
                STORE = STORE.list[index];
                i++;


        }

    }

    return RES;
}



scopeVar checkCanInc(ELEMENT M, ACTION ACT, Ui::MainWindow* ui) {
  scopeVar scopev;
    if (M.TYPE==IDENTIFIER) {
        scopev = searchFor(M,ui);
    }
    else {
        cout<< "\nOperation error on line " << M.lineNo <<" column "<< M.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(M.TYPE)<< std::flush;
        oss<< "\nOperation error on line " << M.lineNo <<" column "<< M.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(M.TYPE);
        showError(ui, oss.str());
        failedSoFar=true;
    }
    if(!typeCheck(ACT,M)) {
        cout<< "\nOperation error on line " << M.lineNo <<" column "<< M.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(M.TYPE)<< std::flush;
        oss<< "\nOperation error on line " << M.lineNo <<" column "<< M.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(M.TYPE);
        showError(ui, oss.str());
        failedSoFar=true;
    }
  return scopev;
}

ELEMENT interpret(deque<instruction> instructions) {



  //cout<<"INTERPETING ========>"<<scopeStack.size()<<std::flush;
  bool creatingVar=false;

  for (int it = 0; it<instructions.size(); it++) {

      if (STOP) {

          break;
      }

     if (!failedSoFar) {
    //if (debugging) {printItems();}

    //if (debugging) {std::cout << "\n[ Executing instruction: " << it->first << " : " << tokenToString(it->second.i) <<" : "<< (it->second.a.lexeme) <<" : "<< (it->second.b.lexeme) <<']'<<std::flush;}
    //cout<<"YOOOOOOOOOOOOOOOOOOOOOOOOOO";
    int InstrucitonID = it;
    //cout<<"CURRRRRRRRRRR====> "<<Items.back().lexeme ;

    string name = instructions[it].a.lexeme;
    ACTION i = instructions[it].i;
    TOKEN A = instructions[it].a;
    ACTION ACT = i;
     // std::cout<<"CAAALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL " <<tokenToString(i)<<endl;
    bool Evaluated;
    switch (i) {
        case ACTION_JUMP_BACK : {
            scopeStack.pop_back();
            //cout<<"JUMPING BACK";
            it=instrucID.back()-1;
            while(1) {
                if (failedSoFar) {
                    break;
                }
              //cout<<"\n BEFORE POP CURR TOP OF STACKw -->> "<< Items.back().lexeme <<std::flush;
              Items.pop_back();
              //cout<<"\n AFTER POP CURR TOP OF STACKw -->> "<< Items.back().lexeme <<"\n"<<std::flush;
              if (Items.back().TYPE==EOF_T2) {
                Items.pop_back();
                break;
              }
             }
            if (failedSoFar) {
                break;
            }
            //cout<<"JUMPING BACK ID = " << it->first;
            instrucID.pop_back();
          break;
        }
         case ACTION_EVAL_WHILE : {
            ELEMENT PLACEHOLDER = {EOF_T2, UNKNOWN_ILLEGAL, "$", -1,-1,EMPTYL};
            Items.push_back(PLACEHOLDER);
            instrucID.push_back(InstrucitonID);
            break;
        }
        case ACTION_CHECK_WHILE : {
            ELEMENT B = Items.back();
            numwhiles=1;
            Items.pop_back();
            if(B.TYPE==BOOL_LITERAL) {
              //if (debugging) {cout<<"\n VALUE FOR IF STATEMENT:=======================> "<<tokenToString(B.NAME)<<endl;}
              if (B.NAME==FALSE_K) {
                  loops = 0;
                  //int depth = instrucID.size();

                  //int level = 0;
                  while (1) {
                      it++;
                      if (instructions[it].i==ACTION_CHECK_WHILE) {
                          numwhiles++;
                      }
                      else if (instructions[it].i==ACTION_JUMP_BACK) {
                          numwhiles--;
                      }
                      if (instructions[it].i==ACTION_JUMP_BACK && numwhiles==0) {
                          //cout<<"LEAVING"<<endl;
                          instrucID.pop_back();
                          break;
                      }
                  }
              }
              else {
                  //loops++;
                  //ui->label->setText("      Console:  " + QString::fromStdString(to_string(loops)));
                  qApp->processEvents();
                  std::unordered_map<string, VARIABLE> nScope;
                  Scope newScope = {nScope};
                  scopeStack.push_back(newScope);
                  qApp->processEvents();
              }
            }
            else {
              cout<<"\nError on line "<< B.lineNo<<" column "<< B.column<<": Expecting a boolean value, got "<<tokenToString(B.NAME);
              oss<<"\nError on line "<< B.lineNo<<" column "<< B.column<<": Expecting a boolean value, got "<<tokenToString(B.NAME);
              showError(ui, oss.str());
              failedSoFar=true;break;
            }
        break;
        }
    case ACTION_NEW_IF : {
      //cout<<"EVALUATING IF STATEMENT"<<endl;
      ELEMENT B = Items.back();
      if(B.TYPE==BOOL_LITERAL) {
        //if (debugging) {cout<<"\n VALUE FOR IF STATEMENT:=======================> "<<tokenToString(B.NAME)<<endl;}
        if (B.NAME==TRUE_K) {
            std::unordered_map<string, VARIABLE> nScope;
            Scope newScope = {nScope};
            scopeStack.push_back(newScope);

          Evaluated=true;

        }
        else {
          Evaluated=false;
          it++;
          while(instructions[it].i!=ACTION_END_IF){
              if (failedSoFar) {
                  break;
              }
            it++;
          }
        }
      }
      else {
        cout<<"\nError on line "<< B.lineNo<<" column "<< B.column<<": Expecting a boolean value, got "<<tokenToString(B.NAME);
        oss<<"\nError on line "<< B.lineNo<<" column "<< B.column<<": Expecting a boolean value, got "<<tokenToString(B.NAME);
        showError(ui, oss.str());
        failedSoFar=true;break;
      }
      break;
    }
    case ACTION_END_IF : {
      scopeStack.pop_back();
      break;
    }
      case ACTION_RETURN: {
        //scopeStack.pop_back();
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        //if (debugging) {cout<<"\nRETURNING: "<<B.lexeme;}
        return B;
      }
      case ACTION_PUSH: {
        TOKEN A = instructions[it].a;
        Items.push_back({A.TYPE, A.NAME, A.lexeme, A.lineNo, A.column, EMPTYL});
        break;
      }
      case ACTION_POP: {
        Items.pop_back();
        break;
      }
    case ACTION_PUSH_BRACK: {
        ELEMENT NUL = {CONSTANT, NULLT, "(", -1,-1,EMPTYL};
        Items.push_back(NUL);
         break;
    }
    case ACTION_PUSH_SQR_BRACK: {
        ELEMENT NUL = {CONSTANT, NULLT, "[", -1,-1,EMPTYL};
        Items.push_back(NUL);
         break;
    }
    case ACTION_COLLECT_LIST : {
        deque<ELEMENT> list;
        ELEMENT item = Items.back();
        while (item.lexeme!="[") {

            if (item.TYPE==IDENTIFIER) {item = searchFor(item,ui).T;                }
            else if (item.TYPE==REFL) {
                item = retrieveData(item);
            }
            if (failedSoFar) {break;}
            list.push_front(item);
            Items.pop_back();
            item = Items.back();
        }
        if (failedSoFar) {break;}
        //cout<<"\nNEWLIST [";
//        for (int i=list.size()-1; i>=0; i--) {
//            if (i!=0) {
//                cout<<list[i].lexeme<<", ";
//            }
//            else {
//                cout<<list[i].lexeme<<"]";
//            }
//        }

        //let c = [2,2,2,3,[34,TRUE]];
        //let ddd = [ee,7];

        Items.pop_back();
        ELEMENT LIST = {DATAL, DATALIST, "<LIST>", Items.back().lineNo, Items.back().column, list};
        Items.push_back(LIST);
        break;
    }
      case ACTION_PARAM : {
        FunctionData func = {{},0};
        int index = 0;
        while(Items.back().lexeme!="(") {
          ELEMENT ARG = Items.back();
          if(ARG.TYPE!=IDENTIFIER) {
            cout<<"\nError on line "<< ARG.lineNo<<" column "<< ARG.column<<": Expecting an identifier, got "<<tokenToString(ARG.NAME);
            oss<<"\nError on line "<< ARG.lineNo<<" column "<< ARG.column<<": Expecting an identifier, got "<<tokenToString(ARG.NAME);
            showError(ui, oss.str());
            failedSoFar=true;break;
          }
          else {
            func.arguments[index]=ARG.lexeme;
            index++;
            func.noArgs=index;
          }
          Items.pop_back();
        }
        Items.pop_back();
        funcData[Items.back().lexeme]=func;
        break;
      }
    case ACTION_INDEX: {
        deque<ELEMENT> indices;
        ELEMENT ARG;
        while(Items.back().lexeme!="[") {
            //cout<<"LOOPING"<<flush;
            ARG = Items.back();
            ELEMENT PARAM;
            if (ARG.TYPE==IDENTIFIER) {
                PARAM = searchFor(ARG,ui).T;
            }
            else if (ARG.TYPE==REFL) {
                PARAM = retrieveData(ARG);
            }
            else {
                PARAM=ARG;
            }
            if (failedSoFar) {break;}
            if (PARAM.TYPE==CONSTANT) {
                deque<ELEMENT> L;
                indices.push_front({CONSTANT, CONST_K, PARAM.lexeme, ARG.lineNo,ARG.column,L});

            }
            else {
                cout<<"\nError on line "<< ARG.lineNo<<" column "<< ARG.column<<": Expecting a constant, got "<<tokenToString(PARAM.NAME);
                oss<<"\nError on line "<< ARG.lineNo<<" column "<< ARG.column<<": Expecting a constant, got "<<tokenToString(PARAM.NAME);
                showError(ui, oss.str());
                failedSoFar=true;break;
            }
            Items.pop_back();
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT LIST = {REFL, DATALIST, "<REF>", Items.back().lineNo, Items.back().column, indices};
        Items.push_back(LIST);
        //cout<<"REF, n"<<flush;
        //printListE(LIST);
        cout<<"\n"<<flush;

//        string r = "\nreferencing array: " + Items.back().lexeme + "[";
//        for (int i = 0; i<indices.size(); i++) {
//            if (i<indices.size()-1) {
//                r+=to_string(indices[i]) + ", ";
//            }
//            else {
//                r+=to_string(indices[i]);
//            }
//        }
//        r+="]";

//        cout<<r;

        break;
    }
      case ACTION_FUNC_CALL: {


          //if (debugging) {printItems();}
           if (failedSoFar) {break;}
          int paramCount=0;
          deque<VARIABLE> variables;
          std::unordered_map<string, VARIABLE> nScope;
          while(Items.back().lexeme!="(") {
            paramCount++;
            ELEMENT T = Items.back();
            if (T.TYPE==IDENTIFIER) {
              T = searchFor(T,ui).T;
            }
            else if (T.TYPE==REFL) {
                T = retrieveData(T);
            }
            if (failedSoFar) {break;}
            variables.push_back({T.lexeme,T.TYPE,T.NAME,T.lineNo,T.column,T.list});
            Items.pop_back();
          }
          if (failedSoFar) {break;}
          Items.pop_back();
          ELEMENT FUNCNAME = Items.back();
          name=FUNCNAME.lexeme;
          bool found=false;
          try {
              functions.at(name);
          }
          catch (const std::out_of_range& e) {
              cout << "Out of Range error.";
              showError(ui, "\nError on line " + to_string(FUNCNAME.lineNo) + " column "+to_string(FUNCNAME.column)+": function \""+name+"\" has not been declared");
              cout<<"\nError on line "<< FUNCNAME.lineNo<<" column "<< FUNCNAME.column<<": function \""<<name<<"\" has not been declared";
              failedSoFar=true;
              break;
          }


          if (paramCount!=funcData[name].noArgs) {
            cout<<"\nError on line "<< FUNCNAME.lineNo<<" column "<< FUNCNAME.column<<": function \"" <<name<<"\" requires "<<funcData[name].noArgs<<" argument(s)!";
            oss<<"\nError on line "<< FUNCNAME.lineNo<<" column "<< FUNCNAME.column<<": function \"" <<name<<"\" requires "<<funcData[name].noArgs<<" argument(s)!";
            showError(ui, oss.str());
            failedSoFar=true;break;
          }
          else {
            //if (debugging) {cout<<"ASSIGNING NEEEW SCOPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP";}
            for (int i = variables.size()-1; i>=0;i--) {
              nScope[funcData[name].arguments[i]]=variables[i];
              //if (debugging) {cout<<"\n ASSIGNMENT FOR NEW SCOPE: =======================================================>";}
              //logAllVariables(newScope);
              variables.pop_back();
            }

          }
          //if (debugging) {cout<<";:::::::::::::::::::::::::::::";}

          //cout<<"CURRRRRRRRRRR====> "<<Items.back().lexeme ;
          //fillRect(100,100,100,100);
          //break;
          Scope newScope = {nScope};
          scopeStack.push_back(newScope);
          ELEMENT NE;
          int curStackSize = GetCurrentStackSize();

          if (curStackSize < _maxAllowedStackUsage) {
              ELEMENT PLACEHOLDER = {EOF_T, UNKNOWN_ILLEGAL, "$", -1,-1,EMPTYL};
              Items.push_back(PLACEHOLDER);
              //printItems();
              NE = interpret(functions[name]);
          }
          else
          {
             //printf("    Can't recurse any more, the stack is too big!\n");
             oss<< "Can't recurse any more, the stack is too big! stackSize: "<< curStackSize <<std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
          }

          scopeStack.pop_back();
         // std::cout<<"PRINTIN------------------------------------G NOOWWW"<<std::endl;
         //printItems();
          //if (debugging) {cout<<"LEAAVING SCOOPEE GGGGGGGGGGGGGGGGGGGGGGGGGGG\n\n\n\n\n\n\n\n\n";}

          //if (debugging) {cout<<"\n NO====>: " <<NE.lexeme;}

          while(1) {
            //cout<<"\n BEFORE POP CURR TOP OF STACKw -->> "<< Items.back().lexeme <<std::flush;
            //cout<<"\n AFTER POP CURR TOP OF STACKw -->> "<< Items.back().lexeme <<"\n"<<std::flush;
            if (Items.back().TYPE==EOF_T) {
              Items.pop_back();
              break;
            }
            Items.pop_back();
          }
         // std::cout<<"PRINTIN------------------------------------G END"<<std::endl;
          Items.pop_back();
          //if (debugging) {cout<<"\n --------------------------------CURR TOP OF STACKw -->> "<< Items.back().lexeme <<std::flush;}
          //if (debugging) {printItems();}
          //if (debugging) {cout<<"PUSHING "<<NE.lexeme;}
          Items.push_back(NE);

        break;
      }
      case ACTION_ADD: {

        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}

        if(!typeCheck(A,ACTION_ADD,B)) {

          cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACTION_ADD)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACTION_ADD)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }

        if (A.TYPE==STR_LITERAL || B.TYPE==STR_LITERAL) {
                    //if (debugging) {cout<< A.lexeme+B.lexeme << "<<"<<std::flush;}
                    ELEMENT T = {STR_LITERAL, STR_LIT, A.lexeme+B.lexeme, A.lineNo, A.column, EMPTYL};
                    Items.pop_back();
                    Items.push_back(T);
                }
                else {
                    float a=strToFloat(A.lexeme);
                    float b=strToFloat(B.lexeme);
                    ELEMENT T = {CONSTANT, CONST_K, convToString(a+b), B.lineNo, B.column,EMPTYL};
                    //if (debugging) {cout<< a<<" + "<<b<<" = "<<a+b<<"\n" <<std::flush;}
                    Items.pop_back();
                    Items.push_back(T);
                }
        break;
      }
      case ACTION_MUL: {

        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}

        if(!typeCheck(A,ACTION_MUL,B)) {
          cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACTION_MUL)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACTION_MUL)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }

        float a=strToFloat(A.lexeme);
        float b=strToFloat(B.lexeme);
        ELEMENT T = {CONSTANT, CONST_K, convToString(a*b), B.lineNo, B.column, EMPTYL};
        //if (debugging) {cout<<"\n"<< a<<" * "<<b<<" = "<<a*b <<std::flush;}
        Items.pop_back();
        Items.push_back(T);

        break;
      }
      case ACTION_INIT : {
         ELEMENT T = Items.back();
         string value = T.lexeme;
         int lineNo = T.lineNo;
         int column = T.column;
         TOKENS NAME = T.NAME;
         TOKEN_TYPE_T type = T.TYPE;
           //if (debugging) {cout<<"LOOKING AT BACK <<< " << T.lexeme;}
           if (exists(T, scopeStack[scopeStack.size()-1])) {
             cout<<"\nError on line "<< T.lineNo<<" column "<< T.column<<": redefinition of variable \""<<T.lexeme<<"\"";
             oss<<"\nError on line "<< T.lineNo<<" column "<< T.column<<": redefinition of variable \""<<T.lexeme<<"\"";
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           else {
             //ELEMENT INIT = {CONSTANT, NULLT, "EMPTYL", -1,-1,-1};
            //if (debugging) { cout<<"APPPPPPPPPPPPPPP";}
             scopeStack[scopeStack.size()-1].vars[T.lexeme] = {value,type,NAME,lineNo,column,T.list};
             //if (debugging) {logAllVariables(scopeStack[scopeStack.size()-1]);}
             //if (debugging) {cout<<"APPPPPPPPPPPPPPP";}
           }
           //if (debugging) {cout<<"LOOKING AT BACK <<< " << T.lexeme;}
        break;
      }
      case ACTION_RESUME : {
        //if (debugging) {cout<<"OIIIIIIIIIIIII LEEAVING SCOPE G";}
        break;
      }

    case FUNC_MOUSE_X_PRIM : {
        ELEMENT NE = {CONSTANT,CONST_K, convToString(getmousex()), -1,-1,EMPTYL};
        return  NE;
        break;
    }
    case FUNC_MOUSE_Y_PRIM : {
        ELEMENT NE = {CONSTANT,CONST_K, convToString(getmousey()), -1,-1,EMPTYL};
        return  NE;
        break;
    }
    case FUNC_ROT_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float r = strToFloat(s.vars["r"].val);
        rotate(r);
        break;
    }
    case FUNC_TRANS_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        translate(x,y);
        break;
    }
    case FUNC_SCALE_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        scale(x,y);
        break;
    }
    case FUNC_SIZE_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        int size = s.vars["list"].list.size();
        ELEMENT NE = {CONSTANT,CONST_K, convToString(size), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_SIN_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = sin(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_COS_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = cos(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_TAN_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = tan(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_ASIN_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = asin(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_ACOS_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = acos(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_LOG_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = log(strToFloat(s.vars["a"].val))/log(strToFloat(s.vars["base"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_ATAN_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = atan(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_ROOT_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = pow(strToFloat(s.vars["a"].val),(float)1/strToFloat(s.vars["root"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_ABS_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = abs(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_FLOOR_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = floor(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_CEIL_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = ceil(strToFloat(s.vars["a"].val));
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_RAND_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];

        float ans = rand() %  (int) strToFloat(s.vars["b"].val) + (int) strToFloat(s.vars["a"].val);

        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_RADIANS_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = ((strToFloat(s.vars["a"].val)*M_PI)/180);
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;

    }
    case FUNC_DEGREES_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float ans = ((strToFloat(s.vars["a"].val)*180)/M_PI);
        ELEMENT NE = {CONSTANT,CONST_K, convToString(ans), -1,-1,EMPTYL};
        return NE;
        break;
    }
    case FUNC_DRAW_OVAL_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        float width = strToFloat(s.vars["width"].val);
        float height = strToFloat(s.vars["height"].val);
        float segments = strToFloat(s.vars["segments"].val);
        drawOval(x,y,width,height,segments);
        break;
    }
    case FUNC_DRAW_ARC_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        float width = strToFloat(s.vars["width"].val);
        float height = strToFloat(s.vars["height"].val);
        float segments = strToFloat(s.vars["segments"].val);
        float start = strToFloat(s.vars["start"].val);
        float end = strToFloat(s.vars["end"].val);
        drawArc(x,y,width,height,start,end,segments);
        break;
    }
    case FUNC_FILL_ARC_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        float width = strToFloat(s.vars["width"].val);
        float height = strToFloat(s.vars["height"].val);
        float segments = strToFloat(s.vars["segments"].val);
        float start = strToFloat(s.vars["start"].val);
        float end = strToFloat(s.vars["end"].val);
        fillArc(x,y,width,height,start,end,segments);
        break;
    }
    case FUNC_DRAW_RECT_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(scopeStack[scopeStack.size()-1].vars["x"].val);
        float y = strToFloat(scopeStack[scopeStack.size()-1].vars["y"].val);
        float width = strToFloat(scopeStack[scopeStack.size()-1].vars["width"].val);
        float height = strToFloat(scopeStack[scopeStack.size()-1].vars["height"].val);
        drawRect(x,y,width,height);
        break;
    }
    case FUNC_FILL_RECT_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        float width = strToFloat(s.vars["width"].val);
        float height = strToFloat(s.vars["height"].val);
        fillRect(x,y,width,height);
        break;
    }
    case FUNC_SET_BACKGROUND_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float r = strToFloat(s.vars["r"].val);
        float g = strToFloat(s.vars["g"].val);
        float b = strToFloat(s.vars["b"].val);
        float a = strToFloat(s.vars["a"].val);
        setBackground(r,g,b,a);
        break;
    }
    case FUNC_FILL_OVAL_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float x = strToFloat(s.vars["x"].val);
        float y = strToFloat(s.vars["y"].val);
        float width = strToFloat(s.vars["width"].val);
        float height = strToFloat(s.vars["height"].val);
        float segments = strToFloat(s.vars["segments"].val);
        fillOval(x,y,width,height,segments);
        break;
    }
    case FUNC_DRAW_LINE_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float startx = strToFloat(s.vars["startx"].val);
        float starty = strToFloat(s.vars["starty"].val);
        float endx = strToFloat(s.vars["endx"].val);
        float endy = strToFloat(s.vars["endy"].val);
        drawLine(startx,starty,endx,endy);
        break;
    }
    case FUNC_SET_LINE_WEIGHT_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float w = strToFloat(s.vars["weight"].val);
        setLineWeight(w);
        break;
    }
    case FUNC_SET_COLOR_PRIM : {
        Scope s = scopeStack[scopeStack.size()-1];
        float r = strToFloat(s.vars["r"].val);
        float g = strToFloat(s.vars["g"].val);
        float b = strToFloat(s.vars["b"].val);
        setPaintColor(r,g,b);
        break;
    }
    case FUNC_CLEAR_SCREEN_PRIM : {
        clearScreen();
        break;
    }
      case FUNC_LOG : {

        Scope s = scopeStack[scopeStack.size()-1];
        string stri = s.vars["string"].val;
        //cout<<A.lexeme;

        if (noPrints>maxPrints) {
            ui->textBrowser_3->clear();
            noPrints=0;
        }
        noPrints++;

       QString str = QString::fromStdString(stri);
       ui->textBrowser_3->setTextColor(QColor(66, 150, 158));
       //ui->textBrowser_3->setText(ui->textBrowser_3->toPlainText()+str);
       ui->textBrowser_3->insertPlainText(str);
       ui->textBrowser_3->verticalScrollBar()->setValue(ui->textBrowser_3->verticalScrollBar()->maximum());
       qApp->processEvents();

        break;
      }
      case FUNC_LOG_2 : {
        //cout<<"PRINTING";
        Scope s = scopeStack[scopeStack.size()-1];
        string stri = s.vars["string"].val;

        if (noPrints>maxPrints) {
            ui->textBrowser_3->clear();
            noPrints=0;
        }
        noPrints++;

        //cout<<A.lexeme<<"\n";
        QString str = QString::fromStdString(stri);
        if (noOfnl>0) {
            str = "\n" +str;
        }
        noOfnl++;
        ui->textBrowser_3->setTextColor(QColor(66, 150, 158));
        //ui->textBrowser_3->setText(ui->textBrowser_3->toPlainText()+str);
        //ui->textBrowser_3->append(str);
        ui->textBrowser_3->insertPlainText(str);
        ui->textBrowser_3->verticalScrollBar()->setValue(ui->textBrowser_3->verticalScrollBar()->maximum());
        qApp->processEvents();
        break;
      }
      case ACTION_ASSIGN: {
        //if (debugging) {cout<<"APPPPPPPPPPPPPPP";}
        //if (debugging) {printItems();}
        ELEMENT B = Items.back();
         if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
         else if (B.TYPE==REFL) {
             B = retrieveData(B);
         }
         if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();

        if (A.TYPE==IDENTIFIER) {
            //if (debugging) {logAllVariables(scopeStack[scopeStack.size()-1]);}
            scopeVar v = searchFor(A,ui);
            if (failedSoFar) {break;}
            //if (debugging) {cout<<"APPPPPPPPPPPPPPP";}
            storeVariable(A.lexeme,B,v.tableIndex);
            //if (debugging) {cout<<"\nSTORED IN TABLE INDEX: "<<v.tableIndex<< " : "<<A.lexeme<<"::"<<B.lexeme;}
            //if (debugging) {logAllVariables(scopeStack[v.tableIndex]);}
            //if (debugging) {cout<<"\nSTORING "<<A.lexeme<<" = "<<B.lexeme<<"\n"<<std::flush;}
            VARIABLE C = scopeStack[v.tableIndex].vars[A.lexeme];

//            if(C.T==DATAL) {
//                printList(C);
//            }

        }
        else if (A.TYPE==REFL) {
            Items.pop_back();
            ELEMENT AR = Items.back();
            scopeVar v = searchFor(AR,ui);
            ELEMENT ARR = v.T;
            if (failedSoFar) {break;}
            if (ARR.TYPE!=DATAL) {
                cout<< "\nOperation error on line " << ARR.lineNo <<" column "<< ARR.column <<" : Attempt to index from non list '"<<ARR.lexeme<<"'"<<std::flush;
                oss<< "\nOperation error on line " << ARR.lineNo <<" column "<< ARR.column <<" : Attempt to index from non list '"<<ARR.lexeme<<"'"<<std::flush;
                showError(ui, oss.str());
                failedSoFar=true;break;
            }
            //cout<<"MAKING: "<<AR.lexeme<<flush;
            //printListE(A);
            int size = A.list.size();
            int i = 1;

//            int asas = 12;
//            int* saas = &asas;
//            *saas = 4;
//            cout<<"ANSWEE:  "<<asas<<flush;
            if (size==0) {
                cout<<"\nError on line "<< A.lineNo<<" column "<<  A.column<<": ZERRO SIZE, got "<<tokenToString(A.NAME);
                oss<<"\nError on line "<<A.lineNo<<" column "<<  A.column<<": Expecting expression, got ']'";
                showError(ui, oss.str());
                failedSoFar=true;
            }


            ELEMENT* RES;
            int index = (int)strToFloat(A.list[0].lexeme);
            int s = scopeStack[v.tableIndex].vars[AR.lexeme].list.size();
            if (index>=s || index<0) {
                //cout<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": ZERRO SIZE, got "<<tokenToString(STORE.NAME);
                oss<<"\nError on line "<<A.list[0].lineNo<<" column "<<A.list[0].column<<": list indexing is out of bounds by "<<index-s+1;
                showError(ui, oss.str());
                failedSoFar=true;break;
            }

            RES = &(scopeStack[v.tableIndex].vars[AR.lexeme].list[index]);
            ELEMENT* STORE = RES;
           // cout<<"SIZE: "<<size;
            while(i<size) {
                index = (int)strToFloat(A.list[i].lexeme);
                //cout<<"::: is " <<index <<" more than "<< STORE->list.size()<<flush;
                s = STORE->list.size();
                if (index>=s || index<0) {
                    //cout<<"\nError on line "<< STORE.lineNo<<" column "<<  STORE.column<<": ZERRO SIZE, got "<<tokenToString(STORE.NAME);
                    oss<<"\nError on line "<<A.list[i].lineNo<<" column "<<A.list[i].column<<": list indexing is out of bounds by "<<index-s+1;
                    showError(ui, oss.str());
                    failedSoFar=true;break;
                }
                RES = &(STORE->list.at(index));
                STORE = &(STORE->list.at(index));
                i++;
            }


             // cout<<"dfdf"; printList(scopeStack[v.tableIndex].vars[AR.lexeme]); cout<<"dfdf";
           // scopeStack[v.tableIndex].vars[AR.lexeme].list[(int)strToFloat(A.list[0].lexeme)]=B;
              *RES = B;
           // cout<<"INTO "<<B.lexeme<<flush;
        }
        else {
            cout<<"\nError on line "<< A.lineNo<<" column "<< A.column<<": Expecting an identifier, got "<<tokenToString(A.NAME);
            oss<<"\nError on line "<< A.lineNo<<" column "<< A.column<<": Expecting an identifier, got "<<tokenToString(A.NAME);
            showError(ui, oss.str());
            failedSoFar=true;break;
        }

        break;
      }
      case ACTION_POS : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        if(!typeCheck(ACT,B)) {
          cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
          oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }
            ELEMENT T = {CONSTANT, CONST_K, B.lexeme, B.lineNo, B.column, EMPTYL};
        //if (debugging) {cout<<"\n + "<<T.lexeme<<" = "<<T.lexeme<<"\n" <<std::flush;}
        Items.pop_back();
        Items.push_back(T);
        break;
      }
      case ACTION_NEG : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        if(!typeCheck(ACT,B)) {
          cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
          oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }

        ELEMENT T = {CONSTANT, CONST_K, convToString(strToFloat(B.lexeme)*-1), B.lineNo, B.column, EMPTYL};
        //if (debugging) {cout<<"\n + "<<T.lexeme<<" = "<<T.lexeme<<"\n" <<std::flush;}
        Items.pop_back();
        Items.push_back(T);
        break;
        }
        case ACTION_PLUS_ASS : {
          ELEMENT B = Items.back();
          Items.pop_back();
          ELEMENT A = Items.back();
          scopeVar MASK;

          if (A.TYPE==IDENTIFIER || A.TYPE==DATAL ) {MASK = searchFor(A,ui);if (failedSoFar) {break;}}
          else {
            cout<< "\nOperatidon error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
            oss<< "\nOperatidon error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
            showError(ui, oss.str());
            failedSoFar=true;break;
          }
          if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
          else if (B.TYPE==REFL) {
              B = retrieveData(B);
          }
          if (failedSoFar) {break;}

          if (MASK.T.TYPE==DATAL) {
             scopeStack[MASK.tableIndex].vars[A.lexeme].list.push_back(B);
             break;
          }

          if(!typeCheck(MASK.T,ACT,B)) {
            cout<< "\nOpseration error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
            oss<< "\nOpseration error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
            showError(ui, oss.str());
            failedSoFar=true;break;
          }
          scopeStack[MASK.tableIndex].vars[A.lexeme].val=convToString(strToFloat(scopeStack[MASK.tableIndex].vars[A.lexeme].val) + strToFloat(B.lexeme));
          break;
        }
        case ACTION_SUB_ASS : {
        ELEMENT B = Items.back();
        Items.pop_back();
        ELEMENT A = Items.back();
        scopeVar MASK;

        if (A.TYPE==IDENTIFIER || A.TYPE==DATAL ) {MASK = searchFor(A,ui);if (failedSoFar) {break;}}
        else {
          cout<< "\nOperatidon error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          oss<< "\nOperatidon error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}

        if (MASK.T.TYPE==DATAL) {
           scopeStack[MASK.tableIndex].vars[A.lexeme].list.push_front(B);
           break;
        }

        if(!typeCheck(MASK.T,ACT,B)) {
          cout<< "\nOpseration error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          oss<< "\nOpseration error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
          showError(ui, oss.str());
          failedSoFar=true;break;
        }
        scopeStack[MASK.tableIndex].vars[A.lexeme].val=convToString(strToFloat(scopeStack[MASK.tableIndex].vars[A.lexeme].val) - strToFloat(B.lexeme));
        break;
        }
        case ACTION_PWR_ASS : {
          ELEMENT B = Items.back();
          Items.pop_back();
          ELEMENT A = Items.back();
          scopeVar MASK;
          if (A.TYPE==IDENTIFIER) {MASK = searchFor(A,ui); if (failedSoFar) {break;}}
          else {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
          if (failedSoFar) {break;}
          if(!typeCheck(MASK.T,ACT,B)) {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          scopeStack[MASK.tableIndex].vars[A.lexeme].val=convToString(pow(strToFloat(scopeStack[MASK.tableIndex].vars[A.lexeme].val),strToFloat(B.lexeme)));
          break;
        }
        case ACTION_DIV_ASS : {
          ELEMENT B = Items.back();
          Items.pop_back();
          ELEMENT A = Items.back();
          scopeVar MASK;
          if (A.TYPE==IDENTIFIER) {MASK = searchFor(A,ui);if (failedSoFar) {break;}}
          else {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<<B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
          if (failedSoFar) {break;}
          if(!typeCheck(MASK.T,ACT,B)) {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          scopeStack[MASK.tableIndex].vars[A.lexeme].val=convToString(strToFloat(scopeStack[MASK.tableIndex].vars[A.lexeme].val) / strToFloat(B.lexeme));
          break;
        }
        case ACTION_MUL_ASS : {
          ELEMENT B = Items.back();
          Items.pop_back();
          ELEMENT A = Items.back();
          scopeVar MASK;
          if (A.TYPE==IDENTIFIER) {MASK = searchFor(A,ui);if (failedSoFar) {break;}}
          else {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
          if (failedSoFar) {break;}
          if(!typeCheck(MASK.T,ACT,B)) {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }
          scopeStack[MASK.tableIndex].vars[A.lexeme].val=convToString(strToFloat(scopeStack[MASK.tableIndex].vars[A.lexeme].val) * strToFloat(B.lexeme));
          break;
        }
        case ACTION_DIV: {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}

          float a=strToFloat(A.lexeme);
          float b=strToFloat(B.lexeme);

          if(!typeCheck(A,ACT,B)) {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }

            ELEMENT T = {CONSTANT, CONST_K, convToString(a/b), B.lineNo, B.column, EMPTYL};
            //if (debugging) {cout<< a<<" / "<<b<<" = "<<a/b<<"\n" <<std::flush;}
            Items.pop_back();
            Items.push_back(T);
          break;
        }
        case ACTION_SUB: {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}

          float a=strToFloat(A.lexeme);
          float b=strToFloat(B.lexeme);

          if(!typeCheck(A,ACT,B)) {
              cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
              showError(ui, oss.str());
              failedSoFar=true;break;
          }

            ELEMENT T = {CONSTANT, CONST_K, convToString(a-b), B.lineNo, B.column, EMPTYL};
            //if (debugging) {cout<<a<<" - "<<b<<" = "<<a-b<<"\n" <<std::flush;}
            Items.pop_back();
            Items.push_back(T);

          break;
         }
         case ACTION_NOT : {
           ELEMENT B = Items.back();
           if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
           else if (B.TYPE==REFL) {
               B = retrieveData(B);
           }
           if (failedSoFar) {break;}
           if(!typeCheck(ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " with " <<typeToString(B.TYPE)<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           TOKENS Truth;
           if (B.NAME==FALSE_K) {
             Truth = TRUE_K;
           }
           else {
             Truth = FALSE_K;
           }
          ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};
          Items.pop_back();
          Items.push_back(T);
          break;
         }
         case ACTION_LOR : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
            TOKENS Truth = orV(A,B);
             ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};
             Items.pop_back();
            Items.push_back(T);

           break;
         }
         case ACTION_LAND : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           TOKENS Truth = andV(A,B);
            ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};
            Items.pop_back();
            Items.push_back(T);
           break;
         }
         case ACTION_IS_EQ : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
              TOKENS Truth;

              if (A.TYPE==CONSTANT && B.TYPE==CONSTANT) {
                  if (strToFloat(A.lexeme)==strToFloat(B.lexeme)) {
                      Truth = TRUE_K;
                  }
                  else {
                      Truth = FALSE_K;
                  }
              }
                else if (A.lexeme==B.lexeme) {
                    Truth = TRUE_K;
                }
                else {
                    Truth = FALSE_K;
                }
             ELEMENT T = {BOOL_LITERAL,Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};
             Items.pop_back();
            Items.push_back(T);

           break;
         }
         case ACTION_NOT_EQ : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           TOKENS Truth;
           if (A.lexeme!=B.lexeme) {
               Truth = TRUE_K;
           }
           else {
               Truth = FALSE_K;
           }
          ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};
          Items.pop_back();
          Items.push_back(T);

           break;
         }
         case ACTION_POW : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
            float b=strToFloat(B.lexeme);

            ELEMENT T = {CONSTANT, CONST_K, convToString(pow(a,b)), B.lineNo, B.column, EMPTYL};

            Items.pop_back();
            Items.push_back(T);

           break;
         }
         case ACTION_MOD : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
             float b=strToFloat(B.lexeme);

             ELEMENT T = {CONSTANT, CONST_K, convToString(fmod(a,b)), B.lineNo, B.column, EMPTYL};

             Items.pop_back();
             Items.push_back(T);

           break;
         }
         case ACTION_GT : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
             float b=strToFloat(B.lexeme);

             TOKENS Truth;
             if (a>b) {
                 Truth = TRUE_K;
             }
             else {
                 Truth = FALSE_K;
             }
            ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};

             Items.pop_back();
             Items.push_back(T);

           break;
         }
         case ACTION_LT : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
             float b=strToFloat(B.lexeme);

             TOKENS Truth;
             if (a<b){
                 Truth = TRUE_K;
             }
             else {
                 Truth = FALSE_K;
             }
            ELEMENT T = {BOOL_LITERAL,  Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};

             Items.pop_back();
             Items.push_back(T);

           break;
         }
         case ACTION_LTE : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
             float b=strToFloat(B.lexeme);

             TOKENS Truth;
             if (a<=b) {
                 Truth = TRUE_K;
             }
             else {
                 Truth = FALSE_K;
             }
            ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};

             Items.pop_back();
             Items.push_back(T);

           break;
         }
         case ACTION_GTE : {
        ELEMENT B = Items.back();
        if (B.TYPE==IDENTIFIER) {B = searchFor(B,ui).T;}
        else if (B.TYPE==REFL) {
            B = retrieveData(B);
        }
        if (failedSoFar) {break;}
        Items.pop_back();
        ELEMENT A = Items.back();
        if (A.TYPE==IDENTIFIER) {A = searchFor(A,ui).T;}
        else if (A.TYPE==REFL) {
            A = retrieveData(A);
        }
        if (failedSoFar) {break;}
           if(!typeCheck(A,ACT,B)) {
             cout<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             oss<< "\nOperation error on line " << B.lineNo <<" column "<< B.column <<" : Attempt to "<<tokenToString(ACT)<< " a " << typeToString(A.TYPE)<<"("<<A.lexeme<<")"<< " and " << typeToString(B.TYPE)<<"("<<B.lexeme<<")"<< std::flush;
             showError(ui, oss.str());
             failedSoFar=true;break;
           }
           float a=strToFloat(A.lexeme);
             float b=strToFloat(B.lexeme);

             TOKENS Truth;
             if (a>=b) {
                 Truth = TRUE_K;
             }
             else {
                 Truth = FALSE_K;
             }
            ELEMENT T = {BOOL_LITERAL, Truth, tokenToString(Truth),  B.lineNo, B.column, EMPTYL};

             Items.pop_back();
             Items.push_back(T);

           break;
         }
         case ACTION_POST_INC : {
           ELEMENT B = Items.back();
           Items.pop_back();
           scopeVar v = checkCanInc(B, ACT,ui);
           if (failedSoFar) {break;}
           string valuePOST = scopeStack[v.tableIndex].vars[B.lexeme].val;
           ELEMENT T = {CONSTANT, CONST_K, valuePOST, B.lineNo, B.column, EMPTYL};
           Items.push_back(T);
           scopeStack[v.tableIndex].vars[B.lexeme].val=convToString(strToFloat(valuePOST)+1);
           break;
         }
         case ACTION_POST_DEC : {
           ELEMENT B = Items.back();
           Items.pop_back();
           scopeVar v = checkCanInc(B, ACT, ui);
           if (failedSoFar) {break;}
           string valuePOST = scopeStack[v.tableIndex].vars[B.lexeme].val;
           ELEMENT T = {CONSTANT, CONST_K, valuePOST, B.lineNo, B.column, EMPTYL};
           Items.push_back(T);
           scopeStack[v.tableIndex].vars[B.lexeme].val=convToString(strToFloat(valuePOST)-1);
           break;
         }
         case ACTION_PRE_INC : {
           ELEMENT B = Items.back();
           Items.pop_back();
           scopeVar v = checkCanInc(B, ACT,ui);
           if (failedSoFar) {break;}
           string valuePRE = scopeStack[v.tableIndex].vars[B.lexeme].val;
           string updatedValue = convToString(strToFloat(valuePRE)+1);
           ELEMENT T = {CONSTANT, CONST_K, updatedValue, B.lineNo, B.column, EMPTYL};
           Items.push_back(T);
           scopeStack[v.tableIndex].vars[B.lexeme].val=updatedValue;
           break;
         }
         case ACTION_PRE_DEC : {
           ELEMENT B = Items.back();
           Items.pop_back();
           scopeVar v = checkCanInc(B, ACT,ui);
           if (failedSoFar) {break;}
           string valuePRE = scopeStack[v.tableIndex].vars[B.lexeme].val;
           string updatedValue = convToString(strToFloat(valuePRE)-1);
           ELEMENT T = {CONSTANT, CONST_K, updatedValue, B.lineNo, B.column, EMPTYL};
           Items.push_back(T);
           scopeStack[v.tableIndex].vars[B.lexeme].val=updatedValue;
           break;
         }
    }

    //if (debugging) {cout<<"\n TOP OF STACK -->> "<< Items.back().lexeme <<std::flush;}

  }
}


  // for (std::map<int,instruction>::iterator it=function_instructions.begin(); it!=function_instructions.end(); ++it) {
  //   std::cout << "\n[ funcinstruction: " << it->first << " : " << tokenToString(it->second.i) <<" : "<< (it->second.a.lexeme) <<" : "<< (it->second.b.lexeme) <<']'<<std::flush;
  //   int InstrucitonID = it->first;
  //   INSTRUCTION i = it->second.i;
  // }
  //
  // for (std::map<int,instruction>::iterator it=instructions.begin(); it!=instructions.end(); ++it) {
  //   std::cout << "\n[ instruction: " << it->first << " : " << tokenToString(it->second.i) <<" : "<< (it->second.a.lexeme) <<" : "<< (it->second.b.lexeme) <<']'<<std::flush;
  //   int InstrucitonID = it->first;
  //   string name = it->second.a.lexeme;
  //   INSTRUCTION i = it->second.i;
  // }
      ELEMENT NUL = {CONSTANT, NULLT, "EMPTYL", -1,-1,EMPTYL};
      qApp->processEvents();
      //scopeStack.pop_back();
      //logInstructions();
  return NUL;
}

void doSetup() {
    if (!STOP) {
        if (!failedSoFar) {
            //cout<<"PREPARIONG CANVAS";
            std::unordered_map<string, VARIABLE> nScope;
            Scope newScope = {nScope};
            scopeStack.push_back(newScope);
            interpret(functions["prepare"]);
            //cout<<"\nSIZE::: "<<Items.size();
            Items.clear();
            //cout<<"\nSCOPE STACK::: "<<scopeStack.size();
            scopeStack.pop_back();
        }

    }else {
        scopeStack.clear();
    }
    qApp->processEvents();
}

bool callLeftButton=false;
bool callLeftButtonR=false;


void callLeftButtonPress() {
    callLeftButton=true;


}

void callLeftButtonRelease() {
    callLeftButtonR=true;
}


void doInterpret() {

    if (!STOP) {

        if (!failedSoFar) {
            if (reachedEnd) {

                if(!prepared) {
                    doSetup();
                    prepared=true;
                }

                std::unordered_map<string, VARIABLE> nScope;
                Scope newScope = {nScope};
                scopeStack.push_back(newScope);
                interpret(functions["render"]);
                //cout<<"\nSIZE::: "<<Items.size();
                Items.clear();
               // cout<<"\nSCOPE STACK::: "<<scopeStack.size();
                scopeStack.pop_back();
                if (callLeftButton) {
                    std::unordered_map<string, VARIABLE> nScope;
                    Scope newScope = {nScope};
                    scopeStack.push_back(newScope);
                    interpret(functions["leftMousePress"]);
                    scopeStack.pop_back();
                    callLeftButton=false;
                }
                if (callLeftButtonR) {
                    std::unordered_map<string, VARIABLE> nScope;
                    Scope newScope = {nScope};
                    scopeStack.push_back(newScope);
                    interpret(functions["leftMouseRelease"]);
                    scopeStack.pop_back();
                    callLeftButtonR=false;
                }

            }
        }
        else {

            scopeStack.clear();
        }


    }

    qApp->processEvents();
}

void addDimensions(int w, int h) {
    deque<ELEMENT> l;
    scope.vars["WIDTH"] = {convToString(w), CONSTANT, CONST_K, -1,-1, l};
    scope.vars["HEIGHT"] = {convToString(h), CONSTANT, CONST_K, -1,-1, l};
}
