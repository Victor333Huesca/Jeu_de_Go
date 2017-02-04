# Jeu_de_Go

##Présentation du projet
* Projet de Jeu de solveur de vie/mort au jeu de GO dans le cadre de l'ue HLIN405.
* Le but de ce projet est de parvenir a créer une IA basic indiquant si, à partir d'une situation donnée, un groupe de pierre peuvent survivre.
* Ceci pouvant ammener si tout se passe comme prévu à une IA basic permetant de jouer en Humain vs Machine sur une plateau résonnable (8 x 8 ?).

##Pourquoi la *SFML* ?
* La *SFML* est une bibliothèque originelement déstiné au language *C++* mais portée également vers [*d'autres languages*](http://www.sfml-dev.org/download/bindings-fr.php) divers et variés. Celle-ci permettet -entre autre- un affichage *graphique*, des outils *système*, *réseau* et même *audio*.
* Notre choix s'est porté sur celle-ci car elle est extrèmement bien documentée (en français en plus) et elle présente un bon rapport en simplicité d'utilisation et possibilitées appportées.

##Procédure d'instalation##
1. **Télécharger** la *sfml* pour votre plaforme (
[linux](http://www.sfml-dev.org/files/SFML-2.4.1-linux-gcc-64-bit.tar.gz), 
[mac OS X](http://www.sfml-dev.org/files/SFML-2.4.1-osx-clang.tar.gz), 
[autres](http://www.sfml-dev.org/download/sfml/2.4.1/index-fr.php)).
2. **Cloner** le présent dépôt dans votre répertoire ed travail.
3. **Décompresser** l'archive.
4. Pluieurs possibilitées existent.
  1. **Placer** les dossiers *include* et *lib* dans */usr/local/*.
  2. **Placer** les dossiers *include* et *lib* dans le dossier contenant le makefile.
  3. **Placer** les dossiers le dossier *SFML-2.X.X* où vous le souhaitez *-par explemple dans votre home-* et modifiez la variable *REP_SFML* du *makefile* par l'emplacement du dossier.
5. **Ouvrez** un *terminal* à l'emplacement du *makefile* et **executer** la commande *make* pour lancer la compilation.
6. **Executer** le fichier *GoSolver* et profitez de votre partie de *GO* !
