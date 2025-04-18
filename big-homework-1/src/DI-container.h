#include <iostream>
#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>

class DIContainer {
private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> objects_;

public:
    template <typename T, typename... Args>
    void RegisterObject(Args&&... args) {
        objects_[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    std::shared_ptr<T> GetObject() {
        auto it = objects_.find(typeid(T));
        if (it != objects_.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }
};