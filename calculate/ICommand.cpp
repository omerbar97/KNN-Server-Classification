//
// Created by omer on 1/12/23.
//

#include "ICommand.h"

#include <utility>

ICommand::ICommand(std::string description, const DefaultIO& io) : io(const_cast<DefaultIO &>(io)) , description(std::move(description)){

}

ICommand::~ICommand() {

}
