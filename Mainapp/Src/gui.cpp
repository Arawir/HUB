#include "Inc/gui.hh"
 
#include <QCoreApplication>
 
Window::Window(QWidget *parent) : QMainWindow(parent){
  m_button = new QPushButton("My Button", this);
  connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
}
 
void Window::handleButton(){
  m_button->setText("Example");
  emit Button_clicked();
}
