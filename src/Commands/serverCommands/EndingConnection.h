//
// Created by oem on 1/19/23.
//

#ifndef A_OUT_ENDINGCONNECTION_H
#define A_OUT_ENDINGCONNECTION_H


#include "../ICommand.h"

class EndingConnection : public ICommand{

public:
    EndingConnection(DefaultIO &io);

    ~EndingConnection() override;

    void execute() override;

};
#endif //A_OUT_ENDINGCONNECTION_H
