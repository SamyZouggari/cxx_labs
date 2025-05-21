# Créer un executable à partir de fichiers sources
add_executable(test_particules1  ../test/test_particules1.cxx)
add_executable(test_particules2  ../test/test_particules2.cxx)
# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_particules1 vecteur)
target_link_libraries(test_particules2 vecteur)
