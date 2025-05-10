#include "piece.h"
#include <math.h>

Piece::Piece(const Vector2<double> &pos, double r) : pos(pos), rayon(r) {}

const Vector2<double> & Piece::valPosition() const {
    return pos;
}

double Piece::valRayon() const {
    return rayon;
}

void Piece::modifierPosition(const Vector2<double> &pos) {
    this->pos = pos;
}

void Piece::modifierRayon(double r) {
    this->rayon = r;
}



bool Piece::estEncolosionAvecRectangle(const Rectangle &rect) const {
    float cx = pos.x;
    float cy = pos.y;
    float radius = rayon;
    float rx = rect.valPositionX();
    float ry = rect.valPositionY();
    float rw = rect.valLargeur();
    float rh = rect.valHauteur();
    // temporary variables to set edges for testing
    float testX = cx;
    float testY = cy;

    // which edge is closest?
    if (cx < rx)         testX = rx;      // test left edge
    else if (cx > rx+rw) testX = rx+rw;   // right edge
    if (cy < ry)         testY = ry;      // top edge
    else if (cy > ry+rh) testY = ry+rh;   // bottom edge

    // get distance from closest edges
    float distX = cx-testX;
    float distY = cy-testY;
    float distance = sqrt((distX*distX) + (distY*distY));

    // if the distance is less than the radius, collision!
    if (distance <= radius) {
        return true;
    }
    return false;
}

void Piece::testRegression() {
    //Test de la classe Piece
    Vector2<double> pos(0,0);
    double r = 1.0;
    Piece piece(pos, r);
    assert(piece.valPosition().x == 0);
    assert(piece.valPosition().y == 0);
    assert(piece.valRayon() == 1.0);
    Vector2<double> new_pos(5.0, 5.0);
    piece.modifierPosition(new_pos);
    assert(piece.valPosition().x == new_pos.x);
    assert(piece.valPosition().y == new_pos.y);
    double new_r = 2.0;
    piece.modifierRayon(new_r);
    assert(piece.valRayon() == new_r);
}