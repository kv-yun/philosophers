# philosophers

Projet en C ayant pour but de nous faire découvrir la programmation multithread. Pour cela nous devions réaliser une simulation du fameux probleme du Dîner des philosphes

# execution

Compilation: `Make`

Format d'execution: `./philo nombre_philosophe temps_avant_de_mourir temps_pour_manger temps_pour_dormir`

# resultat

`temps_en_ms index_philo action`

Exemple:

`Make`

`./philo 3 210 100 100`

`0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
100 1 is sleeping
100 3 has taken a fork
100 3 is eating
100 2 has taken a fork
200 1 is thinking
200 3 is sleeping
200 2 has taken a fork
200 2 is eating
200 1 has taken a fork
210 1 died`
