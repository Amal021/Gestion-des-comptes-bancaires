#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


//Structure
typedef struct {
	int j , m , a ; 
}Date;
	
typedef struct {
	char nm[30] , prn[30] , ville[30] ;
	int cin ;
	Date ddn ;
}Client;

typedef struct {
	int nc , prop ;
	Date ddc ;
	char ville[40] , lo ;
	float sa , so ;
}CompteBancaire;


//Vérifier que le CIN n'existe pas dans le tableau client
bool CinExiste (Client *t, int cin, int n) {
	int i;
	for (i=0 ; i<n; i++) {
		if (cin==(t+i)->cin) {
			printf("\n CIN existant, veuillez utiliser un autre ");
			return true;
		}
	}
	return false;
}


//Ajout dun client (Remplissage et Affichage) :
void AjouterClient( Client *t , int n )
{	
	CompteBancaire *b ;
	int i, cinClient; 
	bool Existe;
	
	for (i=0 ; i<n ; i++)
	{ printf ("\nClient %d : \n",i+1);
	  
	  printf ("Nom et Prenom : ");
	  scanf ("%s%s",(t+i)->nm,(t+i)->prn);
	  
	  printf ("Ville : ");
	  scanf ("%s",(t+i)->ville);
	  
	  printf ("  Date de naissance ( JJ / MM / AAAA ): \n");
	do {	printf ("   -> Jour : ");
	  		scanf ("%d",&(t+i)->ddn.j);
	  	}while ( (t+i)->ddn.j<0 || (t+i)->ddn.j>31 );
	  		
	do {    printf ("   -> Mois : ");
	  		scanf ("%d",&(t+i)->ddn.m);
	  	}while( (t+i)->ddn.m<0 || (t+i)->ddn.m>12);

	do 	{	printf ("   -> Annee : ");
	  		scanf ("%d",&(t+i)->ddn.a);
	  }while ( (t+i)->ddn.a>2021 );
	  
	  do {	printf ("CIN : "); 
	  		scanf("%d",&cinClient);   
	  		Existe=CinExiste(t,cinClient,n);
			  if (!Existe) { 
				  (t+i)->cin=cinClient;
				  }
		} while ( Existe );
	}
	
	 printf ("\n");
}


//Vérifier si le compte bancaire existe dans la table des comptes
bool NumcompteExiste (CompteBancaire *b, int NumCompte, int n) {
	int i;
	for (i=0 ; i<n; i++) {
		if (NumCompte==(b+i)->nc) {
			return true;
		}
	}
	return false;

}


//Vérifier le cin dans la table des clients
bool cinExiste (Client *t, int cin, int n) {
	int i;
	for (i=0 ; i<n; i++) {
		if (cin==(t+i)->cin) {
			return true;
		}
	}
	return false;
}


//Vérifier le propriétaire du nouveau compte est un client et n'a pas un compte bancaire
bool Verifierclient (CompteBancaire *b, Client *t, int prop, int m, int n) {
	bool nouveauClient=false;
	bool dejaCompte=false;
	int i;
	
	for (i=0; i<n; i++) {
		if (prop==(t+i)->cin) {nouveauClient=true;}
	}
	
	if (!nouveauClient) {printf("le prop n'existe pas en tant que client, veuillez utiliser le cin d'un autre client, ");}
	
	for (i=0; i<m; i++) {
		if (prop==(b+i)->prop) 
		  { nouveauClient=false; 
		    dejaCompte=true;
		  }
	}

	if (dejaCompte) {printf("le prop possede deja un compte bancaire, veuillez utiliser le cin d'un autre client, ");}
	
	return nouveauClient;
}


