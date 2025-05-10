#ifndef _MONDE_H_
#define _MONDE_H_

#include "obstacle.h"
#include "personnage.h"
#include "rectangle.h"
#include "plateforme.h"
#include "Vector2.hpp"
#include "piece.h"
#include <vector>


/**
 * @class Monde
 * 
 * @brief classe monde ayant un personnage,des plateformes, des obstacles...
*/
class Monde {
    private:
        Personnage perso; /**< Le personnage du monde*/
        vector<Plateforme> liste_plat; /**< La liste de plateformes du monde*/
        double score; /**< Le score du monde (hauteur)*/
        double vit;/**< La vitesse du monde*/
        Vector2<double> dimension; /**< La dimension du monde*/
        vector<Obstacle> liste_obstacle; /**< La liste d'obstacles*/
        vector<Piece> liste_piece; /**< La liste de pièces*/
        double pieces_amassees;

        /**
         * @brief Permet de supprimmer les plateformes et obstacles hors du monde
        */
        void supprToutHorsMonde();

        /**
         * @brief Initialise la position du personnage 
         * @param Position à laquelle le personnage va etre placé
        */
        void initPosPerso(Vector2<double> position);

        /**
         * @brief Initialise aléatoirement le monde
        */
        void creationAleaMonde();

        /**
         * @brief Permet de générer la suite du monde
        */
        void generationSuiteMonde();

        /**
         * @brief Permet d'actualiser la position des obstacles qui bougent
        */
        void actualiserPosObstacle();

        /**
         * @brief Permet d'actualiser la position des plateformes qui bougent
        */
        void actualiserPosPlateformes();

        
    public:

        /**
         *
         *
        */
        enum TypePlateforme { STABLE = 0, CASSABLE = 1, MOBILE = 2, RESSORT = 3, FAUSSE=4};
        /**
         * @brief Actualise la position du personnage
         * @return id de l'état du personnage
        */
        bool actualiserPosPerso(double dt);

        /**
         * @brief Constructeur par défault du monde 
        */
        Monde() ;


        /**
         * @brief Initialise le monde 
        */
        void initDebutMonde();

        /**
         * @brief Actualise l'intégralité du monde en prenant en compte tous les parametres
         * @return Booléen pour savoir si le personnage est encore vie
        */
        bool actualiser();


        /**
         * @brief Renvoie le Rectangle du personnage
         * @return Un objet rectangle représentant le rectangle du personnage
        */
        Rectangle valRectanglePerso() const ;
        
        /**
         * @brief Renvoie la position du personnage
         * @return Un objet Vector2<double> représentant la position du personnage  
        */
        Vector2<double>  valPositionPerso() const ;

        /**
         * @brief Renvoie la dimension du monde
         * @return Un objet Vector2<double> représentant la dimension du monde
        */
        Vector2<double> valDimension() const ;

        /**
         * @brief Renvoie la liste de toute les plateforme qui sont dans le monde
         * @return Un objet vecteur représentant la liste des plateformes du monde
        */
        const vector<Plateforme> & valListPlateforme() const ;
        
        /**
         * @brief Renvoie la liste de toute les pièces qui sont dans le monde
         * @return Un objet vecteur représentant la liste des pièces du monde
        */
        const vector<Piece> & valListPiece() const ;

        /**
         * @brief Deplace le personnage dans l'axe des abscisse du monde
         * @param i représante le déplacement du personnage
        */
        void deplacerPersoX(double i) ;

        /**
         * @brief Retourne la hauteur limite que peut atteindre le personnage sur l'affichage actuelle
         * @return Un objet double 
        */
        double valHautMax() const ;



        /**
         * @brief Renvoie la liste de tout les obstacles qui sont dans le monde
         * @return Un objet vecteur représentant la liste des obstacles du monde
        */
        const vector<Obstacle> & valListObstacle() const ;



};






#endif // fin _MONDE_H_