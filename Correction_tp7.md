# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 1
+ Équipe #   : 1112
+ Correcteur : Ahmad Faour

# CODE

| Points importants                                        | Poids        |
| -------------------------------------------------------- | ------------ |
| La qualités et le choix de vos portions de code choisies | (3/5.0)      |
| La qualités de vos modifications aux Makefiles           | (3/5.0)      |
| __Résultat partiel__                                     | __(6/10.0)__ |

# RAPPORT

| Points importants                                                           | Poids       |
| --------------------------------------------------------------------------- | ----------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (2/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (2/2.0)     |
| Explications claires avec un bon niveau de détails                          | (2/2.0)     |
| Bon français                                                                | (1/1.0)     |
| __Résultat partiel__                                                        | __(7/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5        |
| ------------------------ | ----------- |
| compilation sans erreurs |             |
| etc                      |             |
| __Résultat partiel__     | __(3/3.0)__ |


# Résultat

__Total des points: 16.0/20__

# Commentaires du correcteur:
## Commentaire global

## Commentaire par fichiers/Classes
### Can
* Beaucoup de commentaire inutile
* Les classes commencent par une lettre majuscule

### Hbridge
* Les constructeurs/destructeurs sont toujours les premriers dans l'ordre
* Valeur magique
* Très bonne utilisation des paramètres `const`

### IO
* Les fonctions en lien avec les *Led* ne devrait pas se retrouver dans ce fichier
* Commentaire inutile
* Code mort
* Dans la méthode `setInputInterrupts` pourquoi ne pas avoir mis un `enum` pour donner l'option de comment réagir au interruption?

### Timer
* Quand vous utilisez les constructeurs/desctructeur par défaut faite juste pas en mettre XD
* L'attribut `timer_step_ms`
  * Ne respecte pas le camelCase
  * N'est utilisé qu'à un endroit et ne représente pas vraiment un attribut de la classe
* Utilisation d'un enum pour le *Prescaler*
* Trop de commentaire
* Code mort
* Je ne comprends pas le nom du paramètre `reg` dans `setPrescaler`

### Uart
* Valeur magique
* Trop de commentaire inutile
* Vous activez la reception, mais vous n'avez aucune méthode pour lire?


## Makefile
### Librairie
* Constante inutile: `LDFLAGS`
* Manque des constates pour: `AR=avr-ar`, `ARFLAGS=-crs`, `CXX=avr-g++`, `REMOVE=rm -f`
### Exec
* Manque `INC=-I./librairie` (ligne 35), pour inclure les fichiers de la librairie
* Aurait dû être `LIBS=-L./librairie -llibrairie.a` (ligne 38)


# Basé sur le commit suivant
```
commit 8bb612b3685d39e875dfcfb34d95d8fd941b3a46
Author: Maxime Laroche <maxime-1.laroche@polymtl.ca>
Date:   Wed Mar 17 14:56:05 2021 -0400

    mkis le tout dans codecommun
```

# Fichiers indésirables pertinents
Aucun

# Tous les fichiers indésirables
Aucun

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `codecommun/tp/tp7/lib`
```
make: *** correction_tp7/1112/codecommun/tp/tp7/lib: No such file or directory.  Stop.

```

## Sortie de `make` dans `codecommun/tp/tp7/exec`
```
make: *** correction_tp7/1112/codecommun/tp/tp7/exec: No such file or directory.  Stop.

```
