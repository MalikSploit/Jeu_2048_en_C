/* 
##Autheurs
- Malik Makkes
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h> //Pour utiliser l'affichage graphique en 2D.
#include <SDL/SDL_image.h> //Pour utiliser les images avec SDL, pour notre grille.
#include <SDL/SDL_ttf.h> //Pour utiliser le font avec SDL, c'est a dire le texte.

int main() //Fonction principale
{
    SDL_Surface *ecran = NULL; //On initialise la surface ecran.
    SDL_Surface *menu1 = NULL; //On initialise la surface 1er menu.
    SDL_Surface *titre = NULL; //On initialise la surface du titre.
    SDL_Surface *menu2 = NULL; //On initialise la surface du 2eme menu.
    SDL_Rect positionMenu1; //On cree le rectangle positionMenu1 qu'on collera plus tard sur notre ecran.
    SDL_Rect posTitre; //On cree le rectangle posTitre qu'on collera plus tard sur notre ecran.
    SDL_Rect positionMenu2; //On cree le rectangle positionMenu2 qu'on collera plus tard sur notre ecran.
    SDL_Event event; //On cree la variable evenement de type SDL_Event.
    TTF_Font *police = NULL; //On initialise le font.
    SDL_Color couleurNoire = {0, 0, 0}; //On initialise la couleur noir.
    SDL_Color couleurBleue = {43, 96, 255}; //On initialise la couleur bleue.
    int TheGame(SDL_Surface* ecran); // Retourne le score qu'on utilisera dans le main.
    int continuer = 1; //Pour la boucle infini.
    int score = 0; //Pour le score.

    SDL_Init(SDL_INIT_VIDEO); //On initialise l'affichage graphique
    TTF_Init(); //On initialise le font.
    ecran = SDL_SetVideoMode( 600 , 675, 32, SDL_HWSURFACE); //Creation de l'ecran de taille 600 en longeur et 675 en hauteur, avec 32 bits par pixel et enfin on utilisera notre memoire de la carte graphique vu qu'elle est tres puissante.
    SDL_WM_SetCaption("Malik et Anis 2048", NULL); //On cree le titre de la fenetre.
    Uint32 blanc = SDL_MapRGB(ecran->format, 255, 255, 255); //On cree la couleur blanche avec le max de rouge, vert et bleu.
    SDL_FillRect(ecran, NULL, blanc); //On remplit entierement la fenetre ecran avec la couleur blanche.
    police = TTF_OpenFont("Style.ttf", 65); //On donne a police le style ariale avec une taille de 65.
    titre = TTF_RenderText_Blended(police, "Jeu de Malik et Anis", couleurNoire); //On cree la zone de texte et on lui donne notre chaine de caracteres ainsi que la couleur.
    posTitre.x = 14; //On donne la position du titre sur l'ecran au niveau des abscisses.
    posTitre.y = 25; //On donne la position du titre sur l'ecran au niveau des ordonnées.
    police = TTF_OpenFont("Style.ttf", 60); ////On donne a police le style ariale avec une taille de 60 cette fois.
    menu1 = TTF_RenderText_Blended(police, " Cliquer deux fois ici" , couleurBleue); //On cree la zone de texte et on lui donne notre chaine de caracteres ainsi que la couleur.
    positionMenu1.x = 15; //On donne la position du 1er menu sur l'ecran au niveau des abscisses.
    positionMenu1.y = 300; //On donne la position du 2eme menu sur l'ecran au niveau des ordonnées.
    menu2 = TTF_RenderText_Blended(police, " pour jouer à 2048" , couleurBleue); //On cree la zone de texte et on lui donne notre chaine de caracteres ainsi que la couleur.
    positionMenu2.x = 28; //On donne la position du 2eme menu sur l'ecran au niveau des abscisses.
    positionMenu2.y = 380; //On donne la position du 2eme menu sur l'ecran au niveau des ordonnées.
    SDL_Flip(ecran); //On met a jour la fenetre pour que les changements soient perceptibles sur l'ecran.
    while (continuer) //Boucle infini, mais qui a un cas d'arret bien evidemment.
    {
        SDL_WaitEvent(&event); //Tant qu'il n' y a pas de nouvel evenement on fait absolument rien.
        switch(event.type) //Switch pour les differents type d'evenements.
        {
        case SDL_QUIT: //On quitte la SDL.
            continuer = 0; //On quitte le jeu.
            break; //On sort de cette boucle.
        case SDL_KEYDOWN : //Cas si l'utilisateur appuie sur une touche.
            switch(event.key.keysym.sym) //On utilise : event.key.keysym.sym; Pour savoir de quelle touche provient l'evenemnt.
            {
            case SDLK_ESCAPE: //Cas si l'utilisateur clique sur le bouton ESCAPE.
                continuer = 0; //On quitte le jeu.
                break; //On sort de cette boucle.
            case SDLK_KP1:
                score = TheGame(ecran); //On met a jour le score.
                break; //On sort de cette boucle.
            }
            break; //On sort de cette boucle.
	    case SDL_MOUSEBUTTONUP : //Cas si l'utilisateur fait un swipe vers le haut avec la souris.
	      score = TheGame(ecran); //On met a jour le score.
		break; //On sort de cette boucle.
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //On remplit l'ecran avec la couleur blanche.
        SDL_BlitSurface(titre, NULL, ecran, &posTitre); //On colle la surface titre sur notre ecran.
        SDL_BlitSurface(menu1, NULL, ecran, &positionMenu1); //On colle la surface menu1 sur notre ecran.
        SDL_BlitSurface(menu2, NULL, ecran, &positionMenu2); //On colle la surface menu2 sur notre ecran.
        SDL_Flip(ecran); //On met a jour la fenetre pour que les changements soient perceptibles sur l'ecran.
    }
    SDL_FreeSurface(menu1); //On vide la case memoire de menu1.
    SDL_FreeSurface(menu2); //On vide la case memoire de menu2.
    SDL_FreeSurface(titre); //On vide la case memoire de titre.
    SDL_Quit(); //On quitte la SDL.
    if (score > 2048) //Le cas ou le joueur commence a avoir un bon score.
    {
		printf("Bien Joué ton score finale est : %d", score);  //On affiche sur la console son bon score.
	}
	else //sinon.
	{
		printf("Ton score finale est : %d", score); //On affiche sur la console son score.
	}
	FILE *fp=fopen("Score.txt", "a+"); //On ouvre le fichier score en mode append.
	fprintf(fp, "Votre socre de la dernière partie est : %d\n", score); //On enregistre dedans le socre de la partie.
	fclose(fp); //On ferme le fichier.
	return 0; //Terminer.
}
