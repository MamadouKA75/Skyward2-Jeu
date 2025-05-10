#include "monde.h"
#include <cstdlib>
#include <ctime>
#include "personnage.h"
#include "plateforme.h"
#include <iostream>
#include <stdlib.h>
#include "piece.h"



using namespace std;

Monde::Monde() {
    score = 0;
    dimension = Vector2<double>(400, 1000);
    Vector2<double> v(0,25);
    Vector2<double> pos(dimension.x*0.5 - dimension.x*0.1*0.5*0.5,0);//dimension.y*0.5 - dimension.y*0.1/2);
    Vector2<double> p(0,-9.81);
    Rectangle r(pos, dimension.y*0.1*0.55,dimension.x*0.1*0.55); //pos
    perso = Personnage(v,10,p,r);
    pieces_amassees = 0;
}

void Monde::supprToutHorsMonde() {
    //cout<<"nombre de plateformes : "<<liste_plat.size()<<endl;
    // Suppression des plateformes hors du monde
    for (long unsigned int i = 0; i < liste_plat.size(); i++) {
        if (liste_plat[i].valRectangle().valPositionY() < -dimension.y*0.55 + score) {
            liste_plat.erase(liste_plat.begin() + i);
        }
    }
    // Suppression des obstacles hors du monde
    for (long unsigned int i = 0; i < liste_obstacle.size(); i++) {
        if (liste_obstacle[i].valRectangle().valPositionY() < -dimension.y*0.55 + score) {
            liste_obstacle.erase(liste_obstacle.begin() + i);
        }
    }
    for (long unsigned int i = 0; i < liste_piece.size(); i++) {
        if (liste_piece[i].valPosition().y < -dimension.y*0.55 + score) {
            liste_piece.erase(liste_piece.begin() + i);
        }
    }
}


void Monde::initPosPerso(Vector2<double> position) {
    perso.modifierPosition(position);
}


Rectangle Monde::valRectanglePerso() const {
    return perso.valRectangle();
}


Vector2<double> Monde::valPositionPerso() const {
    return perso.valPosition();
}


Vector2<double> Monde::valDimension() const {
    return dimension;
}

bool Monde::actualiserPosPerso(double dt) {

    for (int i=0;i<dt*10;i++) {
        if (perso.limitMouvement == true) {
            perso.actualise(dt/10,-dimension.y*0.02,dimension.y*0.025);
        } else {
            perso.actualise(dt/10,-dimension.y,dimension.y);
        }
        
        if (score<perso.valPosition().y) {
            score += perso.valPosition().y - score;
            //cout<<"score actuelle : "<<(int)score<<endl;
        }else if (perso.valPosition().y<score - dimension.y*0.55) {
            //cout<<"Partie Terminee"<<endl;
            //cout<<"Score : "<<(int)score<<endl;
            return false;
        }
        if (perso.descendre()) {
            perso.limitMouvement = true;
            Rectangle hitbox(perso.valPosition(),perso.valRectangle().valHauteur()*0.3,perso.valRectangle().valLargeur());
            for (long unsigned int i = 0; i < liste_plat.size(); i++) {
                if (liste_plat[i].valRectangle().estEnColision(hitbox)) {
                    perso.sautEnDescente(liste_plat[i].valRebond());
                    
                    if ((liste_plat[i].valId()==CASSABLE) ||(liste_plat[i].valId()==FAUSSE))
                        liste_plat.erase(liste_plat.begin() + i);
                    else if (liste_plat[i].valId() == RESSORT) perso.limitMouvement = false;
                    break;
                }
            }
        }

        double tx = dimension.x*0.00007*0.1*(dt/10); 
        double ty = dimension.y*0.00007*0.1*(dt/10); 
        for (long unsigned int i = 0; i < liste_obstacle.size(); i++) {
            if (liste_obstacle[i].valRectangle().estEnColision(perso.valRectangle())) {
                return false;
            } else if (liste_obstacle[i].valId()==0){
                liste_obstacle[i].modifierPosition(Vector2<double>((1.0-tx)*liste_obstacle[i].valRectangle().valPositionX() + tx*(perso.valPosition().x + perso.valRectangle().valLargeur()),(1.0-ty)*liste_obstacle[i].valRectangle().valPositionY() + ty*(perso.valPosition().y+perso.valRectangle().valHauteur())));
            }
        }
        for (long unsigned int i = 0;  i < liste_plat.size(); i++){
            if(liste_plat[i].valId()==MOBILE){
               liste_plat[i].actualise(0.1);
            }
        }


        for (long unsigned int i = 0; i < liste_piece.size(); i++) {
            if (liste_piece[i].estEncolosionAvecRectangle(perso.valRectangle())) {
                pieces_amassees++;
                cout<<"nombre de pieces : "<<pieces_amassees<<endl;
                liste_piece.erase(liste_piece.begin() + i);
            }
        }

    }
    supprToutHorsMonde();
    generationSuiteMonde();
    return true;
}



