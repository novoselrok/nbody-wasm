//
// Created by rok on 10.9.2018.
//

#include "bhtree.h"

BHTree::BHTree(const std::shared_ptr<Quad> &quad) : quad(quad) {}

bool BHTree::isExternal() {
    return this->firstQuad == nullptr && this->secondQuad == nullptr && this->thirdQuad == nullptr &&
           this->fourthQuad == nullptr;
}

void BHTree::insert(const std::shared_ptr<Body> &body) {
    if (this->body == nullptr) {
        this->body = body;
        return;
    }

    if (this->isExternal()) {
        this->firstQuad = std::make_shared<BHTree>(this->quad->firstQuad());
        this->secondQuad = std::make_shared<BHTree>(this->quad->secondQuad());
        this->thirdQuad = std::make_shared<BHTree>(this->quad->thirdQuad());
        this->fourthQuad = std::make_shared<BHTree>(this->quad->fourthQuad());

        this->putBody(this->body);
        this->putBody(body);

        this->body = this->body->plus(body);
    } else {
        this->body = this->body->plus(body);
        putBody(body);
    }
}

void BHTree::putBody(const std::shared_ptr<Body> &body) {
    if (body->in(this->quad->firstQuad())) {
        this->firstQuad->insert(body);
    } else if (body->in(this->quad->secondQuad())) {
        this->secondQuad->insert(body);
    } else if (body->in(this->quad->thirdQuad())) {
        this->thirdQuad->insert(body);
    } else if (body->in(this->quad->fourthQuad())) {
        this->fourthQuad->insert(body);
    }
}

void BHTree::updateForce(const std::shared_ptr<Body> &body) {
    if (this->body == nullptr || body == this->body) {
        return;
    }

    if (this->isExternal()) {
        body->addForce(this->body);
    } else {
        double s = this->quad->getLength();
        double d = this->body->distanceTo(body);

        if (s / d < THETA) {
            body->addForce(this->body);
        } else {
            this->firstQuad->updateForce(body);
            this->secondQuad->updateForce(body);
            this->thirdQuad->updateForce(body);
            this->fourthQuad->updateForce(body);
        }
    }
}
