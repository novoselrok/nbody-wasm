#ifndef NBODY_WASM_BODY_H
#define NBODY_WASM_BODY_H

#include <memory>

#include "quad.h"

class Body {
public:
    const double G = 6.67e-11;

    // Position
    double x, y;
    // Velocity
    double vx, vy;
    // Force
    double fx = 0.0, fy = 0.0;
    // Mass
    double mass;


    Body(double x, double y, double vx, double vy, double mass);

    void resetForce();

    void update(double dt);

    double distanceTo(const std::shared_ptr<Body> &otherBody);

    void addForce(const std::shared_ptr<Body> &otherBody);

    bool in(const std::shared_ptr<Quad> &quad);

    std::shared_ptr<Body> plus(const std::shared_ptr<Body> &otherBody);
};


#endif //NBODY_WASM_BODY_H