const vector<Plateforme> & Monde::valListPlateforme() const {
    return liste_plat;
}
const vector<Obstacle> & Monde::valListObstacle() const {
    return liste_obstacle;
}

const vector<Piece> & Monde::valListPiece() const {
    return liste_piece;
}

void Monde::initDebutMonde() {
    srand(time(NULL));
    double reb = dimension.y/40;
    /*for (int i = 1; i < 0; i++) { //6
        Vector2<double> pos(rand() % (int)(dimension.x - dimension.x*0.2), (int)dimension.y*0.1*i);
        Rectangle rect(pos,dimension.y*0.01,dimension.x*0.2);
        Plateforme p(rect,reb);
        liste_plat.push_back(p);
    }*/
    //plat millieu
    for (int i = 0; i < 6; i++) { //6
        Vector2<double> pos((int)dimension.x*0.5 - dimension.x*0.8*0.5 , (int)dimension.y*i*0.2);
        Rectangle rect(pos,dimension.y*0.01,dimension.x*0.8);
        Plateforme p(rect,reb,STABLE);
        liste_plat.push_back(p);
    }
    
    /*Plateforme debut(Rectangle(Vector2<double>(dimension.x/2-dimension.x*0.2/2,dimension.y*0.1),dimension.y*0.01,dimension.x*0.2),reb,3);
    liste_plat.push_back(debut);*/
    //Plateforme sol(Rectangle(Vector2<double>(0,0),3,dimension.x),reb);
    //liste_plat.push_back(sol);
    liste_obstacle.push_back(Obstacle(Rectangle(Vector2<double>(dimension.x*0.5-dimension.x*0.05*0.5,dimension.y*2.0),dimension.y*0.05,dimension.x*0.05),reb));    
}




void Monde::deplacerPersoX(double i) {
    perso.modifierPosition(perso.valPosition() - Vector2<double>(i,0));
    if (perso.valPosition().x<perso.valRectangle().valLargeur()*0.01) {
        Vector2<double> np(dimension.x*0.99-perso.valRectangle().valLargeur(),perso.valPosition().y);
        perso.modifierPosition(np);
    }
    if (perso.valPosition().x>dimension.x-perso.valRectangle().valLargeur()*0.99)  {
        Vector2<double> np(dimension.x*0.01,perso.valPosition().y);
        perso.modifierPosition(np);
    }
}

double Monde::valHautMax() const {
    return score;
}


int choix_id_plat(int prc_id_0, int prc_id_1, int prc_id_2, int prc_id_3, int prc_id_4){
    int prc=(rand()%100) + 1;
    int cmpt = 0;
    cmpt += prc_id_0;
    if (cmpt>=prc) return 0;
    cmpt += prc_id_1;
    if (cmpt>=prc) return 1;
    cmpt += prc_id_2;
    if (cmpt>=prc) return 2;
    cmpt += prc_id_3;
    if (cmpt>=prc) return 3;
    cmpt += prc_id_4;
    if (cmpt>=prc) return 4;
    return -1;
}


