**Suivi de Performance Athlétique**


**Aperçu**

Ce programme en C sert de suivi de performance athlétique, permettant aux utilisateurs de gérer les profils des athlètes, d'enregistrer les séances d'entraînement et d'analyser les données de performance. Le programme offre des fonctionnalités pour les athlètes individuels ainsi que pour les équipes de relais.

**Fonctionnalités**

Gestion des Athlètes: Les utilisateurs peuvent créer et gérer les profils des athlètes, y compris les détails personnels tels que le nom, l'âge, le genre et le type de performance.
Enregistrement des Séances d'Entraînement: Les athlètes peuvent enregistrer leurs séances d'entraînement, en spécifiant la date, le type d'événement (par exemple, 100m, 400m) et le temps réalisé.
Entraînement en Relais: Support spécial pour les événements de relais, permettant à plusieurs participants d'enregistrer les temps de passage et les positions.
Analyse des Données: Le programme offre diverses fonctionnalités pour analyser la performance des athlètes, notamment :
Résumé de performance pour des événements spécifiques, montrant les meilleurs, les pires et les temps moyens.
Recherche des meilleurs athlètes pour des événements spécifiques basés sur la performance.
Suivi de la progression de l'athlète entre deux dates pour un événement donné.
Analyse de régression linéaire pour prédire les tendances de performance futures basées sur les données historiques.

**DEMARRAGE**

Etape 1 | Cloner le Dépôt: Clonez ce dépôt sur votre machine locale en utilisant :
git clone https://github.com/chady12/suivi-performance-athletique.git

**OU**

Télécharger le fichier main.c et suivre les prochaines étapes sur le terminale (**PLUS SIMPLE**)

Etape 2 | Compiler le Programme: Compilez le programme en utilisant votre compilateur C préféré. Par exemple :
gcc -o main main.c

Etape 3 | Exécuter le Programme: Exécutez le programme compilé :
./main

Etape 4 | Suivre les Instructions à l'Écran: Utilisez l'interface interactive du programme pour gérer les athlètes, enregistrer les séances d'entraînement et analyser les données de performance.

**UTILISATION**

- Création de Profils d'Athlètes: Les utilisateurs peuvent créer des profils d'athlètes en fournissant des détails personnels tels que le nom, l'âge, le genre et le type de performance.

- Enregistrement des Séances d'Entraînement: Les athlètes peuvent ajouter des séances d'entraînement, en spécifiant la date, le type d'événement et le temps réalisé. Un support spécial est disponible pour les événements de relais.

- Analyse de la Performance: Les utilisateurs peuvent analyser la performance des athlètes grâce à diverses fonctionnalités, notamment des résumés de performance, des classements des meilleurs athlètes et des analyses de progression.

**EXPLICATION DU PROGRAMME**
1. `isValidDateFormat(const char *date)`
   - Fonction pour valider le format de date (AAAA-MM-JJ).
   - Entrée : `date` (chaîne de caractères)
   - Sortie : `booléen` (vrai ou faux)
   
2. `linearRegression(Performance performances[], int num_performances, float *slope, float *intercept)`
   - Fonction pour calculer la régression linéaire.
   - Entrées : `performances` (tableau de structures Performance), `num_performances` (entier), `slope` (pointeur de float), `intercept` (pointeur de float)
   - Sorties : Aucune (résultats stockés dans `slope` et `intercept`)

3. `enterAthleteData(Athlete *athlete)`
   - Fonction pour saisir les informations de l'athlète.
   - Entrée : `athlete` (pointeur vers la structure Athlete)
   - Sortie : Aucune

4. `createAthleteFile(Athlete athlete)`
   - Fonction pour créer un fichier pour l'athlète.
   - Entrée : `athlete` (structure Athlete)
   - Sortie : Aucune

5. `readAthleteFile(char *filename)`
   - Fonction pour lire et afficher les informations de l'athlète à partir d'un fichier.
   - Entrée : `filename` (chaîne de caractères)
   - Sortie : Aucune

6. `loadExistingAthlete()`
   - Fonction pour charger les données d'un athlète existant.
   - Sortie : `Athlete` (structure de l'athlète chargée)

7. `addRelayTraining(Athlete *athlete, const char *training_date)`
   - Fonction pour ajouter un entraînement de relais pour un athlète.
   - Entrées : `athlete` (pointeur vers la structure Athlete), `training_date` (chaîne de caractères)
   - Sortie : Aucune

8. `addTraining(Athlete *athlete)`
   - Fonction pour ajouter un entraînement pour un athlète.
   - Entrée : `athlete` (pointeur vers la structure Athlete)
   - Sortie : Aucune

9. `readAthleteTrainingHistory(char *filename)`
   - Fonction pour lire et afficher l'historique d'entraînement de l'athlète à partir d'un fichier.
   - Entrée : `filename` (chaîne de caractères)
   - Sortie : Aucune

10. `readAthleteRelayTrainingHistory(char *filename)`
    - Fonction pour lire et afficher l'historique d'entraînement de relais de l'athlète à partir d'un fichier.
    - Entrée : `filename` (chaîne de caractères)
    - Sortie : Aucune

11. `readAthleteTrainingHistoryByDate(char *filename)`
    - Fonction pour lire et afficher l'historique d'entraînement de l'athlète pour une date spécifique à partir d'un fichier.
    - Entrée : `filename` (chaîne de caractères)
    - Sortie : Aucune

12. `readAthleteRelayTrainingHistoryByDate(char *filename, char *searchDate)`
    - Fonction pour lire et afficher l'historique d'entraînement de relais de l'athlète pour une date spécifique à partir d'un fichier.
    - Entrées : `filename` (chaîne de caractères), `searchDate` (chaîne de caractères)
    - Sortie : Aucune

13. `athletePerformanceSummary(Athlete athlete, EventType event_type)`
    - Fonction pour calculer le meilleur, le pire et le temps moyen pour un événement donné pour un athlète.
    - Entrées : `athlete` (structure Athlete), `event_type` (énumération EventType)
    - Sortie : Aucune

14. `findTopAthletesForEvent(Athlete *athletes, int num_athletes, EventType event_type)`
    - Fonction pour trouver les meilleurs athlètes pour un événement donné en fonction des temps moyens.
    - Entrées : `athletes` (tableau de structures Athlete), `num_athletes` (entier), `event_type` (énumération EventType)
    - Sortie : Aucune

15. `athleteProgression(Athlete athlete, char *start_date, char *end_date, EventType event_type)`
    - Fonction pour afficher la différence de temps pour un athlète entre deux dates pour un événement spécifique.
    - Entrées : `athlete` (structure Athlete), `start_date` (chaîne de caractères), `end_date` (chaîne de caractères), `event_type` (énumération EventType)
    - Sortie : Aucune

16. `main()`
    - Fonction principale où les données de l'athlète, les entraînements, les analyses et les opérations sur les fichiers sont effectuées.
    - Entrée : Aucune
    - Sortie : `entier` (statut de retour)

**CONTRIBUTEUR**

- ZAAROUR Chady
- BOUDARGA Mohamed-Amine
- Ait el-Kadi Amine

CECI EST UN PROJET DEDIER A **CY TECH**
