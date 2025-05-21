# Simulation de particules en C++ — TP 3

Projet réalisé dans le cadre du module **MMIS C++ pour les mathématiques appliquées** à Grenoble INP.

## Objectif

Le but de ce TP est de concevoir une simulation de particules en interaction gravitationnelle, en exploitant les opérateurs C++ pour rendre les structures de données plus expressives et efficaces.

Ce laboratoire approfondit la manipulation des objets, des opérateurs et des conteneurs en C++, en construisant une mini-simulation physique.

------------------------------------------------------------------------

### QUESTION 1

Une classe `Vecteur` représentant un vecteur 3D a été implémentée.

La classe possède trois attributs qui correspondent chacune a une coordonnées de l'espace. Le type des composantes est `double` pour une meilleure précision.

### QUESTION 2

Cette classe possède un constructeur (qui gère une instanciation par défaut). Le constructeur par recopie est `default` car les attributs ne sont pas des pointeurs.

Pour les surcharges: nous avons décidé de surcharger seulement les opérations qui nous sont utiles. l'opérateur `+=`, `-=`, `==`, `!=`, `*=`, `[]`, `=`, `+`, `-`, `*`, `<<`.

L'opérateur d'affectation par recopie aurait pu être default. La surcharge de `[]` a été réalisée de deux manières afin de différencier les accès en tant que lvalue ou en tant que rvalue.

Une méthode norme a été implémentée, elle servira pour plus tard.

### QUESTION 3

Nous avons fait des tests qui permettent de vérifier chaque méthode. C'est l'éxecutable test_1.

### QUESTION 4

Nous modifions la classe `Particule` afin de stocker les positions et les vitesse directement à l'aide de la nouvelle classe `Vecteur`. Nous modifions les getters en conséquence.

### QUESTION 5

Une classe Univers est créée possédant les attributs privés dim, nbParticules, et un vecteur de particules. Les méthodes demandées ont été implémentées.

### QUESTION 6

Un fichier de test a été créé permettant de répondre aux questions

### QUESTION 7

L'éxecution du code de test a prit 0.014s pour un vecteur de particules. Cela aurait pu être plus rapide pour un conteneur de type std::list mais c'est seulement plus efficace pour l'insertion ou la suppression. Il est donc préférable de garder un std::vector comme structure de conteneur.

### QUESTION 8

Le temps pris pour calculer les forces d'intéraction (et l'insertion dans le conteneur) pour (2^3)^5 partocuiles est 0.15s. 9.65s pour (2^4)^5 particules. Cela prend trop de temps pour les puissances supérieures.

### QUESTION 9

Pour diviser le temps de calcul par 2, nous utilisons le fait que la force d'interaction est symétrique. F_ij = -F_ji. L'implémentation a été faite dans une deuxième méthode de calcul des forces.

## QUESTION 10

La force d'interaction interparticules est négligeable pour des particules éloignées. En guise de simplification nous pouvons ignorer les particules éloignées. ------------------------------------------------------------------------

## 🔧 Compilation

make all
