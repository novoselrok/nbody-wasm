#include <cmath>
#include "body.h"

Body::Body(double x, double y, double vx, double vy, double mass) : x(x), y(y), vx(vx), vy(vy), mass(mass) {}

void Body::resetForce() {
    this->fx = 0.0;
    this->fy = 0.0;
}

void Body::update(double dt) {
    this->vx += dt * this->fx / this->mass;
    this->vy += dt * this->fy / this->mass;
    this->x += dt * this->vx;
    this->y += dt * this->vy;
}

double Body::distanceTo(const std::shared_ptr<Body> &otherBody) {
    double dx = this->x - otherBody->x;
    double dy = this->y - otherBody->y;
    return sqrt(dx * dx + dy * dy);
}

void Body::addForce(const std::shared_ptr<Body> &otherBody) {
    double EPS = 3e4;
    double dx = otherBody->x - this->x;
    double dy = otherBody->y - this->y;
    double dist = sqrt(dx * dx + dy * dy);
    double F = (G * this->mass * otherBody->mass) / (dist * dist + EPS * EPS);
    this->fx += F * dx / dist;
    this->fy += F * dy / dist;
}

bool Body::in(const std::shared_ptr<Quad> &quad) {
    return quad->contains(this->x, this->y);
}

std::shared_ptr<Body> Body::plus(const std::shared_ptr<Body> &otherBody) {
    double totalMass = this->mass + otherBody->mass;
    double newX = (this->x * this->mass + otherBody->x * otherBody->mass) / totalMass;
    double newY = (this->y * this->mass + otherBody->y * otherBody->mass) / totalMass;

    return std::make_shared<Body>(newX, newY, this->vx, this->vy, totalMass);
}
