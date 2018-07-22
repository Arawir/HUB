#ifndef SERVER_HH
#define SERVER_HH

#include "client.hh"
///////////////////////////////////////////////////////////////////////////////
class Server : public QObject{
  Q_OBJECT
private:
  qint32 noc; //number of clients
  QTcpServer *server;
  QList<Client*> clients;
  QList<QString> messages;
public:
  explicit Server(QObject *parent = 0);
  void Send_message(QString data, QString id);
  QString Pull_message();
  bool Messages_empty();
signals:
  void Client_connected();
  void New_message();
public slots:
  void New_connection();
  void Receive_message();
};

#endif 
