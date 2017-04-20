#include <conio.h>

#include "Evenements.h"

void Curseur::deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax)
{
    switch(_key)
    {
    case 'Z': // Z : Haut
    case 'z':
        _ligneCurseurDamier--; //remonte le curseur
        if(_ligneCurseurDamier < 0) _ligneCurseurDamier = 0; //ne peut pas d�passer le damier

        _ligneCurseurAffichage-=2; //le curseur affich� remonte de 2
        if(_ligneCurseurAffichage < _origineCurseurLigne) _ligneCurseurAffichage = _origineCurseurLigne; //ne peut pas d�passer
        break;

    case 'S': // S : Bas
    case 's':
        _ligneCurseurDamier++;
        if(_ligneCurseurDamier > _ligneCurseurDamierMax) _ligneCurseurDamier = _ligneCurseurDamierMax; // nbLignes-1 car l'indice va de 0 � 4

        _ligneCurseurAffichage+=2;
        if(_ligneCurseurAffichage > _ligneCurseurAffichageMax) _ligneCurseurAffichage = _ligneCurseurAffichageMax;
        break;

    case 'Q': // Q : Gauche
    case 'q':
        _colonneCurseurDamier--;
        if(_colonneCurseurDamier < 0) _colonneCurseurDamier = 0;

        _colonneCurseurAffichage-=4;
        if(_colonneCurseurAffichage < _origineCurseurColonne) _colonneCurseurAffichage = _origineCurseurColonne;
        break;

    case 'D': // D : Droite
    case 'd':
        _colonneCurseurDamier++;
        if(_colonneCurseurDamier > _colonneCurseurDamierMax) _colonneCurseurDamier = _colonneCurseurDamierMax; //nbColonnes-1 car l'indice va de 0 � 4


        _colonneCurseurAffichage+=4;
        if(_colonneCurseurAffichage > _colonneCurseurAffichageMax) _colonneCurseurAffichage = _colonneCurseurAffichageMax;
        break;
    }
}

int Partie::deroulement(int mode, Console* pConsole, Damier* damier, FenetreAllegro* pAllegro, char tour, char adv)
{
    /// DECLARATION DES VARIABLES D'AFFICHAGE DU CURSEUR DU DAMIER

    //initialisation des valeurs constantes du sous-programme
    const int origineCurseurLigne = damier->getLigneAffichage()+1;
    const int origineCurseurColonne = damier->getColonneAffichage()+2;

    int ligneCurseurDamier, colonneCurseurDamier;
    int ligneCurseurAffichage, colonneCurseurAffichage;

    //ligne et colonne maximale d'affichage du curseur
    int ligneCurseurAffichageMax, colonneCurseurAffichageMax;
    int ligneCurseurDamierMax, colonneCurseurDamierMax;

    /// INITIALISATION DES VARIABLES

    /// DEBUT VARIABLES CURSEUR
    //coordonn�es r�elles de la case point�e par le curseur
    ligneCurseurDamier = 0;
    colonneCurseurDamier = 0;

    //coordonn�es maximales de la case point�e par le curseur
    ligneCurseurDamierMax = damier->getTaille()-1;
    colonneCurseurDamierMax = damier->getTaille()-1;

    //ligne et colonne maximale d'affichage du curseur
    ligneCurseurAffichageMax = 2*damier->getTaille() + origineCurseurLigne-2;
    colonneCurseurAffichageMax = 4*(damier->getTaille() -1) + origineCurseurColonne;

    //coordonn�es d'affichage du curseur
    ligneCurseurAffichage = origineCurseurLigne;
    colonneCurseurAffichage = origineCurseurColonne;

    bool rafraichirEcran = true; //pour rentrer d�s le d�but dans la boucle d'affichage
    bool continuerTour=true;
    int quitter = 0;

    GfxDamier::afficher(pConsole, damier);

    while(continuerTour)
    {
        // GESTIONS DES EVENEMENTS CLAVIER
        if(key[KEY_G] && pAllegro->IsAllegroActive())
        {
            pAllegro->FermetureModeGraphique();
        }
        if(pConsole->isKeyboardPressed())
        {
            //r�cup�ration de la touche sur laquelle l'utilisateur a appuy�
            char touche = pConsole->getInputKey();

            if(touche=='z' || touche=='s' || touche=='q' || touche=='d') //commandes de d�placement du curseur
            {
                Curseur::deplacer(touche, ligneCurseurDamier, colonneCurseurDamier, ligneCurseurAffichage, colonneCurseurAffichage,
                                  origineCurseurLigne, origineCurseurColonne, ligneCurseurAffichageMax, colonneCurseurAffichageMax,
                                  ligneCurseurDamierMax, colonneCurseurDamierMax);

                pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);
            }

            if(touche==13 && damier->getDamier()[ligneCurseurDamier][colonneCurseurDamier]==COUP_JOUABLE)
            {
                damier->changement(tour, adv, ligneCurseurDamier, colonneCurseurDamier);
                continuerTour=false;
                damier->reset();
                rafraichirEcran = true;
            }

            if(touche == 27) //si appuie sur ECHAP
            {
                //ouvre le menu ECHAP
                quitter=GfxMenu::echap(pConsole, mode, damier);

                //si le joueur veut quitter
                if(quitter)
                {
                    continuerTour=false;
                    rafraichirEcran=false;
                }
                else //s'il veut juste reprendre le jeu
                {
                    continuerTour=true;
                    rafraichirEcran=true;
                }
            }

            // Ouverture du mode graphique
            if((touche == 'g' || touche == 'G') && !pAllegro->IsAllegroActive())
            {
                pAllegro->OuvertureModeGraphique(1280, 720, false);

                /// TEMP
                pAllegro->AfficherDamier(damier, tour);
            }
        }

        if(rafraichirEcran)
        {
            pConsole->gotoLigCol(origineCurseurLigne-4, origineCurseurColonne);

            GfxInfos::afficherTour(pConsole, tour);
            GfxInfos::afficherScore(pConsole, damier);
            damier->afficher(pConsole);

            pConsole->gotoLigCol(ligneCurseurAffichage, colonneCurseurAffichage);

            rafraichirEcran = false;
        }

        if(pAllegro->IsAllegroActive())
            blit(pAllegro->buffer(), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    system("cls");

return quitter;
}

bool Partie::verification(Damier* damier)
{
    bool ok = false;

    for(int i=0 ; i<damier->getTaille() ; i++)
    {
        for(int j=0 ; j<damier->getTaille() ; j++)
        {
            if(damier->getDamier()[i][j] == COUP_JOUABLE)
            {
                ok = true;
                break;
            }
        }
        if(ok) break;
    }

    return ok;
}

void Partie::sauvegarde(Damier* d, int mode)
{

    std::ofstream fichier("partie.txt", std::ios::out | std::ios::trunc);

    if(fichier)
    {
        d->reset();
        fichier << mode << " " << d->getTaille() << std::endl;
        for(int i=0; i<d->getTaille() ; i++)
        {
            for(int j=0; j<d->getTaille(); j++)
            {
                if(d->getDamier()[i][j]!=' ')
                    fichier << d->getDamier()[i][j] << " " ;
                else
                    fichier << '0' << " ";
            }
            fichier << std::endl;
        }
        fichier.close();
    }
    else
    {
        std::cerr << "Impossible" << std::endl;
    }
}
