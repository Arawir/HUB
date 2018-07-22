#ifndef CLIENT_HH
#define CLIENT_HH

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

///////////////////////////////////////////////////////////////////////////////
class Client : public QObject{
Q_OBJECT
private:
  QString id;
  QTcpSocket *socket;
  QList<QString> messages;
public:
  explicit Client(QObject *parent = 0);

  void Set_socket(QTcpSocket *s);
  void Set_id(QString nid){ id = nid; }
  QString Id(){ return id; }
  
  void Send_message(QString data);
  
  QString Pull_message();
  bool Messages_empty(){ return messages.isEmpty(); }

signals:
  void New_message();
public slots:
  void Receive_message();
};

////////////////////////////////////////////////////////////////////////////////
#endif
