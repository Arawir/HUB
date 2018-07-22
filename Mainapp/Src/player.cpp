#include "Mainapp/Inc/player.hh"

////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS

void Player::Debug(){
  qDebug() << "Next player data: ";
  qDebug() << "   ID    : " << id;
  qDebug() << "   ROLE  : " << role;
  qDebug() << "   NAME  : " << name;
  qDebug() << "   STATUS: " << status;
  qDebug() << "   PHASE : " << phase;
}

////////////////////////////////////////////////////////////////////////////////
//SLOTS
