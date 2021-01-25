#include "Entity.h"

Entity::Entity() {
    x = y = 0;
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
    if (health == 0) {
        this->die();
    }
} 

bool Entity::checkCollision(SDL_Rect *a, SDL_Rect *b) {
    if (SDL_HasIntersection(a, b) == SDL_TRUE) {
        return true;
    } else {
        return false;
    }
}