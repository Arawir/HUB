#include "Mainapp/Inc/main_app.hh"

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS A
void Main_app::Execute_message(QString msg){
  QString sender_id = "";
  QString command = "";
  
  msg.remove("\r");
  msg.remove("/r");
  msg.remove("\n");
  msg.remove("/n");
      
  QStringList parameters = msg.split("_|_");
  if(parameters.isEmpty()!=1){
    sender_id = parameters[0];
    parameters.removeFirst();
  }
  if(parameters.isEmpty()!=1){
    command = parameters[0];
    parameters.removeFirst();
  }

  
  if(command=="SET_ID") Add_player(sender_id);
  if(command=="SET_NAME") Set_player_name(parameters[0], sender_id);
  if(command=="FREE_ROLES") Show_free_roles(sender_id);
  if(command=="SET_ROLE") Set_player_role(parameters[0], sender_id);
}

////////////////////////////////////////////////////////////////////////////////
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
}

void Main_app::Set_player_name(QString new_name, QString sender_id){
  P(sender_id)->Set_name(new_name);
  Send_message("H_|_SET_NAME_|_" + new_name , sender_id);
}

void Main_app::Show_free_roles(QString sender_id){
  QString out = "H_|_FREE_ROLES";
  for(int i=0; i<nop; i++)
    if(player_status[i]==0){ out += ("_|_" + QString::number(i)); }
  Send_message(out, sender_id);
}

void Main_app::Set_player_role(QString new_role, QString sender_id){
  if(player_status[new_role.toInt()]==0){
    player_status[new_role.toInt()]=1;
    P(sender_id)->Set_role(new_role);
    Send_message("H_|_SET_ROLE_|_" + new_role , sender_id);
  }
  else Show_free_roles(sender_id);
}


