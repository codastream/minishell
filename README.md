# miniShell
MiniShell

Règles à respecter pour le shell :
1. Affichage et commandes de base :
  • Afficher une invite lorsqu’il attend une nouvelle commande.
  • Avoir un historique fonctionnel.
2. Recherche et exécution des commandes :
  • Rechercher et lancer le bon exécutable :
    • En fonction de la variable PATH.
    • Ou en utilisant un chemin relatif ou absolu.
3. Gestion des caractères spéciaux et des citations :
  • Ne pas interpréter :
    • Les guillemets non fermés.
    • Les caractères spéciaux qui ne sont pas requis (ex. \ ou ;).
  • Gérer les guillemets simples (') : empêcher l’interprétation des métacaractères dans la séquence entre guillemets.
  • Gérer les guillemets doubles (") : empêcher l’interprétation des métacaractères sauf pour $.
5. Redirections :
  • < : Rediriger l’entrée.
  • > : Rediriger la sortie.
  • << :
    • Accepter un délimiteur.
    • Lire l’entrée jusqu’à rencontrer une ligne contenant ce délimiteur.
    • Note : Cela ne doit pas mettre à jour l’historique.
  • >> : Rediriger la sortie en mode ajout (append).
5. Gestion des pipes :
  • Gérer les pipes (|) :
    • La sortie de chaque commande doit être connectée à l’entrée de la commande suivante.
6. Gestion des variables et du statut d'exécution :
  • Gérer les variables d’environnement ($ suivi d’une séquence de caractères) et les développer en leurs valeurs.
  • Gérer ? pour qu’il se développe en le statut de sortie du dernier pipeline exécuté en premier plan.
7. Gestion des raccourcis clavier :
  • ctrl-C : Afficher une nouvelle invite sur une nouvelle ligne (en mode interactif).
  • ctrl-D : Quitter le shell.
  • ctrl-\ : Ne rien faire (en mode interactif).
8. Commandes internes à implémenter :
  • echo avec l’option -n.
  • cd avec un chemin relatif ou absolu uniquement.
  • pwd sans options.
  • export sans options.
  • unset sans options.
  • env sans options ni arguments.
  • exit sans options.
