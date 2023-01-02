// Cette directive permet d'indiquer au compilateur de ne pas inclure ce fichier plusieurs fois lors de la compilation
#pragma once

#include<structures_pacman.hpp>
#include <vector>

/*
 * Tout ce qui se rapproche au fonctionnement du jeu
 */
enum TypeEtat {
    Accueil,
    Parametre,
    Chargement,
    EnCours,
    GameOver,
    Pause
};

struct Reglages {
    bool musique; // true = avec musique, false = sans musique.
    unsigned int difficulty; // 0 = facile, 1 = moyen, 2 = difficile.
    unsigned int vies; // 1, 2, 3.

};

struct Jeu {
    // Etat actuel du jeu, permettra d'afficher les bons éléments et de charger les bons niveaux
    TypeEtat etat;

    // Réglages de la partie telle que la diffilculté ou le nombre de vies
    Reglages parametres;

    // Personnage joué avec tous ses paramètres
    Pacman pacman;

    // Murs de la carte
    std::vector<Mur> listeObstacles;

    // Fantômes
    std::vector<Fantome> listeFantomes;


    // Élements comestibles
    std::vector<PointAManger> pointsAManger;

    // Score actuel
    unsigned int score;

    // Nombre de vies restantes
    unsigned int nbVies;

    // Niveau actuel
    unsigned int niveau;

    // Temps écoulé depuis le début du jeu (en secondes)
    unsigned int tempsEcoule;
};



