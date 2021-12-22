/*
##Autheur
- Malik Makkes
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Pour utiliser la fonction aleatoire.
#include <math.h> //Pour utiliser la fonction puissance.
#include <SDL/SDL.h> //Pour utiliser l'affichage graphique en 2D.
#include <SDL/SDL_ttf.h> //Pour utiliser le font avec SDL, c'est a dire le texte.
#include <SDL/SDL_image.h> //Pour utiliser les images avec SDL, pour notre grille.

enum    {HAUT, BAS, GAUCHE, DROITE}; //On utilise la fonction enumeration pour donner à nos mouvements un simple nom et leur type sera des entiers automatiquement, c'est à dire 0, 1, 2 et 3.

int detecterCasesVides(int cases[][4], int casesVides[16]);

int deplacerCases(int* premiereCase, int* secondeCase) // Fonction qui retourne 0 si la case a été déplacée, la puissance de deux si elle a été fusionnée sinon -1, elle sera cruciale pour la fonction Mouvement.
{
    if (*secondeCase == 0) //Cas 1 : si la seconde case est egale à 0 car il y a eu un simple mouvement de case sans fusionnage.
    {
        *secondeCase = *premiereCase; //seconde case prend le pointeur vers la premiere case.
        *premiereCase = 0; //ensuite premiere case prend la valeure 0.
        return 0; //On quitte la fonction.
    }
    else  if (*secondeCase == *premiereCase) //Cas 2 : La seconde case a été fusionné 
    {
        (*secondeCase)++; //seconde case prend plus 1
        *premiereCase = 0; //on remet premiere case à 0.
        return *secondeCase; //On retourne la seconde case.
    }
    else
        return -1; //Cas 3 : C'est le cas d'arret lorsque la partie est terminé et il n'y a plus aucun mouvement disponible et donc on retourne -1.
}

void Mouvement(int *score, int cases[][4], int sens) //Fonction qui évalue les differents mouvements, haut, bas, gauche et droite.
{
    int i = 0, j = 0, k = 0; //Initialisatoin des variables.
    int retourDeplacer = 0; //Initialisatoin des variables.

    switch (sens) //Pour tester les differents cas.
    {
    case HAUT: //Cas 0 : la touche HAUT est appuyé.
        for (i = 0 ; i < 4 ; i++)
        {
            for (j = 1 ; j < 4 ; j++)
            {
                switch (j)
                {
                case 1:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if(retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if(retourDeplacer == 0)
                        retourDeplacer = deplacerCases(&cases[i][j - 1], &cases[i][j - 2]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j - 1]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    if(retourDeplacer == 0)
                    {
                        retourDeplacer = deplacerCases(&cases[i][j - 1], &cases[i][j - 2]);
                        if(retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[i][j - 2], &cases[i][j - 3]);
                        if (retourDeplacer > 0)
                            *score+=pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case BAS: //Cas 1 : la touche BAS est appuyé.
        for (i = 0 ; i < 4 ; i++)
        {
            for (j = 2 ; j >= 0 ; j--)
            {
                switch (3 - j)
                {
                case 1:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if(retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if(retourDeplacer == 0)
                        retourDeplacer = deplacerCases(&cases[i][j + 1], &cases[i][j + 2]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer = deplacerCases(&cases[i][j], &cases[i][j + 1]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    if(retourDeplacer == 0)
                    {
                        retourDeplacer = deplacerCases(&cases[i][j + 1], &cases[i][j + 2]);
                        if(retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[i][j + 2], &cases[i][j + 3]);
                        if (retourDeplacer > 0)
                            *score+=pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case GAUCHE: //Cas 2 : la touche GAUCHE est appuyé.
        for (i = 0 ; i < 4 ; i++)
        {
            for (j = 1 ; j < 4 ; j++)
            {
                switch (j)
                {
                case 1:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if(retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if(retourDeplacer == 0)
                        retourDeplacer = deplacerCases(&cases[j - 1][i], &cases[j - 2][i]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j - 1][i]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    if(retourDeplacer == 0)
                    {
                        retourDeplacer = deplacerCases(&cases[j - 1][i], &cases[j - 2][i]);
                        if(retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[j - 2][i], &cases[j - 3][i]);
                        if (retourDeplacer > 0)
                            *score+=pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    case DROITE: //Cas 3 : la touche DROITE est appuyé.
        for (i = 0 ; i < 4 ; i++)
        {
            for (j = 2 ; j >= 0 ; j--)
            {
                switch (3 - j)
                {
                case 1:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if(retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 2:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if(retourDeplacer == 0)
                        retourDeplacer = deplacerCases(&cases[j + 1][i], &cases[j + 2][i]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    break;
                case 3:
                    retourDeplacer = deplacerCases(&cases[j][i], &cases[j + 1][i]);
                    if (retourDeplacer > 0)
                        *score+=pow(2, retourDeplacer);
                    if(retourDeplacer == 0)
                    {
                        retourDeplacer = deplacerCases(&cases[j + 1][i], &cases[j + 2][i]);
                        if(retourDeplacer == 0)
                            retourDeplacer = deplacerCases(&cases[j + 2][i], &cases[j + 3][i]);
                        if (retourDeplacer > 0)
                            *score+=pow(2, retourDeplacer);
                    }
                    break;
                }
            }
        }
        break;
    }
}

int Chiffres(int nombre) //Fonction qui renvoie le nombre de chiffres qui composent le nombre en base 10. 
{
    int nbChiffres = 0; //Initialisation de la variable.

    if (nombre == 0) //C'est le premier cas
    {
        nbChiffres = 1; //nbChiffres vaut tout simplement 1.
    }
    else //Sinon on sait que nombre est superieur à 0.
    {
        while (nombre != 0) // On effectue une operation mathematique assez simple jusqu'à que nombre soit egale à 0.
        {
            nbChiffres += 1; //a chaque fois nbChiffres prend sa propre valeur plus 1.
            nombre /= 10; //Nombre prendre simplement le resultat de nombre/10.
        }
    }
    return nbChiffres; //Et on retourne enfin nbChiffres.
}

int detecterCasesVides(int cases[][4], int casesVides[16 + 1]) //Fonction qui remplit le tableau casesVides contenant les coordonnées des cases vides.
{
    int i = 0, j = 0, nbCasesVides = 0; //Initialisation des variables.
    for (i = 0 ; i < 4 ; i++) 
    {
        for (j = 0 ; j < 4 ; j++) //Boucle pour parcourir tout le tableau qui represente toute les cases du jeu.
        {
            if (cases[i][j] == 0) //Si c'est vrai alors c'est une case vide.
            {
                casesVides[nbCasesVides] = i*10 + j; //On affecte une valeur au tableau casesVides.
                nbCasesVides++; //On incremente nbCasesVides de 1 à chaque tour.
            }
        }
    }
    casesVides[nbCasesVides] = 0; //On donne a la case à indice nbCasesVides la valeur 0.

    return nbCasesVides; //On finit par retourner la valeur de nbCasesVides
}


void placerNbAlea(int cases[][4], int casesVides[16])
{
    int nbCasesVides = 0, caseChoisie = 0, nombre = 0;
    srand(time(NULL)); //On utilise la fonction aleatoire.
    nombre = rand()%30 + 1; //nombre prend la valeur d'un nombre aleatoire, ensuite on lui applique le modulo 30 + 1.
    if (nombre < 29) //Si nombre inferieur à 29.
        nombre = 1; 
    else
        nombre = 2;
    nbCasesVides = detecterCasesVides(cases, casesVides); //On lui donne une case vide.
    caseChoisie = casesVides[rand()%nbCasesVides]; //On lui donne la valeur 2 ou 4 pour la case
    if (cases[caseChoisie/10][caseChoisie - (caseChoisie / 10) * 10] != 0) //Cas ou il n y a plus de cases vides.
    {
        exit(EXIT_FAILURE); //On quitte le jeu immédiatement.
    }
    cases[caseChoisie/10][caseChoisie - (caseChoisie / 10) * 10] = nombre; //On donne la valeur de la case generer aleatoirement à nombre.
}


int TheGame(SDL_Surface* ecran) //Fonction qui retourne le score mais fait plusieurs autres choses.
{
    SDL_Surface *grille = NULL;
    SDL_Surface *chrono = NULL;
    SDL_Surface *texte = NULL;
    SDL_Surface *nombre[20] = {NULL};
    SDL_Rect positionGrille;
    SDL_Rect position;
    SDL_Rect chronoPosition;
    SDL_Rect positionTexte;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleur = {0, 0, 0};
    int continuer = 1; 
    int i = 0; 
    int j = 0;
    int nb = 1;
    int nbChiffres = 0; 
    int taille = 0; 
    int score = 0; 
    int x = 0; 
    int y = 0; 
    char chronometre[20]; //Les valeurs de notre timer seront stocker ici.
    Uint32 time; //Initialisation du type du timer.
    int casesVides[16] = {0}; //Initialisation du tableau.
    int cases[4][4] = {0}; //Initialisation des cases.
    char puissanceDeux[100]; //Tableau pour stocker nos puissances de deux.

    // Chargement de l'images constituant la grille du jeu.
    grille = IMG_Load("cases.png");
    positionGrille.x = 0 ;
    positionGrille.y = 75;

    // Génération des cases de nombres ainsi que leur couleurs.
    for (i = 0 ; i < 20 ; i++)
    {
        // On augmente d'une puissance de deux.
        nb*=2;

        //Changement de la couleur du texte
        if (i == 0 || i == 1)
        {
            couleur.r = 119;
            couleur.g = 110;
            couleur.b = 101;
        }
        else
        {
            couleur.r = 249;
            couleur.g = 246;
            couleur.b = 242;
        }

        //Mise à jour du texte.
        nbChiffres = Chiffres(nb);
        taille = 150/nbChiffres*0.95; //Pour la proportionnalité par rapport à la taille de la longeur du texte.
        police = TTF_OpenFont("Style.ttf", taille); 
        sprintf(puissanceDeux, "%d", nb); 
        texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
        position.x = 150 / 2 - texte->w / 2; //Pour mettre le texte au milieu de la case. 
        position.y = 150 / 2 - texte->h / 2; //Pour mettre le texte au milieu de la case.

        //Changement de la couleur du fond exactement comme le vrai jeu 2048.
        switch (i)
        {
        case 0:
            couleur.r = 17;
            couleur.g = 27;
            couleur.b = 37;
            break;
        case 1:
            couleur.r = 18;
            couleur.g = 31;
            couleur.b = 55;
            break;
        case 2:
            couleur.r = 13;
            couleur.g = 78;
            couleur.b = 134;
            break;
        case 3:
            couleur.r = 10;
            couleur.g = 106;
            couleur.b = 156;
            break;
        case 4:
            couleur.r = 9;
            couleur.g = 131;
            couleur.b = 160;
            break;
        case 5:
            couleur.r = 9;
            couleur.g = 161;
            couleur.b = 196;
            break;
        case 6:
            couleur.r = 18;
            couleur.g = 48;
            couleur.b = 141;
            break;
        default:
            couleur.b = (255/20)*i;
            couleur.g = (255/20)*i;
            couleur.r = (255/20)*i;
        }

        //Placement du texte dans la case.
        nombre[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 150 - 1, 150 - 1, 32, 0, 0, 0, 0);
        SDL_FillRect(nombre[i], NULL, SDL_MapRGB(nombre[i]->format, 255 - couleur.r, 255 - couleur.g, 255 - couleur.b));
        SDL_BlitSurface(texte, NULL, nombre[i], &position);
    }
    SDL_Flip(ecran);

    //Configuration du texte avec leur couleur et leur police.
    couleur.r = 119;
    couleur.g = 110;
    couleur.b = 101;
    taille = 150 * 0.95;
    police = TTF_OpenFont("Style.ttf", taille);
    sprintf(puissanceDeux, "%d", score);
    texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
    positionTexte.x = 10;
    positionTexte.y = 75 / 2 - texte->h /2;

    placerNbAlea(cases, casesVides);
    placerNbAlea(cases, casesVides);

    //Boucle Principale pour nos mouvements de clavier, Haut, Bat, Gauche et Droite
    while(continuer)
    {
        SDL_WaitEvent(&event); 

        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_UP:
                Mouvement(&score, cases, HAUT);
                break;
            case SDLK_DOWN:
                Mouvement(&score, cases, BAS);
                break;
            case SDLK_LEFT:
                Mouvement(&score, cases, GAUCHE);
                break;
            case SDLK_RIGHT:
                Mouvement(&score, cases, DROITE);
                break;
            }
            //On ajoute une case de 2 ou une case de 4 aléatoirement.
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
            {
                if (detecterCasesVides(cases, casesVides) == 0) // Si aucune case n'a pu être bougée par manque de place.
                    continuer = 0;
                else
                    placerNbAlea(cases, casesVides);
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            x = event.button.x;
            y = event.button.y;
            break;
        case SDL_MOUSEBUTTONUP :
            x -= event.button.x;
            y -= event.button.y;
            if (x > 0 &&  abs(x) > abs(y))
                Mouvement(&score, cases, GAUCHE);
            else if (x < 0 &&  abs(x) > abs(y))
                Mouvement(&score, cases, DROITE);
            else if (y > 0 &&  abs(x) < abs(y))
                Mouvement(&score, cases, HAUT);
            else if (y < 0 &&  abs(x) < abs(y))
                Mouvement(&score, cases, BAS);
            else
                break;
            //Ajout d'une case (2 ou 4)
            if (detecterCasesVides(cases, casesVides) == 0) // Si aucune case n'a pu être bougée par manque de place.
                continuer = 0;
            else
                placerNbAlea(cases, casesVides);
            break;
        }

        // Effacement de l'écran et nettoyage de la grille.
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 204, 192, 179));

        //Placement du score et du timer qui sera afficher en secondes avec leur police, taille et couleur.
        police = TTF_OpenFont("Style.ttf", 43);
        time = SDL_GetTicks();
        sprintf(chronometre, "Timer : %d sec", time/1000);
        sprintf(puissanceDeux, "Score : %d", score);
		chrono = TTF_RenderText_Blended(police, chronometre, couleur);
        texte = TTF_RenderText_Blended(police, puissanceDeux, couleur);
        positionTexte.x = 5;
        positionTexte.y = 15;
        chronoPosition.x = 300;
        chronoPosition.y = 15;
        SDL_BlitSurface(chrono, NULL, ecran, &chronoPosition);
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);

        //Placement des Cases.
        for (i = 0 ; i < 4 ; i++)
        {
            for (j = 0 ; j < 4 ; j++)
            {
                nb = cases[i][j] - 1;
                if (nb != -1)
                {
                    position.x = i * 150;
                    position.y = j * 150 + 75;
                    SDL_BlitSurface(nombre[nb], NULL, ecran, &position);
                }
            }
        }
        SDL_BlitSurface(grille, NULL, ecran, &positionGrille);
        SDL_Flip(ecran);
    }
    //Nettoyage des surfaces.
    SDL_FreeSurface(grille);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(chrono);
    for (i = 0 ; i < 20 ; i++)
        SDL_FreeSurface(nombre[i]); 
    return score; //On retourne le score.
}
