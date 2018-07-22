#ifndef MAIN_APP_HH
#define MAIN_APP_HH

#include "gui.hh"
#include "server.hh"
#include "player.hh"
#include "config.hh"
////////////////////////////////////////////////////////////////////////////////
class Main_app : public QObject{
  Q_OBJECT
private:
  Server *S;
  Window *W;

  qint32 round;
  qint32 max_players;
  QList<Player*> players;
  qint32 player_status[100]; // tmp 100 // 0-free 1 - occ
public:
  explicit Main_app(QObject *parent = NULL);                                //A
  void Connect_to_server(Server *serv);
  void Connect_to_gui(Window *win);

  
  void Add_player(QString sender_id);                                        //B
  void Send_message(QString data, QString id);
  void Set_player_role(QString new_role, QString sender_id);
  void Set_player_name(QString new_name, QString sender_id);
  void Set_player_status(QString new_stat, QString sender_id);
  void Set_player_phase(QString new_phase, QString sender_id);

  void Send_job_offer(QString sender_id);
  void Send_job_offer_to_all();
  void Start_recruitment_process(QString position, QString sender_id);

  
  void Execute_message(QString msg);                                         //C


  void Player_ready(QString sender_id);                                        //D
  void Player_move(QString sender_id);
  void Player_send(QString sender_id);
  void Player_wait(QString sender_id);

  
  void Next_round();                                                         //E
  void Calculate_round();
  void Send_data();

  void Debug();                                                              //F
public slots:
  void Receive_message();
  void Button_clicked(); //tmp
};

////////////////////////////////////////////////////////////////////////////////
#endif
