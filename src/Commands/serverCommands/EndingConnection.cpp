//
// Created by oem on 1/19/23.
//

#include "EndingConnection.h"



EndingConnection::EndingConnection(DefaultIO &io) :ICommand(io) {
    this->description = "8. exit.";

}

EndingConnection::~EndingConnection() {

}

void EndingConnection::execute() {

}