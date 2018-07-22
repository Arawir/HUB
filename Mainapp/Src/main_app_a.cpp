#include "Mainapp/Inc/main_app.hh"

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS A
Main_app::Main_app(QObject *parent) : QObject(parent){ }

void Main_app::Connect_to_server(Server *serv){
  S = serv;
  connect(S, SIGNAL(New_message()), this, SLOT(Receive_message_slot()));
  connect(S, SIGNAL(Client_connected()), this, SLOT(Receive_message_slot()));
}

/*void Main_app::Connect_to_gui(Window *win){
  W = win;
  connect(W, SIGNAL(Button_clicked()), this, SLOT(Debug_slot()));
  }*/

////////////////////////////////////////////////////////////////////////////////

Player* Main_app::P(QString id){
  foreach(Player* p, players){
    if(p->Id() == id) return p;
  }
  return nullptr;
}

void Main_app::Send_message(QString msg, QString id){
  S->Send_message(msg, id);
}

void Main_app::Set_nop(qint32 n){
  if(players.isEmpty()==1){
    nop = n;
    for(int i=0; i<100; i++) player_status[i] = 1;
    for(int i=0; i<nop; i++) player_status[i] = 0;
  }
}

void Main_app::Debug(){
  qDebug() << "///////////////////////////////////////////////////////////";
  qDebug() << "   SERVER    : " << S;
  // qDebug() << "   WINDOW    : " << W;
  qDebug() << "   ROUND     : " << round;
  qDebug() << "   N_PLAYERS : " << nop;
  qDebug() << "   PLAYER_STATUS : " << player_status[0] << " "
	   << player_status[1] << " " << player_status[2] << " "
	   << player_status[3] << " " << player_status[4] << " "
	   << player_status[5];
  foreach(Player *P, players) P->Debug();
  qDebug() << "///////////////////////////////////////////////////////////";
  
}

////////////////////////////////////////////////////////////////////////////////
//SLOTS
void Main_app::Receive_message_slot(){
  QString msg;
  while(!S->Messages_empty()){
    msg = S->Pull_message();
    Execute_message(msg);
  }
}

void Main_app::Debug_slot(){
  Debug();
}
