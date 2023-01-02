// Cette directive permet d'indiquer au compilateur de ne pas inclure ce fichier plusieurs fois lors de la compilation
#pragma once

#include <iostream>
/*
 * Élément de la carte
 */

// Liste des directions possibles de Pacman
enum Direction
{
    Haut,
    Bas,
    Gauche,
    Droite
};

// La structure point représente un point dans l'espace (x, y)
struct Point {
    short x; // abscisse
    short y; // ordonnée
};

// La structure Mur représente un mur dans le jeu
struct Mur {
    Point p1;
    Point p2;
};

// Cette structure représente un élément à manger dans le jeu
struct PointAManger {
    Point position; // Position de l'élément comestible
    unsigned int rayon; // Taille de l'élément comestible
    bool mangeable; // S'il a déjà été mangé par Pacman : mangeable = false
    bool nourriture; // Est-ce de la nourriture ou un bonus (nourriture = true)
};

// Element vivant, les fantômes
struct Fantome {
    unsigned int id; // identifiant du fantome.

    Point position; // Position du fantôme dans (x,y)

    Direction direction; // Direction actuelle du fantôme

    std::string nomTexture1; // Texture du fantôme dans son état normal

    std::string nomTexture2; // Texture du fantôme dans son état vulnérable

    unsigned short vitesse; // Vitesse de déplacement

    unsigned short rayon; // Rayon du fantôme (pour la collision)

    bool vivant; // Indique si le fantôme est encore en vie

    bool vulnerable; // Indique si le fantôme peut être mangé

    bool possedeTrajectoire; // Indique si le fantôme a une trajectoire en attente

    bool enQueue; // Indique si le fantôme a une trajectoire en cours

};


