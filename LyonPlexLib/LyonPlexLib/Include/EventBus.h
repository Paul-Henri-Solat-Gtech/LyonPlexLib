
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <any>
#include <mutex>

class EventBus {
public:
    // Acces au singleton
    static EventBus& instance() {
        static EventBus s_instance;
        return s_instance;
    }

    // Ne pas copier ni deplacer
    EventBus(EventBus const&) = delete;
    EventBus& operator=(EventBus const&) = delete;

    // Inscription à un type d’evenement E
    template<typename E>
    void subscribe(std::function<void(typename E::Payload const&)> cb) {
        std::lock_guard<std::mutex> lock(_mtx);
        auto& vec = _subscribers[typeid(E)];
        vec.push_back([cb](std::any const& a) {
            cb(std::any_cast<typename E::Payload>(a));
            });
    }

    // Publication d’un evenement E
    template<typename E>
    void publish(typename E::Payload const& payload) {
        std::lock_guard<std::mutex> lock(_mtx);
        auto it = _subscribers.find(typeid(E));
        if (it == _subscribers.end()) return;
        for (auto& fn : it->second) {
            fn(payload);
        }
    }

private:
    EventBus() = default;
    ~EventBus() = default;

    std::mutex _mtx;

    // map type_index -> liste de callbacks prenant un std::any
    std::unordered_map<std::type_index, std::vector<std::function<void(std::any const&)>>> _subscribers;
};