//Creation dun compte :
void Creation(CompteBancaire *b , Client *t, int m, int n)
{	int i, numcompte, prop;
	bool compteExiste;
	bool nouveauClient;
	
	for ( i=0 ; i<m ; i++ )
	{ 
	do {
	  printf ("Numero de compte : ");
	  scanf("%d",&numcompte);
	  compteExiste=NumcompteExiste(b,numcompte,m);
	  if(!compteExiste){
		(b+i)->nc=numcompte;
	  } else {
		printf("\n Numero de compte existant, veuillez utiliser un autre ");
	  }
	  }while (compteExiste);
	
	printf ("  Date de creation ( JJ / MM / AAAA ): \n");
	
	do {	printf ("   -> Jour : ");
	  		scanf ("%d",&(b+i)->ddc.j);
	  	}while ( (b+i)->ddc.j<0 || (b+i)->ddc.j>31 );
	  		
	do {    printf ("   -> Mois : ");
	  		scanf ("%d",&(b+i)->ddc.m);
	  	}while( (b+i)->ddc.m<0 || (b+i)->ddc.m>12);

	do 	{	printf ("   -> Annee : ");
	  		scanf ("%d",&(b+i)->ddc.a);
	  }while ( (b+i)->ddc.a>2021 );
	  
	
	printf ("Ville de creation de compte : ");
	scanf ("%s",(b+i)->ville);
	
	do {	printf ("Proprietaire : ");
			scanf("%d",&prop);
	 		nouveauClient=Verifierclient(b,t,prop,m,n);
			if(nouveauClient){
				(b+i)->prop=prop;
			}
	  }while (!nouveauClient ); 
	
	printf ("Solde actuel : ");
	scanf ("%f",&(b+i)->sa);
	
	printf ("Ancien solde : ");
	scanf ("%f",&(b+i)->so);
	
	do{ printf ("Derniere operation ( D:Depot , V:Virement , R:Retrait ) : ");
     	scanf ("%s",&(b+i)->lo);
	}while((b+i)->lo!='V' && (b+i)->lo!='R' && (b+i)->lo!='D' );
	
	printf ("\n              **  Nouveau solde pour le compte %d  **            \n",(b+i)->nc);
	
	printf ("\n");
	}
}


//Retrait :
void Retrait (CompteBancaire *b , int n)
{	
	int i ; 
	float Rt ;
    int compteurID;
    bool existe=false;
	
	 for ( i=0 ; i<n ; i++ )
        { printf("Enterz Votre CIN: ");
    	  scanf("%d",&compteurID);
            if(compteurID==(b+i)->prop)
            {
                do{ printf("\nEntrez l'argent que vous voulez retrait : ");
                    scanf("%f",&Rt);
                  } while(Rt>(b+i)->sa);
				(b+i)->so = (b+i)->sa ;
				(b+i)->sa -= Rt ; 
				(b+i)->lo ='R';
				printf("\nNouveau solde pour le compte %d : %.3f Dh ",(b+i)->nc,(b+i)->sa); 
                existe=true; 
				break;
            }
        }
        if (!existe) {printf ("CIN non existant !\n");}
    
    printf ("\n");
}


//Depot :
void depot (CompteBancaire *b , int n )
{
	int i ; 
	int compteurID;
	float Dp ;
    bool existe=false;
    
    printf("Entrez Votre CIN : ");
    scanf("%d",&compteurID);

	for ( i=0 ; i<n ; i++ )
        {   
			if( compteurID==(b+i)->prop ) 
            { 
			do { 
				printf("\nEntrez l'argent que vous voulez deposer: ");
                scanf("%f",&Dp );
                } while ( Dp < 0 );
              (b+i)->so = (b+i)->sa ;
			  (b+i)->sa += Dp ;   
			  (b+i)->lo = 'D' ;
              printf("\nNouveau solde pour le compte %d : %.3f Dh",(b+i)->nc,(b+i)->sa);
              existe=true;
			  break; 
            }
            
        }
        if (!existe) {printf ("CIN non existant !\n");}
        
        printf ("\n");
}


//Virement entre deux comptes bancaires :
void virement(CompteBancaire *b, int ncexpditeur , int ncdestinataire , float value, int n) 
{
	bool expediteurcompteExiste   = NumcompteExiste(b,ncexpditeur,n);
	bool destinatairecompteExiste = NumcompteExiste(b,ncexpditeur,n);
	int i;
	
	if (expediteurcompteExiste && destinatairecompteExiste) {
	for (i=0; i<n; i++) {
		if (ncexpditeur==(b+i)->nc && (b+i)->sa>value) {
			(b+i)->so=(b+i)->sa;
			(b+i)->sa-=value;
			(b+i)->lo='V';
		} 
		else if (ncexpditeur==(b+i)->nc && (b+i)->sa<value) {
			printf("\n Attention le compte %d n'as pas suffisament d'argent !\n",ncexpditeur);
		}
	}
		for (i=0; i<n; i++) {
		if (ncdestinataire==(b+i)->nc) {
			(b+i)->so=(b+i)->sa;
			(b+i)->sa+=value;
			(b+i)->lo='V';
		}
	}
	printf("\n Virement de valeur %.3f reussi entre le compte %d et le compte %d.\n",value,ncexpditeur,ncdestinataire);
	} else {
	printf("\n Veuillez utiliser des comptes existants !\n");
	}
}


