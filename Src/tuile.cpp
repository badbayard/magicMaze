#include "tuile.hpp"
#include "couleurs.hpp"

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <time.h>



namespace MMaze {

  /*-1 vide
    1: sortie jaune
    2: sortie orange
    3: sortie vert
    4: sortie violet

    11: obj jaune
    12: obj orange
    13: obj vert
    14: obj violet

    21: porte jaune
    22: porte orange
    23: porte vert
    24: porte violet

    31: depart jaune
    32: depart orange
    33: depart vert
    34: depart violet 

    42: entree tuile
  */	

  Tuile::Tuile() {
  }

  Tuile::~Tuile(){
  }

  Tuile::Tuile(bool _tuile_depart,Melangeur objectifs){
    tuile_depart = _tuile_depart;
    srand (time(NULL));

    if(tuile_depart == true){	
      porte_acces = -1;

      Site sj; // sortie jaune
      sj.index = 13;
      sj.contenu = 1;
      sites.push_back(sj);

      Site so;   //sortie orange
      so.index = 2;
      so.contenu = 2;
      sites.push_back(so);

      Site sve;  // sortie vert
      sve.index = 11;
      sve.contenu  = 3;
      sites.push_back(sve);

      Site svi; // sortie violet
      svi.index = 4;
      svi.contenu = 4;
      sites.push_back(svi);
    
      Site dj; // depart jaune
      dj.index = 5;
      dj.contenu = 31;
      sites.push_back(dj);
    
      Site dO; // depart orange
      dO.index = 6;
      dO.contenu = 32;
      sites.push_back(dO);

      Site dve; // depart vert
      dve.index = 9;
      dve.contenu = 33;
      sites.push_back(dve);

      Site dvi; // depart violet
      dvi.index = 10;
      dvi.contenu = 34;
      sites.push_back(dvi);

      murs[0]=true;
      murs[1]=false;
      murs[2]=false;
      murs[3]=true;
      murs[4]=true;
      murs[5]=false;
      murs[6]=false;
      murs[7]=true;
      murs[8]=true;
      murs[9]=false;
      murs[10]=false;
      murs[11]=true;
      murs[12]=false;
      murs[13]=false;
      murs[14]=false;
      murs[15]=false;
      murs[16]=false;
      murs[17]=false;
      murs[18]=false;
      murs[19]=false;
      murs[20]=false;
      murs[21]=false;
      murs[22]=false;
      murs[23]=true;

      
    }
    else {

      int b = rand()%2;
	  
      Melangeur positions(sizeof(int));
      int *v1 = new int ;
      int *v2 = new int ;
      int *v3 = new int ;
      int *v4 = new int ;
      *v1=2;
      *v2=4;
      *v3=11;
  
      positions.inserer(v1);
      positions.inserer(v2);
      positions.inserer(v3);

      *v1= 21;
      *v2= 22;
      *v3= 23;
      *v4= 24;

      Melangeur couleurs(sizeof(int));
    
      couleurs.inserer(v1);
      couleurs.inserer(v2);
      couleurs.inserer(v3);
      couleurs.inserer(v4);


      bool positions_objectif[16];
      for(int i = 0;i<16;i++){
	if(i==13){positions_objectif[i]=false;}
	else{positions_objectif[i]=true;}
      }

      int nb_portes = 0;
      
      Site entree;
      entree.index = 13;
      entree.contenu = 42;
      sites.push_back(entree);
      
      do{
	
	Site* porte= new Site;
	positions.retirer(v1);
	porte->index = *v1;

	positions_objectif[porte->index]=false;
	
	couleurs.retirer(v1);
	porte->contenu = *v1;
      
	sites.push_back(*porte);
	nb_portes++;
      }while(rand()%2 == 1 && nb_portes < 3);

      
      if(b==1){
	Site objectif;
	objectifs.retirer(v1);
	objectif.contenu = *v1;

	Melangeur pos_obj(sizeof(int));
	for(int j=0;j<16;j++){
	  if(positions_objectif[j]==true){
	    *v1 = j;
	    pos_obj.inserer(v1);
	  }
	}
	
	pos_obj.retirer(v1);
	objectif.index = *v1;

	sites.push_back(objectif);
      }
      for (int i = 0 ; i < 24 ; i++){
	murs[i]=1;
      }
      setup_tuile();

    }
    
    std::cout<<std::endl;               // Il y a un buffer à vider (pourquoi?)
    
  } 


