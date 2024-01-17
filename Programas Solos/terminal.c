#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>
#include <string.h>

#define qtdAlt 3

int main() {
    setlocale(LC_ALL, "Portuguese");
    
	char musica[50],artistas[50];
    
    //ARMAZENANDO A BD EM VARIÁVEIS---------------------------------------------------------------------------------------------------------------------
    
    FILE *arqCad = fopen("BancoDeDados.csv", "r");
    

	if (arqCad == NULL) {
	 	printf("Erro ao abrir o arquivo de perguntas.\n");
	 	return 1;
	}
	
	//Contagem de linhas--
	
	int cont_lin = 0;
    char lin_TAM[1000];

    while (fgets(lin_TAM, sizeof(lin_TAM), arqCad) != NULL) {
        cont_lin++;
    }
    
    // Reinicialização da leitura--
    
    fseek(arqCad, 0, SEEK_SET);
	
	//Armazenamento--
	int i;
 	
	char nome [5][100],datanasc[cont_lin][100],cpf[cont_lin][15],email[cont_lin][100],senha[cont_lin][100],
	 	 artista1[cont_lin][50],artista2[cont_lin][50],artista3[cont_lin][50],artista4[cont_lin][50],artista5[cont_lin][50],
		 totalart[cont_lin][50],modpag[cont_lin][50],metpag[cont_lin][50],ticket[cont_lin][11],situacao[cont_lin][16];
 	
 	for (i=0;i<cont_lin;i++){
 		fscanf(arqCad,"%99[^;];%99[^;];%14[^;];%99[^;];%99[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%49[^;];%10[^;];%15[^\n]",
		 			   nome[i],datanasc[i],cpf[i],email[i],senha[i],artista1[i],artista2[i],artista3[i],
					   artista4[i],artista5[i],totalart[i],modpag[i],metpag[i],ticket[i],situacao[i]);
	}

	fclose(arqCad);
	
	//ARMAZENANDO AS MUSICAS EM VARIÁVEIS---------------------------------------------------------------------------------------------------------------------
	
	FILE *arqMusE = fopen("Artistas/Ernesto Nazareth/musErnestoNazareth.csv", "r");
	FILE *arqMusD = fopen("Artistas/Dilermando Reis/musDilermandoReis.csv", "r");
	FILE *arqMusH = fopen("Artistas/Heitor Villa-Lobos/musHeitorVillaLobos.csv", "r");
	FILE *arqMusC = fopen("Artistas/Caetano Veloso/musCaetanoVeloso.csv", "r");
	FILE *arqMusT = fopen("Artistas/Tom Jobim/musTomJobim.csv", "r");
	
	if (arqMusE==NULL){
    		printf("Erro ao abrir o arquivo de Ernesto Nazareth.\n");
	 		return 1;
		}
	if (arqMusD==NULL){
    		printf("Erro ao abrir o arquivo de Dilermando Reis.\n");
	 		return 1;
		}
	if (arqMusH==NULL){
    		printf("Erro ao abrir o arquivo de Heitor Villa-Lobos.\n");
	 		return 1;
		}
	if (arqMusC==NULL){
    		printf("Erro ao abrir o arquivo de Caetano Veloso.\n");
	 		return 1;
		}
	if (arqMusT==NULL){
    		printf("Erro ao abrir o arquivo de Tom Jobim.\n");
	 		return 1;
		}
	
	char musE[3][100];
	char musD[3][100];
	char musH[3][100];
	char musC[3][100];
	char musT[3][100];
	
	fscanf(arqMusE,"%99[^;];%99[^;];%99[^\n]",musE[0],musE[1],musE[2]);
	fscanf(arqMusD,"%99[^;];%99[^;];%99[^\n]",musD[0],musD[1],musD[2]);
	fscanf(arqMusH,"%99[^;];%99[^;];%99[^\n]",musH[0],musH[1],musH[2]);
	fscanf(arqMusC,"%99[^;];%99[^;];%99[^\n]",musC[0],musC[1],musC[2]);
	fscanf(arqMusT,"%99[^;];%99[^;];%99[^\n]",musT[0],musT[1],musT[2]);
	
	fclose(arqMusE);
	fclose(arqMusD);
	fclose(arqMusH);
	fclose(arqMusC);
	fclose(arqMusT);
	
	
	//INSERÇÃO DE TICKET-------------------------------------------------------------------------------------------------------------------------------
	
    int linhauser;

    while (1) {
    	char ticketuser[20];
    	
        printf("Insira seu ticket: ");
        scanf("%s", ticketuser);

        int length = strlen(ticketuser);

        if (length >= 5) {
        	
        	//Retirando linha do ticket--
        	
            char confline[20];
            strcpy(confline, ticketuser + 4);
            linhauser = atoi(confline);
            
            //Verificando se o ticket pode ser utilizado--
            
            if(strcmp(ticketuser,ticket[linhauser])==0){
            	if(strcmp(situacao[linhauser],"1")==0){
					system("cls");
					printf("Ticket já foi utilizado.\n");
					continue;
				}
            	system("cls");
            	break;
			}	
			else {
				system("cls");
				printf("Ticket incorreto.\n");	
			}
        } else {
            system("cls");
            printf("Ticket incorreto.\n");
        }
    }
   
   	//INSERÇÃO DE SENHA-------------------------------------------------------------------------------------------------------------------------------
    
    while (1) {
    	char senhauser[100];
		printf("Insira sua senha: ");
        scanf("%s",senhauser);
        
        //Verificando se a senha está correta--
        
        if(strcmp(senhauser,senha[linhauser])==0){
        	system("cls");
        	break;
		}	
		else {
			system("cls");
			printf("Senha incorreta.\n");
		}
    }
    
    //IMPEDIR NOVOS ACESSOS COM O MESMO TICKET-------------------------------------------------------------------------------------------------------------------------------
    
    FILE *cadastro = fopen("BancoDeDados.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    
    if (cadastro == NULL || temp == NULL) {
        perror("Erro ao abrir os arquivos.");
        return 1;
    }

    int linha_alterar = linhauser+1; 
    int coluna_alterar = 15; 

    int linha = 1;
    char linha_atual[10000];

    while (fgets(linha_atual, sizeof(linha_atual), cadastro) != NULL) {
        if (linha == linha_alterar) {
            char *token = strtok(linha_atual, ";");
            int coluna = 1;

            while (token != NULL) {
                if (coluna == coluna_alterar) {
                    // Substituir o valor na posição desejada
                    fprintf(temp, "1");
                } else {
                    // Escrever o valor original
                    fprintf(temp, "%s;", token);
                }

                token = strtok(NULL, ";");
                coluna++;
            }

            fprintf(temp, "\n");
        } else {
            // Se não estiver na linha a ser alterada, copiar a linha original
            fprintf(temp, "%s", linha_atual);
        }

        linha++;
    }

    fclose(cadastro);
    fclose(temp);

    // Remover o arquivo original
    remove("BancoDeDados.csv");

    // Renomear o arquivo temporário para o nome original
    rename("temp.csv", "BancoDeDados.csv");
    
    
    while (1){
		
    	printf("Escolha um artista: \n\n");
		
		if(strcmp(artista1[linhauser],"1")==0)printf("Setor 1. %s\n",artista1[0]);
		if(strcmp(artista2[linhauser],"1")==0)printf("Setor 2. %s\n",artista2[0]);
		if(strcmp(artista3[linhauser],"1")==0)printf("Setor 3. %s\n",artista3[0]);
		if(strcmp(artista4[linhauser],"1")==0)printf("Setor 4. %s\n",artista4[0]);
		if(strcmp(artista5[linhauser],"1")==0)printf("Setor 5. %s\n",artista5[0]);
		printf("\nDigite o setor que deseja visitar, ou ""S"" para sair:\n");
		
		char opcao;
		int opcaomusica;
		
		printf("\n= ");
    	scanf(" %c",&opcao);
    	
    	if(opcao=='s'||opcao =='S'){
    		char opend;
    		system("cls");
    		printf("Ao optar por sair, não será possível entrar na exposição novamente. Deseja realmente sair?\n\n");
    		printf("1. Sim\n2. Não\n\n= ");
    		scanf(" %c",&opcao);
    		if(opcao=='1') return 0;
    		else {system("cls");continue;}
		}
		
		
    	
    	system("cls");	
    	

    	
    	while(1){
    		printf("Escolha uma música: \n\n");
    		
    		if (opcao == '1') {
    			strcpy(artistas,artista1[0]);	
				for (i=0;i<3;i++){
					printf("%d. %s\n",i+1,musE[i]);
				}
				printf("4. Voltar\n\n= ");
				scanf("%d",&opcaomusica);
				if(opcaomusica <1 || opcaomusica > 4){
					system("cls");
					printf("Selecione uma opção válida.\n\n");
				}
				if (opcaomusica == 1) strcpy (musica,"ApanheiTeCavaquinho");
	    		if (opcaomusica == 2) strcpy (musica,"Brejero");
	    		if (opcaomusica == 3) strcpy (musica,"Odeon");
	    		if (opcaomusica==4) break;
	    	}
    		if (opcao == '2') {
    			strcpy(artistas,artista2[0]);	
				for (i=0;i<3;i++){
					printf("%d. %s\n",i+1,musD[i]);
				}
				printf("4. Voltar\n\n= ");
				scanf("%d",&opcaomusica);
				if(opcaomusica <1 || opcaomusica > 4){
					system("cls");
					printf("Selecione uma opção válida.\n\n");
				}
				if (opcaomusica == 1) strcpy (musica,"AbismoDeRosas");
	    		if (opcaomusica == 2) strcpy (musica,"NoiteDeLua");
	    		if (opcaomusica == 3) strcpy (musica,"SeElaPerguntar");
	    		if (opcaomusica==4) break;
	    	}
    		if (opcao == '3') {
    			strcpy(artistas,artista3[0]);	
				for (i=0;i<3;i++){
					printf("%d. %s\n",i+1,musH[i]);
				}
				printf("4. Voltar\n\n= ");
				scanf("%d",&opcaomusica);
				if(opcaomusica <1 || opcaomusica > 4){
					system("cls");
					printf("Selecione uma opção válida.\n\n");
				}
				if (opcaomusica == 1) strcpy (musica,"ChoroN1");
	    		if (opcaomusica == 2) strcpy (musica,"EstudoN1");
	    		if (opcaomusica == 3) strcpy (musica,"PreludioN1");
	    		if (opcaomusica==4) break;
	    	}
    		if (opcao == '4') {
    			strcpy(artistas,artista4[0]);	
				for (i=0;i<3;i++){
					printf("%d. %s\n",i+1,musC[i]);
				}
				printf("4. Voltar\n\n= ");
				scanf("%d",&opcaomusica);
				if(opcaomusica <1 || opcaomusica > 4){
					system("cls");
					printf("Selecione uma opção válida.\n\n");
				}
				if (opcaomusica == 1) strcpy (musica,"AlegriaAlegria");
	    		if (opcaomusica == 2) strcpy (musica,"CoraçãoVagabundo");
	    		if (opcaomusica == 3) strcpy (musica,"DesdeSamba");
	    		if (opcaomusica==4) break;
	    	}
	    	if (opcao == '5') {
    			strcpy(artistas,artista5[0]);	
				for (i=0;i<3;i++){
					printf("%d. %s\n",i+1,musT[i]);
				}
				printf("4. Voltar\n\n= ");
				scanf("%d",&opcaomusica);
				if(opcaomusica <1 || opcaomusica > 4){
					system("cls");
					printf("Selecione uma opção válida.\n\n");
				}
				if (opcaomusica == 1) strcpy (musica,"EuSeiQueVouTeAmar");
	    		if (opcaomusica == 2) strcpy (musica,"GarotadeIpanema");
	    		if (opcaomusica == 3) strcpy (musica,"Wave");
	    		if (opcaomusica==4) break;
	    	}
    		char perg[500],resp[500];

			strcpy(perg, "Artistas/");
			strcat(perg,artistas);
			strcat(perg,"/");
			strcat(perg,musica);
			strcat(perg,"/perg");
			strcat(perg,musica);
			strcat(perg,".csv");
			
			strcpy(resp, "Artistas/");
			strcat(resp,artistas);
			strcat(resp,"/");
			strcat(resp,musica);
			strcat(resp, "/resp");
			strcat(resp,musica);
			strcat(resp,".csv");
			
			printf("%s",perg);
			system("pause");
			
			int opcaoart[3];
			char id[4][100],pergunta[4][10000],alt1[4][100],alt2[4][100],sobre1[4][1000],sobre2[4][1000];
			
			FILE *arqPerg = fopen(perg, "r");
			
			 if (arqPerg == NULL) {
			 	printf("Erro ao abrir o arquivo de perguntas.\n");
			 	return 0;
			 }
		
			for (i=0;i<4;i++){
			 		fscanf(arqCad,"%99[^;];%9999[^;];%99[^;];%99[^;];%9999[^;];%9999[^\n]",id[i],pergunta[i],alt1[i],alt2[i],sobre1[i],sobre2[i]);
				}
		
			fclose(arqPerg);
			
			system("cls");
			
			printf("Música: %s\n\n",id[3]);
			printf("Descrição: %s\n\n\n",pergunta[3]);
			for(i=0;i<3;i++){
				while(1){
					printf("Pergunta %d: %s\n\n",i+1, pergunta[i]);
					printf("1. %s\n2. %s\n\n",alt1[i],alt2[i]);
					printf("= ");
			   	 	scanf("%d",&opcaoart[i]);
			    	if (opcaoart[i]<1||opcaoart[i]>2) {
				    	system("cls");
				    	printf("Selecione uma opção válida.\n\n");
				    	continue;
					}
					printf("\nAleternativa selecionada: ");
					if (opcaoart[i]==1){
						printf("%s\n\n%s\n\n",alt1[i],sobre1[i]);
						system("pause");
						system("cls");
						break;
					} 
					if (opcaoart[i]==2){
						printf("%s\n\n%s\n\n",alt2[i],sobre2[i]);
						system("pause");
						system("cls");
						break;
					}
				}		
			}
			
			FILE *arqRes = fopen(resp,"a+");
			
			if (arqRes == NULL){
		    	printf("Erro ao abrir o arquivo de respostas.\n");
			 	return 1;
			}
			
			for(i=0;i<3;i++){
				fprintf(arqRes,"%d;%d\n",i+1,opcaoart[i]);
			}
			
			fclose(arqRes);
			
			system("pause");
			continue;
		}
		
		if (opcaomusica==4){
			system("cls");
			continue;
		}
		break;
	}
    	
	
	return 0;
}
