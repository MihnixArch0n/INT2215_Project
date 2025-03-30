#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP


#include "defs.hpp"


class Mediator;


class GameManager
{
public:
    virtual ~GameManager() = default;

    void setMediator(Mediator *mediator) {pMediator = mediator;}
    [[nodiscard]] virtual ManagerType getType() const = 0;
protected:
    Mediator* pMediator = nullptr;
};



#endif //GAMEMANAGER_HPP
