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
  std::cout<< v1+v2 << std::endl;
  std::cout<< "test de la soustraction entre v1 et v2" << std::endl;
  std::cout<< v1-v2 << std::endl;
  std::cout<< "test du produit entre v1 et 2" << std::endl;
  std::cout<< v1*2 << std::endl;  
  std::cout << "Test d'égalité entre v2 et v3 (meme coordonnées)" << std::endl;
  std::cout << (v2==v3) << std::endl;
  std::cout << "Test d'égalité entre v2 et v1 (coordonnées différentes)" << std::endl;
  std::cout << (v2==v1) << std::endl;
  std::cout << "Test d'accès aux coordonnées x,y et z de v1 (avec out of range)" << std::endl;
  std::cout << "x = " << v1[0] << ", y = " << v1[1] << ", z =" << v1[2] << std::endl;
  std::cout << "Modification de x puis affichage" << std::endl;
  v1[0] = 10;
  std::cout << "nouveau x :" << v1[0] << std::endl;


  return EXIT_SUCCESS;
}