#include "Player.h"

Player::Player() : Entity() {
    setTexture(App::instance().getDrawingManager()->loadTexture("player.png"));
    SDL_SetTextureBlendMode(getTexture()->image, SDL_BLENDMODE_BLEND);
    setHealth(10);
    setSpeed(PLAYER_SPEED);
    for (int i = 0; i < 4; i++) {
        direction[i] = false;
    }
    lives = 3;
    score = 0;
    shooting = false;
    immune = false;
}

Player::~Player() {}

void Player::update() {
    App& app = App::instance();

    if (shooting) {
        if (reload == 0) {
            shoot();
            reload = PLAYER_RELOAD_SPEED;
        } else {
            reload--;
        }
    }

    move();    
    checkBoundaries();

    if (immune) {
        if (SDL_GetTicks() - oldTime < 2000) {
            Uint8 alpha;
            SDL_GetTextureAlphaMod(getTexture()->image, &alpha);
            alpha = (alpha == 0) ? 255 : 0;
            SDL_SetTextureAlphaMod(getTexture()->image, alpha);
        } else {
            immune = false;
            oldTime = 0;
            SDL_SetTextureAlphaMod(getTexture()->image, 255);
        }
    }
}

void Player::move() {
    
    struct { int x, y; } dir;
    dir.x = 0;
    dir.y = 0;

    if (direction[DIRECTION_UP]) {
        dir.y = -1;
    }
    if (direction[DIRECTION_DOWN]) {
        dir.y = 1;
    }
    if (direction[DIRECTION_LEFT]) {
        dir.x = -1;
    }
    if (direction[DIRECTION_RIGHT]) {
        dir.x = 1;
    }

    float dx, dy;
    double n;

    n = sqrt(pow(dir.x, 2) + pow(dir.y, 2));

    if (n != 0) {    
        dx = dir.x / n;
        dy = dir.y / n;

        setX(getX() + dx * getSpeed());
        setY(getY() + dy * getSpeed());
    }
}

void Player::setMovement(int direction, bool value) {
    this->direction[direction] = value;
}

void Player::checkBoundaries() {
    float x = getX();
    float y = getY();
    int w = getTexture()->rect.w;
    int h = getTexture()->rect.h;

    if (x < 0) {
        setX(0);
    }
    if (x > SCREEN_WIDTH - w) {
        setX(SCREEN_WIDTH - w);
    }
    if (y < 0) {
        setY(0);
    }
    if (y > SCREEN_HEIGHT - h) {
        setY(SCREEN_HEIGHT - h);
    }
}

void Player::toggleFire() {
    shooting = !shooting;
    reload = PLAYER_RELOAD_SPEED;
}

void Player::shoot() {
    Bullet *bullet = new Bullet(BULLETTYPE_PLAYER);
    bullet->setPos(this->getX() + this->getW() / 2 - bullet->getW() / 2, this->getY());
    bullet->setTrajectory();
    reload = PLAYER_RELOAD_SPEED;
    App::instance().getStage()->addEntity(bullet);
}

void Player::addScore(unsigned int score) {
    this->score += score;
}

void Player::die() {
    Animation *explosion = new Animation("explosion.png", 8, 96, 96);
    explosion->setPos(getX() + getW() / 2 - 48, getY() + getH() / 2 - 48);
    App::instance().getStage()->addAnimation(explosion);

    if (--lives == 0) {
        App::instance().getStage()->gameOver(SDL_GetTicks());
    } else {
        oldTime = SDL_GetTicks();
        respawn();
    }
}

void Player::respawn() {
    setHealth(10);
    immune = true;
    setPos(SCREEN_WIDTH / 2 - getW() / 2, SCREEN_HEIGHT - getH() * 2);
}