Snell-Descartes
---------------

Visualisation de la transmission d'une onde à l'interface entre 2 milieux.

![Application screenshot](/Snell-Descartes.png?raw=true)

Installation :
--------------

Sous Windows

Avant la toute première exécution, vous aurez besoin d'installer le dernier gtk3 runtime 64bits
disponible sur ce dépot : https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer/releases
en laissant les valeurs par défaut, excepté le répertoire d'installation, si besoin.

"Snel-Descartes" peut être exécuté depuis n'importe quel répertoire tant que le précédent runtime
est installé sur la machine.




Sous linux

Vous aurez besoin que la librairie gtk3 soit installée sur votre système.


Compilation :
-------------

Sous linux utiliser la commande

$ make -f Makefile.gcc


Sous Msys pour Windows :

$ make -f Makefile.win
