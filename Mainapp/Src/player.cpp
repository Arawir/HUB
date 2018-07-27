#include "Mainapp/Inc/player.hh"

#include <QRandomGenerator>
////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS
void Player::randStart(){
  Gold = QRandomGenerator::global()->generate() % 1000 + 2000;
  BankAcc = 0;
  
}
QStringList Player::toSend(){
  QStringList out;

  out.append("H_|_SET_FREE_GOLD_|_" + QString::number(Gold) );
  out.append("H_|_SET_BANK_ACC_|_" + QString::number(BankAcc) );

  return out;
}


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
