//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DISPLAYCLIENTCOMMAND_H
#define A_OUT_DISPLAYCLIENTCOMMAND_H
class DisplayClientCommand : public ICommand {
public:
    DisplayClientCommand(DefaultIO &io);
    void execute() override;
private:

};
#endif //A_OUT_DISPLAYCLIENTCOMMAND_H
