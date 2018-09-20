#include <iostream>
#include <emscripten.h>
#include <memory>
#include <vector>

#include "body.h"
#include "quad.h"
#include "bhtree.h"

std::vector<std::shared_ptr<Body>> bodies;
double R;

void _init(int n_bodies, double *x_pos, double *y_pos, double *x_vel, double *y_vel, double *mass, double radius) {
    bodies.clear();
    R = radius;
    for (int i = 0; i < n_bodies; i++) {
        bodies.push_back(std::make_shared<Body>(x_pos[i], y_pos[i], x_vel[i], y_vel[i], mass[i]));
    }
}

void _step(double dt) {
    std::shared_ptr<Quad> quad = std::make_shared<Quad>(0, 0, R);
    std::shared_ptr<BHTree> tree = std::make_shared<BHTree>(quad);

    for (const auto &body : bodies) {
        if (body->in(quad)) {
            tree->insert(body);
        }
    }

    for (const auto &body : bodies) {
        body->resetForce();
        tree->updateForce(body);
        body->update(dt);
    }
}

double *_getXPos() {
    auto xPos = (double *) malloc(bodies.size() * sizeof(double));
    for (int i = 0; i < bodies.size(); i++) {
        xPos[i] = bodies[i]->x;
    }
    return xPos;
}

double *_getYPos() {
    auto yPos = (double *) malloc(bodies.size() * sizeof(double));
    for (int i = 0; i < bodies.size(); i++) {
        yPos[i] = bodies[i]->y;
    }
    return yPos;
}

extern "C" {

void init(int n_bodies, double *x_pos, double *y_pos, double *x_vel, double *y_vel, double *mass, double radius) {
    _init(n_bodies, x_pos, y_pos, x_vel, y_vel, mass, radius);
}

void step(double dt) {
    _step(dt);
}

double *getXPos() {
    return _getXPos();
}

double *getYPos() {
    return _getYPos();
}

}

int main() {
    emscripten_exit_with_live_runtime();
    return 0;
}
