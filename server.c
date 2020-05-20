
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
//#include "code.h"

#define SA struct sockaddr

#define PORT 8080
#define MAX 2048

struct Annonce {
	char *adresse;
	char *texte;
	struct Annonce *suivant;
};
typedef struct Annonce Annonce_t;

Annonce_t *liste_annonces;
int ajout(char *adresse, char *texte);
int suppression(Annonce_t *annonce);
char *lister();
size_t longueur();

void fonction(int sockfd){
	char buff[MAX] , buffw[MAX],stocka[MAX],stock[MAX];
	int n =0;
	
	while(1){
		printf("11111111\n");
		bzero(buff, MAX);
		read(sockfd, buff, sizeof(buff));
		printf("%s\n",buff);
		write(sockfd,"recu",sizeof("recu"));
		if ((strncmp(buff, "AJOUT",5)) == 0){
			printf("22222222");
			bzero(buff, MAX);
			read(sockfd,stocka, sizeof(stocka));
			write(sockfd,"recu",sizeof("recu"));
			read(sockfd,stock, sizeof(stock));
			bzero(buff, MAX);
			printf("%s\t%s\n",stocka,stock);

			if((ajout(stocka,stock)) == -1){
				perror("erruer ajout ");
			}
			bzero(stocka, MAX);
			strcpy(stocka,lister());
			bzero(stock, MAX);
		
		}
		if ((strncmp(buff, "LISTER",6)) == 0){
			printf("33333333\n");
			bzero(buff, MAX);
			strcpy(buff,"bonjour depuis le serveur action LISTER\n");
			//printf("%s\n",buff);
			write(sockfd, buff,sizeof(buff));
		
		}
		if ((strncmp(buff, "SUPPRIMER",9)) == 0){
			Annonce_t *ann = malloc(sizeof(Annonce_t));
			ann->adresse = malloc(MAX*sizeof(char));
			ann->adresse = malloc(MAX*sizeof(char));
			bzero(buff, MAX);
			read(sockfd,stocka, sizeof(stocka));
			write(sockfd,"recu",sizeof("recu"));
			read(sockfd,stock, sizeof(stock));
			bzero(buff, MAX);
			strcpy(ann->adresse,stocka);
			strcpy(ann->texte,stock);
			int n = 0 ;//suppression(ann);
			if(n == 0){
				write(sockfd,"supprimer",sizeof("supprimer"));
			}
			if(n == -1){
				write(sockfd,"erreur_sup",sizeof("erreur_sup"));
			}
			if(n == -2){
				write(sockfd,"annonce_inexistante",sizeof("annonce_inexistante"));
			}
			
		}
	}
}	

int main(){
	int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        perror("creation de socket échoué"); 
        exit(0); 
    } 
    bzero(&servaddr, sizeof(servaddr)); 
  
    
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        perror("echec du bind"); 
        exit(0); 
    } 
  
    
    if ((listen(sockfd, 5)) != 0) { 
        perror("echec du listen"); 
        exit(0); 
    } 
     
    len = sizeof(cli); 
  
 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        perror("echec de connexion au serveur"); 
        exit(0); 
    }

    fonction(connfd); 
  
    
    close(sockfd); 
} 

int ajout(char *adresse, char *texte) {
	Annonce_t *annonce;
	if ((annonce = (Annonce_t *) malloc (sizeof(Annonce_t))) == NULL) return -1;
	annonce->adresse = adresse;
	annonce->texte = texte;
	annonce->suivant = liste_annonces;
	liste_annonces = annonce;
	return 0;
}

/*int suppression(Annonce_t *annonce) {
	if (annonce == NULL) return -1;
	if (liste_annonces == NULL) return -2;
	Annonce_t *tmp = liste_annonces;
	Annonce_t *tmp_pred;
	if (strcmp(tmp->adresse,annonce->adresse) == 0 && strcmp(tmp->texte,annonce->texte) == 0) {
		liste_annonces = liste_annonces->suivant;
		return 0;
	}
	tmp_pred = tmp;
	tmp = tmp->suivant;
	while (tmp != NULL) {
		if (strcmp(tmp->adresse,annonce->adresse) == 0 && strcmp(tmp->texte,annonce->texte) == 0) {
			tmp_pred->suivant = tmp->suivant;
			return 0;
		}
		tmp_pred = tmp;
		tmp = tmp->suivant;
	}
	return -2;
}
*/
char *lister() {
	char *s;
	Annonce_t *tmp = liste_annonces;
	if ((s = (char *) malloc (longueur() * sizeof(char) + 1)) == NULL) return NULL;
	while (tmp != NULL) {
		strcat(s,tmp->adresse);
		strcat(s,"\t");
		strcat(s,tmp->texte);
		strcat(s,"\n");
		tmp = tmp->suivant;
	}
	return s;
}

size_t longueur() {
	size_t l = 0;
	Annonce_t *tmp = liste_annonces;
	while (tmp != NULL) {
		l += strlen(tmp->adresse) + 1 + strlen(tmp->texte) + 1;
		tmp = tmp->suivant;
	}
	return l;
}

		
		
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	
		
