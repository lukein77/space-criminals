#include "Entity.h"

Entity::Entity() {}

Entity::Entity(int x, int y, SDL_Texture *texture) {
    this->x = x;
    this->y = y;
    this->texture = texture;
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

void Entity::setXSpeed(int dx) {
    this->dx = dx;
}

void Entity::setYSpeed(int dy) {
    this->dy = dy;
}

void Entity::setTexture(SDL_Texture *texture) {
    this-> texture = texture;
}

void Entity::update() {
    x += dx;
    y += dy;
}