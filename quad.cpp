#include <memory>

#include "quad.h"

Quad::Quad(double xMid, double yMid, double length) : xMid(xMid), yMid(yMid), length(length) {}

double Quad::getLength() const {
    return length;
}

bool Quad::contains(double x, double y) {
    double halfLen = this->length / 2;
    return x <= this->xMid + halfLen &&
           x >= this->xMid - halfLen &&
           y <= this->yMid + halfLen &&
           y >= this->yMid - halfLen;
}

std::shared_ptr<Quad> Quad::firstQuad() {
    return std::make_shared<Quad>(this->xMid + this->length / 4.0, this->yMid + this->length / 4.0, this->length / 2.0);
}

std::shared_ptr<Quad> Quad::secondQuad() {
    return std::make_shared<Quad>(this->xMid - this->length / 4.0, this->yMid + this->length / 4.0, this->length / 2.0);
}

std::shared_ptr<Quad> Quad::thirdQuad() {
    return std::make_shared<Quad>(this->xMid + this->length / 4.0, this->yMid - this->length / 4.0, this->length / 2.0);
}

std::shared_ptr<Quad> Quad::fourthQuad() {
    return std::make_shared<Quad>(this->xMid - this->length / 4.0, this->yMid - this->length / 4.0, this->length / 2.0);
}
