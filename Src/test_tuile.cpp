#include "tuile.hpp"
#include "melangeur.hpp"
#include "couleurs.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace MMaze ;

int main() {


  Melangeur objectifs(sizeof(int));
  int *v1 = new int;
  *v1=1;
  objectifs.inserer(v1);
  *v1=2;
  objectifs.inserer(v1);
  *v1=3;
  objectifs.inserer(v1);
  *v1=4;
  objectifs.inserer(v1);
  *v1=11;
  objectifs.inserer(v1);
  *v1=12;
  objectifs.inserer(v1);
  *v1=13;
  objectifs.inserer(v1);
  *v1=14;
  objectifs.inserer(v1);

  bool rep;
  int dep,arr;
  std::cout<<"tuile classique?(bool)"<<std::endl;
  std::cin>>rep;

  Tuile t(rep,objectifs);
  std::cout << t << std::endl ;

  std::cout<<"entrez la case de depart"<<std::endl;
  std::cin>>dep;

  std::cout<<"entrez la case d'arrivée"<<std::endl;
  std::cin>>arr;

  t.dijkstra(dep,arr);
  
  /*
  CaseUF test1;
  CaseUF test2;
  CaseUF test3;
  CaseUF test4;


  test1.index=1;
  test2.index=2;
  test3.index=3;
  test4.index=4;
  
  
  test1.rep=&test2;
  test2.rep=&test4;
  test3.rep=&test3;
  test4.rep=&test4;


  std::vector<CaseUF*> tab;
  tab.push_back(&test1);
  tab.push_back(&test2);
  tab.push_back(&test3);
  tab.push_back(&test4);

  
  bool res=(t.estRelie(tab));
    
  std::cout<< res << " " << " " <<std::endl;
  */





  //utilisation des couleurs
  
  std::cout
    << TXT_JAUNE << "&"
    << TXT_ORANGE << "&"
    << TXT_VERT << "&"
    << TXT_VIOLET << "&"
    << TXT_CLEAR
    << BG_JAUNE << "&"
    << BG_ORANGE << "&"
    << BG_VERT << "&"
    << BG_VIOLET << "&"
    << TXT_CLEAR
    << std::endl ;

  return 0 ;
}
