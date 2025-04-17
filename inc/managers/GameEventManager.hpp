#ifndef GAMEEVENTMANAGER_HPP
#define GAMEEVENTMANAGER_HPP


#include <queue>
#include <string>


class GameEventManager
{
public:
    GameEventManager(const GameEventManager&) = delete;
    GameEventManager& operator=(const GameEventManager&) = delete;

    static GameEventManager& getInstance();

    void pushEvent(const std::string& eventName) {eventQueue.push(eventName);}
    void popEvent() {eventQueue.pop();}
    [[nodiscard]] const std::string& topEvent() const {return eventQueue.front();}
    [[nodiscard]] bool isEmpty() const {return eventQueue.empty();}
private:
    GameEventManager() = default;
    std::queue<std::string> eventQueue;

};



#endif //GAMEEVENTMANAGER_HPP
