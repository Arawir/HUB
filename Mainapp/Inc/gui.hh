#ifndef GUI_HH
#define GUI_HH
 
#include <QMainWindow>
#include <QPushButton>
////////////////////////////////////////////////////////////////////////////////
namespace Ui {
  class MainWindow;
}
 
class Window : public QMainWindow{
  Q_OBJECT
public:
  explicit Window(QWidget *parent = 0);

signals:
  void Button_clicked();
private slots:
  void handleButton();
private:
  QPushButton *m_button;
};
////////////////////////////////////////////////////////////////////////////////
#endif
