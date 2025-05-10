#ifndef PIECE_H
#define PIECE_H

#include <SDL2/SDL.h>
#include "rectangle.h"
/**
 * @class Piece
 * 
 * @brief  Représente une piece
*/
class Piece{
    private:
        Vector2<double> pos; /**< position */
        //rayon de la piece
        double rayon; /**< rayon */
    
    public:
        Piece();
        /**
         * @brief Constructeur de la classe Piece
         * @param pos : un objet Vector2 représentant la position de la piece
         * @param r : un double représentant le rayon de la piece
         */
        Piece(const Vector2<double> &pos, double r);
        /**
         * @brief pour obtenir la position de la piece
         * @return un objet Vector2 représentant la position de la piece
         */
        const Vector2<double> & valPosition() const;
        /**
         * @brief pour obtenir le rayon de la piece
         * @return un double représentant le rayon de la piece
         */
        double valRayon() const;
        /**
         * @brief pour modifier la position de la piece
         * @param pos : un objet Vector2 représentant la nouvelle position de la piece
         */
        void modifierPosition(const Vector2<double> &pos);
        /**
         * @brief pour modifier le rayon de la piece
         * @param r : un double représentant le nouveau rayon de la piece
         */
        void modifierRayon(double r);
        /**
         * @brief colision entre la piece et un rectangle
         * @param rect : un objet Rectangle représentant le rectangle avec lequel on veut tester la colision
         * @return un booléen représentant si il y a colision ou non
         */
        bool estEncolosionAvecRectangle(const Rectangle &rect) const;
        /**
         * @brief test de regression de la classe
         */
        void testRegression();
};

#endif