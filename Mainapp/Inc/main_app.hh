#ifndef MAIN_APP_HH
#define MAIN_APP_HH

//#include "gui.hh"
#include "Server/Inc/server.hh"
#include "player.hh"
////////////////////////////////////////////////////////////////////////////////
class Main_app : public QObject{
  Q_OBJECT
private:
  Server *S;
  //Gui *G;

  qint32 round;
  qint32 nop; //number of players
  QList<Player*> players;
  qint32 player_status[100]; // tmp 100 // 0-free 1 - occ
public:
  explicit Main_app(QObject *parent = NULL);                                
  void Connect_to_server(Server *serv);
  //void Connect_to_gui(Window *win);

  
  void Add_player(QString sender_id);                                       
  void Send_message(QString msg, QString id);
  void Set_nop(qint32 n);
  void Set_round(qint32 r);
  Player* P(QString id);

  void Show_free_roles(QString sender_id);
  
  void Set_player_role(QString new_role, QString sender_id);
  void Set_player_name(QString new_name, QString sender_id);
  void Set_player_status(QString new_stat, QString sender_id);
  void Set_player_phase(QString new_phase, QString sender_id);
  
  void Execute_message(QString msg);                                       

  void Debug();                                                             
public slots:
  void Receive_message_slot();
  void Debug_slot(); //tmp
};

////////////////////////////////////////////////////////////////////////////////
#endif
