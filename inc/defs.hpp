#ifndef DEFS_HPP
#define DEFS_HPP


constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr char WINDOW_TITLE[] = "Brick Breaker";


enum class ObjectType
{
    BALL,
    PADDLE,
    BRICK,
    DROP,
    TOTAL
};

enum class BallType
{
    NORMAL,
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


#endif //DEFS_HPP
