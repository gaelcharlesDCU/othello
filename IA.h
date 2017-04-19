#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "Console.h"
#include "Damier.h"
#include <vector>

class IA
{
    private :
        int m_difficulte; // 1: facile (al�atoire)
    public :
        // C & D
        IA();
        ~IA();

        // M�thodes
        bool deroulement(Console* _pConsole, Damier* _pDamier, char _tour, char _adv);
        std::vector<int> ChooseRandomCell(Damier* _pDamier);

        // G & S
        int getDifficulte() const { return m_difficulte; }
        void setDifficulte(int _difficulte);
};

#endif // IA_H_INCLUDED