  bool Tuile::mur(Mur m) const {
    unsigned int temp = m.index();
    return murs[temp] ;
  }

  bool Tuile::accessible(Case c) const {
    /* remplacez ce code */
    return false ;
  }

  void Tuile::afficher_horizontal(std::ostream& out, unsigned int i) const {
    assert(i < 5) ;
    if(i == 0 || i == 4) {
      out << "+---+---+---+---+" ;
    } else {
      out << "+" ;
      for(unsigned int m = 0; m < 4; ++m) {
	Case up = Case(i-1, m) ;
	Case down = Case(i, m) ;
	if(mur(Mur(up, down))) {
	  out << "---+" ;
	} else {
	  out << "   +" ;
	}
      }
    }
  }

  void Tuile::afficher_vertical(std::ostream& out, unsigned int i) const {
    assert(i < 4) ;
    out << "|" ;
    for(unsigned int m = 0; m < 4; ++m) {
      out << "   " ;
      if(m < 3) {
	Case left = Case(i, m) ;
	Case right = Case(i, m+1) ;
	if(m < 3 && mur(Mur(left, right))) {
	  out << "|" ;
	} else {
	  out << " " ;
	}
      }
    }
    out << "|" ;
  }



  void Tuile::setup_tuile(){
    std::vector<CaseUF*> casesARelier;
    for(unsigned int i=0;i<sites.size();i++){
      CaseUF* temp= new CaseUF;
      temp->rep = temp;
      temp->index =0;
      temp->index = sites[i].index;
      casesARelier.push_back(temp);
    }
    
    relierSites(casesARelier);

    
  }

  void Tuile::relierSites(std::vector<CaseUF*> sites){

    CaseUF* tabCases[16];
    int select,case1,case2;

    for (int i=0;i<16;i++){
      CaseUF* temp = new CaseUF;
      temp->index=i;
      temp->rep=temp;
      tabCases[i]= temp;
    }

    
    for(unsigned int k=0;k<sites.size();k++){
      int index = sites[k]->index;
      delete(tabCases[index]);
      tabCases[index]=sites[k];
    }

    
    while(!estRelie(sites)){
      
      select=rand()%24;
      while(!murs[select]){select=rand()%24;}
      murs[select]=false;
      if (select<12){
      	case1=select;
	case2=select+4;
      }
      else{
	int ligne = (select-12)/4;
	int colonne = select%4;
      	case1=ligne*4+colonne;
      	case2=case1+1;
      }
      _union(tabCases[case1],tabCases[case2]);
    }
  }

  CaseUF* Tuile::find(CaseUF* _case){
    if (_case->rep == _case->rep->rep){return _case->rep;}
    else{
      _case->rep=find(_case->rep);
      return _case->rep;
    }
  }

  void Tuile::_union(CaseUF* case1,CaseUF* case2){
    CaseUF* temp=find(case2);
    temp->rep=find(case1);
  }

  std::ostream& operator<< (std::ostream& out, const Tuile& t) {
    for(unsigned int i = 0; i < 4; ++i) {
      t.afficher_horizontal(out, i) ;
      out << std::endl ;
      t.afficher_vertical(out, i) ;
      out << std::endl ;
    }
    t.afficher_horizontal(out, 4) ;
    return out ;
  }


