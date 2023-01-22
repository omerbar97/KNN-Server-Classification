//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
#define A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
#include <string>
#include <sstream>
#include <sstream>
#include "../ICommand.h"

/**
 * This class is one of the command Server can make.
 * which let the client change the setting of the KNN algorithm
 */
class AlgorithemSettingServerCommand : public ICommand{

private:
    /**
     * This function split string that the server get from the client and check if the new setting are valid value
     * , if so change the setting, otherwise send the client for invalid input,
     * @param str ,string we got from client.
     * @param delim ,delim is the space.
     * @return int-in{1,2,3,4} - 1= k invalid, 2 = metric invalid , 3 = k and metric invlaid, 4 = too many args.
     */
    int tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

public:
    AlgorithemSettingServerCommand(DefaultIO &io, int k);

    ~AlgorithemSettingServerCommand() override;

    void execute() override;

};

#endif //A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