//Detail dun compte :
void DetailCompte(CompteBancaire *b , int n )
{
    int compteurID , i ; 
	bool existe=false;
	
    printf(" Chercher un compte par CIN:  ");
    scanf("%d",&compteurID); //Proprietaire
    
    for ( i=0 ; i<n ; i++ ) {
    if ( compteurID == (b+i)->prop ) //proprietaire existant 
            {
                printf("\n\n Voila votre information : \n");
                printf("\nNumero de Compte      : %d",(b+i)->nc);
        		printf("\nCIN                   : %d",(b+i)->prop);
        		printf("\nSolde de Compte       : %.3fDh",(b+i)->sa);
        		printf("\nVille de creation     : %s",(b+i)->ville);
        		printf("\nDate de creation      : %d/%d/%d",(b+i)->ddc.j,(b+i)->ddc.m,(b+i)->ddc.a);
				printf("\nDerniere operation    : %c",(b+i)->lo);
                existe=true;
            }
    }
    if(!existe) {printf("\n CIN n'existe pas.\n");} //proprietaire non existant
}


//Liste des comptes :
void listeCompte(CompteBancaire *b , int n)
 {
    int i;
     
    for ( i=0 ; i<n ; i++ )
    {	 printf("\n- Compte %d : \n",i+1);
         printf("\n   Numero de Compte   : %d",(b+i)->nc);
         printf("\n   CIN                : %d",(b+i)->prop);
         printf("\n   Ville de creation  : %s",(b+i)->ville);
         printf("\n   Date de creation   : %d/%d/%d",(b+i)->ddc.j,(b+i)->ddc.m,(b+i)->ddc.a);
         printf("\n   Solde de Compte    : %.3f Dh",(b+i)->sa);
         printf("\n   Derniere Operation : %c  \n",(b+i)->lo);
    }
    printf ("\n");
}
 

//Detail dun client :
void DetailClient(Client *t , int n )
{
    int compteurID , i ; 
	bool existe=false;
    
	printf(" Chercher un compte par CIN :  ");
    scanf("%d",&compteurID); //CIN 
    
	for ( i=0 ; i<n ; i++ ) {
    if ( compteurID == (t+i)->cin ) //CIN existant
            {
                printf("\n\n Voila votre information : \n");
                printf("\nNom et Prenom        : %s %s",(t+i)->nm,(t+i)->prn);
        		printf("\nCIN                  : %d",(t+i)->cin);
        		printf("\nVille                : %s",(t+i)->ville);
        		printf("\nDate de naissance    : %d/%d/%d\n",(t+i)->ddn.j,(t+i)->ddn.m,(t+i)->ddn.a);
                existe=true;
            }
    }
    if(!existe) {printf("\n CIN n'existe pas.\n");} //proprietaire non existant
    printf ("\n");
}


//Liste des clients :
void listeClient(Client *t , int n)
 {
    int i ;
    for ( i=0 ; i<n ; i++ )
    {	 printf("\n- Client %d : \n",i+1);
         printf("\n   Nom et Prenom      : %s %s",(t+i)->nm,(t+i)->prn);
         printf("\n   Ville              : %s",(t+i)->ville);
         printf("\n   CIN                : %d",(t+i)->cin);
         printf("\n   Date de naissance  : %d/%d/%d \n",(t+i)->ddn.j,(t+i)->ddn.m,(t+i)->ddn.a);
    }
    printf ("\n");
 }


//Supprimer un compte :
int cloturerCompte (CompteBancaire *b, int nc, int n) {
	bool compteExiste = NumcompteExiste(b,nc,n) ;
	int i , j ;
	if (compteExiste) {
		for (i=0; i<n; i++) {
			if (nc==(b+i)->nc) {
				for(j=i;j<n-1;j++){
					*(b+j)=*(b+j+1);
				}
				n--;
				break;
 			}
		}
	} else {
		printf("\n ce compte n'existe pas");
	}
	return n;
}

//Supprimer un client :
int supprimerClient(Client *t, CompteBancaire *b,int cin, int n) {
	int i,j,p;
	bool cinExist=cinExiste(t,cin,n);
	
	if (cinExist) {
		for (i=0; i<n; i++) {
			if (cin==(t+i)->cin) {
				p=cloturerCompte(b,(b+i)->nc,n);
				for(j=i;j<n-1;j++){
					*(t+j)=*(t+j+1);
				}
				n--;
				b=(CompteBancaire*)realloc(b,p*sizeof(CompteBancaire));
				break;
 			}
		}
	}
	return n;
}


