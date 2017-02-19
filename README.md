# Jeu_de_Go

##Présentation du projet
* Projet de Jeu de solveur de vie/mort au jeu de GO dans le cadre de l'ue HLIN405.
* Le but de ce projet est de parvenir à créer une IA basique indiquant si, à partir d'une situation donnée, un groupe de pierre peut survivre.
* Ceci pouvant amener si tout se passe comme prévu à une IA permetant de jouer en Humain vs Machine sur un plateau résonnable (8 x 8 ?).

##Pourquoi la *SFML* ?
* La *SFML* est une bibliothèque originellement destinée au language *C++* mais portée également vers [*d'autres languages*](http://www.sfml-dev.org/download/bindings-fr.php) divers et variés. Celle-ci permet -entre autre- un affichage *graphique*, des outils *système*, *réseau* et même *audio*.
* Notre choix s'est porté sur celle-ci car elle est extrêmement bien documentée (en français en plus) et elle présente un bon rapport en simplicité d'utilisation et possibilitées appportées.

##Procédure d'installation
1. **Télécharger** la *sfml* pour votre plate-forme (
[Linux](http://www.sfml-dev.org/files/SFML-2.4.1-linux-gcc-64-bit.tar.gz), 
[Mac OS X](http://www.sfml-dev.org/files/SFML-2.4.1-osx-clang.tar.gz), 
[autres](http://www.sfml-dev.org/download/sfml/2.4.1/index-fr.php)).
2. **Cloner** le présent dépôt dans votre répertoire de travail.
3. **Décompresser** l'archive.
4. Plusieurs possibilitées existent.
  - **Installer** la SFML depuis le gestionnaire de paquets de votre distribution Linux : *libsfml-dev* pour Ubuntu et *SFML-devel* pour Fedora.
  - **Télécharger** la SFML via le [site internet de la bibliothèque](http://www.sfml-dev.org/index-fr.php) et effectuer l'une des opérations suivantes au choix : 
    * **Placer** les dossiers *include* et *lib* dans */usr/local/*.
    * **Placer** le dossier de la SFML contenant les dossiers *lib* et *include* dans le dossier *Jeu_de_Go* (à l'emplacement du makefile). Vous devrez dans ce cas compléter les lignes *25* et *26* du makefile par -respectivement- les lignes suivantes : -L $(REP_LIB) et -I $(REP_INC).
    * **Placer** les dossiers le dossier *SFML-2.X.X* où vous le souhaitez *-par exemple dans votre home-* et modifier le makefile comme précédemment en modifiant la valeur ligne *12* par le nouvel emplacement de la SFML.
  - **Compiler** la SFML depuis les sources disponibles sur ce [github](https://github.com/SFML/SFML.git). Clonez le repo, utilisez *cmake .* puis *make install* pour l'installer comme au 1er point ci-dessus ou simplement *make* et en choisissant une des deux autres possiblités déjà expliquées ci-dessus.
5. **Ouvrez** un *terminal* à l'emplacement du *makefile* et **exécuter** la commande *make* pour lancer la compilation.
6. **Exécuter** le fichier *GoSolver* et profitez de votre partie de *GO* !
