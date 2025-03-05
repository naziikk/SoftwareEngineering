#include "ProcessRequest.h"
#include "../observer/Observer.h"

class Invoker {
public:
    void SetCommand(std::shared_ptr<Command> cmd) {
        command = std::move(cmd);
        NotifyObservers("Запрос добавлен в очередь на выполнение");
    }

    void RunCommand() {
        if (command) {
            command->Execute();
            NotifyObservers("Запрос обработан");
        }
    }

    void AddObserver(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }

private:
    void NotifyObservers(const std::string& message) {
        for (auto& observer : observers_) {
            observer->Update(message);
        }
    }

    std::shared_ptr<Command> command;
    std::vector<std::shared_ptr<Observer>> observers_;
};