int main ()
{
	int choix , n, m;
	int ncexpditeur, ncdestinataire ; //Pour virement ( case 5 )
	int nc,newSize,cinClient; //Pour cloturer compte et supprimer clien( case 11 , 10)
	float valeur; 
	bool w=true ; //Booleen
	Client *t ;
	CompteBancaire *b ;
		
		
	//Allocations :
		t=(Client*)malloc(n*sizeof(Client));
		b=(CompteBancaire*)malloc(n*sizeof(CompteBancaire));
		
		
	//MENU :
		system("color 80");
		printf("\t\n_________________________________________________________________________________________\n");
        printf("|** ** ** ** ** ** ** ** ** ** ** ** **  Bienvenue ** ** ** ** ** ** ** ** ** ** ** ** **|");
		printf("\t\n|  -> 1. Ajouter un Client.                                                              |");
        printf("\t\n|  -> 2. Creation Compte.                                                                |");
		printf("\t\n|  -> 3. Retrait.                                                                        |");
        printf("\t\n|  -> 4. Depot.                                                                          |");
        printf("\t\n|  -> 5. Virement.                                                                       |");
        printf("\t\n|  -> 6. Detail d'un Client.                                                             |");
        printf("\t\n|  -> 7. Liste de Clients.                                                               |");
        printf("\t\n|  -> 8. Detail d'un Compte.                                                             |");
		printf("\t\n|  -> 9. Liste de Comptes.                                                               |");
		printf("\t\n|  -> 10. Supprimer un Client.                                                           |");
        printf("\t\n|  -> 11. Cloturer un Compte.                                                            |");
		printf("\t\n|  -> 12. Quitter l'application.                                                         |");
        printf("\n|________________________________________________________________________________________|\n");
        
    //Choix :
	do { 
		do
        { printf("\n Choisissez une Operation : ");
          scanf("%d",&choix);
        } while(choix>12 || choix<0);
        
        switch(choix)
        {
        case 1 :	
        	printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Ajout De Client                     ");
        	printf ("\n---------------------------------------------------------\n");
			printf ("Donner le nombre de client a ajouter : ");
			scanf ("%d",&n);
			AjouterClient(t,n);
            break;
            
		case 2:
			printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Ajout De Compte                     ");
        	printf ("\n---------------------------------------------------------\n");
			printf ("Donner le nombre de compte a ajouter : ");
			scanf ("%d",&m);
            Creation(b,t,m,n); break;
        case 3 :
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                         Retrait                         ");
        	printf ("\n---------------------------------------------------------\n");
		    Retrait(b,m); 
			break;
			
        case 4 :
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                          Depot                          ");
        	printf ("\n---------------------------------------------------------\n");
			depot(b,m);   
			break;
            
        case 5 :
			printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                        Virement                         ");
        	printf ("\n---------------------------------------------------------\n");
			printf ("Donner le numero de compte de client: ");
			scanf ("%d",&ncexpditeur);
			printf ("Donner le numero de compte de destinataire: ");
			scanf ("%d",&ncdestinataire);
			printf ("Remplir la valeur a envoyer: ");
			scanf ("%f",&valeur);
            virement(b,ncexpditeur,ncdestinataire,valeur,m);  
			break;
            
        case 6 :
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Detail Client                       ");
        	printf ("\n---------------------------------------------------------\n");
			DetailClient(t,n); 
			break;
            
        case 7 :
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Liste Clients                       ");
        	printf ("\n---------------------------------------------------------\n");
			listeClient(t,n); 
			break;
            
        case 8 : 
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Detail Compte                       ");
        	printf ("\n---------------------------------------------------------\n");
			DetailCompte(b,m); 
			break;
            
        case 9 : 
            printf ("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
			printf ("\n                     Liste Comptes                       ");
        	printf ("\n---------------------------------------------------------\n");
			listeCompte(b,m); 
			break;
            
        case 10 :
            printf ("Donner le cin du client: ");
			scanf ("%d",&cinClient);
			n=supprimerClient(t,b,cinClient,n);
			t=(Client*)realloc(t,n*sizeof(Client));
			break;
            
        case 11 :
			printf ("Donner le numero de compte de client: ");
			scanf ("%d",&nc);
            m=cloturerCompte(b,nc,m);
			b=(CompteBancaire*)realloc(b,m*sizeof(CompteBancaire));
			break;
			
        case 12 :
            printf ("\n---------------------------------------------------------\n");
			printf ("                     Fin du programme...               ");
        	printf ("\n---------------------------------------------------------\n");
            exit(0); break;
        }
	}while( w!=false );	
    
    getch();    
}