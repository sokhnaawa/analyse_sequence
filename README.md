Présentation:
==============
Ce projet vise la mise en œuvre d’un logiciel d’analyse de séquences génomiques et protéiques eucaryotes, mettant à
disposition de l’utilisateur des modules complémentaires pouvant s’enchaîner à la manière d’un pipeline :
 
1. Transcription d’une séquence ADN en séquence ARN
2. Traduction d’une séquence codante en séquence protéique 
3. Calcul du score d’identité entre deux séquences 
4. Calcul du score de similarité de polarité entre deux séquences protéiques 
5. Recherche d’une séquence consensus à partir d’un alignement multiple

Compiler le projet
==================
compiler tous les modules:
-----------------
+ cd to /path_tp_project
+ $ make build_all

Compiler par module
---------------------

***A. Module transcription***
   + make transcription

***B. Recherche sequence***
   + make recherche

***C. Traduction***
   + make translation

***D. calcule score***
   + make calculescore

***E. score semilaire***
   + make scoresemilaire


Personnaliser l'endroit d'enregistrement des fichiers générer:
-------------------------------------------------------------
Dans le fichier: lib/constants.h


