#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <QTextDocument>
#include "QKeyEvent"
#include "QWheelEvent"
#include <QtWidgets>
#include <string.h>
#include "QResizeEvent"
#include "QSize"
#include "QScrollBar"
#include "../../Syntax_Analysis/Parser.h"
#include "zefopengl.h"

float incre=0;
bool liveMode = true;

int canvasHeight;
int canvasWidth;

int mousex=0;
int mousey=0;

void goback();
void resetCalls();
void callLeftButtonPress();
void callLeftButtonRelease();
void setCurrent(int w, int h, float t);

bool running=false;
int currentHeight = 0;
int currentWidth = 0;
int oldgldim;

int currentDimw;
int currentDimh;

int originalPTWidth = 0;
int originalPTHeight = 0;
bool pastSep = false;

int calculateCanvasWidth(Ui::MainWindow* ui) {
return ui->label_9->geometry().width();

}

int calculateCanvasHeight(Ui::MainWindow* ui) {
    return ui->label->geometry().y() - 60;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{



    setStyleSheet(QString::fromUtf8(
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
        "QScrollBar:vertical {"
        "    border: 0px solid #999999;"
        "    background-color:rgba(0,0,0,0);"
        "    width:9px;    "
        "    margin: 0px 5px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47), stop:1 rgb(184, 59, 47));"
        "    min-height: 10px;"
        "}"
        "QScrollBar::add-line:vertical {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47),  stop:1 rgb(184, 59, 47));"
        "    height: 0px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:vertical {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0  rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47),  stop:1 rgb(184, 59, 47));"
        "    height: 0 px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal{"
        "    background: none;"
        "}"
        "QScrollBar:horizontal {"
        "    border: 0px solid #999999;"
        "    background-color:rgba(0,0,0,0);"
        "    height:4px;    "
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47), stop:1 rgb(184, 59, 47));"
        "    min-height: 0px;"
        "}"
        "QScrollBar::add-line:horizontal {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0 rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47),  stop:1 rgb(184, 59, 47));"
        "    height: 0px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "}"
        "QScrollBar::sub-line:horizontal {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "    stop: 0  rgb(184, 59, 47), stop: 0.5 rgb(184, 59, 47),  stop:1 rgb(184, 59, 47));"
        "    height: 0 px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "}"
        ));


    ui->setupUi(this);
    ui->label_11->setStyleSheet(QString::fromUtf8(
                                    "    background-color: rgb(130, 232, 100);"
                                    ));
    //int canvasWidth = ui->label_4->geometry().width()-18;
   // int canvasHeight = ui->label_4->geometry().height()-18;
    initializeElements(ui);

    canvasWidth = calculateCanvasWidth(ui);
    canvasHeight = calculateCanvasHeight(ui);

   string canvasText =  "    Canvas " + to_string(canvasWidth) + " x " + to_string(canvasHeight);
   QString QcanvasText = QString::fromStdString(canvasText);
    ui->textBrowser_2->setAlignment(Qt::AlignRight);
    ui->label_3->setText(QcanvasText);
        std::string code ("");
        string txt;
        int size = 0;
        ifstream file("script.zef");
        int lNumber=0;
        if (file.is_open()) {
             while (file.good()) {
                 getline(file, txt);
                    code+=txt;
                    size+=txt.size();
                    code+="\n";
                    lNumber++;
                  }
            }
        file.close();
        //collectTokens("script", ui);

    currentDimw = 1600;
    currentDimh = 900;
    oldgldim = 971;

    //cout<<currentDimh;

    if (size>0) {
        QString str = QString::fromStdString(code);
        ui->plainTextEdit->appendPlainText(str);
        //setWindowFlags(Qt::FramelessWindowHint);
    }


}

MainWindow::~MainWindow()
{

    delete ui;
}


int getmousex() {
    return mousex;
}

int getmousey() {
    return mousey;
}

void MainWindow::on_toolButton_clicked()
{

    //QString code = ui->textEdit->toPlainText();
    QString text = ui->textBrowser_3->toPlainText();
    QString code = ui->plainTextEdit->toPlainText();
    //ui->textBrowser->setText(text+ "> " +code + "LINE NO:  " + QString::number(code.split( "\n" ).size()-1));
}


void MainWindow::on_plainTextEdit_blockCountChanged(int newBlock)
{
    ui->textBrowser_2->setAlignment(Qt::AlignRight);
    //QString code = ui->plainTextEdit->toPlainText();
    QString lineNo = "";
    for(int i = 0; i<newBlock; i++) {
       lineNo.append(QString::number(i+1) +  "\n");
    }
    ui->textBrowser_2->setText(lineNo);

    //ui->textBrowser->setText("\n ypos: " + QString::number(ypos));
}

