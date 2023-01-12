//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_ICOMMAND_H
#define A_OUT_ICOMMAND_H
#include <string>
#include <fstream>

class ICommand {
public:
    std::string description;

    virtual ~ICommand();
    virtual void execute() const = 0;
};


#endif //A_OUT_ICOMMAND_H
