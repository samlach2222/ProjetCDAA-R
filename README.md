# Projet CDAA-R

[![GitHub version](https://img.shields.io/badge/version-2.1.2-purple.svg)](https://img.shields.io/badge)

## Projet de CDAA (Conception et Développement Avancée d'Applications) portant sur la création d'une interface de gestion de contacts en C++ avec Qt.

# I) Introduction
## Qu'est-ce que CDAA-R

Le projet CDAA-R est un projet développé en Qt (partie graphique) et en C++ (partie métier). Celui-ci consiste en la création d'une application de gestion de contacts avec toutes les fonctions qui lui sont liées.
Les notions alors abordées sont :
- La conception graphique
- La programmation Objet
- La gestion de base de données SQLite
- La gestion de fichiers JSON
- Les différents contrôleurs de Qt

Nous allons donc présenter dans ce rapport notre application finie, des coulisses de celle-ci, jusqu'à son installation.

## Documentation Doxygen

Notre projet étant en source libre sur **GitHub** , la documentation **Doxygen** est un outil indispensable pour permettre à toute personnes s'intéressant au projet de savoir rapidement les composants et le fonctionnement de celui-ci. On peut alors retrouver cette documentation **ci-dessous** :
-  [lien vers la documentation](Doxygen/html)

# II) Conception
## Diagramme de classe

[![Conception du projet](Conception/projetCDAA.png "Cliquez pour la version PDF")](https://github.com/samlach2222/ProjetCDAA-R/blob/main/Conception/projetCDAA.pdf?raw=true)

Nous trouvons sur la feuille précédente le diagramme UML de Classes présentant notre projet. Il est composé de la partie Métier/Logic qui forme l'ensemble des classes gérant les structures et les choses internes ; de la partie Interface/IHM gérant toutes les classes visuelles avec des fenêtres montrées au joueur ; et enfin de la partie Stockage/Storage gérant les entrées et sorties du projet que ce soit par fichier ou par base de données. Les classes qui composent ces trois packages et leurs liaisons seront décrites dans les parties suivantes.

## Explication des liaisons interclasses
### 1. Package Métier/Logic

Dans ce premier package, la classe principale est la classe GestionContact. Elle est composée de plusieurs contacts, elle gère donc ceux-ci. Pour toutes modifications, on a une agrégation de la classe Log sur GestionContact, afin de notifier tout changement. À un contact on peut ajouter des interactions, FicheContact est donc composée d'Interaction. Une interaction est elle-même composée d'un ou plusieurs tagsInteraction (tags date et todo). Afin de toujours savoir quand un ajout a été fait, les classes FicheContact, Interaction et Log sont horodatées avec la classe Horodatage dans des liaisons d'agrégation. Avec ces compositions nous avons donc des liaisons qui sont grammaticalement logiques. En effet, s'il n'y a plus de gestions de contacts, les contacts n'existent plus ; s'il n'y a plus de contact, il n'y a plus d'interactions liées et de même pour les tags. Nous avons donc ainsi un respect des principes SOLID. Enfin la dernière classe est SoundPlayer, c'est une classe statique, elle est appelée sans être instanciée donc elle n'a pas de liaisons UML.

### 2. Package Interface/IHM :

Au sein de ce package, les liaisons sont plus faciles. Toutes les classes UI_nomDeLaClasse sont des composants de MainWindow. En effet si celle-ci est détruite, il n'y a plus de programme, donc toutes les autres fenêtres formées par les classes UI sont fermées, il y a donc compositions. Si les liaisons intra-package sont faciles, les liaisons extra-packages sont plus complexes. MainWindow est composée de GestionContact du package précédent. Par la même occasion, UI_SaveGestionContact récupère GestionContact pour l'import et l'export. Enfin UI_InteractionContact récupère FicheContact pour récupérer directement les interactions de ce contact.


### 3. Package Stockage/Storage :

Pour finir, ce package est composé uniquement de classes statiques. Il ne comprend donc aucunes liaisons UML.

# III) Installation
## Installation EXE + UWP

Notre installateur se présente comme un fichier EXE permettant d'installer notre application. En l'exécutant, la fenêtre d'installation s'ouvre et l'application peut être installée en suivant la procédure suivante :

https://user-images.githubusercontent.com/89837262/146622589-b53abf32-9fe8-4255-985f-78dee8e1b28c.mp4

À la fin de l'installation, le répertoire d'installation s'ouvre. On y retrouve l'exécutable EXE de l'application. Si on regarde dans le menu démarrer, on trouvera également l'application au format UWP (Universal Windows Platform, application Windows Store). Enfin dans le dossier d'installation se trouve le fichier APK (Android Package Kit) qui va nous servir pour la partie suivante.

## Installation APK

Une fois que nous avons notre fichier APK, nous le récupérons depuis notre appareil Android (tablette, smartphone). En cliquant sur celui-ci, une demande d'autorisation vous sera faite, il suffit d'accepter pour lancer l'installation de celui-ci comme ci-contre :

https://user-images.githubusercontent.com/89837262/146622718-3394e0a5-5147-4ae4-8616-3cb5b06bc881.mp4

# IV) Utilisation

Maintenant que l'application est installée sur notre support préféré, nous allons voir deux points qui se distingue de l'utilisation normale que l'on aurait de l'application.

## Touches clavier pour naviguer

Beaucoup d'utilisateurs ayant un usage avancé d'un ordinateur utilisent les raccourcis clavier pour naviguer sur un logiciel. La navigation à l'aide du clavier est donc totalement possible sur notre application, comme montré ci-dessous :

https://user-images.githubusercontent.com/89837262/146622739-081e7fe3-8162-415e-a353-80d00bc25fef.mp4

## Feedbacks sonores

Dans un jeu vidéo comme dans une application, aussi petite soit-elle, la patte musicale est super importante. On reconnaitra facilement une interface avec des bons retours (ou feedbacks) sonores (comme les menus de Nintendo avec des bruitages très reconnaissables et qui donnent plaisir à juste naviguer dans cette interface).

À notre petite échelle, nous avons donc musicalement travaillé sur les sons des boutons afin d'obtenir une sonorité agréable à l'oreille, qui donne envie de cliquer sur les différents boutons de notre application. Après analyse des sons de plusieurs applications et systèmes d'exploitation, nous avons décidé de procéder à un enregistrement personnel, avec une série de traitement pour façonner ce bruitage à notre image. Le deuxième bruitage est le message d'erreur, celui-ci se doit d'être impactant et de ne pas frustrer l'utilisateur, nous l'avons donc créé en conséquence. Vous pouvez alors les entendre ci-dessous :

https://user-images.githubusercontent.com/89837262/146622763-99f3f85a-80d1-43a3-90e7-9f81045c7af6.mp4

https://user-images.githubusercontent.com/89837262/146622787-12927ad6-4e1b-41f3-899f-fb2163442990.mp4

#### Membres du projet :

* **Loïs PAZOLA** - [@Mahtwo](https://github.com/Mahtwo)
* **Samuel LACHAUD** - [@samlach2222](https://github.com/samlach2222)