void MainWindow::on_toolButton_5_released()
{

reachedEnd=false;
failedSoFar=true;
STOP=true;
        //clearScreen();
        QString code = ui->plainTextEdit->toPlainText();
        ui->textBrowser_3->clear();
        oss.str(std::string());
        clearData();
        STOP=false;
        prepared=false;
        setBackground(20,20,20,1);
        //cout<<"PARSING" << endl;
        ofstream myfile;
        myfile.open ("script.zef");
        myfile << code.toStdString();
        myfile.close();

        failedSoFar=false;
        running=true;
        reachedEnd=false;
        if (code.size()>0) {
            collectTokens("script", ui);
            //logAllTokens(ui);

            char topOfStack;
           _topOfStack = &topOfStack;
           _maxAllowedStackUsage = 14404*130;


            parse(ui);
            addPrimitiveFunctions();
            addDimensions(canvasWidth,canvasHeight);
            scopeStack.push_back(scope);
            checkRenderFunction(ui);
            checkPrepareFunction(ui);
            //logInstructions();
            //logFunctions();
            interpret(instructions);
            //logInstructions();
            reachedEnd=true;
            running=false;
            //logAllVariables(var_tab);
            //logDrawInstructions();

    }

}
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   int x = ui->plainTextEdit->geometry().x();
   int y = ui->plainTextEdit->geometry().y();
   currentWidth = event->size().width();
   currentHeight = event->size().height();
   originalPTWidth = ui->plainTextEdit->geometry().width();
   originalPTHeight = ui->plainTextEdit->geometry().height();
   ui->plainTextEdit->setGeometry(x,y,originalPTWidth,originalPTHeight+(currentHeight-currentDimh));
   //ui->textBrowser->setText(ui->textBrowser->toPlainText() + "delta width: " + (QString::number(event->size().width()-currentDimw)));
   //ui->textBrowser->setText(ui->textBrowser->toPlainText() + "\ndelta height: " + (QString::number(event->size().height()-currentDimh)));
  //  event->size().scale(QSize(10,10), Qt::KeepAspectRatio);





   x = ui->textBrowser_2->geometry().x();
   y = ui->textBrowser_2->geometry().y();
   //currentWidth = event->size().width();
   int originaltxB2Height = ui->textBrowser_2->geometry().height();
   int originaltxB2Width = ui->textBrowser_2->geometry().width();
   ui->textBrowser_2->setGeometry(x,y,originaltxB2Width,originaltxB2Height+(currentHeight-currentDimh));

   int consolex=ui->textBrowser_3->geometry().x();
   int consoley=ui->textBrowser_3->geometry().y();
   int consoleWidth = ui->textBrowser_3->geometry().width();
   int consoleHeight = ui->textBrowser_3->geometry().height();
   ui->textBrowser_3->setGeometry(consolex,consoley+(currentHeight-currentDimh),consoleWidth+(currentWidth-currentDimw),consoleHeight);


   int bpaddingx=ui->textBrowser_4->geometry().x();
   int bpaddingy=ui->textBrowser_4->geometry().y();
   int bpaddingWidth = ui->textBrowser_4->geometry().width();
   int bpaddingHeight = ui->textBrowser_4->geometry().height();
   ui->textBrowser_4->setGeometry(bpaddingx,bpaddingy+(currentHeight-currentDimh),bpaddingWidth+(currentWidth-currentDimw),bpaddingHeight);


   int linex=ui->line->geometry().x();
   int liney=ui->line->geometry().y();
   int lineWidth = ui->line->geometry().width();
   int lineHeight = ui->line->geometry().height();
   ui->line->setGeometry(linex,liney+(currentHeight-currentDimh),lineWidth+(currentWidth-currentDimw),lineHeight);

   int line2x=ui->line_2->geometry().x();
   int line2y=ui->line_2->geometry().y();
   int line2Width = ui->line_2->geometry().width();
   int line2Height = ui->line_2->geometry().height();
   ui->line_2->setGeometry(line2x,line2y,line2Width+(currentWidth-currentDimw),line2Height);

   int label7x=ui->label_7->geometry().x();
   int label7y=ui->label_7->geometry().y();
   int label7Width = ui->label_7->geometry().width();
   int label7Height = ui->label_7->geometry().height();
   ui->label_7->setGeometry(label7x,label7y,label7Width+(currentWidth-currentDimw),label7Height);


   int label3x=ui->label_3->geometry().x();
   int label3y=ui->label_3->geometry().y();
   int label3Width = ui->label_3->geometry().width();
   int label3Height = ui->label_3->geometry().height();
   ui->label_3->setGeometry(label3x,label3y,label3Width+(currentWidth-currentDimw),label3Height);


   int label5x=ui->label_5->geometry().x();
   int label5y=ui->label_5->geometry().y();
   int label5Width = ui->label_5->geometry().width();
   int label5Height = ui->label_5->geometry().height();
   ui->label_5->setGeometry(label5x,label5y,label5Width+(currentWidth-currentDimw),label5Height);


   int labelx=ui->label->geometry().x();
   int labely=ui->label->geometry().y();
   int labelWidth = ui->label->geometry().width();
   int labelHeight = ui->label->geometry().height();
   ui->label->setGeometry(labelx,labely+(currentHeight-currentDimh),labelWidth,labelHeight);

   int label9x=ui->label_9->geometry().x();
   int label9y=ui->label_9->geometry().y();
   int label9Width = ui->label_9->geometry().width();
   int label9Height = ui->label_9->geometry().height();
   ui->label_9->setGeometry(label9x,label9y+(currentHeight-currentDimh),label9Width+(currentWidth-currentDimw),label9Height);



   int widgetx=ui->widget->geometry().x();
   int widgety=ui->widget->geometry().y();
   int widgetWidth = ui->widget->geometry().width();
   int widgetHeight = ui->widget->geometry().height();

   int scaleInc;

   if (currentHeight-currentDimh>currentWidth-currentDimw) {
       scaleInc=currentHeight-currentDimh;
   }else {
       scaleInc=currentWidth-currentDimw;
   }
   //setCurrent(widgetWidth+(scaleInc),widgetHeight+(scaleInc),scaleInc);
  // ui->widget->setGeometry(widgetx,widgety,widgetWidth+(scaleInc),widgetHeight+(scaleInc));


   //ui->textBrowser_3->append(QString::fromStdString(to_string(scaleInc)));

   currentDimh=currentHeight;
   currentDimw=currentWidth;

   canvasWidth = calculateCanvasWidth(ui);
   canvasHeight = calculateCanvasHeight(ui);

   string canvasText =  "    Canvas " + to_string(canvasWidth) + " x " + to_string(canvasHeight);
   QString QcanvasText = QString::fromStdString(canvasText);
   ui->label_3->setText(QcanvasText);

   addDimensions(canvasWidth,canvasHeight);
}

