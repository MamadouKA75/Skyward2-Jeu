#include "jeusdl2.h"
#include <iostream>
#include <time.h>
#include <ctime>
#include "SDL2/SDL_mixer.h"
using namespace std;
double deplacement = 0.0;




struct Button {
    int x, y;
    SDL_Rect rect;
    std::string text;
    SDL_Color textColor;
    SDL_Texture* texture;
};


void JeuSdl2::initFenetre() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " <<
        SDL_GetError() << std::endl;
        SDL_Quit();
    }
    fenetre = SDL_CreateWindow( "SkyWard",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, DimX, DimY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    rendu = SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED);
    SDL_Surface *surfaceFond=IMG_Load("data/nuages.png");
    textureFond=SDL_CreateTextureFromSurface(rendu, surfaceFond);
}

void JeuSdl2::detruireFenetre() {
    //SDL_DestroyTexture(jouerTexture);
    //SDL_DestroyTexture(quitTexture);
    SDL_DestroyTexture(textureFond);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}



void JeuSdl2::afficherPerso(double dist) {
    Rectangle rect_perso = monde.valRectanglePerso();
    SDL_Rect rect;
    rect.x = rect_perso.valPositionX() * DimX / monde.valDimension().x ;
    rect.y = DimY - (rect_perso.valPositionY()+rect_perso.valHauteur()) * DimY / monde.valDimension().y + dist;
    rect.w =  rect_perso.valLargeur() * DimX / monde.valDimension().x ;
    rect.h =  rect_perso.valHauteur() * DimY / monde.valDimension().y ;

    SDL_SetRenderDrawColor(rendu, 100, 255 ,0, 255);
    SDL_RenderFillRect(rendu,&rect);

}


void JeuSdl2::afficherPlateformes(double dist) {
    // plateforme
    SDL_SetRenderDrawColor(rendu, 255,255,0, 0);
    SDL_Rect r;
    vector<Plateforme> lp = monde.valListPlateforme();
    for (long unsigned int i=0; i<lp.size();i++) {
        r.x = lp[i].valRectangle().valPositionX() * DimX / monde.valDimension().x ;
        r.y = DimY - (lp[i].valRectangle().valPositionY()+lp[i].valRectangle().valHauteur()) * DimY / monde.valDimension().y + dist;
        r.w = lp[i].valRectangle().valLargeur() * DimX / monde.valDimension().x ;
        r.h = lp[i].valRectangle().valHauteur() * DimY / monde.valDimension().y ;
        if (lp[i].valId()==Monde::CASSABLE)   SDL_SetRenderDrawColor(rendu, 255,0,0, 0);
        else if (lp[i].valId()==Monde::RESSORT)   SDL_SetRenderDrawColor(rendu, 100,100,255, 0);
        else if(lp[i].valId()==Monde::MOBILE) SDL_SetRenderDrawColor(rendu, 255,0,255, 0);
        else if(lp[i].valId()==Monde::STABLE) SDL_SetRenderDrawColor(rendu, 255,255,0, 0);
        else if(lp[i].valId()==Monde::FAUSSE) SDL_SetRenderDrawColor(rendu,127,81,18,0);
        SDL_RenderFillRect(rendu,&r);

        if (lp[i].valId()==Monde::MOBILE) {
            r.x = lp[i].valRectZone().valPositionX() * DimX / monde.valDimension().x ;
            r.y = DimY - (lp[i].valRectZone().valPositionY()+lp[i].valRectZone().valHauteur()) * DimY / monde.valDimension().y + dist;
            r.w = lp[i].valRectZone().valLargeur() * DimX / monde.valDimension().x ;
            r.h = lp[i].valRectZone().valHauteur() * DimY / monde.valDimension().y ;
            SDL_SetRenderDrawColor(rendu, 255,255,255, 0);
            SDL_RenderDrawRect(rendu,&r);
        }
        
    }
}
void JeuSdl2::afficherObstacles(double dist) {
    SDL_Rect r;
    vector<Obstacle> lo = monde.valListObstacle();
    for (long unsigned int i=0; i<lo.size();i++) {
        r.x = lo[i].valRectangle().valPositionX() * DimX / monde.valDimension().x ;
        r.y = DimY - (lo[i].valRectangle().valPositionY()+lo[i].valRectangle().valHauteur()) * DimY / monde.valDimension().y + dist;
        r.w = lo[i].valRectangle().valLargeur() * DimX / monde.valDimension().x ;
        r.h = lo[i].valRectangle().valHauteur() * DimY / monde.valDimension().y ;
        if (lo[i].valId()==0)   SDL_SetRenderDrawColor(rendu, 255,165,0, 0);
        else SDL_SetRenderDrawColor(rendu, 0,255,255, 0);
        SDL_RenderFillRect(rendu,&r);
    }
}


