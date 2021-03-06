#include "Affichage.h"
#include "Constantes.h"
#include "Evenements.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <allegro.h>
#include <winalleg.h>
#include <MMsystem.h>

void GfxDamier::Afficher(Console* _pConsole, Damier* _pDamier)
/**********************************************************************************************
 * \brief Afficher : Affiche en console le plateau de jeu                                     *
 * \author Ga�l                                                                               *
 *                                                                                            *
 * \param _pConsole : Pointeur sur l'instance de console                                      *
 * \param _pDamier : Pointeur sur le damier � afficher                                        *
 * \return (void)                                                                             *
 *                                                                                            *
 **********************************************************************************************/
{
    // Variables constantes
    const int origineLig = _pDamier->getLigneAffichage();
    const int origineCol = _pDamier->getColonneAffichage();
    const int dep_lig[] = {-1, 2*TAILLE_PLATEAU+1};
    const int dep_col[] = {-3, 4*TAILLE_PLATEAU+2};

    // Positionnement initial
    _pConsole->gotoLigCol(origineLig, origineCol);

    // Premi�re ligne de bordures
    std::cout << BORDURE_ANGLE_HG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<_pDamier->getTaille()-1 ; i++)
        std::cout << BORDURE_INTER3_BAS << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_HD;
    _pConsole->gotoLigCol(origineLig+1, origineCol); // Retour � la ligne

    // Bordures des 64 cases
    for(int i(0) ; i<=_pDamier->getTaille() ; i++)
    {
        // Milieux de cases
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
            std::cout << BORDURE_BARRE_VERT << "   ";
        std::cout << BORDURE_BARRE_VERT;
        _pConsole->gotoLigCol(origineLig+2*i+1, origineCol); // Retour � la ligne

        // Barres horizontales
        if(i != _pDamier->getTaille())
        {
            _pConsole->gotoLigCol(origineLig+2*i+2, origineCol); // Retour � la ligne
            std::cout << BORDURE_INTER3_DROITE << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            for(int j(0) ; j<_pDamier->getTaille()-1 ; j++)
                std::cout << BORDURE_INTER4 << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
            std::cout << BORDURE_INTER3_GAUCHE;
            _pConsole->gotoLigCol(origineLig+2*i+1, origineCol); // Retour � la ligne
        }
    }
    // Derni�re ligne de bordures
    _pConsole->gotoLigCol(origineLig+2*TAILLE_PLATEAU, origineCol); // Retour � la ligne
    std::cout << BORDURE_ANGLE_BG << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    for(int i(0) ; i<_pDamier->getTaille()-1 ; i++)
        std::cout << BORDURE_INTER3_HAUT << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ << BORDURE_BARRE_HORZ;
    std::cout << BORDURE_ANGLE_BD;

    // Coordonn�es des cases sur les bordures
    _pConsole->setColor(COULEUR_BLANC, COULEUR_MARRON);
    for(int dl : dep_lig)
    {
        _pConsole->gotoLigCol(origineLig+dl, origineCol-3);
        std::cout << "    ";
        for(int c(0) ; c<TAILLE_PLATEAU ; c++)
            std::cout << " " << char('A'+c) << "  ";
        std::cout << "   ";
    }
    for(int dc : dep_col)
    {
        for(int c(1) ; c<=2*TAILLE_PLATEAU+1 ; c++)
        {
            _pConsole->gotoLigCol(origineLig+c-1, origineCol+dc);
            if(dc == -3)
                c%2==0 ? std::cout << ' ' << (c+1)/2 : std::cout << "  ";
            else
                c%2==0 ? std::cout << (c+1)/2 << ' ' : std::cout << "  ";
        }
    }

    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
}

void GfxDamier::AfficherContenu(Console* _pConsole, Damier* _pDamier)
/**********************************************************************************************
 * \brief afficherContenu : Affiche le contenu des cases du damier                            *
 * \author Camille, Ga�l                                                                      *
 *                                                                                            *
 * \param _pConsole : Pointeur sur l'instance de console                                      *
 * \param _pDamier : Pointeur sur le damier � afficher                                        *
 * \return (void)                                                                             *
 *                                                                                            *
 **********************************************************************************************/
{
    // Variables
    const int origineLig = _pDamier->getLigneAffichage()+1;
    const int origineCol = _pDamier->getColonneAffichage()+2;

    for(int i(0) ; i<_pDamier->getTaille() ; i++)
    {
        for(int j(0) ; j<_pDamier->getTaille() ; j++)
        {
            // D�placement � la case associ�e
            _pConsole->gotoLigCol(2*i+origineLig, 4*j+origineCol);

            // Affichage du contenu
            switch(_pDamier->getDamier()[i][j])
            {
            case BLANC:
                _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
                std::cout << 'O';
                break;

            case NOIR:
                _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
                std::cout << 'O';
                break;

            case COUP_JOUABLE:
                _pConsole->setColor(COULEUR_MARRON, COULEUR_VERT);
                std::cout << COUP_JOUABLE;
                break;

            default :
                { std::cout << ' '; }
            }
            _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); // Par d�faut
        }
    }
}

void GfxInfos::AfficherTour(Console* _pConsole, char tour)
/**********************************************************************************************
 * \brief afficherTour : indique quel joueur doit jouer ce tour                               *
 * \author Camille                                                                            *
 *                                                                                            *
 * \param _pConsole : Pointeur sur l'instance de console                                      *
 * \param tour : tour de jeu                                                                  *
 * \return (void)                                                                             *
 *                                                                                            *
 **********************************************************************************************/
{
    _pConsole->gotoLigCol(1, 6);
    std::cout << "C\'est au tour des";

    _pConsole->gotoLigCol(2, 6);
    if(tour == NOIR)
    {
        _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
        std::cout << CARAC_CARRE << " noirs " << CARAC_CARRE << ' ';
    }
    else if(tour == BLANC)
    {
        _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
        std::cout << CARAC_CARRE << " blancs " << CARAC_CARRE;
    }
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); // Par d�faut
}