  bool Tuile::estRelie(std::vector<CaseUF*> tab){
    
    /* for(unsigned int k=0;k<tab.size();k++){
       std::cout<< tab[k]->index  <<std::endl;               
       }*/
    
    
    CaseUF* temp=find(tab[0]);
    for(unsigned int i=1; i<tab.size(); i++){
      
      //	std::cout<< tab[i]->index << " a pour rep " << find(tab[i])->index <<std::endl;               
      
      
      CaseUF* temp2 = find(tab[i]);
      if (temp2!=temp){
	return false;
      }
    }
    return true;
  }

  
  void Tuile::dijkstra(int case_src,int case_arrivee){

    Graph graphe=creerGraph();
    int distances[16][2];
    int predecesseur[16];
    std::queue<int> file;
    std::queue<int> chemin;
    int n, dist,temp,tempChemin;
    unsigned int a;
    n=case_src;    
    
    for(int i=0; i<16;i++){
      distances[i][1]=0;
      if(i == n){
	      distances[i][0]=0;
      }else{
	      distances[i][0]=-1;
      }
    }
        
    for(int j=0; j<16; j++){
      predecesseur[j]=-1;
    }
        
    distances[n][1]=1;
    
    file.push(n);

    std::cout << " ";
      for(int w=0;w<16;w++){
	std::cout << " ";
      }
      std::cout<< std:: endl;

    while(!file.empty()){
      temp= file.front();
      
      file.pop();
      for(unsigned int i=0;i<graphe.graph[temp].voisins.size();i++){
	
	dist = distances[temp][0]+1;
	if(distances[graphe.graph[temp].voisins[i]][0]==-1 || dist<distances[graphe.graph[temp].voisins[i]][0]){
	    distances[graphe.graph[temp].voisins[i]][0]=dist;
  predecesseur[graphe.graph[temp].voisins[i]]=temp;
	  if(distances[graphe.graph[temp].voisins[i]][1]==0){
	      file.push(graphe.graph[temp].voisins[i]);
	      distances[graphe.graph[temp].voisins[i]][1]=1;
	  }
	}
      }
    }
    
    
    tempChemin=case_arrivee;
    do{
      n=tempChemin;
      chemin.push(tempChemin);
      tempChemin=predecesseur[tempChemin];
    }while(n!=case_src);

    std::cout << "Chemin le plus court de la case " << case_src << " à la case " << case_arrivee << ":" << std::endl;
													   a=chemin.size();
    for(unsigned int l;l<a;l++){
      std::cout << chemin.front() << " " ;
      chemin.pop();
    }
    std::cout<< std::endl;
    
  }
  
    Graph Tuile::creerGraph(){
      Graph res;
      int courant;
      bool temp;

      for(int i = 0;i<16;i++){
	courant=i;
	temp=false;
	while(courant%4 != 3 && !temp){
	  courant++;
	  temp=murs[4*(courant%4+2)+courant/4];
	  if(!temp){
	    res.graph[i].voisins.push_back(courant);
	  }
	}
      
	courant=i;
	temp=false;
      
	while(courant%4 != 0 && !temp){
	  courant--;
	  temp=murs[4*(courant%4+3)+courant/4];
	  if(!temp){
	    res.graph[i].voisins.push_back(courant);
	  }
	}
	courant=i;
	temp=false;
      
	while(courant<=11 && !temp){
	  courant=courant+4;
	  temp=murs[courant-4];
	  if(!temp){
	    res.graph[i].voisins.push_back(courant);
	  }
	}
	courant=i;
	temp=false;
      
	while(courant>=4 && !temp){
	  courant=courant-4;
	  temp=murs[courant];
	  if(!temp){
	    res.graph[i].voisins.push_back(courant);
	  }
	}
      }

      for(int j=0;j<16;j++){
	/*std::cout << " nb de voisins de " << j << ": " << res.graph[j].voisins.size()<<std::endl;
	for(unsigned int k=0;k<res.graph[j].voisins.size();k++){
	  std::cout<< res.graph[j].voisins[k] << " " ;
	}
	std::cout<<std::endl;
	*/
      }

      return res;
    }
  
} //end of namespace MMaze