void JeuSdl2::SDL_RenderFillCircle(SDL_Renderer* rend, int x0, int y0, int radius)
{
    if (x0-radius>DimX)return ;
    if (y0-radius>DimY)return ;
	// Uses the midpoint circle algorithm to draw a filled circle
	// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	int x = radius;
	int y = 0;
	int radiusError = 1 - x;
	while (x >= y) {
		SDL_RenderDrawLine(rend, x + x0, y + y0, -x + x0, y + y0);
		SDL_RenderDrawLine(rend, y + x0, x + y0, -y + x0, x + y0);
		SDL_RenderDrawLine(rend, -x + x0, -y + y0, x + x0, -y + y0);
		SDL_RenderDrawLine(rend, -y + x0, -x + y0, y + x0, -x + y0);
		y++;
		if (radiusError < 0)
			radiusError += 2 * y + 1;
		else {
			x--;
			radiusError += 2 * (y - x + 1);
		}
	}
}

void JeuSdl2::afficherPieces(double dist) {
    vector<Piece> lo = monde.valListPiece();
    SDL_SetRenderDrawColor(rendu, 155,155,0, 0);
    for (long unsigned int i=0; i<lo.size();i++) {
        double x = lo[i].valPosition().x * DimX / monde.valDimension().x ;
        double y = DimY - (lo[i].valPosition().y) * DimY / monde.valDimension().y + dist;
        double r = lo[i].valRayon() * DimX / monde.valDimension().x ;
        SDL_RenderFillCircle(rendu,x,y,r);
    }
}


void JeuSdl2::afficherFond(){
    SDL_Rect Rectangle;
    Rectangle.x=0;
    if (monde.valHautMax()* DimY/monde.valDimension().y<DimY/2) 
        Rectangle.y = 0;
    
    else 
        Rectangle.y=((int) (monde.valHautMax()* DimY/monde.valDimension().y)%(int)DimY) - DimY/2;
    
    Rectangle.w=DimX;
    Rectangle.h=DimY;
    SDL_RenderCopy(rendu,textureFond,NULL,&Rectangle);
    Rectangle.y-=DimY;
    SDL_RenderCopy(rendu,textureFond,NULL,&Rectangle);
    Rectangle.y+=DimY*2;
    SDL_RenderCopy(rendu,textureFond,NULL,&Rectangle);


}


