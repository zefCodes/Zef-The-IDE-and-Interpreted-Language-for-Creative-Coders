#ifndef ZEFOPENGL_H
#define ZEFOPENGL_H

#include <QGLWidget>


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    void draw();

};



#endif // ZEFOPENGL_H
