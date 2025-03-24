#include"univers.hxx"
#include"vecteur.hxx"
#include"cellule.hxx"
#include"particule.hxx"


int main(){
    Univers u = Univers(3, 10, 0,10, Vecteur(5,5,5), 2.5);
    std::cout << "Création des particules dans l'univers" << std::endl;
    u.initParticulesRandom();
    std::cout << "\nAffichage des particules" << std::endl;
    u.display_particules();
    std::cout << "\nAffichage des cellules découpant l'univers" << std::endl;
    u.display_cellules();
    return 1;
}