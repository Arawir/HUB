#include <QApplication>
#include <QCoreApplication>
#include "Server/Inc/server.hh"


int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  Server *S = new Server();

  return app.exec();
}
