// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <unistd.h>
#include <omp.h>
#include <math.h>
#include "zefopengl.h"

void doInterpret();
void doSetup();

int WIDTH;
int HEIGHT;
int calls = 0;
float xdf = 0.7;
int draws=0;
float xLOCA=0;
float transInc=0;

int currentW;
int currentH;

const float DEG2RAD = 3.14159/180;

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}

MyGLWidget::~MyGLWidget()
{

}
void setPaintColor(float r, float g, float b) {
    glColor3f(r/255.0, g/255.0, b/255.0);
}

void drawArc(float x, float y, float radius1, float radius2, float start, float end, float segments)
{

    if (segments<1) {
        segments=1;
    }
    //std::cout<<"OVVAALL "<<x<<"||"<<y<<"||"<<radius1<<"||"<<radius2<<"||"<<segments<<"\n";
    glTranslatef(-1,(float)transInc/WIDTH,0);
    y-=485;
    x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_LINE_STRIP);
    radius1=(radius1/WIDTH)*2;
    radius2=(radius2/HEIGHT)*2;



   for (int i=start; i < end; i+=end/segments)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius1,-sin(degInRad)*radius2);
   }

   glEnd();
   glTranslatef(1,-(float)transInc/WIDTH,0);
   glTranslatef(-xLoc*2,-yLoc*2,0);
}

void fillArc(float x, float y, float radius1, float radius2, float start, float end, float segments)
{
    glTranslatef(-1,(float)transInc/WIDTH,0);
    y-=485;
    x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_POLYGON);

    radius1=(radius1/WIDTH)*2;
    radius2=(radius2/HEIGHT)*2;

    if (segments<1) {
        segments=1;
    }

   for (int i=start; i < end; i+=  (int) (end/segments))
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius1,-sin(degInRad)*radius2);
   }

   glEnd();
   glTranslatef(1,-(float)transInc/WIDTH,0);
   glTranslatef(-xLoc*2,-yLoc*2,0);
}


void setCurrent(int w, int h, float t) {
    WIDTH=w;
    HEIGHT=h;
    transInc=t;
}

void translate(float x, float y) {
    x=(float)x/(float)WIDTH;
    y=(float)y/(float)HEIGHT;
    glTranslatef(x*2,-y*2,0);
}

void scale(float x, float y) {
    glScalef(x,y,0);
}

void rotate(float r) {
    glRotatef(r,0,0,1);
}

void drawLine(float startx, float starty, float endx, float endy) {
    glTranslatef(-1,(float)transInc/WIDTH,0);
    starty-=485;
    endy-=485;
    float xLoc = (float)startx/(float)WIDTH;
    float yLoc = -(float)starty/(float)HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(((endx-startx)/WIDTH)*2,-((endy-starty)/HEIGHT)*2);
    glEnd();
   glEnd();
   glTranslatef(1,-(float)transInc/WIDTH,0);
   glTranslatef(-xLoc*2,-yLoc*2,0);

}

void setBackground(float r, float g, float b, float a) {
    glClearColor(r/255.0, g/255.0, b/255.0,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void MyGLWidget::initializeGL()
{
    makeCurrent();
    setBackground(20,20,20,1);
    WIDTH=MyGLWidget::geometry().width();
    HEIGHT=MyGLWidget::geometry().height();
}
void resetCalls() {
    calls=0;
}

void clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void drawRect(float x,float y, float width, float height) {
    glTranslatef(-1,(float)transInc/WIDTH,0);
    y-=485;
    x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;
    float sizex = width/WIDTH;
    float sizey = height/HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, -sizey*2);
        glVertex2f(sizex*2, -sizey*2);
        glVertex2f(sizex*2, 0);
        glVertex2f(0, 0);
    glEnd();
    glTranslatef(1,-(float)transInc/WIDTH,0);
    glTranslatef(-xLoc*2,-yLoc*2,0);
    draws++;
}

void fillRect(float x,float y, float width, float height) {
    glTranslatef(-1,(float)transInc/HEIGHT,0);
    y-=485;
        x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;
    float sizex = width/WIDTH;
    float sizey = height/HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_QUADS);
        glVertex2f(0, -sizey*2);
        glVertex2f(sizex*2, -sizey*2);
        glVertex2f(sizex*2, 0);
        glVertex2f(0, 0);
    glEnd();
    glTranslatef(1,-(float)transInc/HEIGHT,0);
    glTranslatef(-xLoc*2,-yLoc*2,0);
    draws++;
}


void MyGLWidget::paintGL() {


    //interpret(instructions);
    glLoadIdentity();
    doInterpret();
    //drawRect(xLOCA++,400,100,100);
    //xLOCA = fmod(xLOCA,900);
    usleep(100000/60);
    //std::cout<<"FPS: "<<draws;
    //draws=0;
    update();

    //Items.push_back(interpret(instructions, ui));
}


void MyGLWidget::resizeGL(GLsizei width,GLsizei height){


    float adj = (float)width/(float)height;
    glViewport(0, 0, width, height); // reset the viewport
    glMatrixMode(GL_PROJECTION); // modify the projection matrix
    glLoadIdentity();            // load an identity matrix into the projection matrix
    glOrtho(0, width, 0, height, 1.0, 1.0); // create new projection matrix

    /// Important!!! You need to switch back to the model-view matrix
    /// or else your OpenGL calls are modifying the projection matrix!
    //glMatrixMode(GL_MODELVIEW); // return to the model matrix          // load an identity matrix into the model-view matrix

    // OpenGL has now compensated for the resized window, and is ready to draw again.
    update();

  }

void setLineWeight(float w) {
    glLineWidth(w);
}





void drawOval(float x, float y, float radius1, float radius2, float segments)
{

    if (segments<1) {
        segments=1;
    }
    //std::cout<<"OVVAALL "<<x<<"||"<<y<<"||"<<radius1<<"||"<<radius2<<"||"<<segments<<"\n";
    glTranslatef(-1,(float)transInc/WIDTH,0);
    y-=485;
        x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_LINE_LOOP);

    radius1=(radius1/WIDTH)*2;
    radius2=(radius2/HEIGHT)*2;



   for (int i=0; i < 360; i+=360/segments)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius1,sin(degInRad)*radius2);
   }

   glEnd();
   glTranslatef(1,-(float)transInc/WIDTH,0);
   glTranslatef(-xLoc*2,-yLoc*2,0);
}


void fillOval(float x, float y, float radius1, float radius2, float segments)
{
    glTranslatef(-1,(float)transInc/WIDTH,0);
    y-=485;

        x+=1;
    float xLoc = (float)x/(float)WIDTH;
    float yLoc = -(float)y/(float)HEIGHT;

    //std::cout<<"d"<<yLoc*2;
    glTranslatef(xLoc*2,yLoc*2,0);
    glBegin(GL_POLYGON);

    radius1=(radius1/WIDTH)*2;
    radius2=(radius2/HEIGHT)*2;

    if (segments<1) {
        segments=1;
    }

   for (int i=0; i < 360; i+=  (int) (360/segments))
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius1,sin(degInRad)*radius2);
   }

   glEnd();
   glTranslatef(1,-(float)transInc/WIDTH,0);
   glTranslatef(-xLoc*2,-yLoc*2,0);
}

void MyGLWidget::draw()
{
    //update();
    //repaint();
}

void movesquare(float xs) {
    xdf=xs;
}

void goback() {
    xdf=0;
}

