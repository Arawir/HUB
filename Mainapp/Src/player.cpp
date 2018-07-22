#include "Inc/player.hh"

#include <string>
////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
void Card::Set_type(QString t){
  std::string tmp = t.toStdString();
  
  if(tmp=="-100"){
    type = t;
    description = "-100 - I'm evil, but a bit shy... ";
  }
  else if(tmp=="-1000"){
    type = t;
    description = "-1000 - Ha ha loosers! ";
  }
  else if(tmp=="-10%"){
    type = t;
    description = "-10% - Spoil someone's day";
  }
  else if(tmp=="-100%"){
    type = t;
    description = "-100% - Your enemies will suffer";
  }
  else if(tmp=="CHESTER"){
    type = t;
    description = "Cheshire Cat - Anything could happen";
  }
  else{
    type = "UNKNOWN";
    description = "";
  } 
}
////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
Player::Player(QObject *parent){
  id="-1";
  name="";
  status="CONNECTED";
  gold = 0;//beg_gold;
  bank_account=0;
}

void Player::Set_id(QString n){
  id = n;
}

void Player::Set_name(QString n){
  name = n;
}

void Player::Set_status(QString st){
  status = st;
}

void Player::Write(){
  qDebug() << "Next player data: ";
  qDebug() << "   ID    : " << id;
  qDebug() << "   ROLE  : " << role;
  qDebug() << "   NAME  : " << name;
  qDebug() << "   STATUS: " << status;
  qDebug() << "   PHASE : " << phase;
  // foreach(Card *C, cards
}

////////////////////////////////////////////////////////////////////////////////
//SLOTS
