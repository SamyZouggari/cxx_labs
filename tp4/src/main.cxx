#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"


int main(){
    Univers u = Univers(3, 2, 0,10, Vecteur(5,5,5), 2.5);
    u.initParticulesRandom();
    u.display_cellules();
    return 1;
}