void GfxInfos::AfficherScore(Console* _pConsole, Damier* _pDamier)
{
    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()+20, _pDamier->getColonneAffichage()+2);
    _pConsole->setColor(COULEUR_NOIR, COULEUR_VERT);
    std::cout << CARAC_CARRE << ' ' << _pDamier->CompterPions(NOIR) << " pions noirs";

    _pConsole->gotoLigCol(_pDamier->getLigneAffichage()+21, _pDamier->getColonneAffichage()+2);
    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT);
    std::cout << CARAC_CARRE << ' ' << _pDamier->CompterPions(BLANC) << " pions blancs";
}

void GfxInfos::AfficherArbreRecherche(Console* _pConsole, std::vector<Etat*> _arbre_recherches)
{
    // Pour chaque noeud de l'arbre de recherches
    for(unsigned int i(0) ; i<_arbre_recherches.size() ; i++)
    {
        // On affiche les informations sur le noeud
        _arbre_recherches[i]->AfficherEtat(_pConsole, i);
    }
}

void GfxInfos::AfficherFin(Damier* _pDamier)
{
    int n = _pDamier->CompterPions(NOIR);
    int b = _pDamier->CompterPions(BLANC);

    std::cout << "Partie terminee " << std::endl;

    if(n > b)
        std::cout << "Les pions noirs gagnent ! ";
    else if(n < b)
        std::cout << "Les pions blancs gagnent ! ";
    else
        std::cout << "Match nul ! ";
    std::cout << "Score : " << std::endl << "Noirs " << n << " - " << b << " Blancs" << std::endl;
    system("pause");
}

int GfxMenu::Afficher(Damier* _pDamier, Console* _pConsole, IA* _bot, char& _couleur_tour)
/**********************************************************************************************
 * \brief Afficher : Affiche le menu principal et r�cup�re le choix de l'utilisateur          *
 * \author Ga�l, Camille                                                                      *
 *                                                                                            *
 * \param _pDamier : Pointeur sur le damier cr��                                              *
 * \param _pConsole : Pointeur sur la console                                                 *
 * \param _bot : Pointeur sur l'IA �ventuelle                                                 *
 * \param _couleur_tour : R�f�rence sur la couleur du joueur qui commencera                   *
 * \return mode : -1 pour quitter, 0 pour partie 2J, n pour partie 1J avec IA niveau n        *
 *                                                                                            *
 **********************************************************************************************/
{
    // Variables
    int choix = 0, mode = 0;

    // Passe la console en texte noir sur fond blanc
    _pConsole->setColor(COULEUR_NOIR, COULEUR_BLANC);
    system("cls");

    _pConsole->gotoLigCol(2, 0);
    std::cout << MENU_ASCII_ART;
    _pConsole->gotoLigCol(9, 11);
    std::cout << "0. Continuer la partie";
    _pConsole->gotoLigCol(10,11);
    std::cout << "1. Partie un joueur";
    _pConsole->gotoLigCol(11, 11);
    std::cout << "2. Partie deux joueurs";
    _pConsole->gotoLigCol(12, 11);
    std::cout << "3. Quitter";

    do
    {
        _pConsole->gotoLigCol(13, 11);
        std::cin >> choix;
    }while(choix!=0 && choix != 1 && choix != 2 && choix != 3);

    if(choix == 0) // Charger une partie
    {
        mode = _pDamier->Chargement(_couleur_tour);
        if(mode >= 1) _bot->setDifficulte(mode);
    }

    else if(choix == 1)
    {
        system("cls");
        _pConsole->gotoLigCol(2, 0);
        std::cout << MENU_ASCII_ART;
        _pConsole->gotoLigCol(9, 11);
        std::cout << "1. Facile (Aleatoire)";
        _pConsole->gotoLigCol(10, 11);
        std::cout << "2. Moyen (Minimax)";
        // 3. Difficile
        do
        {
            _pConsole->gotoLigCol(11, 11);
            std::cin >> mode;
        }while(mode != 1 && mode != 2);

        _bot->setDifficulte(mode);
    }

    else if(choix == 2)
        mode = 0;

    else if(choix == 3)
        mode = -1;

    return mode;
}

int GfxMenu::Echap(Console* _pConsole, int mode, Damier* _pDamier, char _couleur_tour)
{
    int choix = 0;
    int ret = 0;

    _pConsole->setColor(COULEUR_NOIR, COULEUR_BLANC);
    system("cls");

    _pConsole->gotoLigCol(2, 0);
    std::cout << MENU_ASCII_ART;
    _pConsole->gotoLigCol(9, 14);
    std::cout << "PAUSE" ;
    _pConsole->gotoLigCol(11,11);
    std::cout << "1. Sauvegarder et quitter";
    _pConsole->gotoLigCol(12, 11);
    std::cout << "2. Quitter sans sauvegarder";
    _pConsole->gotoLigCol(13, 11);
    std::cout << "3. Retour au jeu";

    do
    {
        _pConsole->gotoLigCol(14, 11);
        std::cin >> choix;
    } while(choix != 1 && choix != 2 && choix != 3);

    _pConsole->setColor(COULEUR_BLANC, COULEUR_VERT); // Par d�faut

    if(choix == 1)
    {
        Partie::Sauvegarde(_pDamier, mode, _couleur_tour);
        ret = 2;
    }

    if(choix == 2)
    {
        ret = 2;
    }

    if(choix == 3)
    {
        system("cls");
        ret = 0;
    }

    return ret;
}

