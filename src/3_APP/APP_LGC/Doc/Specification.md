# Prolégomène
    ce module gère la logique 
    AArchitecture ROAR -> https://theses.hal.science/tel-00766861v2/document
    Au lieu de faire une architecture séquentielle, c'est-à-dire qu'à chaque cyclic on va lire les sensors, effectuer la logic à partir des valeurs des sensors, et on va set les actuators. Ceci de manière cylclique. Je préferrai faire une Architecture ou chaque module de contrôle du robot (Navigation, Déplacement d'un gantry, etc) determinera dynanmiquement à quelle fréquence sa logique doit être appelé, par exemple si on est dans un moment ou l'on est statique et on récolte de la salade, le module qui s'occupe de la navigation va dire "moi une fois toutes les 500 ms ça suffit" et en revanche le module qui s'occupe du gantry va dire "moi je veux être appelé toutes les 5 ms parce que j'ai plein de truc à faire" 

    chaque agent possède des noeuds fonctionnels 'nodeFunc'. Chaque noeuds représente une partie d'un mouvement complexe
    ou juste un mouvement simple, Chaque noeud peut hérité d'enfant ou être issu d'un parent. Au sens où si un noeud
    est OFF ses enfants le sont aussi. 
    Un noeud possède strictement 
        - Un état général ON/OFF
        - Un état fonctionnel STOPPED/MOVING_INHIBIT etc
        - un/des setPoints pour les actuators

    Le rôle de chaque agent est de d'actualiser cycliquement l'état de leur service et 