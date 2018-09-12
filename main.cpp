#include <iostream>
#include <memory>
#include <vector>

#include "quad.h"
#include "body.h"
#include "bhtree.h"

int main() {
    double dt = 0.1;
    double radius = 2.5E11;

    std::vector<std::shared_ptr<Body>> bodies;
    bodies.push_back(std::make_shared<Body>(0.0, 0.0, 0.0, 0.0, 4.97250E41));
    bodies.push_back(std::make_shared<Body>(5.790E10, 0.0, 0.0, 2.395E10, 8.25500E34));


    for (double t = 0; t < 0.5; t += dt) {
        std::shared_ptr<Quad> quad = std::make_shared<Quad>(0, 0, radius);
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

        for (const auto &body : bodies) {
            printf("%10.3E %10.3E %10.3E %10.3E\n", body->x, body->y, body->vx, body->vy);
        }

        printf("======\n");
    }
    return 0;
}
