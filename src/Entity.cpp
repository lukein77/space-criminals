#include "Entity.h"

Entity::Entity() {
    x = y = 0;
    speed = 0;
    health = 1;
}

Entity::Entity(int x, int y, Texture *texture) {
    this->texture.rect.x = x;
    this->texture.rect.y = y;
    this->texture = *texture;
}

void Entity::setX(int x) {
    this->texture.rect.x = x;
}

void Entity::setY(int y) {
    this->texture.rect.y = y;
}

void Entity::setPos(int x, int y) {
    this->texture.rect.x = x;
    this->texture.rect.y = y;
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

/* Returns a normalized vector between two points.*/
vector Entity::getVector(float x1, float x2, float y1, float y2) {
    vector v;

    v.x = x2 - x1;
    v.y = y2 - y1;
    
    double length = sqrt((v.x * v.x) + (v.y * v.y));
    v.x = v.x / length;
    v.y = v.y / length;

    return v;
}