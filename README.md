# Jeu du 2048

Ce projet consiste à recréer le jeu du 2048 en C++ avec la bibliothèque graphique SDL3.

## Description

Le jeu repose sur une grille de 4 × 4 cases, affichée dans une fenêtre SDL. Chaque case peut contenir une tuile numérique dont la valeur augmente par puissances de deux.

Une grille initiale est générée automatiquement, puis mise à jour à chaque action du joueur. Celui‑ci peut déplacer les tuiles à l’aide des flèches du clavier. Lors d’un déplacement, les tuiles glissent dans la direction choisie et fusionnent avec une tuile de même valeur, conformément aux règles du jeu 2048.

Le programme gère l’ensemble des mécaniques : déplacement, fusion, apparition de nouvelles tuiles, détection de blocages et vérification de la condition de victoire (atteindre la tuile 2048).


## Installation

Pour compiler le projet, il est nécessaire d'avoir installé :

### 1. MSYS2 UCRT64 sous Windows

* Suivre le guide d'installation officiel : 
[https://www.msys2.org/](https://www.msys2.org/)

### 2. Ajouter G++ à la variable PATH :

- Appuyer sur **Windows + R** pour ouvrir la fenêtre **Exécuter**.
- Entrer :

```text
control sysdm.cpl,,3
```
- Cliquer sur **Variables d'environnement...**
- Dans **Variables système**, sélectionner **Path**.
- Cliquer sur **Modifier...**
- Cliquer sur **Nouveau**.
- Ajouter :

```text
C:\msys64\ucrt64\bin
```

- Valider avec **OK** jusqu'à la fermeture des fenêtres.


### 3. SDL3

```bash
#Terminal MSYS2 UCRT64

# Mise à jour des paquets MSYS2 :
pacman -Syu

# Installation de SDL3 :
pacman -S mingw-w64-ucrt-x86_64-sdl3

# Vérification de l’installation :
pacman -Qs SDL3

```


### 4. SDL3_ttf

```bash
#Terminal MSYS2 UCRT64

# Mise à jour des paquets MSYS2 :
pacman -Syu

# Installation de SDL3_TTF :
pacman -S mingw-w64-ucrt-x86_64-sdl3-ttf

# Vérification de l’installation :
pacman -Q mingw-w64-ucrt-x86_64-sdl3-ttf

```

### 5. SDL3_image

```bash
#Terminal MSYS2 UCRT64

# Mise à jour des paquets MSYS2 :
pacman -Syu

# Installation de SDL3_image :
pacman -S mingw-w64-ucrt-x86_64-sdl3-image

# Vérification de l’installation :
ls /ucrt64/include/SDL3_image/

```

### 6. Make

```bash
#Powershell avec les privilèges d'administrateur

# Installation du gestionnaire de paquets Chocolatey :
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# Vérification de l’installation :
choco --version

# Installation de l'outil make :
choco install make -y

# Vérification de l’installation :
make --version

```

# Compilation

Depuis le dossier du projet : `make`

Le Makefile se charge de récupérer les options nécessaires et de compiler les différents fichiers sources.

# Lancement

Après compilation, lancer l'exécutable généré :

`./main.exe`

ou, selon le nom de l'exécutable défini dans le Makefile :

`./nom_du_programme.exe`

Une fenêtre SDL s'ouvre alors et affiche la grille de 2048.

Amusez-vous !
