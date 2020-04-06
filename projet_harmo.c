#include <stdio.h>
#include <stdlib.h>
#include<time.h>


//****************************************************************************************
        /*La structure qui nous permet de gerer nos grilles*/
//****************************************************************************************
struct grille{
    int magrille[9][9];
};
typedef struct grille grille;
//La nombre de grille dans notre tableau de grille
int taille=0;
//notre tableau de grille
grille tabgrille[1000];
//notre grille
grille test;
//le nombre d'iteration qu'on a pour jouer
int nb_iteration;
//Notre tableau pour stocker des positions de grilles qu'on a pas le droit d'effacer
int position[45][2];
//le nombre de valeurs qu'on a pas le droit de supprimer
int a;

//****************************************************************************************
        /*la fonction qui stoque les indices des cases qu'on a le droit de supprimer*/
//****************************************************************************************

int indicePosition(){
            int i,j;
            a=0;
            for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                   if(test.magrille[i][j]==0){
                    position[a][0]=i;
                    position[a][1]=j;
                    a++;
                   }
                }
            }
}
//****************************************************************************************
            /*Verifie si la position prise en parametre est modifiable*/
//****************************************************************************************

int existePos(int i,int j){
         int k;
         for(k=0;k<=a;k++){
            if(position[k][0]==i && position[k][1]==j) return 1;
         }
         return 0;
}
//****************************************************************************************
            /*Verifie si une grille est pleine*/
//****************************************************************************************
int grillePleine(){
		int i,j;
		for(i=0;i<9;i++){
			for(j=0;j<9;j++){
				if(test.magrille[i][j]==0) return 0;
			}
		}
		return 1;
}

//****************************************************************************************
            /*Le menu principal de notre application qui offre les options de l'application */
//****************************************************************************************
int menu (){
 	system("cls");
 	int choix;
 	printf ("-------------------------------------------------------------------------\n");
 	printf ("BIENVENUE SUR LE JEU SUDOKU  SOUHAITEZ VOUS CONTINUER?             | \n");
 	printf ("-------------------------------------------------------------------------\n");
 	printf("                                                                       ---\n");
 	printf("--------------------------------------------------------------------------\n");
 	printf ("1:  ----------A PROPOS DU JEU-------------------------------------------|\n");
 	printf("------------------------------------------------------------------------ -\n");
 	printf("                                                                          \n");
 	printf("--------------------------------------------------------------------------\n");
 	printf ("2:-----------JE SOUHAITE JOUER------------------------------------------|\n");
 	printf("--------------------------------------------------------------------------\n");
 	printf("                                                                          \n");
 	printf("--------------------------------------------------------------------------\n");
 	printf ("3:-----------GENERATEUR ET SOLVEUR DES GRILLES--------------------------|\n");
 	printf("--------------------------------------------------------------------------\n");
 	printf("                                                                          \n");
 	printf("--------------------------------------------------------------------------\n");
 	printf ("4:----------JE SUIS PAS INTERESSE---------------------------------------|\n");
 	printf("--------------------------------------------------------------------------\n");
 	printf("                                                                          \n");

 	printf ("\n----------------------VOTRE CHOIX ?----------------------------------- \n");
 	//On recupere le choix de l'utilisateur en fonction de quoi on saura quoi faire par la suite
 	scanf ("%d",&choix);
 	return choix;

 }
//****************************************************************************************
/*Permet d'effacer une valeur dans la grille en fonction de la position saisie qui est fonction
des cordonnees ligne et colonne*/
//****************************************************************************************

void effacer(){
    		int ligne,colonne;
    		printf("\n Veuillez entrer l'indice de la ligne à éffacer \n");
    		scanf ("%d",&ligne);
    		printf("\n Veuillez entrer l'indice de la colonne à éffacer \n");
    		scanf ("%d",&colonne);

    		if(test.magrille[ligne][colonne]!=0 && existePos(ligne,colonne))
                test.magrille[ligne][colonne]=0;
			else printf("\nCase deja vide ou non supprimable\n");
}
//****************************************************************************************
/*Permet d'ajouter une valeur dans la grille en fonction de la position saisie qui est
 fonction des cordonnees ligne et colonne*/
//****************************************************************************************
void ajoutValeur(){
			int ligne,colonne,k;
    		printf("\n Veuillez entrer l'indice de la ligne ou faire l'affectation \n");
    		scanf ("%d",&ligne);
    		printf("\n Veuillez entrer l'indice de la colonne ou faire l'affectation \n");
    		scanf ("%d",&colonne);
    		printf("\n Veuillez entrer la valeur a affecter \n");
    		scanf ("%d",&k);
			if(k>=0&&k<=9&&	test.magrille[ligne][colonne]==0 && !absentSurBloc(k,ligne,colonne,test.magrille) && !absentSurColonne(k,ligne,colonne,test.magrille) && !absentSurLigne(k,ligne,colonne,test.magrille))
                test.magrille[ligne][colonne]=k;
			else printf("\nValeur non valide ou case non vide veuillez reessayer\n");
}



