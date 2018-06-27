#include "melangeur.hpp"

namespace MMaze {

Melangeur::Melangeur(int octets) {
	tailleElem = octets;
	srand (time(NULL));

}

Melangeur::~Melangeur() {
	vider();
}

void Melangeur::inserer(const void* elem) {
	tab.push_back(std::malloc(tailleElem));
	std::memcpy(tab.back(),elem,tailleElem);
	
}

void Melangeur::retirer(void* elem) {

	int nb = rand()%taille();
	std::memcpy(elem,tab[nb],tailleElem);
	free(tab[nb]);
	tab[nb]=tab.back();
	tab.pop_back();

	
}

void Melangeur::vider() {
  for(unsigned int i=1; i<tab.size();i++){
		free(tab[i]);
	}
	tab.clear();
}

int Melangeur::taille() {
  return tab.size();
}

} //end of namespace MMaze
