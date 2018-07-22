#include "Inc/main_app.hh"

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS A
Main_app::Main_app(QObject *parent){
  max_players = 6;
  for(qint32 i=0; i<100; i++){
    player_status[i]=0;
  }
}

void Main_app::Connect_to_server(Server *serv){
  S = serv;
  connect(S, SIGNAL(New_message()), this, SLOT(Receive_message()));
  connect(S, SIGNAL(Client_connected()), this, SLOT(Receive_message()));
}

void Main_app::Connect_to_gui(Window *win){
  W = win;
  connect(W, SIGNAL(Button_clicked()), this, SLOT(Button_clicked()));
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS B
void Main_app::Add_player(QString sender_id){
  bool flag_exist=0;
  
  foreach(Player *P, players){
    if(P->Id()==sender_id){ P->Set_status("CONNECTED"); flag_exist=1; } //???
  }
  
  if(!flag_exist){
    Player *P = new Player();
  
    P->Set_id(sender_id);
    P->Set_status("CONNECTED");
    players.append(P);
  }

  Send_job_offer(sender_id);
}

void Main_app::Send_message(QString data, QString id){
  S->Send_message_to_client(data, id);
}

void Main_app::Set_player_name(QString new_name, QString sender_id){
  QString msg = "M_|_SET_NAME_|_" + new_name + "\r\n";
    foreach(Player *P, players){
    if(P->Id() == sender_id) P->Set_name(new_name);
  }
  Send_message(msg, sender_id);
}

/*
void Main_app::Set_player_phase(QString new_phase, QString sender_id){
  foreach(Player *P, players){
    if(P->Id() == sender_id) P->Set_phase(new_phase);
  }
  }*/

void Main_app::Send_job_offer(QString sender_id){
  QString msg = "M_|_FREE_ROLES_|_";
  for(qint32 i=0; i<max_players; i++)
    if(player_status[i]==0) msg += QString::number(i) + "_|_";
  msg += "\r\n";
  Send_message(msg, sender_id);
}

void Main_app::Send_job_offer_to_all(){
  QString msg = "M_|_FREE_ROLES_|_";
  for(qint32 i=0; i<max_players; i++)
    if(player_status[i]==0) msg += QString::number(i) + "_|_";
  msg += "\r\n";
  
  foreach(Player *P, players){
    Send_message(msg, P->Id() );
  }
}

void Main_app::Start_recruitment_process(QString position, QString sender_id){
  QString msg="";
  //  qDebug() << "WESSZLO A";
  foreach(Player *P, players){
    if(P->Id() == sender_id)
      if(P->Role()!=""){
	player_status[P->Role().toInt()]=0;
      }
  }
  
  if( player_status[position.toInt()]==0 ){
    player_status[position.toInt()] = 1;
    msg = "M_|_SET_ROLE_|_"+position + "\r\n";
    foreach(Player *P, players){
      if(P->Id() == sender_id) P->Set_role(position);
    }
    qDebug() << "WESZLO b";
    Send_message(msg, position);
  }
  else{
    msg = "M_|_ROLE_OCC\r\n"; 
    Send_message(msg, sender_id);
  }

  Send_job_offer_to_all();
}
/////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS C
void Main_app::Execute_message(QString msg){
  QString sender_id = "";
  QString command = "";
  
  msg.remove("\r");
  msg.remove("/r");
  msg.remove("\n");
  msg.remove("/n");
  qDebug() << "Message: " << msg;
      
  QStringList parameters = msg.split("_|_");
  if(parameters.isEmpty()!=1){
    sender_id = parameters[0];
    parameters.removeFirst();
  }
  if(parameters.isEmpty()!=1){
    command = parameters[0];
    parameters.removeFirst();
  }

  qDebug() << "   Sender: " << sender_id
  	   << "\r\n   Command: " << command
  	   << "\r\n   Parameters: ";
  
  foreach(QString s, parameters) qDebug() << "      " << s;
  qDebug() << "\r\n";


  /////////////////////////////////////////////////////////////////
  if(command=="CONNECTED") Add_player(sender_id);
  if(command=="SET_NAME") Set_player_name(parameters[0], sender_id);
  if(command=="FREE_ROLES") Send_job_offer(sender_id);
  if(command=="SET_ROLE") Start_recruitment_process(parameters[0], sender_id);

  if(command=="SET_PHASE") Set_player_phase(parameters[0], sender_id);
  
  if(command=="READY") Player_ready(sender_id);
  if(command=="MOVE") Player_move(sender_id);
  if(command=="SEND") Player_send(sender_id);
  if(command=="WAIT") Player_wait(sender_id);
}

/////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS D

void Main_app::Set_player_phase(QString new_phase, QString id){
  QString msg;
  qDebug() << "SPHASE1";
  foreach(Player *P, players){
    if((P->Phase()=="-1")&&(new_phase=="START")){
      P->Set_phase("START");
      msg = "M_|_SET_PHASE_|_START\r\n"; 
      Send_message(msg, id);
    }
  }
}

void Main_app::Player_ready(QString sender_id){
  qint32 iter=0;
  Set_player_phase("READY", sender_id);
  foreach(Player *P, players){
    if(P->Phase()=="READY") iter++;
    else break;
  }
  if(iter == players.length()) Next_round();
}

void Main_app::Player_move(QString sender_id){
  Set_player_phase("MOVE", sender_id);
}

void Main_app::Player_send(QString sender_id){
  Set_player_phase("SEND", sender_id);
}

void Main_app::Player_wait(QString sender_id){
  qint32 iter=0;
  Set_player_phase("WAIT", sender_id);
  foreach(Player *P, players){
    if(P->Phase()=="WAIT") iter++;
    else break;
  }
  if(iter == players.length()){
    Calculate_round();
    Send_data();
  }
}

///////////////////////////////////////////////////////////////////////////////
//FUNCTIONS E
void Main_app::Next_round(){
  QString msg = "M_|_SET_PHASE_|_SEND\r\n";
  foreach(Player *P, players){
    if(P->Status()=="HAS_ID") Send_message(msg, P->Id());
  }
  round++;
}

void Main_app::Calculate_round(){
  qDebug() << "CR";
}

void Main_app::Send_data(){
  QString msg = "M_|_SET_PHASE_|_MOVE\r\n";
  qDebug() << "SD";
  //
  // ...
  //

  foreach(Player *P, players){
    if(P->Status()=="HAS_ID") Send_message(msg, P->Id());
  }
  round++;
}
  
///////////////////////////////////////////////////////////////////////////////
//FUNCTIONS F
void Main_app::Debug(){
  qDebug() << "///////////////////////////////////////////////////////////";
  qDebug() << "   SERVER    : " << S;
  qDebug() << "   WINDOW    : " << W;
  qDebug() << "   ROUND     : " << round;
  qDebug() << "   N_PLAYERS : " << max_players;
  qDebug() << "   PLAYER_STATUS : " << player_status[0] << " "
	   << player_status[1] << " " << player_status[2] << " "
	   << player_status[3] << " " << player_status[4] << " "
	   << player_status[5];
  foreach(Player *P, players) P->Write();
  qDebug() << "///////////////////////////////////////////////////////////";
  
}

////////////////////////////////////////////////////////////////////////////////
//SLOTS
void Main_app::Receive_message(){
  QString msg;
  while(!S->Messages_empty()){
    msg = S->Pull_message();
    Execute_message(msg);
  }
}

void Main_app::Button_clicked(){
  Debug();
}
