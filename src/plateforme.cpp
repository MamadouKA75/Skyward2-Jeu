#include "plateforme.h"
#include <cassert>

Plateforme::Plateforme(const Rectangle &r, double reb,int i) : rect(r), rebond(reb) ,id(i){}

Plateforme::Plateforme(const Rectangle &r, double reb,int i, Vector2<double> vit) : rect(r), rebond(reb) ,id(i),vitesse(vit){}

const Rectangle & Plateforme::valRectangle() const {
    return rect;
}

double Plateforme::valRebond() const {
    return rebond;
}

Vector2<double> Plateforme:: valVitesse() const{
    return vitesse;
}

void Plateforme::modifierRectangle(const Rectangle & r) {
    rect = r;
}

void Plateforme::modifierRebond(double reb){
    rebond = reb;
}

Plateforme::Plateforme () {}


void Plateforme::modifierPosition(const Vector2<double> & pos) {
    rect.modifierPosition(pos);
} 

 void Plateforme::modifierVitesse(Vector2<double> nouvVit){
    vitesse=nouvVit;
 }

int Plateforme::valId() const{
    return id;
}

void Plateforme::actualise(double dt) {
    
    rect.modifierPosition(rect.valPosition() + vitesse * dt);
}

void Plateforme::testRegression () {
    //Test de la classe Plateforme
    Rectangle rect(Vector2<double>(0,0), 2.0, 1.0);
    double rebond = 1.0;

    Plateforme plateforme(rect, rebond,0);
    assert(plateforme.valRectangle().valPositionX() ==0);
    assert(plateforme.valRectangle().valPositionY() ==0);
    assert(plateforme.valRectangle().valHauteur() == 2.0);
    assert(plateforme.valRectangle().valLargeur() == 1.0);
    Rectangle new_rect(Vector2<double>(0,0), 3.0, 1.0);
    plateforme.modifierRectangle(new_rect);
    assert(plateforme.valRectangle().valPositionX() == 0);
    assert(plateforme.valRectangle().valPositionY() == 0);
    assert(plateforme.valRectangle().valHauteur() == 3.0);
    assert(plateforme.valRectangle().valLargeur() == 1.0);


    double new_rebond = 0.0;
    plateforme.modifierRebond(new_rebond);
    assert(plateforme.valRebond() == 0.0);

    Vector2<double> nouvelle_pos(5.0, 5.0);
    plateforme.modifierPosition(nouvelle_pos);
    assert(plateforme.valRectangle().valPositionX() == nouvelle_pos.x );
    assert(plateforme.valRectangle().valPositionY() == nouvelle_pos.y );

}
