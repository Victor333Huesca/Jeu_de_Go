#TODO list

##Jeu online
* **Ajouter** la possibilité de faire une partie en *joueur contre joueur*.
* **Ajouter** un *tchat* pour le jeu *en ligne*.

##Menus
###Principaux
* **Créer** un *menu principal* permetant de lancer une *nouvelle partie*.
  - **Créer** un *onglet* de *chargement de partie*.
  - **Créer** un onglet de *chargement de problèmes*.
### Implémentation
* Le main a un tableau d'écran
* Chaque écran gère sa boucle principale et peut en sortir de 2 manières :
  - En renvoyant l'indice vers le nouvel écran (changement d'écran).
  - En appelant à son tour la boucle principale du sous-écran selectionné (uniquement pour les menus).
* Au démarage de chaque écran (et non à sa création) une fonction d'initialisation est appelée.
  - Cette fonction charge les textures.
  - Elle place les sprites.

###Ingame
* **Créer** un *menu pause*.
  - Ce menu doit permettre de **charger** une partie.
  - Il doit permettre de **sauvegarder** une partie.
  - Il doit mettre le jeu en **pause**.
  - On doit pouvoir **quitter le jeu**.
* **Ajouter** un historque des mouvements.
* **Ajouter** un cercle de marquage du dernier coup joué.
* **Ajouter** des raccourcis clavier.
* **Ajouter** un message d'info si il y a un atari et si un joueur place une pierre sur un ko.

##Autres
* **Créer** une *pause*.
* **Ajouter** des vrais graphismes.
* **Ajouter** quelques musiques d'ambiance .

