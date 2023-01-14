//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_CLASSIFYDATACLIENTCOMMAND_H
#define A_OUT_CLASSIFYDATACLIENTCOMMAND_H

#include "../ICommand.h"

class ClassifyDataClientCommand : public ICommand {
public:
    explicit ClassifyDataClientCommand(DefaultIO &io);
    void execute() override;
private:
};
#endif //A_OUT_CLASSIFYDATACLIENTCOMMAND_H
