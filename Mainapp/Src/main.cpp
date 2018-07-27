#include <QApplication>
#include <QCoreApplication>
#include "Server/Inc/server.hh"
#include "Mainapp/Inc/main_app.hh"

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  Server *S = new Server();
  Main_app *M = new Main_app();
  M->Connect_to_server(S);
  M->Set_nop(2);
  
  return app.exec();
}
