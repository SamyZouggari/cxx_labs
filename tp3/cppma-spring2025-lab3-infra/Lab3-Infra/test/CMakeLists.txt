# Créer un executable à partir de fichiers sources
add_executable(exe  ../src/main.cxx)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(exe vecteur)
