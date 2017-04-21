#ifndef EVENEMENTS_H
#define EVENEMENTS_H

#include "Damier.h"
#include "Constantes.h"
#include "Console.h"
#include "Affichage.h"
#include "FenetreAllegro.h"

#include <iostream>
#include <allegro.h>
#include <winalleg.h>
#include <time.h>
#include <fstream>

namespace Curseur
{
    void deplacer(char _key, int& _ligneCurseurDamier, int& _colonneCurseurDamier, int& _ligneCurseurAffichage, int& _colonneCurseurAffichage,
                       int _origineCurseurLigne, int _origineCurseurColonne, int _ligneCurseurAffichageMax, int _colonneCurseurAffichageMax,
                       int _ligneCurseurDamierMax, int _colonneCurseurDamierMax);
}

namespace Partie
{
    int deroulement(int mode, Console* pConsole, Damier* damier, FenetreAllegro* pAllegro, char tour, char adv);
    bool verification(Damier* damier);
    void sauvegarde(Damier* d, int mode);

}


#endif // EVENEMENTS_H_INCLUDED
