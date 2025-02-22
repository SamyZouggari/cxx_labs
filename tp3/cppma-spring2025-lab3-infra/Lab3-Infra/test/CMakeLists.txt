# Créer un executable à partir de fichiers sources
add_executable(test_1  ../src/test_point.cxx)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_1 vecteur)
