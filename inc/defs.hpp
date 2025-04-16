#ifndef DEFS_HPP
#define DEFS_HPP

#include <variant>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr char WINDOW_TITLE[] = "Brick Breaker";

constexpr int LEVEL_WIDTH = SCREEN_WIDTH - 100;
constexpr int LEVEL_HEIGHT = SCREEN_HEIGHT;

constexpr int BRICK_ROW = 5;
constexpr int BRICK_COLUMN = 10;


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
    EASY,
    MEDIUM,
    HARD,
    TOTAL
};

enum class PowerUpType
{
    MULTI_BALL,
    FIRE_BALL,
    TOTAL
};

using ObjectSubType = std::variant<BallType, PaddleType, BrickType, PowerUpType>;


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
    BACK,
    OPTION_ENTRY_LEFT,
    OPTION_ENTRY_RIGHT,
    PLAY_AGAIN,
    SAVE,
    LOAD,
    QUIT,
    EXIT
};


enum class MenuGroupType
{
    NORMAL,
    SETTINGS,
};


enum class SettingType
{
    MUSIC_ON_OFF,
    MUSIC_VOLUME,
    SOUND_ON_OFF,
    SOUND_VOLUME
};


enum class SoundType
{
    HIT,
    COLLECT
};

#endif //DEFS_HPP
