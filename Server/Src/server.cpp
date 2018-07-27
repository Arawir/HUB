#include "Server/Inc/server.hh"

#include <unistd.h>
////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
Server::Server(QObject *parent) : QObject(parent){
  noc = 0;
  server = new QTcpServer(this);
  connect(server, SIGNAL(newConnection()), this, SLOT(New_connection()));
  if(!server->listen(QHostAddress::Any, 1234)){
    qDebug() << "Server could not start!";
  }
  else{ qDebug() << "Server started!"; }
}

void Server::Send_message(QString data, QString id){
  foreach(Client *c, clients){
    if(c->Id() == id){
      c->Send_message(data);
      qDebug() << "Sen: " << data;
      break;
    }
  }
}

QString Server::Pull_message(){
  if(messages.isEmpty()) return "";
  QString tmp = messages.first();

  qDebug() << "Rec: " << tmp;
  messages.removeFirst();
  return tmp;
}

bool Server::Messages_empty(){
  return messages.isEmpty();
}

//////////////////////////////////////////////////////////////////////////////
//SLOTS
void Server::New_connection(){
  Client *C = new Client();

  QString msg = "S_|_NEW_ID_|_" + QString::number(noc) + "\r\n";
  
  QTcpSocket *socket = server->nextPendingConnection();
  // sleep(10);
  socket->write(msg.toStdString().c_str());
  socket->flush();
  socket->waitForBytesWritten(3000);

  C->Set_socket(socket);
  C->Set_id( QString::number(noc) );
  connect(C, SIGNAL(New_message()), this, SLOT(Receive_message()));
  clients.append(C);

  noc++;
  emit Client_connected();
}

void Server::Receive_message(){
  QString buffer;
  foreach(Client *c, clients){
    while(!c->Messages_empty()){
      buffer = c->Pull_message();
      messages.append(buffer);
    }
  }
  emit New_message();
}

