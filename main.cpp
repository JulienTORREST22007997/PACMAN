#define FPS_LIMIT 60

#include<structure_elements.hpp>
#include<structures_pacman.hpp>
#include<structure_jeu.hpp>

#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iterator>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/audio/audioengine.h"
#include "mingl/gui/sprite.h"
#include "mingl/gui/text.h"


using namespace std;

bool debugMode = false;

deque<pair<Direction, Fantome>> directionsFantome;


double distance(Point p1, Point p2) {
    return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

/**
 *
 * Cette fonction permet d'ajouter un mur sur la carte et d'enregistrer sa collision.
 *
 * @brief ajouterMur
 * @param p1 : Le premier coin du mur.
 * @param p2 : Le second coin du mur.
 */
void ajouterMur(Point p1, Point p2, Jeu &partieActuelle) {
    Mur mur;
    mur.p1 = p1;
    mur.p2 = p2;
    partieActuelle.listeObstacles.emplace_back(mur);
}



Jeu chargerLaPartie(unsigned int niveau, Reglages param) {
    Jeu partieActuelle;

    if(niveau == 0) {

        // On définit la musique du sous-système, et on la joue

        partieActuelle.parametres = param;

        partieActuelle.etat = TypeEtat::Accueil;


    }
    else if(niveau == 1) {
        partieActuelle.parametres = param;

        partieActuelle.etat = TypeEtat::Chargement;
    }
    else if(niveau == 2) {
        partieActuelle.parametres = param;

        partieActuelle.etat = TypeEtat::Parametre;
    }
    else if(niveau == 3) {
        Pacman pacman;

        pacman.position.x = 100;
        pacman.position.y = 325;

        pacman.rayon = 20;
        pacman.vitesse = 5;
        pacman.vitesseBouche = 7;

        pacman.direction = Droite;

        pacman.score = 0;

        pacman.vivant = true;
        pacman.peutSeDeplacer = true;

        pacman.pointBouche1.x = pacman.rayon * pacman.factorX1 - pacman.rayon;
        pacman.pointBouche1.y = pacman.rayon * pacman.factorY1 - pacman.rayon;

        pacman.pointBouche2.x = pacman.rayon * pacman.factorX2 - pacman.rayon;
        pacman.pointBouche2.y = pacman.rayon * pacman.factorY2 - pacman.rayon;

        partieActuelle.pacman = pacman;

        partieActuelle.etat = TypeEtat::EnCours;

        partieActuelle.pointsAManger = {
            {{650, 70}, 5, true, false},
            {{625, 70}, 5, true, false},
            {{600, 70}, 5, true, false},
            {{575, 70}, 5, true, false},
            {{530, 70}, 10, true, false},
            {{500, 70}, 5, true, false},
            {{475, 70}, 5, true, false},
            {{450, 70}, 5, true, false},
            {{1100, 200}, 5, true, false},
            {{97, 635}, 5, true, false},

            {{500, 400}, 5, true, true}};

        partieActuelle.score = 0;
        partieActuelle.nbVies = 3;
        partieActuelle.niveau = 1;
        partieActuelle.tempsEcoule = 0;


        // Cloisons
        ajouterMur(Point{0, 0}, Point{1280, 50}, partieActuelle);
        ajouterMur(Point{0, 150}, Point{50, 720}, partieActuelle);
        ajouterMur(Point{0, 680}, Point{1280, 720}, partieActuelle);
        ajouterMur(Point{1230, 0}, Point{1280, 720}, partieActuelle);

        ajouterMur(Point{0, 150}, Point{550,95}, partieActuelle);
        ajouterMur(Point{600, 95}, Point{1000, 250}, partieActuelle);
        ajouterMur(Point{105, 350}, Point{450, 400}, partieActuelle);
        ajouterMur(Point{100, 200}, Point{395, 305}, partieActuelle);


        ajouterMur(Point{1050, 95}, Point{1094, 350}, partieActuelle);

        ajouterMur(Point{1094, 300}, Point{606, 364}, partieActuelle);

        ajouterMur(Point{150, 468}, Point{572, 531}, partieActuelle);

        ajouterMur(Point{1094, 300}, Point{606, 364}, partieActuelle);

        ajouterMur(Point{630, 475}, Point{716, 689}, partieActuelle);
        ajouterMur(Point{1232, 533}, Point{877, 570}, partieActuelle);


        ajouterMur(Point{1149, 104}, Point{1270, 420}, partieActuelle);


        Fantome pinky;
        pinky.id = 0;
        pinky.position.x = 1100;
        pinky.position.y = 100;
        pinky.direction = Direction::Gauche;
        pinky.nomTexture1 = "res/fantome1.si2";
        pinky.nomTexture2 = "res/vulnerable.si2";
        pinky.vitesse = 3;
        pinky.rayon = 15;
        pinky.vivant = true;
        pinky.vulnerable = false;
        pinky.possedeTrajectoire = false;
        partieActuelle.listeFantomes.emplace_back(pinky);

        Fantome blinky;
        blinky.id = 1;
        blinky.position.x = 300;
        blinky.position.y = 600;
        blinky.direction = Direction::Gauche;
        blinky.nomTexture1 = "res/blinky.si2";
        blinky.nomTexture2 = "res/vulnerable.si2";
        blinky.vitesse = 2;
        blinky.rayon = 15;
        blinky.vivant = true;
        blinky.vulnerable = false;
        blinky.possedeTrajectoire = false;
        partieActuelle.listeFantomes.emplace_back(blinky);

        Fantome punky;
        punky.id = 2;
        punky.position.x = 500;
        punky.position.y = 100;
        punky.direction = Direction::Gauche;
        punky.nomTexture1 = "res/fantome1.si2";
        punky.nomTexture2 = "res/vulnerable.si2";
        punky.vitesse = 2;
        punky.rayon = 15;
        punky.vivant = true;
        punky.vulnerable = false;
        punky.possedeTrajectoire = false;
        partieActuelle.listeFantomes.emplace_back(punky);

        Fantome zobi;
        zobi.id = 3;
        zobi.position.x = 150;
        zobi.position.y = 600;
        zobi.direction = Direction::Gauche;
        zobi.nomTexture1 = "res/blinky.si2";
        zobi.nomTexture2 = "res/vulnerable.si2";
        zobi.vitesse = 4;
        zobi.rayon = 15;
        zobi.vivant = true;
        zobi.vulnerable = false;
        zobi.possedeTrajectoire = false;
        partieActuelle.listeFantomes.emplace_back(zobi);
    }


    return partieActuelle;
}

int mangePoint(Jeu &partieActuelle) {
    Pacman &pacman = partieActuelle.pacman;
    for(size_t i = 0 ; i < partieActuelle.listeFantomes.size() ; ++i) {
        if (partieActuelle.listeFantomes[i].vulnerable && distance(pacman.position, partieActuelle.listeFantomes[i].position) <= pacman.rayon + partieActuelle.pointsAManger[i].rayon) {
            if(partieActuelle.listeFantomes[i].vulnerable) {
                partieActuelle.listeFantomes[i].vivant= false;

                pacman.score += 100;
            }
            else {
                ++pacman.score;
            }

            // On indique que le point à manger a été mangé.
            partieActuelle.pointsAManger[i].mangeable = false;
            // On retourne l'index du point à manger.
            return i;
        }
    }

    for(size_t i = 0 ; i < partieActuelle.pointsAManger.size() ; ++i) {
        if (partieActuelle.pointsAManger[i].mangeable && distance(pacman.position, partieActuelle.pointsAManger[i].position) <= pacman.rayon + partieActuelle.pointsAManger[i].rayon) {
            if(partieActuelle.pointsAManger[i].nourriture && partieActuelle.pointsAManger[i].mangeable) {
                for(Fantome & fantome : partieActuelle.listeFantomes) {
                    fantome.vulnerable = true;
                }
                pacman.score = pacman.score + 150;
            }
            else {
                ++pacman.score;
            }

            // On indique que le point à manger a été mangé.
            partieActuelle.pointsAManger[i].mangeable = false;
            // On retourne l'index du point à manger.
            return i;
        }
    }
    // Si aucun point à manger n'a été mangé, on retourne -1.
    return -1;
}

bool mouseHover = false;
void events(MinGL &window, Jeu & partieActuelle)
{
    // On vérifie chaque évènement de la queue d'évènements
    while (window.getEventManager().hasEvent())
    {
        const nsEvent::Event_t actualEvent = window.getEventManager().pullEvent();

        // On regarde le type d'évènement
        switch (actualEvent.eventType)
        {
        case nsEvent::EventType_t::MouseMove:
            // Il s'agit d'un mouvement de souris
            if(actualEvent.eventData.moveData.x >= 494 && actualEvent.eventData.moveData.y >= 315 &&
                    actualEvent.eventData.moveData.x <= 803 && actualEvent.eventData.moveData.y <= 387) {
                mouseHover = true;

            } else {
                mouseHover = false;

            }

            break;

        case nsEvent::EventType_t::MouseClick:
            // Il s'agit d'un click de souris
            cout << "x: " << actualEvent.eventData.clickData.x << " y: " << actualEvent.eventData.clickData.y << endl;

            if(partieActuelle.etat == TypeEtat::Accueil) {
                if(actualEvent.eventData.clickData.x >= 494 && actualEvent.eventData.clickData.y >= 315 &&
                        actualEvent.eventData.clickData.x <= 803 && actualEvent.eventData.clickData.y <= 387) {
                    cout << "Jouer" << endl;
                    partieActuelle = chargerLaPartie(1, partieActuelle.parametres);


                }
                if(actualEvent.eventData.clickData.x >= 489 && actualEvent.eventData.clickData.y >= 424 &&
                        actualEvent.eventData.clickData.x <= 825 && actualEvent.eventData.clickData.y <= 466) {
                    cout << "Paramètre" << endl;
                    partieActuelle = chargerLaPartie(2, partieActuelle.parametres);

                }
            }
            else if(partieActuelle.etat == TypeEtat::Parametre) {
                // faire qqch

                // coordonnées bouton AVEC musique
                if(actualEvent.eventData.clickData.x >= 572 && actualEvent.eventData.clickData.y >= 295 &&
                        actualEvent.eventData.clickData.x <= 626 && actualEvent.eventData.clickData.y <= 320) {
                    partieActuelle.parametres.musique = true;
                }

                // coordonnées bouton SANS musique
                if(actualEvent.eventData.clickData.x >= 654 && actualEvent.eventData.clickData.y >= 295 &&
                        actualEvent.eventData.clickData.x <= 708 && actualEvent.eventData.clickData.y <= 320) {
                    partieActuelle.parametres.musique = false;
                }

                // Facile
                if(actualEvent.eventData.clickData.x >= 575 && actualEvent.eventData.clickData.y >= 350 &&
                        actualEvent.eventData.clickData.x <= 631 && actualEvent.eventData.clickData.y <= 370) {
                    partieActuelle.parametres.difficulty = 0;
                }


                // Moyen
                if(actualEvent.eventData.clickData.x >= 658 && actualEvent.eventData.clickData.y >= 350 &&
                        actualEvent.eventData.clickData.x <= 719 && actualEvent.eventData.clickData.y <= 370) {
                    partieActuelle.parametres.difficulty = 1;
                }

                // Difficulté
                if(actualEvent.eventData.clickData.x >= 736 && actualEvent.eventData.clickData.y >= 350 &&
                        actualEvent.eventData.clickData.x <= 805 && actualEvent.eventData.clickData.y <= 370) {
                    partieActuelle.parametres.difficulty = 2;
                }

                if(actualEvent.eventData.clickData.x >= 605 && actualEvent.eventData.clickData.y >= 405 &&
                        actualEvent.eventData.clickData.x <= 675 && actualEvent.eventData.clickData.y <= 430) {
                    partieActuelle.parametres.vies = 1;
                }
                else if(actualEvent.eventData.clickData.x >= 675 && actualEvent.eventData.clickData.y >= 405 &&
                        actualEvent.eventData.clickData.x <= 800 && actualEvent.eventData.clickData.y <= 430) {
                    partieActuelle.parametres.vies = 2;
                }
                else if(actualEvent.eventData.clickData.x >= 800 && actualEvent.eventData.clickData.y >= 405 &&
                        actualEvent.eventData.clickData.x <= 865 && actualEvent.eventData.clickData.y <= 430) {
                    partieActuelle.parametres.vies = 3;
                }

                // Retour
                else if(actualEvent.eventData.clickData.x >= 15 && actualEvent.eventData.clickData.y >= 15 &&
                        actualEvent.eventData.clickData.x <= 80 && actualEvent.eventData.clickData.y <= 80) {
                    partieActuelle = chargerLaPartie(0, partieActuelle.parametres);
                }

            }
            else if(partieActuelle.etat == TypeEtat::EnCours) {
                cout << "x: " << actualEvent.eventData.clickData.x << " y: " << actualEvent.eventData.clickData.y << endl;

            }
            break;
        case nsEvent::EventType_t::MouseDrag:
            // Difficile
            if(actualEvent.eventData.moveData.x >= 605 && actualEvent.eventData.moveData.y >= 405 &&
                    actualEvent.eventData.moveData.x <= 675 && actualEvent.eventData.moveData.y <= 430) {
                partieActuelle.parametres.vies = 1;
            }
            else if(actualEvent.eventData.moveData.x >= 675 && actualEvent.eventData.moveData.y >= 405 &&
                    actualEvent.eventData.moveData.x <= 800 && actualEvent.eventData.moveData.y <= 430) {
                partieActuelle.parametres.vies = 2;
            }
            else if(actualEvent.eventData.moveData.x >= 800 && actualEvent.eventData.moveData.y >= 405 &&
                    actualEvent.eventData.moveData.x <= 865 && actualEvent.eventData.moveData.y <= 430) {
                partieActuelle.parametres.vies = 3;
            }

            break;

        default:
            // L'évènement ne nous intéresse pas
            break;
        }

    }
}



void dessiner(MinGL &window, Jeu &partieActuelle)
{
    if(partieActuelle.etat == TypeEtat::Accueil) {
        nsGui::Sprite textureFantome("res/jouer.si2", nsGraphics::Vec2D(500, 300));
        window << textureFantome;

        nsGui::Sprite parametres("res/settings.si2", nsGraphics::Vec2D(500, 400));
        window << parametres;
        if(mouseHover) {
            window << nsShape::Rectangle (nsGraphics::Vec2D(510, 400), nsGraphics::Vec2D(780, 405), nsGraphics::KWhite);
        }

        if(debugMode) {
            window << nsShape::Circle(nsGraphics::Vec2D(494, 315), 5, nsGraphics::KCyan); // P1 délimitation du bouton JOUER
            window << nsShape::Circle(nsGraphics::Vec2D(803, 387), 5, nsGraphics::KCyan);  // p2 délimitation du bouton JOUER

        }

    }
    else if(partieActuelle.etat == TypeEtat::Chargement) {
        window << nsGui::Text(nsGraphics::Vec2D(500, 300), " Loading... ", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_TIMES_ROMAN_24);
    }

    else if(partieActuelle.etat == TypeEtat::Parametre) {
        window << nsGui::Sprite("res/pacman_logo.si2", nsGraphics::Vec2D(500, 160));


        window << nsGui::Sprite ("res/retour.si2", nsGraphics::Vec2D(18, 18));


        window << nsGui::Text(nsGraphics::Vec2D(480, 270), "PARAMETRES", nsGraphics::KOrangeClair, nsGui::GlutFont::BITMAP_HELVETICA_18);

        window << nsGui::Text(nsGraphics::Vec2D(480, 315), "Musique", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        if(partieActuelle.parametres.musique) {
            window << nsGui::Text(nsGraphics::Vec2D(580, 315), "Avec", nsGraphics::KYellow, nsGui::GlutFont::BITMAP_HELVETICA_18);
            window << nsGui::Text(nsGraphics::Vec2D(660, 315), "Sans", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);

        } else {
            window << nsGui::Text(nsGraphics::Vec2D(580, 315), "Avec", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);
            window << nsGui::Text(nsGraphics::Vec2D(660, 315), "Sans", nsGraphics::KYellow, nsGui::GlutFont::BITMAP_HELVETICA_18);
        }


        window << nsGui::Text(nsGraphics::Vec2D(480, 365), "Niveau", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        nsGui::Text facile(nsGraphics::Vec2D(580, 365), "Facile", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);
        nsGui::Text moyen(nsGraphics::Vec2D(660, 365), "Moyen", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);
        nsGui::Text difficile(nsGraphics::Vec2D(740, 365), "Difficile", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);

        if(partieActuelle.parametres.difficulty == 0) {
            facile = nsGui::Text(nsGraphics::Vec2D(580, 365), "Facile", nsGraphics::KYellow, nsGui::GlutFont::BITMAP_HELVETICA_18);
            window << nsGui::Text(nsGraphics::Vec2D(470, 500), "Facile : Les ennemis sont 30% plus lent et moins aggressif.", nsGraphics::KOrangeClair, nsGui::GlutFont::BITMAP_HELVETICA_18);

        }
        else if(partieActuelle.parametres.difficulty == 1) {
            moyen = nsGui::Text(nsGraphics::Vec2D(660, 365), "Moyen", nsGraphics::KYellow, nsGui::GlutFont::BITMAP_HELVETICA_18);
            window << nsGui::Text(nsGraphics::Vec2D(470, 500), "Moyen (recommande) : Niveau de base du jeu", nsGraphics::KOrange, nsGui::GlutFont::BITMAP_HELVETICA_18);

        }
        else if(partieActuelle.parametres.difficulty == 2) {
            difficile = nsGui::Text(nsGraphics::Vec2D(740, 365), "Difficile", nsGraphics::KYellow, nsGui::GlutFont::BITMAP_HELVETICA_18);
            window << nsGui::Text(nsGraphics::Vec2D(470, 500), "Difficile : Les fantomes sont rapides et tres aggressifs.", nsGraphics::KRed, nsGui::GlutFont::BITMAP_HELVETICA_18);

        }
        window << facile;
        window << moyen;
        window << difficile;

        window << nsGui::Text(nsGraphics::Vec2D(480, 415), "Vies", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsShape::Rectangle (nsGraphics::Vec2D(580, 410), nsGraphics::Vec2D(800, 415), nsGraphics::KOrangeClair);

        nsShape::Rectangle curseur(nsGraphics::Vec2D(580, 405), nsGraphics::Vec2D(595, 420), nsGraphics::KOrange);

        if(partieActuelle.parametres.vies == 1) {
            curseur = nsShape::Rectangle(nsGraphics::Vec2D(580, 405), nsGraphics::Vec2D(595, 420), nsGraphics::KOrange);
        }
        else if(partieActuelle.parametres.vies == 2) {
            curseur = nsShape::Rectangle(nsGraphics::Vec2D(680, 405), nsGraphics::Vec2D(695, 420), nsGraphics::KOrange);
        }
        else if(partieActuelle.parametres.vies == 3) {
            curseur = nsShape::Rectangle(nsGraphics::Vec2D(785, 405), nsGraphics::Vec2D(800, 420), nsGraphics::KOrange);
        }
        window << curseur;

        window << nsGui::Text(nsGraphics::Vec2D(580, 445), "1", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsGui::Text(nsGraphics::Vec2D(680, 445), "2", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsGui::Text(nsGraphics::Vec2D(785, 445), "3", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);

    }
    else if(partieActuelle.etat == TypeEtat::EnCours) {


        // window << nsShape::Circle(nsGraphics::Vec2D(100, 320), 50, nsGraphics::KYellow);
        Pacman pacman = partieActuelle.pacman;
        window << nsShape::Circle(nsGraphics::Vec2D(pacman.position.x, pacman.position.y), 20, nsGraphics::KYellow);
        //    window << nsShape::Circle(nsGraphics::Vec2D(posCircleX, posCircleY), 5, nsGraphics::KRed); // milieu constante

        if(debugMode) {
            window << nsShape::Circle(nsGraphics::Vec2D(550, 100), 5, nsGraphics::KRed);
            window << nsShape::Circle(nsGraphics::Vec2D(500, 500), 5, nsGraphics::KGreen);

            window << nsShape::Circle(nsGraphics::Vec2D(pacman.position.x  + pacman.rayon * pacman.factorX1, pacman.position.y  + pacman.rayon * pacman.factorY1), 5, nsGraphics::KRed);

            window << nsShape::Circle(nsGraphics::Vec2D(pacman.position.x, pacman.position.y), 5, nsGraphics::KCyan); // milieu constante
            window << nsShape::Circle(nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche1.x, pacman.position.y+pacman.pointBouche1.y), 5, nsGraphics::KCyan); // 75, 370
            window << nsShape::Circle(nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche2.x, pacman.position.y+pacman.pointBouche2.y), 5, nsGraphics::KCyan); // 125, 370

            window << nsShape::Triangle(nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche1.x, pacman.position.y+pacman.pointBouche1.y),
                                        nsGraphics::Vec2D(pacman.position.x, pacman.position.y),
                                        nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche2.x, pacman.position.y+pacman.pointBouche2.y),
                                        nsGraphics::KLime);
        } else {
            window << nsShape::Triangle(nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche1.x, pacman.position.y+pacman.pointBouche1.y),
                                        nsGraphics::Vec2D(pacman.position.x, pacman.position.y),
                                        nsGraphics::Vec2D(pacman.position.x+pacman.pointBouche2.x, pacman.position.y+pacman.pointBouche2.y),
                                        nsGraphics::KBlack);
        }

        for(const Mur& mur: partieActuelle.listeObstacles) {
            window << nsShape::Rectangle (nsGraphics::Vec2D(mur.p1.x, mur.p1.y), nsGraphics::Vec2D(mur.p2.x, mur.p2.y), nsGraphics::KCyan);
        }

        for(const PointAManger& points : partieActuelle.pointsAManger) {
            if(points.nourriture) continue;

            if(points.mangeable) {
                window << nsShape::Circle(nsGraphics::Vec2D(points.position.x, points.position.y), points.rayon, nsGraphics::KCyan);
            }
        }

        for(const Fantome& fantome: partieActuelle.listeFantomes) {
            if(fantome.vivant) {
                if(fantome.vulnerable) {
                    nsGui::Sprite textureFantome(fantome.nomTexture2, nsGraphics::Vec2D(fantome.position.x-20, fantome.position.y-20));
                    window << textureFantome;
                } else {
                    nsGui::Sprite textureFantome(fantome.nomTexture1, nsGraphics::Vec2D(fantome.position.x-20, fantome.position.y-20));
                    window << textureFantome;
                }
            }
        }

        window << nsGui::Text(nsGraphics::Vec2D(20, 40), "Score: " + to_string(pacman.score), nsGraphics::KBlack, nsGui::GlutFont::BITMAP_9_BY_15);
    }

}

bool touchePacman(Fantome fantome, Pacman pacman) {
    int dx = fantome.position.x - pacman.position.x;
    int dy = fantome.position.y - pacman.position.y;
    int distance = sqrt(dx * dx + dy * dy); // Calcule de la distance entre le fantôme et Pac-Man
    return distance <= fantome.rayon + pacman.rayon; // Retourne vrai si le fantôme touche Pac-Man
}

void rotateMouth(bool & ouvreLaBouche, Jeu & partieActuelle)
{
    Pacman& pacman = partieActuelle.pacman;
    if(pacman.peutSeDeplacer) {
        if(!ouvreLaBouche) { // si il ferme la bouche
            if(pacman.direction == Droite || pacman.direction == Gauche) {
                if(pacman.pointBouche1.y > 25 ) // on vérifie qu'elle est pas totalement fermée
                {
                    ouvreLaBouche = true; // si elle est fermée on ouvre la bouche
                }
            } else {
                if(pacman.pointBouche1.x > 25 ) // on vérifie qu'elle est pas totalement fermée
                {
                    ouvreLaBouche = true; // si elle est fermée on ouvre la bouche
                }
            }

        } else { // si il ouvre la bouche
            if(pacman.direction == Droite || pacman.direction == Gauche) {
                if(pacman.pointBouche1.y < 0) // on vérifie qu'elle est pas totalement ouverte
                {
                    ouvreLaBouche = false; // on ferme la bouche si elle est totalement ouverte
                }
            } else {
                if(pacman.pointBouche1.x < 0) // on vérifie qu'elle est pas totalement ouverte
                {
                    ouvreLaBouche = false; // on ferme la bouche si elle est totalement ouverte
                }
            }
        }


        if(!ouvreLaBouche) { // si il ferme la bouche
            if(pacman.direction == Droite || pacman.direction == Gauche) {
                pacman.pointBouche1.y = pacman.pointBouche1.y + pacman.vitesseBouche;
                pacman.pointBouche2.y = pacman.pointBouche2.y - pacman.vitesseBouche;
            }
            else {
                pacman.pointBouche1.x = pacman.pointBouche1.x + pacman.vitesseBouche;
                pacman.pointBouche2.x = pacman.pointBouche2.x - pacman.vitesseBouche;
            }
        }
        else {
            if(pacman.direction == Droite || pacman.direction == Gauche) {
                pacman.pointBouche1.y = pacman.pointBouche1.y - pacman.vitesseBouche;
                pacman.pointBouche2.y = pacman.pointBouche2.y + pacman.vitesseBouche;
            }
            else {
                pacman.pointBouche1.x = pacman.pointBouche1.x- pacman.vitesseBouche;
                pacman.pointBouche2.x = pacman.pointBouche2.x + pacman.vitesseBouche;
            }
        }
    }
}

void setMouthRotation(Pacman & pacman) {
    float &factorX1 = pacman.factorX1;
    float &factorY1 = pacman.factorY1;

    float &factorX2 = pacman.factorX2;
    float &factorY2 = pacman.factorY2;

    if(pacman.direction == Droite) {
        factorX1 = 2;
        factorY1 = 0.5;

        factorX2= 2;
        factorY2 = 1.5;

    }
    else if(pacman.direction == Gauche) {
        factorX1 = 0;
        factorY1 = 0.5;

        factorX2= 0;
        factorY2 = 1.5;

    }
    else if(pacman.direction == Bas) {
        factorX1 = 0.5;
        factorY1 = 2;

        factorX2= 1.5;
        factorY2 = 2;
    }
    else if(pacman.direction == Haut) {
        factorX1 = 0.5;
        factorY1 = 0;

        factorX2= 1.5;
        factorY2 = 0;
    }

    pacman.pointBouche1.x = pacman.rayon * factorX1 - pacman.rayon;
    pacman.pointBouche1.y = pacman.rayon * factorY1 - pacman.rayon;

    pacman.pointBouche2.x = pacman.rayon * factorX2 - pacman.rayon;
    pacman.pointBouche2.y = pacman.rayon * factorY2 - pacman.rayon;
}

bool peutAvancer(MinGL &window, Pacman & pacman, const Mur& mur)
{
    int gauchePacman = pacman.position.x - pacman.rayon;
    int droitePacman = pacman.position.x + pacman.rayon;
    int hautPacman = pacman.position.y - pacman.rayon;
    int basPacman = pacman.position.y + pacman.rayon;

    int murFaceGauche = min(mur.p1.x, mur.p2.x);
    int murFaceDroite = max(mur.p1.x, mur.p2.x);
    int murFaceHaut = min(mur.p1.y, mur.p2.y);
    int murFaceBas = max(mur.p1.y, mur.p2.y);
    if (pacman.direction == Droite) {
        return !(droitePacman + 7 > murFaceGauche && droitePacman < murFaceDroite &&
                 hautPacman < murFaceBas && basPacman > murFaceHaut) &&
                (int) (pacman.position.x + pacman.rayon) < window.getWindowSize().getX();
    }
    else if (pacman.direction == Gauche) {
        if(pacman.position.y == 75) {
            if(pacman.position.x < 0) pacman.position.x = 1280;
            return true;
        }
        return !(gauchePacman - 7 < murFaceDroite && gauchePacman > murFaceGauche &&
                 hautPacman < murFaceBas && basPacman > murFaceHaut &&
                 pacman.position.x > 0) && pacman.position.x - pacman.rayon > 0;
    }
    else if (pacman.direction == Haut) {
        return !(hautPacman - 7 < murFaceBas && hautPacman > murFaceHaut &&
                 gauchePacman < murFaceDroite && droitePacman > murFaceGauche &&
                 pacman.position.y > 0) && pacman.position.y - pacman.rayon > 0;
    }
    else if (pacman.direction == Bas) {
        return !(basPacman + 7 > murFaceHaut && basPacman < murFaceBas &&
                 gauchePacman < murFaceDroite && droitePacman > murFaceGauche) &&
                (int) (pacman.position.y + pacman.rayon) < window.getWindowSize().getY();
    }

    return true;
}

void avancer(MinGL &window, Jeu & partieActuelle) {

    Pacman & pacman = partieActuelle.pacman;
    for(const Mur& mur : partieActuelle.listeObstacles) {
        if(!peutAvancer(window, pacman, mur)) {
            pacman.peutSeDeplacer = false;
            return;
        }
    }

    pacman.peutSeDeplacer = true;

    switch(pacman.direction) {
    case Droite:
        if(pacman.peutSeDeplacer) {
            pacman.position.x = pacman.position.x + pacman.vitesse;
        }
        break;

    case Gauche:
        if(pacman.peutSeDeplacer) {
            pacman.position.x = pacman.position.x - pacman.vitesse;
        }
        break;

    case Bas:
        if(pacman.peutSeDeplacer) {
            pacman.position.y = pacman.position.y + pacman.vitesse;
        }
        break;

    case Haut:
        if(pacman.peutSeDeplacer) {
            pacman.position.y = pacman.position.y - pacman.vitesse;
        }
        break;

    default:
        break;
    }
    mangePoint(partieActuelle);
}

void gestionEntreesClavier(MinGL &window, Jeu & partieActuelle){
    Pacman copy = partieActuelle.pacman;
    Pacman &pacman = partieActuelle.pacman;

    if (window.isPressed({'z', false})) {
        if(pacman.direction == Haut) return;
        copy.direction = Haut;

        for(const Mur& mur : partieActuelle.listeObstacles) {
            if(!peutAvancer(window, copy, mur)) {
                return;
            }
        }

        pacman.direction = Haut;
        setMouthRotation(pacman);
    }
    if (window.isPressed({'s', false})) {
        if(pacman.direction == Bas) return;
        copy.direction = Bas;

        for(const Mur& mur : partieActuelle.listeObstacles) {
            if(!peutAvancer(window, copy, mur)) {
                return;
            }
        }

        pacman.direction = Bas;
        setMouthRotation(pacman);

    }
    if (window.isPressed({'q', false})){
        if(pacman.direction == Gauche) return;
        copy.direction = Gauche;

        for(const Mur& mur : partieActuelle.listeObstacles) {
            if(!peutAvancer(window, copy, mur)) {
                return;
            }
        }
        pacman.direction = Gauche;
        setMouthRotation(pacman);

    }
    if (window.isPressed({'d', false})) {
        if(pacman.direction == Droite) return;
        copy.direction = Droite;

        for(const Mur& mur : partieActuelle.listeObstacles) {
            if(!peutAvancer(window, copy, mur)) {
                return;
            }
        }
        pacman.direction = Droite;
        setMouthRotation(pacman);
    }
}



// renvoie true s'il n'y a pas d'obstacle
bool peutAvancerFantome(MinGL &window, Fantome fantome, vector<Mur> &murs)
{
    bool canMove = true;

    int gauchefantome = fantome.position.x - fantome.rayon;
    int droitefantome = fantome.position.x + fantome.rayon;
    int hautfantome = fantome.position.y - fantome.rayon;
    int basfantome = fantome.position.y + fantome.rayon;

    for(const Mur& mur : murs) {
        int murFaceGauche = min(mur.p1.x, mur.p2.x);
        int murFaceDroite = max(mur.p1.x, mur.p2.x);
        int murFaceHaut = min(mur.p1.y, mur.p2.y);
        int murFaceBas = max(mur.p1.y, mur.p2.y);

        if (fantome.direction == Droite) {

            canMove = !(droitefantome + fantome.vitesse > murFaceGauche && droitefantome < murFaceDroite &&
                        hautfantome < murFaceBas && basfantome > murFaceHaut) &&
                    (int) (fantome.position.x + fantome.rayon) < window.getWindowSize().getX();
        }
        else if (fantome.direction == Gauche) {
            if(fantome.position.y == 75) {
                if(fantome.position.x < 0) fantome.position.x = 1280;
                return true;
            }
            canMove = !(gauchefantome - fantome.vitesse < murFaceDroite && gauchefantome > murFaceGauche &&
                        hautfantome < murFaceBas && basfantome > murFaceHaut &&
                        fantome.position.x > 0) && fantome.position.x - fantome.rayon > 0;
        }
        else if (fantome.direction == Haut) {
            canMove = !(hautfantome - fantome.vitesse < murFaceBas && hautfantome > murFaceHaut &&
                        gauchefantome < murFaceDroite && droitefantome > murFaceGauche &&
                        fantome.position.y > 0) && fantome.position.y - fantome.rayon > 0;
        }
        else if (fantome.direction == Bas) {
            canMove = !(basfantome + fantome.vitesse > murFaceHaut && basfantome < murFaceBas &&
                        gauchefantome < murFaceDroite && droitefantome > murFaceGauche) &&
                    (int) (fantome.position.y + fantome.rayon) < window.getWindowSize().getY();
        }
        if (!canMove) return false;
    }
    return true;
}

void avancerDansLaDirection(Fantome& fantome, MinGL & window, vector<Mur> & murs) {

    if (fantome.direction == Droite && peutAvancerFantome(window, fantome, murs)) {

        fantome.position.x += fantome.vitesse;
    }
    else if (fantome.direction == Gauche  && peutAvancerFantome(window, fantome, murs)) {
        fantome.position.x -= fantome.vitesse;

    }
    else if (fantome.direction == Haut  && peutAvancerFantome(window, fantome, murs)) {
        fantome.position.y -= fantome.vitesse;

    }
    else if (fantome.direction == Bas  && peutAvancerFantome(window, fantome, murs)) {
        fantome.position.y += fantome.vitesse;

    }
}

Direction trouverDirection(Fantome &fantome, Pacman pacman, std::vector<Mur> murs, MinGL &window)
{
    // On calcule la distance entre le fantôme et Pacman dans chaque direction
    Point & positionFantome = fantome.position;
    Point positionPacman = pacman.position;

    int distanceHaut = positionPacman.y - positionFantome.y;
    int distanceBas = positionFantome.y - positionPacman.y;
    int distanceGauche = positionPacman.x - positionFantome.x;
    int distanceDroite = positionFantome.x - positionPacman.x;


    std::vector<std::pair<Direction, int>> distances = {
        {Direction::Haut, distanceHaut},
        {Direction::Bas, distanceBas},
        {Direction::Gauche, distanceGauche},
        {Direction::Droite, distanceDroite}};

    if(fantome.vulnerable) {
        std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    } else {
        std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    }

    //    cout << "---------" << endl;
    //    cout << distances.at(0).first << " : " << distances.at(0).second << endl;
    //    cout << distances.at(1).first << " : " << distances.at(1).second << endl;
    //    cout << distances.at(2).first << " : " << distances.at(2).second << endl;
    //    cout << distances.at(3).first << " : " << distances.at(3).second << endl;
    //    cout << "---------" << endl;


    Direction elementMax = distances.at(0).first;
    // cout << elementMax -> first << "  " << elementMax->second <<endl;

    if(elementMax == Bas) {
        Fantome clone = fantome;
        clone.direction = Haut;
        // Si Pacman est en haut et que le fantôme peut avancer vers le haut
        if(peutAvancerFantome(window, clone, murs)) return Haut;
    }
    else if(elementMax == Haut) {
        Fantome clone = fantome;
        clone.direction = Bas;
        // Si Pacman est en bas et que le fantôme peut avancer vers le bas
        if(peutAvancerFantome(window, clone, murs)) return Bas;
    }
    else if(elementMax == Droite) {
        Fantome clone = fantome;
        clone.direction = Gauche;
        // Si Pacman est à gauche et que le fantôme peut avancer vers la gauche
        if(peutAvancerFantome(window, clone, murs)) return Gauche;
    }
    else if(elementMax == Gauche) {
        Fantome clone = fantome;
        clone.direction = Droite;
        // Si Pacman est à droite et que le fantôme peut avancer vers la droite
        if(peutAvancerFantome(window, clone, murs)) return Droite;
    }

    Fantome clone = fantome;

    //    cout << "---------" << endl;
    //    cout << "fantome.x : " << fantome.position.x << endl;
    //    cout << "fantome.y : " << fantome.position.y << endl;
    //    cout << "pacman.position.x : " << pacman.position.x << endl;
    //    cout << "pacman.position.y : " << pacman.position.y << endl;
    //    cout << "---------" << endl;

    if(!fantome.possedeTrajectoire) {
        if((fantome.position.x - pacman.position.x < fantome.vitesse) && (fantome.position.x - pacman.position.x >= 0) && fantome.position.y != pacman.position.y) {
            bool findWay = false;
            unsigned int compteur = 0;

            while(!findWay && compteur < 300) {
                compteur += 1;

                clone.direction = Direction::Gauche;
                if(!peutAvancerFantome(window, clone, murs)) {
                    compteur = 150;
                }

                clone.direction = Direction::Droite;
                if(!peutAvancerFantome(window, clone, murs)) {
                    if(compteur == 150) break;
                }

                // On veut savoir si le fantôme doit aller à droite ou à gauche
                if(compteur < 150) {
                    // Test à Gauche
                    clone.position.x -= clone.vitesse*2;

                    clone.direction = distances[3].first;
                    if(peutAvancerFantome(window, clone, murs)) {
                        cout << "issue vers la direction : " << distances[3].first << " trouvée à Gauche" << endl;
                        directionsFantome.emplace_back(distances[3].first, fantome);

                        for(unsigned int i (0) ; i <= compteur*2 ; ++i) {
                            directionsFantome.emplace_back(Direction::Gauche, fantome);
                        }
                        fantome.possedeTrajectoire = true;
                        return Direction::Gauche;
                    }

                }
                else {
                    // test à Droite
                    clone.position.x += clone.vitesse*2;
                    clone.direction = distances[3].first;

                    if(peutAvancerFantome(window, clone, murs)) {
                        cout << "issue vers la direction : " << distances[3].first << " à Droite" << endl;
                        directionsFantome.emplace_back(distances[3].first, fantome);

                        for(unsigned int i (0) ; i <= (compteur-149)*2 ; ++i) {
                            directionsFantome.emplace_back(Direction::Droite, fantome);
                        }
                        fantome.possedeTrajectoire = true;
                        return Direction::Droite;
                    }

                }
            }
        }

        if((fantome.position.y - pacman.position.y < fantome.vitesse) && (fantome.position.y - pacman.position.y >= 0)) {
            // **même ligne**
            // On cherche le plus court chemin pour aller à Droite / Gauche par l'axe vertical (haut / bas)
            bool findWay = false;
            unsigned int compteur = 0;

            while(!findWay && compteur < 300) {
                compteur += 1;

                clone.direction = Direction::Gauche;
                if(!peutAvancerFantome(window, clone, murs)) {
                    compteur = 150;
                }

                clone.direction = Direction::Droite;
                if(!peutAvancerFantome(window, clone, murs)) {
                    if(compteur == 150) break;
                }

                // On veut savoir si le fantôme doit aller en Bas ou en Haut
                if(compteur < 150) {
                    // test en Haut
                    clone.position.y -= clone.vitesse*2;
                    clone.direction = distances[3].first;

                    if(peutAvancerFantome(window, clone, murs)) {
                        cout << "issue vers la direction : " << distances[3].first << " trouvée En Haut" << endl;
                        directionsFantome.emplace_back(distances[3].first, fantome);

                        for(unsigned int i (0) ; i <= compteur*2 ; ++i) {
                            directionsFantome.emplace_back(Direction::Haut, fantome);
                        }
                        fantome.possedeTrajectoire = true;
                        return Direction::Haut;
                    }
                } else {
                    // test en Bas
                    clone.position.y += clone.vitesse*2;
                    clone.direction = distances[3].first;

                    if(peutAvancerFantome(window, clone, murs)) {
                        cout << "issue vers la direction :  " << distances[3].first << " en Bas" << endl;
                        directionsFantome.emplace_back(distances[3].first, fantome);

                        for(unsigned int i (0) ; i <= (compteur-149)*2 ; ++i) {
                            directionsFantome.emplace_back(Direction::Bas, fantome);
                        }
                        fantome.possedeTrajectoire = true;
                        return Direction::Bas;
                    }
                }
            }
        }
    }


    // S'il ne peut pas aller dans la bonne direction
    Fantome fantomeClone = fantome;
    for(size_t i (distances.size()-1) ; i != 0; --i) {
        fantomeClone.direction = distances.at(i).first;
        if(peutAvancerFantome(window, fantomeClone, murs)) {
            cout << "il a bien pu avancer en " << fantomeClone.direction << endl;
            return fantomeClone.direction;
        } else {
            cout << "il ne peut pas aller en " << fantomeClone.direction << endl;
        }
    }
    return fantome.direction;
}



int main()
{
    // Initialise le système
    MinGL window("Pac-Man", nsGraphics::Vec2D(1280, 720), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Initialise le sous-système audio
    nsAudio::AudioEngine audioEngine;

    audioEngine.setMusic("music.wav");
    audioEngine.startMusicFromBeginning();


    Reglages parametres;
    parametres.difficulty = 0;
    parametres.vies = 1;
    parametres.musique = true;

    Jeu partieActuelle = chargerLaPartie(0, parametres);

    bool ouvreLaBouche = false;

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();


    // On fait tourner la boucle tant que la fenêtre est ouverte

    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        if(partieActuelle.etat == TypeEtat::Accueil) {
            dessiner(window, partieActuelle);
            events(window, partieActuelle);
        }
        else if (partieActuelle.etat == TypeEtat::Parametre) {
            dessiner(window, partieActuelle);
            events(window, partieActuelle);

        } else if (partieActuelle.etat == TypeEtat::Chargement) {
            dessiner(window, partieActuelle);
            this_thread::sleep_for(chrono::milliseconds(5000) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

            partieActuelle = chargerLaPartie(3, partieActuelle.parametres);

            //this_thread::sleep_for(chrono::milliseconds(3000) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        }
        else if (partieActuelle.etat == TypeEtat::EnCours) {
            // On affiche l'image
            for(size_t i(0) ; i < partieActuelle.pointsAManger.size() ; ++i) {
                if(partieActuelle.pointsAManger[i].nourriture && partieActuelle.pointsAManger[i].mangeable) {
                    nsGui::Sprite pomme("res/pomme.si2", nsGraphics::Vec2D(partieActuelle.pointsAManger[i].position.x, partieActuelle.pointsAManger[i].position.y));
                    window << pomme;
                }
            }

            // On dessine les formes géométriques
            dessiner(window, partieActuelle);
            rotateMouth(ouvreLaBouche, partieActuelle);
            gestionEntreesClavier(window, partieActuelle);
            avancer(window, partieActuelle);
            events(window, partieActuelle);

            for(Fantome & fantome : partieActuelle.listeFantomes) {
                fantome.enQueue = false;
            }

            cout << directionsFantome.size() << endl;
            // On parcoure les trajectoires enregistrées
            for(Fantome & fantome : partieActuelle.listeFantomes) {
                if(directionsFantome.empty()) break;

                // On parcoure nos fantômes
                if(!fantome.enQueue) {

                    pair<Direction, Fantome> trajectoire = directionsFantome.back(); // On récupère la dernière trajectoire
                    if(trajectoire.second.id == fantome.id) { // Si la trajectoire est celle de notre fantôme

                        directionsFantome.pop_back(); // On la retire de la liste
                        fantome.direction = trajectoire.first; // On définit la direction de notre fantôme sur celle de la trajectoire

                        avancerDansLaDirection(fantome, window, partieActuelle.listeObstacles); // On fait avancer le fantôme

                        fantome.enQueue = true;
                    }
                }
            }


            for(Fantome & fantome : partieActuelle.listeFantomes) {
                if(!fantome.enQueue) {
                    fantome.possedeTrajectoire = false;
                    fantome.direction = trouverDirection(fantome, partieActuelle.pacman, partieActuelle.listeObstacles, window);

                    avancerDansLaDirection(fantome, window, partieActuelle.listeObstacles);
                }
            }
        }

        window.finishFrame();

        // On vide la queue d'évènements
        if(partieActuelle.etat != TypeEtat::Accueil && partieActuelle.etat != TypeEtat::Parametre /*&& partieActuelle.etat != TypeEtat::EnCours*/) {
            // window.getEventManager().clearEvents();
        }

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);

    }
    return 0;

}
