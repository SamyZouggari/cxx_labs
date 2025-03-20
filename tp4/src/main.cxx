#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"


int main(){
    Univers u = Univers(3, 40, 0,10, Vecteur(20,20,20), 2.5);
    u.displayUnivers();
    return 1;
}