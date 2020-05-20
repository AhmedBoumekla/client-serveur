
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#define SA struct sockaddr

#define PORT 8080
#define MAX 2048


void fonction(int sockfd){
	
	char addr[MAX], texte[MAX], readbuf[MAX], buf[MAX];
	int n;
	while(1){
		bzero(addr, MAX);
		bzero(texte, MAX);
		bzero(readbuf, MAX);
		printf("Choisir l'action à executer : \n");
		n = 0;
		while((readbuf[n++] = getchar()) != '\n') ;
		write(sockfd,readbuf,sizeof(buf));
		bzero(buf, MAX);
		read(sockfd,buf,sizeof(buf));
		if ((strncmp(buf, "recu",4)) == 0){
		
			if ((strncmp(readbuf, "AJOUT",5)) == 0){
				
				bzero(readbuf, MAX);
				printf("donner l'addresse : ");
				n = 0;
				while((addr[n++] = getchar()) != '\n') ;
				printf("écrire votre annonce  : ");
				n = 0;
				while((texte[n++] = getchar()) != '\n') ;
				printf("%s\n%s\n",addr,texte);
				write(sockfd, addr, sizeof(addr));
				read(sockfd, readbuf, sizeof(readbuf));
				if ((strncmp(readbuf, "recu",4)) == 0){
					bzero(readbuf, MAX);
					write(sockfd, texte, sizeof(texte));
				}
				else{ break;}	
			
			}
			if ((strncmp(readbuf, "LISTER",6)) == 0){
				printf("2222222\n");
				write(sockfd, readbuf, sizeof(readbuf));
				bzero(readbuf, MAX);
				read(sockfd, readbuf, sizeof(readbuf));
				printf(" %s \n", readbuf);
			}
			if ((strncmp(readbuf, "SUPPRIMER",9)) == 0){
			
				bzero(readbuf, MAX);
				printf("donner l'addresse : ");
				n = 0;
				while((addr[n++] = getchar()) != '\n') ;
				printf("écrire votre annonce  : ");
				n = 0;
				while((texte[n++] = getchar()) != '\n') ;
				write(sockfd, addr, sizeof(addr));
				read(sockfd, readbuf, sizeof(readbuf));
				if ((strncmp(readbuf, "recu",4)) == 0){
					bzero(readbuf, MAX);
					write(sockfd, texte, sizeof(texte));
				}
				else{ break;}
			}
		}
		else break;
	}
}
		
		
		
int main(){
	
	int sock, conn;
	
	struct sockaddr_in serv, client;
	if((sock = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("erreur d'ouverture de socket ");
		exit(0);
	}
	bzero(&serv,sizeof(serv));
	
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(PORT);
		
 	if (connect(sock,(SA*)&serv, sizeof(serv)) != 0) { 
        printf("connexion échoué \n"); 
        exit(0); 
    } 
	
	fonction(sock);
	
	close(sock);
	
	return 0;
}		
	
	
	
	

		
		
		
