#include "Entity.h"

Entity::Entity() {
    x = y = 0;
    for (int i = 0; i < 4; i++) {
        direction[i] = false;
    }
    speed = 0;
    health = 1;
}

Entity::Entity(int x, int y, Texture *texture) {
    this->x = x;
    this->y = y;
    this->texture = *texture;
}

void Entity::setX(int x) {
    this->x = x;
}

void Entity::setY(int y) {
    this->y = y;
}

void Entity::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void Entity::setMovement(int direction, bool value) {
    this->direction[direction] = value;
}

void Entity::setSpeed(int speed) {
    this->speed = speed;
}

void Entity::setTexture(Texture *texture) {
    this->texture = *texture;
}

void Entity::setHealth(int health) {
    this->health = health;
}

void Entity::takeDamage(int damage) {
    health = (health > damage) ? health - damage : 0;
} 

void Entity::move() {

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

        x += dx * speed;
        y += dy * speed;
    }
}

void Entity::checkBoundaries() {
    if (x < 0) {
        x = 0;
    }
    if (x > SCREEN_WIDTH - texture.rect.w) {
        x = SCREEN_WIDTH - texture.rect.w;
    }
    if (y < 0) {
        y = 0;
    }
    if (y > SCREEN_HEIGHT - texture.rect.h) {
        y = SCREEN_HEIGHT - texture.rect.h;
    }
}

bool Entity::checkCollision(SDL_Rect *a, SDL_Rect *b) {
    if (SDL_HasIntersection(a, b) == SDL_TRUE) {
        return true;
    } else {
        return false;
    }
}