//Ajoute une grille dans notre tableau de grille

void ajoutGrille(grille* t){
    	  tabgrille[taille]=*t;
          taille++;
}
//****************************************************************************************
            /*Un sous menu, les option du menu principale de l'interface*/
//****************************************************************************************
void afficher(){
 	system("cls");
 	int a;
 	printf("\n le principe du jeu est tres simple \n ");
 	printf("\n 1: Le but du jeu est de remplir ces cases avec des chiffres allant de 1 jusqu'a 9'\n");
 	printf("\n 2: Chaque chiffre figure une fois sur une ligne, une fois sur une colonne et une fois dans le carré \n");

 	printf("\n 3: La ligne est un ensemble de neuf cases/cellules disposées horizontalement \n");
 	printf("\n 4: La colonne est un ensemble de neuf cases disposées verticalement\n");
 	printf("\n 5: Le carré est un ensemble de neuf cases disposées en carré de 3x3 cases,la grille étant composées de neuf de ces carrés\n");
 	printf("Attention vous avez un nombre limité de tentatives faut étre tactique");
 	printf("\n Souhaitez vous jouer ?");
 	printf("\n 1:OUI \n");
 	printf("\n 2:REVENIR AU MENU PRINCIPAL \n");
 	printf("\n 3:JE SOUHAITE QUITTER        \n");
 	scanf("%d",&a);
 	switch(a){

 	case 1 : jeu();break;
 	case 2 : menu();break;
 	case 3 : return; break;
 	default : return; break;
 }

 }
//****************************************************************************************
        /*Verifie si 2 grilles sont egales*/
//****************************************************************************************
int equalsGrille(grille grille2, grille grille1){
	        int i,j;
	           for(j=0;j<9;j++){
		             for(i=0;i<9;i++){
		             	if(grille2.magrille[i][j]!=grille1.magrille[i][j]) return 0;
		}
	}
	return 1;
}
//****************************************************************************************
        /*Genere une grille a partir d'une grille existante*/
//****************************************************************************************
void generateur(grille *t,int n){
			srand(time(NULL));
			int nb=n*15,i,j,k,f=0;
			nb_iteration=nb*5;
			for(i=0;i<nb;i++){
				j=rand()%10;k=rand()%10;
				if(t->magrille[j][k]!=0) t->magrille[j][k]=0;
				else nb++;
			}
			while(!equalsGrille(tabgrille[f],*t) && f<taille) f++;
			if(f==taille) ajoutGrille(t);

}

//****************************************************************************************
            /*affiche une grille*/
//****************************************************************************************
void affichage (int grille[9][9])
{
    int ligne,colonne;
    for (ligne=0; ligne<9; ligne++)
    {
        for ( colonne=0; colonne<9; colonne++)
        {
            printf( ((colonne+1)%3) ? "%d " : "%d|", grille[ligne][colonne]);
        }
        putchar('\n');
        if (!((ligne+1)%3))
            puts("------------------");
    }
    puts("\n\n");
}
//****************************************************************************************
//le solveur, qui resout une grille qu'il prend en entree
//****************************************************************************************
int resolution( int ligne, int colonne,int grille[9][9]){
    int t_ligne = 0;
    int t_colonne = 0;
    int valeur = 1;// la valeur minimale est 1

    if(grille[ligne][colonne] != 0){
        if(ligne == 8 && colonne == 8){
                // si on se trouve au dernier case du tableau
            return 1;
        }
        // si on n'est pas a la derniere case
        if(ligne<8){
            ligne++; // tant qu'on est pas arrive a la derniere ligne
        }else{
            ligne=0; // Quand on atteint la derniere ligne on revient sur la premiere ligne
            colonne++; // et ensuite on parcour les colonnes
        }

        if(resolution(ligne,colonne,grille)){
            return 1; // si toute les valeurs des lignes et colonnes sont non nulle
        }else{
            return 0;
        }
    }

    if(grille[ligne][colonne] == 0){
        // le while parce que la valeur maximale que prendre valeur est 10
        while(valeur<10){
            // On verifie les conditions sur les lignes colonnes et bloques de 9
            if(!absentSurBloc(valeur,ligne,colonne,grille) && !absentSurLigne(valeur,ligne,colonne,grille) && !absentSurColonne(valeur,ligne,colonne,grille)){
                grille[ligne][colonne] = valeur;// si c'est verifie on ajoute le nombre
                if(ligne == 8 && colonne == 8){
                    return 1;
                }
                if(ligne<8){
                    t_ligne = ligne +1;
                }else{
                    if(colonne<8){
                        t_ligne = 0;
                        t_colonne = colonne + 1;
                    }
                }
                if(resolution(t_ligne,t_colonne,grille)){
                    return 1;
                }
            }
            valeur++;
        }
        grille[ligne][colonne] = 0;
        return 0;
    }
}
//****************************************************************************************
            /*Permutte les lignes et les colonnes d'une grille*/