void JeuSdl2::boucleJeu() {
    SDL_Event e;
    bool quit = !boucleMenu(e, quit);
    monde.initDebutMonde();
    clock_t time;
    clock_t time2;

     
    
    time = clock();
	
	while (!quit) {
        
        double dist = 0;
        Vector2<double> a = monde.valDimension();
        if ( monde.valHautMax()> a.y/2 ) {
            dist = (monde.valHautMax() - a.y/2) * DimY/a.y;
            
        }
        //background
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 100);
        SDL_RenderClear(rendu);

        afficherFond();
        afficherPerso(dist);
        time2 = clock();
        quit = ! monde.actualiserPosPerso((double) 100 * (double) vitesse * (double) (clock() - time)/(double) CLOCKS_PER_SEC); //
        //cout << vitesse * (clock() - time)/CLOCKS_PER_SEC <<endl;
        time = time2;
        afficherPieces(dist);
        afficherPlateformes(dist);
        afficherObstacles(dist);
        


        
        // Afficher le score
      /*  //definir la police de caractère et la couleur du texte
        TTF_Font* font = TTSDL_RenderCopy(rendu,o,NULL,NULL);F_OpenFont("Sans.ttf", 100);
        SDL_Color textColor = { 255, 0, 0, 255 };
        // Mettre à jour le score
        int score = monde.valHautMax();
        //convertir le score en chaine de caractère
        std::string scoreStr = "Score: " + std::to_string(score);
        // Créer une surface à partir de la chaine de caractère
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
        // definir les coordonnées de placement du texte
        SDL_Rect scoreRect = { 10, 10, 0, 0};
        //creer une texture sdl à partir de la surface de texte
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(rendu, textSurface);
        //dessiner la texture de texte à l'écran
        SDL_RenderCopy(rendu, textTexture, NULL, &scoreRect);
        //liberer la mémoire utilisée par la surface de texte et la texture de texte
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        // Afficher le rendu à l'écran*/
        
        /*
        TTF_Font* font = TTF_OpenFont("Sans.ttf", 100);
        std::string scoreStr = "Score: " + std::to_string(monde.valHautMax());
        SDL_Color color = { 255, 0, 0, 255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, scoreStr.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
        SDL_Rect recto ;
        int u,ui;
        SDL_GetWindowSize(fe//cout<<"Partie Terminee"<<endl;
        //cout<<"Score : "<<(int)score<<endl;netre,&u,&ui);
        recto.x = 0;
        recto.y = 0;
        recto.w = u*0.5;
        recto.h = u*0.5;
        SDL_RenderCopy(rendu, texture, NULL, &recto);
        //SDL_FreeSurface(surface);
        //SDL_DestroyTexture(texture);
        */
		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        
        SDL_RenderPresent(rendu);
        //clavier
        quit = (quit || gestionInteractionClavier());
        
        
    }
    //system("clear");
    if (monde.valHautMax()>0) {
        cout<<"----------------------"<<endl;
        cout<<"Partie Terminee"<<endl;
        cout<<"Score : "<<monde.valHautMax()<<endl;
        cout<<"----------------------"<<endl;
    }
}

void jouerMusiqueFond() {
    
}


void JeuSdl2::jouer() {
    initFenetre();
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    int volume;
    volume = (MIX_MAX_VOLUME * 1) / 100;
    cout<<"volume : "<<volume<<endl;
    Mix_Music *m = NULL;
	m = Mix_LoadMUS("data/(FREE) clone1 type beat “REVIVAL”.wav");
	//Mix_Volume(1, volume);
    /*Mix_MasterVolume(volume);
	Mix_PlayMusic(m, -1);
    Mix_MasterVolume(volume);*/
    boucleJeu();
    Mix_FreeMusic(m);
    //Mix_Quit();
    //SDL_Quit();
    detruireFenetre();
    

}

    

JeuSdl2::JeuSdl2(unsigned int x,unsigned int y,double vit,double vitLat) :DimX(x),DimY(y),vitesse(vit),vitLaterale(vitLat) {

}



bool JeuSdl2::gestionInteractionClavier() {
    SDL_Event evenements;
    while (SDL_PollEvent(&evenements)) {
        if (evenements.type == SDL_QUIT) return true;          
        else if (evenements.type == SDL_KEYDOWN) {            
            switch (evenements.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    return true;
                    break;
                default: 
                    break;
            }
            switch( evenements.key.keysym.sym ){
                case SDLK_LEFT:
                    deplacement = vitLaterale*vitesse*monde.valDimension().x*300/CLOCKS_PER_SEC;
                    break;
                case SDLK_RIGHT:
                    deplacement = -vitLaterale*vitesse*monde.valDimension().x*300/CLOCKS_PER_SEC;
                    break;
                case SDLK_d :
                    deplacement = -vitLaterale*vitesse*monde.valDimension().x*300/CLOCKS_PER_SEC;
                    break;
                case SDLK_q :
                    deplacement = vitLaterale*vitesse*monde.valDimension().x*300/CLOCKS_PER_SEC;
                    break;
                default:
                    break;
            }
        } else if (evenements.type == SDL_WINDOWEVENT) {
            if (evenements.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(fenetre,&DimX,&DimY);
                if (DimX<100) {
                    DimX = 100;
                }
                if (DimY<200) {
                    DimY = 200;
                }
            }
        } else if (evenements.type == SDL_KEYUP) {
            deplacement = 0;
        }

	}
    monde.deplacerPersoX(deplacement);
    return false;
}






