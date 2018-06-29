#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_toolButton_clicked();
    void on_plainTextEdit_blockCountChanged(int newBlockCount);
    void mousePressEvent(QMouseEvent* eventPress);
    void mouseReleaseEvent(QMouseEvent* eventPress) ;
    void on_toolButton_5_released();
    void resizeEvent(QResizeEvent* event);

    void mouseMoveEvent(QMouseEvent* event);
    void on_textBrowser_3_textChanged();

    void on_plainTextEdit_textChanged();

    void on_toolButton_10_released();

    void on_toolButton_11_released();

private:
    Ui::MainWindow *ui;
};

#endif
