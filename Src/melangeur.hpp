#ifndef MMAZE_MELANGEUR_HPP
#define MMAZE_MELANGEUR_HPP

#include <vector>
#include <cstdlib>
#include <cstring>
#include <time.h>

namespace MMaze {

class Melangeur {

	private:
		int tailleElem;
		std::vector<void*> tab;

  public :
    Melangeur(int octets) ;

    ~Melangeur() ;

    void inserer(const void* elem) ;

    void retirer(void* elem) ;

    void vider() ;

    int taille() ;

  /* vos membres ici */

} ;

} //end of namespace MMaze

#endif
