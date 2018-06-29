/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include <zefopengl.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QToolButton *toolButton;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QFrame *line;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QToolButton *toolButton_9;
    MyGLWidget *widget;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_2;
    QLabel *label_5;
    QFrame *line_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_10;
    QToolButton *toolButton_10;
    QLabel *label_11;
    QToolButton *toolButton_11;
    QLabel *label_9;
    QTextBrowser *textBrowser_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(1600, 900);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setMouseTracking(true);
        MainWindow->setTabletTracking(true);
        QIcon icon;
        icon.addFile(QStringLiteral("zefLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(1);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(0,0,0);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        centralWidget->setTabletTracking(true);
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(0, 0, 51, 29));
        toolButton->setCursor(QCursor(Qt::ArrowCursor));
        toolButton->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        toolButton_4 = new QToolButton(centralWidget);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setGeometry(QRect(100, 0, 71, 29));
        toolButton_4->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_4->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        toolButton_5 = new QToolButton(centralWidget);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        toolButton_5->setGeometry(QRect(170, 0, 51, 29));
        toolButton_5->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_5->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        toolButton_6 = new QToolButton(centralWidget);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        toolButton_6->setGeometry(QRect(50, 0, 51, 29));
        toolButton_6->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_6->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        toolButton_7 = new QToolButton(centralWidget);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));
        toolButton_7->setGeometry(QRect(270, 0, 51, 29));
        toolButton_7->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_7->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(630, 650, 971, 31));
        line->setStyleSheet(QStringLiteral("background-color: rgb(5,5,5);"));
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(0, 60, 41, 838));
        textBrowser_2->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(20,20,20);\n"
"font:8pt \"Verdana\";\n"
"margin-top: 0px;"));
        textBrowser_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_3 = new QTextBrowser(centralWidget);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(630, 670, 971, 228));
        textBrowser_3->setBaseSize(QSize(0, 0));
        textBrowser_3->setMouseTracking(true);
        textBrowser_3->setFocusPolicy(Qt::StrongFocus);
        textBrowser_3->setStyleSheet(QLatin1String("background-color: rgb(5,5,5);\n"
"border-style:none;\n"
"border-width:0px;\n"
"color: rgb(66, 150, 158);\n"
"padding-left:15px;\n"
"padding-top:5px;\n"
"padding-bottom:10px;\n"
"\n"
" "));
        textBrowser_3->setFrameShadow(QFrame::Sunken);
        textBrowser_3->setCursorWidth(1);
        textBrowser_3->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        toolButton_9 = new QToolButton(centralWidget);
        toolButton_9->setObjectName(QStringLiteral("toolButton_9"));
        toolButton_9->setGeometry(QRect(320, 0, 51, 29));
        toolButton_9->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_9->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(630, 60, 2000, 971));
        widget->setMouseTracking(true);
        widget->setTabletTracking(true);
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(40, 60, 591, 838));
        plainTextEdit->setStyleSheet(QLatin1String("background-color: rgb(13,13,13);\n"
"font: 8pt \"Verdana\";\n"
"color: rgb(60,60,60);\n"
"border-style:none;\n"
"padding-left:5px;\n"
"padding-bottom:5px;\n"
""));
        plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        plainTextEdit->setTabStopDistance(20);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 30, 641, 27));
        label_2->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(13,13,13);"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 0, 1601, 20));
        label_5->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(13,13,13);"));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 5, 1601, 51));
        line_2->setStyleSheet(QStringLiteral("background-color: rgb(13,13,13);"));
        line_2->setLineWidth(1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(-100, 30, 1601, 21));
        label_6->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(21, 21, 21);"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(640, 30, 961, 27));
        label_3->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(13,13,13);"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(-110, 40, 1711, 20));
        label_7->setStyleSheet(QStringLiteral("background-color: rgb(20,20,20);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(631, 650, 171, 21));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setStyleSheet(QLatin1String("color: rgb(255, 210, 210);\n"
"background-color: rgb(184, 59, 47);\n"
"border-style:none;"));
        label->setInputMethodHints(Qt::ImhNone);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(0, 30, 40, 31));
        label_10->setStyleSheet(QLatin1String("background-color: rgb(20,20,20);\n"
"border-style: none;"));
        toolButton_10 = new QToolButton(centralWidget);
        toolButton_10->setObjectName(QStringLiteral("toolButton_10"));
        toolButton_10->setGeometry(QRect(120, 33, 61, 20));
        toolButton_10->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_10->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(110, 40, 8, 8));
        toolButton_11 = new QToolButton(centralWidget);
        toolButton_11->setObjectName(QStringLiteral("toolButton_11"));
        toolButton_11->setGeometry(QRect(220, 0, 51, 29));
        toolButton_11->setCursor(QCursor(Qt::ArrowCursor));
        toolButton_11->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(66, 150, 158);\n"
"background-color: rgb(13,13,13);"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(631, 649, 971, 6));
        label_9->setStyleSheet(QLatin1String("border-style:none;\n"
"background-color: rgb(184, 59, 47);"));
        textBrowser_4 = new QTextBrowser(centralWidget);
        textBrowser_4->setObjectName(QStringLiteral("textBrowser_4"));
        textBrowser_4->setGeometry(QRect(0, 897, 1621, 3));
        textBrowser_4->setStyleSheet(QLatin1String("border-style:none;\n"
"color: rgb(184, 59, 47);\n"
"background-color: rgb(20,20,20);\n"
"font:8pt \"Verdana\";\n"
"margin-top: 0px;"));
        textBrowser_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        MainWindow->setCentralWidget(centralWidget);
        label_5->raise();
        line_2->raise();
        label_7->raise();
        label_6->raise();
        toolButton_5->raise();
        toolButton->raise();
        toolButton_9->raise();
        toolButton_6->raise();
        toolButton_7->raise();
        toolButton_4->raise();
        widget->raise();
        label_2->raise();
        label_3->raise();
        textBrowser_2->raise();
        textBrowser_3->raise();
        line->raise();
        plainTextEdit->raise();
        label_10->raise();
        toolButton_10->raise();
        label_11->raise();
        toolButton_11->raise();
        label_9->raise();
        label->raise();
        textBrowser_4->raise();

        retranslateUi(MainWindow);
        QObject::connect(toolButton_9, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "zef IDE", nullptr));
        toolButton->setText(QApplication::translate("MainWindow", "Open", nullptr));
        toolButton_4->setText(QApplication::translate("MainWindow", "Save as", nullptr));
        toolButton_5->setText(QApplication::translate("MainWindow", "Run", nullptr));
        toolButton_6->setText(QApplication::translate("MainWindow", "Save", nullptr));
        toolButton_7->setText(QApplication::translate("MainWindow", "Debug", nullptr));
        toolButton_9->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        plainTextEdit->setPlainText(QString());
        label_2->setText(QApplication::translate("MainWindow", "                 Editor", nullptr));
        label_5->setText(QString());
        label_6->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Canvas", nullptr));
        label_7->setText(QString());
        label->setText(QApplication::translate("MainWindow", "      Console   ", nullptr));
        label_10->setText(QString());
        toolButton_10->setText(QApplication::translate("MainWindow", "Toggle Live", nullptr));
        label_11->setText(QString());
        toolButton_11->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
