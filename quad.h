#ifndef NBODY_WASM_QUAD_H
#define NBODY_WASM_QUAD_H

#include <memory>


class Quad {
private:
    double xMid;
    double yMid;
    double length;

public:
    Quad(double xMid, double yMid, double length);

    double getLength() const;

    bool contains(double x, double y);

    std::shared_ptr<Quad> firstQuad();

    std::shared_ptr<Quad> secondQuad();

    std::shared_ptr<Quad> thirdQuad();

    std::shared_ptr<Quad> fourthQuad();
};


#endif //NBODY_WASM_QUAD_H
