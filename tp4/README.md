# TP4 - Découpage de l'univers

## Objectifs

Ce TP poursuit l’évolution du simulateur particulaire en C++, avec un accent mis sur :
- L’optimisation du calcul des forces entre particules
- L’utilisation du **potentiel de Lennard-Jones**
- La mise en place d’un **maillage spatial** pour limiter la complexité
- La gestion d’un univers organisé en **cellules et voisinages**
- Une première **application physique** : collision entre deux blocs de particules

## 1. Création de l’univers

Nous avons conçu une nouvelle classe `Univers`, qui représente :
- Les **dimensions** de l’univers (1D, 2D ou 3D)
- Le **nombre total de particules** dans celui-ci
- Les **limites spatiales** avec un vecteur `ld`
- Un **rayon de coupure** (`rcut`) à partir duquel l’interaction est négligée
- Un **nombre de cellules** dans chaque direction de l'espace : `nc`
- Un **conteneur de particules** afin de stocker toutes les particules de l'univers (dans un `std::vector`)
- Un dictionnaire dont la clef est 

L’espace est découpé en **cellules** de taille `rcut`, organisées en grille tensorielle :
- Chaque cellule connaît ses **voisines**
- Chaque particule appartient à une cellule

Cette structure permet de restreindre les calculs d’interaction à des cellules proches.