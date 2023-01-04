// Cette directive permet d'indiquer au compilateur de ne pas inclure ce fichier plusieurs fois lors de la compilation
#pragma once

#include <structure_elements.hpp>
#include<vector>

/*
 * Personnages vivant
 */

// Définit le personnage Pacman dans le jeu
struct Pacman {
    Point position; // Position de Pacman dans (x,y)

    unsigned int rayon; // Rayon de Pacman

    unsigned short vitesse; // Vitesse de déplacement

    unsigned short vitesseBouche; // Vitesse d'ouverture & fermeture de la bouche

    Direction direction; // Direction actuelle de Pacman

    unsigned int score; // Score du joueur

    bool vivant; // Indique si le pacman est encore en vie

    bool peutSeDeplacer; // Indique si Pacman peut se déplacer ou non (pour gérer les collisions avec les murs)

    unsigned int disparition = 0;

    Point pointBouche1; // Premier point de la bouche de Pacman (pour l'animation)
    Point pointBouche2; // Deuxième point de la bouche de Pacman (pour l'animation)

    float factorX1 = 2;
    float factorY1 = 0.5;

    float factorX2 = 2;
    float factorY2 = 1.5;
};