void MainWindow::on_textBrowser_3_textChanged()
{

}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    setMouseTracking(true);
    int x = event->pos().x();
    int y = event->pos().y();

    x=x-ui->plainTextEdit->geometry().width()-ui->textBrowser_2->geometry().width();

    y=y-ui->widget->geometry().y();

    mousex=x;
    mousey=y;
}

void MainWindow::on_plainTextEdit_textChanged()
{

    STOP=true;
    reachedEnd=false;
    if (liveMode) {
        QString code = ui->plainTextEdit->toPlainText();
        if(code.size()>0) {

            QChar currentChar;
            if (ui->plainTextEdit->textCursor().position()==0) {
                currentChar = ui->plainTextEdit->toPlainText().at(0);
            }else {
                currentChar = ui->plainTextEdit->toPlainText().at(ui->plainTextEdit->textCursor().position()-1);
            }

            QString s = "";
            s+=currentChar;
            failedSoFar=true;
            if (!running&&s!="\n"&&s!=" "&&s!="\t") {

                //clearScreen();
                setBackground(20,20,20,1);
                QString code = ui->plainTextEdit->toPlainText();
                ui->textBrowser_3->clear();
                oss.str(std::string());
                clearData();
                STOP=false;
               // cout<<"PARSING" << endl;
                ofstream myfile;
                myfile.open ("script.zef");
                myfile << code.toStdString();
                myfile.close();
                prepared=false;
                failedSoFar=false;
                running=true;

                if (code.size()>0) {
                    collectTokens("script", ui);
                    //logAllTokens(ui);

                    char topOfStack;
                   _topOfStack = &topOfStack;
                   _maxAllowedStackUsage = 14404*130;


                    parse(ui);
                    addPrimitiveFunctions();
                    addDimensions(canvasWidth,canvasHeight);
                    scopeStack.push_back(scope);
                    checkRenderFunction(ui);
                    checkPrepareFunction(ui);
                    //logInstructions();
                    //logFunctions();
                    interpret(instructions);
                    //logInstructions();
                    reachedEnd=true;
                    running=false;
                    //logAllVariables(var_tab);
                    }

            }
         }
    }


}

void MainWindow::mousePressEvent(QMouseEvent *eventPress) {
    if (eventPress->button()==Qt::LeftButton) {
       callLeftButtonPress();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *eventPress) {
    if (eventPress->button()==Qt::LeftButton) {
       callLeftButtonRelease();
    }
}

void MainWindow::on_toolButton_10_released()
{
    liveMode^=true;
    if (liveMode) {
        ui->label_11->setStyleSheet(QString::fromUtf8(
                                        "    background-color: rgb(130, 232, 100);"
                                        ));
    }
    else {
        ui->label_11->setStyleSheet(QString::fromUtf8(
                                        "   background-color: rgb(184, 59, 47);"
                                        ));
    }

}

void MainWindow::on_toolButton_11_released()
{
    STOP=true;
    reachedEnd=false;
    clearData();
    //clearScreen();
    resetCalls();
    setBackground(20,20,20,1);
    setPaintColor(255,255,255);
    setLineWeight(1);
    running=false;
}

