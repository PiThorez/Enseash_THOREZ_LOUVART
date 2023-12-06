Fichiers test :

Le fichier test1 sert à afficher une autre valeur de fin de code (exit).
Le fichier test2 contient une fonction qui génère une erreur de segmentation, ce qui nous permet de tester si l'on différencie bien la fin d'un programme avec une exit ou un signal.
Le fichier test3 contient une fonction qui permet de faire attendre le programme pendant 100ms, pour tester si notre temps d'execution affiche était cohérent.

Question 1

    On utilise la fonction "write". Ces arguments sont : 

                    - STDOUT_FILENO     : cela correspond à l'endroit ou seront écrit les données (STDIN_FILENO permet d'écrire sur la console)
                    - bienvenue         : correspond au message de bienvenue qu'on souhaite renvoyer
                    - strlen(bienvenue) : présice la taille du message à écrire

![Capture question 1](Images/question1.png)

Question 2

Lecture :
    Pour la lecture, on utilise la fonction "read". Ces arguments sont similaires à "write" :

                    - STDIN_FILENO      : cela correspond à l'endroit ou seront lues les données (STDIN_FILENO permet de lire sur la console)
                    - cmd_read          : permet de récupérer la commande écrite par l'utilisateur
                    - TAILLE            : correspond à la taille maximale de cmd_read (ici 128)

Execution et retour au prompt :

    Grâce à un fork(), cela est possible : on fait deux processus, un qui execute la commande pendant que l'autre se met en attente et reviendra au prompt une fois l'execution terminée.

![Capture question 2](Images/question2.png)

Question 3

    Pour faire un exit en tapant "exit" ou en faisant CTRL+D, il faut se placer avant le fork() sinon un des processus reviendra au prompt "enseash%". De plus, pour reconnaitre si CTRL+D est pressé, il faut regarder quand cmd_size = 0.

![Capture question 3](Images/question3.png)

Question 4
 
    Pour afficher le code de retour de la commande précédente, on se sert du statut pour récupérer cette valeur.

![Capture question 4](Images/question4.png)

Question 5 

    On affiche en complément le temps d'exécution de la commande à l'aide de la fonction clock_gettime.

![Capture question 5](Images/question5.png)


Question 6

    Pour repérer si un argument est présent, on regarde s'il y a un espace " " dans la chaine envoyée par l'utilisateur puis on exécute la commande avec l'argument.

![Capture question 6](Images/question6.png)

Question 7

    Pour gérer les redirections avec '<' et '>', on utilise la fonction dup2

![Capture question 7](Images/question7.png)

Question 8



![Capture question 8](Image/question8.png)