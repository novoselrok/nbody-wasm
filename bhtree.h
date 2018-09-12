#ifndef NBODY_WASM_BHTREE_H
#define NBODY_WASM_BHTREE_H

#include <memory>

#include "body.h"

class BHTree {
private:
    const double THETA = 0.5;

    std::shared_ptr<Body> body;
    std::shared_ptr<Quad> quad;
    std::shared_ptr<BHTree> firstQuad;
    std::shared_ptr<BHTree> secondQuad;
    std::shared_ptr<BHTree> thirdQuad;
    std::shared_ptr<BHTree> fourthQuad;

public:
    BHTree(const std::shared_ptr<Quad> &quad);

    void insert(const std::shared_ptr<Body> &body);

    void putBody(const std::shared_ptr<Body> &body);

    bool isExternal();

    void updateForce(const std::shared_ptr<Body> &body);
};


#endif //NBODY_WASM_BHTREE_H
