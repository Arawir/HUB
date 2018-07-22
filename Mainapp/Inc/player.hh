#ifndef PLAYER_HH
#define PLAYER_HH

#include <QObject>
#include <QDebug>
#include "config.hh"
///////////////////////////////////////////////////////////////////////////////
class Card : public QObject{
Q_OBJECT
private:
  QString type = "UNKNOWN";
  QString description = "";
  QString owner_id = "";
  QString target_id = "";
  qint32 n_rand_card = 5; //ile kart los co ture
public:
  explicit Card(QObject *parent=NULL){ };
  void Set_type(QString t);
  void Set_owner(QString o){ owner_id = o; }
  void Set_target(QString t){ target_id = t; }
  void Set_n_rand_card(qint32 n){ n_rand_card = n; }
  QString Type(){ return type; }
  QString Owner(){ return type; }
  QString Target(){ return type; }

  void Rand_type();
  void Write();
};
///////////////////////////////////////////////////////////////////////////////
class Player : public QObject{
Q_OBJECT
private:
  QString id;
  QString role;
  QString name;
  QString status; // CONNECTED / HAS_ID / DISCONNECTED
  QString phase="-1"; //START / READY_TO_START / MOVE / READY / SEND / WAIT

  qint32 gold;
  qint32 bank_account;

  QList<Card*> cards;
  QList<Card*> next_cards;
public:
  explicit Player(QObject *parent = 0);
  void Set_id(QString n);
  void Set_role(QString new_role){ role = new_role; }
  void Set_name(QString n);
  void Set_status(QString st);
  void Set_phase(QString ph){ phase = ph; };
  QString Id(){ return id; }
  QString Role(){ return role; }
  QString Phase(){ return phase; }
  QString Status(){ return status; }
  void Write();
};

////////////////////////////////////////////////////////////////////////////////
#endif
