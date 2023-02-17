#include "Entity.h"

Entity::Entity() {
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

void Entity::move() {
    setX(getX() + direction.x * speed);
    setY(getY() + direction.y * speed);
}

void Entity::setDirection(double x, double y) {
    this->direction.x = x;
    this->direction.y = y;
    normalizeDirection();
}

void Entity::setDirectionX(double x) {
    this->direction.x = x;
    normalizeDirection();
}

void Entity::setDirectionY(double y) {
    this->direction.y = y;
    normalizeDirection();
}

void Entity::normalizeDirection() {
    double length = sqrt((direction.x*direction.x) + (direction.y*direction.y));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
}

void Entity::setDirectionTowardsPoint(int x1, int y1, int x2, int y2) {
    this->direction = getVector(x1, y1, x2, y2);
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
vector Entity::getVector(int x1, int y1, int x2, int y2) {
    vector v;

    v.x = x2 - x1;
    v.y = y2 - y1;
    
    double length = sqrt((v.x * v.x) + (v.y * v.y));
    v.x = v.x / length;
    v.y = v.y / length;

    return v;
}