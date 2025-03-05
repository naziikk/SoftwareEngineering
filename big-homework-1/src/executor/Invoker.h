#include "ProcessRequest.h"

class Invoker {
public:
    void SetCommand(std::shared_ptr<Command> cmd) {
        command = std::move(cmd);
    }

    void RunCommand() {
        if (command) {
            command->Execute();
        }
    }

private:
    std::shared_ptr<Command> command;
};