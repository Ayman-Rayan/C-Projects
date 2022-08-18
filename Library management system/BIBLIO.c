// Ayman Rayan Kissami
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct livre{
	char titre[30] ;
	char auteur[30] ;
	int page ;
}livre;

typedef struct adherent{
	char nom[30] ;
	int num ;
	int nb ;
	livre L[3] ;
}adherent;


typedef struct biblio{
	adherent A[20] ;
	int cpt ;
}biblio;


adherent creer_adherent(){
	adherent a ;
	printf("Saisir le nom : ") ;
	scanf("%s",a.nom) ;
	printf("Saisir le numero : ") ;
	scanf("%d",&a.num) ;
	a.nb = 0 ;
	return a ;
}

void ajouter_adherent(biblio *B, int N){
	int i ;
	if(N+B->cpt <= 20 ){
		for(i=B->cpt;i<N+B->cpt;i++){
			printf("Remplir %d adherent : \n",i+1) ;
			B->A[i] = creer_adherent() ;
		}
		B->cpt += N ;
	}
	else 
		printf("La taille n'est pas suffisante \n") ;

}


int recherche_num(biblio B,int num){
	int i , pos = -1 ;
	for(i=0;i<B.cpt;i++){
		if(B.A[i].num == num)
			pos = i ;
	}
	return pos ;
}

livre creer_livre(){
	livre l ;
	printf("Saisir le titre : ") ;
	scanf("%s",l.titre) ;
	printf("Saisir le nom de l'auteur : ") ;
	scanf("%s",l.auteur) ;
	printf("Saisir nombre des pages : ") ;
	scanf("%d",&l.page) ;
	return l ;
}

void ajouter_livre(biblio *B , int num){
	int j , i = recherche_num(*B,num) ;
	if( i != -1){
		j = B->A[i].nb ;
		if(j < 3){
			printf("Remplir %d livre : ",j+1) ;
			B->A[i].L[j] = creer_livre() ;
			B->A[i].nb++ ;
		}
		else
			printf("La taille n'est pas suffisante\n") ;	
	}
	else
		printf("Aucun numero correspondant\n") ;
}


void afficher_livre(livre l){
	printf("Le titre : %s,  ",l.titre) ;
	printf("L'auteur : %s,  ",l.auteur) ;
	printf("Nombre des pages %d\n",l.page) ;
}

void afficher_adherent(adherent a){
	int i ;
	printf("Le nom : %s \n",a.nom);
	printf("Le numero : %d\n",a.num) ;
	printf("Les livres : \n") ;
	for(i=0;i<a.nb;i++){
		afficher_livre(a.L[i]) ;
	}
}

void afficher_biblio(biblio B){
	int i ;
	printf("les adherents : \n") ; 
	for(i=0;i<B.cpt;i++){
		afficher_adherent(B.A[i]) ;
		printf("\n") ;
	}
}


int recherche_nom(biblio B , char nom[]){
	int i , pos = -1 ;
	for(i=0;i<B.cpt;i++){
		if(strcmp(B.A[i].nom,nom)==0)
			pos = i ;
	}
	return pos ;
}

void affiche_info(biblio B,char nom[]){
	int i = recherche_nom(B,nom) ;
	if(i != -1){
		afficher_adherent(B.A[i]) ;
	}
	else
		printf("Aucun nom correspondant \n") ;
}


int recherche_titre(adherent a ,char titre[]){
	int i , pos = -1 ;
	for(i=0;i<a.nb;i++){
		if(strcmp(a.L[i].titre,titre)==0)
			pos = i ;
	}
	return pos ;
}

void retourner(biblio *B,int num , char titre[]){
	int j , i = recherche_num(*B,num) ;
	if( i != -1){
		j = recherche_titre(B->A[i],titre) ;
		if( j != -1){
			j = B->A[i].nb-- ;
			for(;j<B->A[i].nb;j++){
				B->A[i].L[j] = B->A[i].L[j+1] ;
			}
		}
		else
			printf("Aucun titre correspondant \n") ;
	}
	else
		printf("Aucun numero correspondant \n") ;
}


void exporter(biblio B){
	int i , j ;
	FILE *f ;
	f = fopen("Exam.txt","w") ;
	if( f != NULL){
		for(i=0;i<B.cpt;i++){
			fprintf(f,"%s %d %d \n",B.A[i].nom,B.A[i].num,B.A[i].nb) ;
			for(j=0;j<B.A[i].nb;j++){
				fprintf(f,"%s %s %d \n",B.A[i].L[j].titre,B.A[i].L[j].auteur,B.A[i].L[j].page) ;
			}
		}
		fclose(f) ;
	}
	else 
		printf("Erreur d'exporter \n") ;
}


void importer(biblio *B){
	int i=0 , j ;
	FILE *f ;
	f = fopen("Exam.txt","r") ;
	if (f != NULL){
		while( !feof(f)){
			fscanf(f,"%s %d %d \n",B->A[i].nom,&B->A[i].num,&B->A[i].nb) ;
			for(j=0;j<B->A[i].nb;j++){
				fscanf(f,"%s %s %d \n",B->A[i].L[j].titre,B->A[i].L[j].auteur,&B->A[i].L[j].page) ;
			}
			i++ ;
		}
		B->cpt = i ;
		fclose(f) ;
	}
	else
		printf("Erreur d'importer \n") ;
}


int menu(){
	int n ;
	do{
		printf("1 : Pour ajouter N adherents \n") ;
		printf("2 : Pour Emprunter un livre \n") ;
		printf("3 : Pour afficher la liste \n") ;
		printf("4 : Pour afficher les information d'un adherent \n") ;
		printf("5 : Pour Retourner un livre \n") ;
		printf("6 : Pour Exporter \n") ;
		printf("7 : Pour Importer \n") ;
		printf("8 : Pour quitter \n") ;
		printf("Votre choix : ") ;
		scanf("%d",&n) ;
	}while(n<1 || n>8 );
	return n ;
}



int main(){
	biblio B ;
	B.cpt = 0 ;
	char ch[30] ;
	int n , N ;
	do{
		n = menu();
		switch(n){
			case 1 : printf("Saisir nombre des adherents : ") ;
					 scanf("%d",&N) ;
					 ajouter_adherent(&B,N) ;
					 break ;
			case 2 : printf("Saisir le numero d'adherent : ") ;
					 scanf("%d",&N) ;
					 ajouter_livre(&B,N) ;
					 break ;
			case 3 : afficher_biblio(B) ;
					 break ;
			case 4 : printf("Saisir le nom d'adherent : ") ;
					 scanf("%s",ch) ;
					 affiche_info(B,ch) ;
					 break ;
			case 5 : printf("Saisir le numero d'aherent : ") ;
					 scanf("%d",&N) ;
					 printf("Saisir le titre de livre : ") ;
					 scanf("%s",&ch) ;
					 retourner(&B,N,ch) ;
					 break ;
			case 6 : exporter(B) ;
					 break ;
			case 7 : importer(&B) ;
					 break ;
			case 8 : printf("you exited the program :) ") ;
		}
	}while( n != 8) ;
}




