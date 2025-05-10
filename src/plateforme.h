#include "rectangle.h"
#ifndef _PLATEFORME_H_
#define _PLATEFORME_H_


/**
 * @class Plateforme
 * 
 * @brief  Représente une plateforme
*/
class Plateforme {
    private:
        Rectangle rect; /**< forme rectangulaire de la plateforme */ 
        double rebond; /**< vecteur de rebondissement de la balle lorsqu'elle touche la plateforme */
        int id;/**< id de la plateforme*/
        Vector2<double> vitesse;
        
    public:
        Plateforme ();
        /**
         * @brief Constructeur de la classe Plateforme
         * @param rect : un objet Rectangle représentant la forme rectangulaire de la plateforme
         * @param rebond : un objet Vector2 représentant le vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         * @param i : un int unique pour chaque Plateforme
         */
        Plateforme(const Rectangle &r, double reb,int i);

        /**
         * @brief Constructeur de la classe Plateforme avec sa vitese
         * @param rect : un objet Rectangle représentant la forme rectangulaire de la plateforme
         * @param rebond : un objet Vector2 représentant le vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         * @param i : un int unique pour chaque Plateforme
         * @param vit : un objet Vector2 représentant la vitesse de déplacement de la plateforme
         */
        Plateforme(const Rectangle &r, double reb,int i, Vector2<double> vit);

        /** 
         * @brief pour obtenir la forme rectangulaire de la plateforme
         * @return un objet Rectangle représentant la forme rectangulaire de la plateforme
         */
        const Rectangle & valRectangle() const;

        /** 
         * @brief Méthode pour obtenir le vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         * @return un objet Vector2 représentant le vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         */
        double valRebond() const ;

        /**
         * @brief Méthode pour obtenir le vecteur de vitesse de la plateforme
         * @return un objet Vector2 représentant le vecteur de vitesse de la plateforme
        */
        Vector2<double> valVitesse() const;

        /**
         * @brief Méthode pour modifier la forme rectangulaire de la plateforme
         * @param r : un objet Rectangle représentant la nouvelle forme rectangulaire de la plateforme
         */
        void modifierRectangle(const Rectangle &r);

        /**
         * @brief pour modifier le vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         * @param rebond : un objet Vector2 représentant le nouveau vecteur de rebondissement de la balle lorsqu'elle touche la plateforme
         */
        void modifierRebond(double rebond);

        /**
         * @brief Méthode pour modifier la vitesse de la plateforme
         * @param nouvVit: un objet Vector2 représentant la nouvelle vitesse de la plateforme
        */
        void modifierVitesse(Vector2<double> nouvVit);

        void actualise (double dt);


        /**
         * @brief 
         * @param pos 
         */
        void modifierPosition(const Vector2<double> &pos) ;


        /**
         * @brief test de regression de la classe
         */
         void testRegression () ;



        /**
         * @brief renvoie l'id de la plateforme
         * @return id 
        */
        int valId() const;
};

#endif // _PLATEFORME_H_
