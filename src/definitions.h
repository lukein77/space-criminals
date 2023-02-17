#ifndef _DEFINITIONS_H_DEFINED_
#define _DEFINITIONS_H_DEFINED_

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 720

#define MAX_KEYBOARD_KEYS 350
#define TEXTURE_CACHE_SIZE 4

#define PLAYER_SPEED 6
#define PLAYER_RELOAD_SPEED 10
#define PLAYER_DAMAGE 10

#define ENEMY_DAMAGE 10
#define ENEMY_SPEED_COMMON 4
#define ENEMY_SPEED_FAST 10
#define ENEMY_SPEED_SUPERFAST 15

#define BULLETSPEED_PLAYER 16
#define BULLETSPEED_ENEMY 10

#define BACKGROUND_SPEED 4

enum {
    GAME_RUNNING,
    GAME_PAUSED,
    GAME_GAMEOVER,
    GAME_EXIT
};

enum {
    BULLETTYPE_PLAYER,
    BULLETTYPE_ENEMY_COMMON,
    BULLETTYPE_ENEMY_FOLLOW
};

enum {
    ENEMYTYPE_COMMON,
    ENEMYTYPE_DIAGONAL,
    ENEMYTYPE_KAMIKAZE
};

enum {
    OBJTYPE_SCORE,
    OBJTYPE_LIFE,
    OBJTYPE_SHIELD
};

enum {
    DIRECTION_UP = 0,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

enum {
    FONTSIZE_DEFAULT = 0,
    FONTSIZE_LARGE,
    FONTSIZE_SMALL
};

typedef struct {
    SDL_Texture *image;
    SDL_Rect rect;
} Texture;

typedef struct vector {
    double x;
    double y;
} vector;

#endif