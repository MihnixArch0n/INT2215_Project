#ifndef DEFS_HPP
#define DEFS_HPP

#include <variant>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr char WINDOW_TITLE[] = "Brick Breaker";


enum class GameState
{
    START,
    PLAYING,
    PAUSED,
    SETTINGS,
    QUIT_TO_START,
    END,
    QUIT
};


enum class ObjectType
{
    BALL,
    PADDLE,
    BRICK,
    POWER_UP_DROP,
    TOTAL
};

enum class BallType
{
    NORMAL,
    FIRE,
    TOTAL
};

enum class PaddleType
{
    NORMAL,
    TOTAL
};

enum class BrickType
{
    NORMAL,
    TOTAL
};

enum class PowerUpDropType
{
    MULTI_BALL,
    FIRE_BALL,
    TOTAL
};

using ObjectSubType = std::variant<BallType, PaddleType, BrickType, PowerUpDropType>;


enum class PowerUpDropStatus
{
    ALIVE,
    COLLECTED,
    DEAD
};


enum class ManagerType
{
    RESOURCE_MANAGER,
    GAME_OBJECT_MANAGER,
    POWER_UP_MANAGER,
    COLLISION_MANAGER
};


enum class ButtonType
{
    PLAY,
    SETTINGS,
    RESUME,
    QUIT,
    EXIT
};


#endif //DEFS_HPP
