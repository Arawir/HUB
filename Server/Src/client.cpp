#include "Server/Inc/client.hh"

////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
Client::Client(QObject *parent) : QObject(parent){
  id="-1";
  socket=NULL;
}

void Client::Send_message(QString data){
  socket->write(data.toStdString().c_str());
  socket->flush();
  socket->waitForBytesWritten(3000);
}

void Client::Set_socket(QTcpSocket *s){
  socket = s;
  connect(socket, SIGNAL(readyRead()), this, SLOT(Receive_message()));
}

QString Client::Pull_message(){
  if(messages.isEmpty()) return "";
  QString tmp = messages.first();
  messages.removeFirst();
  return tmp;
}

////////////////////////////////////////////////////////////////////////////////
//SLOTS
void Client::Receive_message(){
  QString buffer;
  buffer = socket->read(1000);      //max tysiac
  messages.append(buffer);
  emit New_message();  
}


