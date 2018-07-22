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
  QString status; // CONNECTED / HAS_ID / DISCONNECTED
  QString phase="-1"; //START / READY_TO_START / MOVE / READY / SEND / WAIT

public:
  explicit Player(QObject *parent = nullptr) : QObject(parent){ }
  void Set_id(QString i){ id = i; } 
  void Set_role(QString new_role){ role = new_role; }
  void Set_name(QString n){ name = n; }
  void Set_status(QString st){status = st; }
  void Set_phase(QString ph){ phase = ph; };
  QString Id(){ return id; }
  QString Role(){ return role; }
  QString Phase(){ return phase; }
  QString Status(){ return status; }

  void Debug();
};

////////////////////////////////////////////////////////////////////////////////
#endif
