# Jeu_2048_en_C_avec_SDL1.2
Voici le jeu 2048 codé en C avec SDL1.2

##Autheurs
- Malik Makkes

## Conditions
- SDL
- SDL_ttf
- SDL_image


## Répondre aux exigences

**Vous pouvez utiliser CMake pour compiler le projet**

Assurez-vous que les exigences sont remplies.

### Linux

`sudo apt-get update`

`sudo apt-get install cmake`

`sudo apt-get install libsdl-dev`

`sudo apt-get install libsdl-ttf2.0-dev` 

`sudo apt-get install libsdl-image1.2-dev`

Ces commandes installeront les librairies nécessaires pour le fonctionnement du jeu sous linux.


## Comment compiler

Après avoir satisfait les exigences, nous pouvons passer à la compilation du programme.
Vous devez avoir le dossier : `Malik_Jeu` dans Desktop.
Ensuite, nous ouvrons notre dossier, disons que nous sommes en root : `cd /root/Desktop/Malik_Jeu`

Ensuite, nous pouvons construire le projet :

`cmake .`

`make`

Ou nous pouvons simplement utiliser la ligne de compilation suivante :

`gcc -o Malik_Jeu main.c 2048.c 'sdl-config --cflags --libs' -lSDL_image -lSDL_ttf -lm`

Le programme compilé doit se trouver dans le dossier nommé : `Malik_Jeu`


## Executer

Après la compilation, nous pouvons exécuter notre jeu !

`./Malik_Jeu`

Notez qu'il existe un fichier de police appelé Style.ttf dans le dossier. Il est utilisé par le jeu pour le texte.

Le jeu ne fonctionnera pas sans ce dernier car vous obtiendrez segmentation fault à moins que vous l'ayez.