void Monde::generationSuiteMonde() {
    double reb = dimension.y/40;
    // Ajout d'une nouvelle plateforme si nécessaire
    Plateforme& dern_plat = liste_plat.back();
    Vector2<double> dern_pos = dern_plat.valRectangle().valPosition();
    int id;
    double larg;
    double haut;
    Vector2<double> posZone;
    double largeurZone;
    double hauteurZone;
    Vector2<double>vit;
    Vector2<double> posFausse;
    
    



    if (dern_plat.valRectangle().valPositionY() <= dimension.y*0.5 + score + dimension.y*0.25) {

        Vector2<double> position(rand() % int(dimension.x - dimension.x*0.2),dern_pos.y + dimension.y*0.25);
        id=choix_id_plat(33,33,34,0,0);
        larg = dimension.x*0.2;
        haut = dimension.y*0.04;
        if(id==MOBILE){
            double lat = (double)(rand()%2);
            double hor ;
            largeurZone=200;
            hauteurZone=200;
            posZone.x=position.x-dimension.x*0.1;
            posZone.y=position.y-dimension.y*0.1;
            if(posZone.x<0)posZone.x=0;
            if(posZone.x>dimension.x-largeurZone)posZone.x=dimension.x-largeurZone;
            if (lat==0)  hor = 1;
            else hor = (double)(rand()%2);
            vit.x = (double)(dimension.x)*0.001 * lat;
            vit.y= (double)(dimension.y)*0.001 * hor;
            Rectangle zone(posZone,hauteurZone,largeurZone);
            Plateforme nv_plat(Rectangle(position,haut,larg),reb,id,vit,zone);
            liste_plat.push_back(nv_plat);
        }else{
            Plateforme nv_plat(Rectangle(position,haut,larg),reb,id);
            liste_plat.push_back(nv_plat);
        }

        if ((rand()%2)==0 && id==0) {
            position.y += haut;
            Plateforme ressort(Rectangle(position,haut,larg/2.5),reb*2,RESSORT);
            liste_plat.push_back(ressort);
        }
         if (rand()%5==0){
            posFausse.y=position.y;
            if(position.x<dimension.x/2){
                posFausse.x=(dimension.x/2)+(double)(rand()%(int)((dimension.x/2)-larg));
                if((id == MOBILE) && (posFausse.x+larg>posZone.x) && (posFausse.x<posZone.x+largeurZone))posFausse+= posZone.x-posFausse.x;
            }
            if(position.x>dimension.x/2){
                posFausse.x=(double)(rand()%(int)(position.x-larg));
                if((id == MOBILE) && (posFausse.x+larg>posZone.x) && (posFausse.x<posZone.x+largeurZone))posFausse-= (posFausse.x+larg)-posZone.x;
            }

            Plateforme fausse(Rectangle(posFausse,haut,larg),0,FAUSSE);
            liste_plat.push_back(fausse);
        }
        if (rand()%3==0) {
            Piece nv_piece(Piece(Vector2<double>(position.x + larg/2 , position.y + dimension.y * 0.05),dimension.y*0.01456789));
            liste_piece.push_back(nv_piece);
        }
        //Obstacle dern_obs = liste_obstacle.back();
        //dern_pos = dern_obs.valRectangle().valPosition();
        //if ((dern_plat.valRectangle().valPositionY() <= dimension.y*0.5 + score + dimension.y*1.5) ) {
            if ((rand()%10)==0) {
                Obstacle nv_obs(Rectangle(Vector2<double>(rand() % int(dimension.x - dimension.x*0.2), score + dimension.y),dimension.y*0.05,dimension.x*0.05),rand()%3);
                liste_obstacle.push_back(nv_obs);

            }
    }
    

    


    // Suppression des plateformes hors du monde
    //supprToutHorsMonde();
}


void Monde::actualiserPosObstacle() {
}
