# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main
# Remplacer ... par les fichiers nécessaires 
add_library(vecteur affichage.cxx vecteur.cxx particule.cxx univers.cxx cellule.cxx )
target_include_directories(vecteur PUBLIC ${CMAKE_SOURCE_DIR}/include)