#ifndef PLAYER_HH
#define PLAYER_HH

#include <QObject>
#include <QDebug>

///////////////////////////////////////////////////////////////////////////////
class Player : public QObject{
Q_OBJECT
private:
  QString id;
  QString role;
  QString name;
  QString status; 
  QString phase="CONFIGURE";

  qint32 Gold;
  qint32 BankAcc;
public:
  explicit Player(QObject *parent = nullptr) : QObject(parent){ }

  void randStart();
  QStringList toSend();
  
  void Set_id(QString i){ id = i; } 
  void Set_role(QString new_role){ role = new_role; }
  void Set_name(QString n){ name = n; }
  void Set_status(QString st){status = st; }
  void Set_phase(QString ph){ phase = ph; }
  void setGold(qint32 g){ Gold = g; }
  void setBankAcc(qint32 b){ BankAcc = b; }
  
  QString Id(){ return id; }
  QString Role(){ return role; }
  QString Phase(){ return phase; }
  QString Status(){ return status; }
  qint32 gold(){ return Gold; }
  qint32 bankAcc(){ return BankAcc; }

  void Debug();
};

////////////////////////////////////////////////////////////////////////////////
#endif
