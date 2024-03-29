//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_CLASSIFYDATACLIENTCOMMAND_H
#define A_OUT_CLASSIFYDATACLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
/**
 * This class is one of the command client can make.
 * which adk the server to classify the data.
 */
class ClassifyDataClientCommand : public ICommand {
public:
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    ClassifyDataClientCommand(DefaultIO &io);
    ~ClassifyDataClientCommand() override;
    void execute() override;
private:
};
#endif //A_OUT_CLASSIFYDATACLIENTCOMMAND_H