void JeuSdl2::dessinerMenu() {
    
    
}

    // Fonction pour charger les textures
SDL_Texture* loadTexture(SDL_Renderer* rendu, const char* fichier) {
    // Charger la surface depuis le fichier
    SDL_Surface* surface = IMG_Load(fichier);
    if (surface == NULL) {
        cout << "Erreur de chargement de la surface: " << SDL_GetError() << endl;
        return NULL;
    }

    // Creer la texture depuis la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    if (texture == NULL) {
        cout << "Erreur de creation de la texture: " << SDL_GetError() << endl;
        return NULL;
    }




    // Liberer la surface
    SDL_FreeSurface(surface);

    return texture;
}
bool JeuSdl2::boucleMenu(SDL_Event& e, bool& quit){

   
    // Boucle principale
    quit = false;
    SDL_Surface* jouerSurface = IMG_Load("data/jouer.jpg");
    SDL_Texture* jouerTexture = SDL_CreateTextureFromSurface(rendu, jouerSurface);
    //SDL_FreeSurface(jouerSurface);
    SDL_Surface* quitSurface = IMG_Load("data/quitter.jpg");
    SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(rendu, quitSurface);
    //SDL_FreeSurface(quitSurface);  
    SDL_SetRenderDrawColor(rendu, 0xFF, 0xFF, 0xFF, 0xFF);
    // Tableau de boutons
    Button buttons[2];

    // Initialisation des boutons
    buttons[0].text = "Jouer";
    buttons[0].textColor = {255, 255, 255, 255};
    //buttons[1].text = "Options";
    //buttons[1].textColor = {255, 255, 255, 255};
    buttons[1].text = "Quitter";
    buttons[1].textColor = {255, 255, 255, 255};

    // Chargement de la police de caractères
    /*TTF_Font* font = TTF_OpenFont("Sans.ttf", 28);
    if (font == NULL) {
        cout << "Erreur de chargement de la police de caracteres: " << TTF_GetError() << endl;
        return false;
    }*/


    SDL_Rect r;
    
    r.w = DimX*0.6;
    r.h = DimY*0.1;
    r.x = DimX / 2 - r.w *0.5;
    r.y = DimY *0.3 - r.h*0.5;

    SDL_Rect r2;
    
    r2.w = DimX*0.6;
    r2.h = DimY*0.1;
    r2.x = DimX / 2 - r2.w*0.5;
    r2.y = DimY *0.3 + r2.h;

    


    
    buttons[0].x = r.x;
    buttons[0].y = r.y;
    buttons[0].rect = {r.x, r.y, r.w, r.h};

    buttons[1].x = r2.x;
    buttons[1].y = r2.y;
    buttons[1].rect = {r2.x, r2.y, r2.w, r2.h};
       
    
    while (!quit) {
        SDL_SetRenderDrawColor(rendu, 0,0,0, 0);
        SDL_RenderClear(rendu);
        // Gestion des événements
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Fermeture de la fenêtre
            if (e.type == SDL_QUIT) return false;         
            else if (e.type == SDL_KEYDOWN)  // Gestion des événements clavier          
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        return false;
                        break;
                    default: break;
                }

            // Gestion des événements de souris
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p = {x, y};
                for (int i = 0; i < 2; i++) {
                    if (SDL_PointInRect(&p, &buttons[i].rect)) {
                        // Le joueur a cliqué sur un bouton
                        if (i == 0) {
                            // Nouvelle partie
                            std::cout << "Jouer" << std::endl;
                            return true;
                        }
                        else if (i == 1) {
                            // Options
                            std::cout << "quitter" << std::endl;
                            return false;
                        }
                        else if (i == 2) {
                            // Quitter
                            quit = true;
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(rendu, 255,0,0, 0);
        SDL_RenderDrawRect(rendu,&r);
        SDL_RenderDrawRect(rendu,&r2);
        SDL_RenderCopy(rendu, jouerTexture, NULL, &r);

   
        SDL_RenderCopy(rendu, quitTexture, NULL, &r2);

        SDL_RenderPresent(rendu);
        
        
    }

    return quit;
}