//****************************************************************************************
void permutation(){
int i,j,a;
for(j=0;j<9;j++){
    for(i=j+1;i<9;i++){
        a=test.magrille[i][j];
        test.magrille[i][j]=test.magrille[j][i];
        test.magrille[j][i]=a;
    }
}



}
//****************************************************************************************
                    /*Genere des grilles différentes et leur solution respective */
//****************************************************************************************
 void differentesGrilles(){
 	int ligne=0,colonne=0;
    resolution(ligne,colonne,test.magrille);
    permutation();
    generateur(&test,2);
    affichage(test.magrille);
    resolution(ligne,colonne,test.magrille);
    affichage(test.magrille);
    permutation();
    generateur(&test,1);
    affichage(test.magrille);
    resolution(ligne,colonne,test.magrille);
    affichage(test.magrille);
    permutation();
    generateur(&test,5);
    resolution(ligne,colonne,test.magrille);
    generateur(&test,3);
    affichage(test.magrille);
    resolution(ligne,colonne,test.magrille);
    affichage(test.magrille);
    permutation();
    generateur(&test,5);
    resolution(ligne,colonne,test.magrille);
    generateur(&test,4);
    affichage(test.magrille);
    resolution(ligne,colonne,test.magrille);
    affichage(test.magrille);

 }

//*************************************************************************************
 /*Verifie si une valeur est absente sur une ligne, on fixe la colonne et on fait
 varier la ligne,elle retourne 1 si au moins une valeur se repete*/
//*************************************************************************************
int absentSurLigne (int valeur,int ligne ,int colonne,int grille[9][9])
{
	int i;
    for ( i =0; i < 9; i++){
        if (grille[i][colonne] == valeur){
            return 1;
        }
    }

    return 0;
}
//*************************************************************************************
 /*Verifie si une valeur est absente sur une colonne, on fixe la ligne et on fait
 varier la colonne,elle retourne 1 si au moins une valeur se répète*/
//*************************************************************************************
int absentSurColonne (int valeur,int ligne,int colonne, int grille[9][9])
{
int i;
    for ( i=0; i < 9; i++){
        if (grille[ligne][i] == valeur){
            return 1;
        }
    }

    return 0;
}

//****************************************************************************************
// Verifie si une valeur est absente dans un carré 3*3, on parcours les carrés en ligne
// et en colonne on retourne 1 si au moins une valeur est répétée
//****************************************************************************************
int absentSurBloc (int valeur, int ligne, int colonne, int grille[9][9])
{
    int i,j;
    if(ligne<3){
        ligne = 0;
    }else if(ligne<6){
        ligne=3;
    }else{
        ligne =6;
    }
    if(colonne<3){
        colonne=0;
    }else if(colonne<6){
        colonne=3;
    }else{
        colonne=6;
    }
    for(i=ligne;i<ligne+3;i++){
        for(j=colonne;j<colonne+3;j++){
            if(grille[i][j]==valeur){
                return 1;
            }
        }
    }
     return 0;
}
//***************************************************************************************************************************
/* La fonction qui nous permet de jouer au jeu, elle permet de générer une grille en fonction du niveau de difficulte choisit,
 d'ajouter des valeurs, supprimer des valeurs dans la grille*/
//***************************************************************************************************************************
 int jeu() {
    int ligne = 0, colonne = 0,a,b,i=0;
    resolution(ligne,colonne,test.magrille);
    printf("\n Veuillez choisir votre niveau de difficulte en entrant un nombre\n");
    printf("\n 1 : Niveau Facile \n");
    printf("\n 2 : Niveau intermediare \n");
    printf("\n 3 : Niveau difficile \n");
    scanf("%d",&a);
   	switch(a){

 	case 1 : generateur(&test,1);break;
 	case 2 : generateur(&test,2);break;
 	case 3 : generateur(&test,3); break;
 	default : generateur(&test,2); break;
 }
   system("cls");
    printf("\n La grille a resoudre est  \n");
    affichage(test.magrille);
    indicePosition();
    while(i<nb_iteration || grillePleine()==0){
    	 printf("\n 1 : jouer une valeur \n");
    	 printf("\n 2: effacer une valeur \n");
    	 scanf("%d",&b);
    	 	switch(b){

    	 case 1 : ajoutValeur();break;
 	     case 2 : effacer();break;
 	     default : ajoutValeur(); break;
        }
        i++;
    	affichage(test.magrille);
	}
	if(i==nb_iteration) {
		printf("\n nombre maximal d'iteration atteint \n");
		return;
	}
	printf("\n la grille resolue est\n");
	resolution(ligne,colonne,test.magrille);
	affichage(test.magrille);

 }

//****************************************************************************************
        /*Notre fonction principale qui permet d'appeler les autres fonctions*/
//****************************************************************************************

int main()
{
    switch(menu()){
   	case 1: afficher(); break;
   	case 2: jeu();break;
    case 3: differentesGrilles(); break;
   	case 4: return 0; break;
   	default : return 0;break;

   }


    return 0;
}
