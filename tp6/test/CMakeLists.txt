# Créer un executable à partir de fichiers sources
add_executable(exe  ../src/main.cxx)
#add_executable(test_point ../src/test_point.cxx)
add_executable(test_abs test_absorption.cxx)
add_executable(test_period test_period.cxx)
add_executable(test_reflex test_reflex.cxx)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(exe vecteur)
target_link_libraries(test_abs PRIVATE vecteur)
target_link_libraries(test_period PRIVATE vecteur)
target_link_libraries(test_reflex PRIVATE vecteur)