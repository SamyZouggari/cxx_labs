#include<iostream>
#include"vecteur.hxx"
#include"particule.hxx"
int main(){
  Vecteur v1= Vecteur(1,2,3);
  Vecteur v2= Vecteur(6,5,4);
  Vecteur v3 = Vecteur(6,5,4);
  std::cout<< "test d'affichage" << std::endl;
  std::cout<<v1<<std::endl;
  std::cout<<v2<<std::endl;

  std::cout<< "test de l'addition entre v1 et v2" << std::endl;
  std::cout<< v1+3 << std::endl;


  return EXIT_SUCCESS;
}