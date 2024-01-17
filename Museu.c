#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <conio.h>


int bilheteria ();
int contatos();
int terminal();

void cabecalho(){
	printf("**************************************************************************************************************************************************\n"); 
    printf("\t\t\t\t\t\t\t** MUSEU DA MÚSICA POPULAR BRASILEIRA **\n"); 
    printf("**************************************************************************************************************************************************\n"); 
}

void sair(){
	system("cls");
	cabecalho();
	printf("\n\t\t\t\t\t\t\tAgradecemos por usar nosso sistema!\n");
	exit (0);
}

void getPassword(char *password, int maxLen) {
    int i = 0;
    char c;

    while (1) {
        c = getch(); // 

        if (c == '\r' || c == '\n') {
            break;
        } else if (c == '\b' && i > 0) { 
            printf("\b \b"); 
            i--;
        } else if (i < maxLen - 1) {
            password[i] = c;
            printf("*"); 
            i++;
        }
    }

    password[i] = '\0'; 
}

int verifyEmail(char *email) {
    int i,verificado = 0;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            verificado = 1;
            break;
        }
    }
    return verificado;
}

int verifySenha(char *senha) {
    if (strlen(senha) >= 8) {
        return 1;
    }
    return 0;
}

int verifyData (char*data){
	if (strlen(data) != 10) {
        return 0;
    }
    
    int i;

    for (i = 0; i < 10; i++) {
    	if (i==0){
    		if (data[i]!='0'&&data[i]!='1'&&data[i]!='2'&&data[i]!='3'){
    			return 0;
			}
		}
		if (i==1){
    		if (data[0]=='3'&&data[i]!='0'&&data[i]!='1'){
    			return 0;
			}
		}
    	
    	if (i==2||i==5){
    		if (data[i]!='/'){
    			return 0;
			}
		}
		
		if (i==3){
			if (data[i]!='0'&&data[i]!='1'){
    			return 0;
			}
		}
		
		if (i==4){
			if (data[3]=='1'&&data[i]!='0'&&data[i]!='1'&&data[i]!='2'){
    			return 0;
			}
		}
		
		if (i==6){
			if (data[i]!='1'&&data[i]!='2'){
    			return 0;
			}
		}
		
		if (i==7){
			if (data[6]=='1'&&data[i]!='9'){
    			return 0;
			}
			if (data[6]=='2'&&data[i]!='0'){
    			return 0;
			}
		}
		
		if (i==8){
			if (data[6]=='2'&&data[i]!='0'&&data[i]!='1'&&data[i]!='2'){
    			return 0;
			}
		}
		
		if (i==9){
			if (data[6]=='2'&&data[8]=='2'&&data[i]!='0'&&data[i]!='1'&&data[i]!='2'&&data[i]!='3'){
    			return 0;
			}
		}
    }
    
    return 1;
}

int verifyCPF(char *cpf) {
    if (strlen(cpf) != 14) {
        return 0;
    }
    
    int i;

    for (i = 0; i < 14; i++) {
        if (i == 3 || i == 7) {
            if (cpf[i] != '.') {
                return 0;
            }
        } else if (i == 11) {
            if (cpf[i] != '-') {
                return 0;
            }
        } else {
            if (cpf[i] < '0' || cpf[i] > '9') {
                return 0;
            }
        }
    }

    return 1;
}

typedef struct {
    char nome[200], data_nascimento[11], cpf[15], email[100], senha[100], senharpt[100], ticket[200];
    int qtd_art, opcao_art, opcao_mod, opcao_pag, uso;
    int art[5];
} cadastro;


////////////////////////////////////////////////////////////////////////////


int main() {
	
    char opcao;
    
    setlocale(LC_ALL, "Portuguese");

    do {
        system("cls");
        
        
        cabecalho();

    	printf("\n\t\t\t\t\t\t\t\t\tMENU\n\n\n"); 

        
		printf("Bem-vindo ao Museu da Música Popular Brasileira.\n\n\n");
		printf("Digite uma opção abaixo:\n");
        printf("\n1 - Bilheteria\n");
        printf("\n2 - Ver a exposição\n");
        printf("\n3 - Contatos\n");
        printf("\n4 - Sair\n");
        printf("\n\nEscolha uma opção: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                bilheteria();
                break;
            case '2':
               	terminal();
                break;
            case '3':
                contatos(); 
                break;
            case '4':
                sair();
                break;
            default:
                printf("Opção inválida. Digite uma opção válida.\n");
        }
    } while (opcao != '4');

    return 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------



//BILHETERIA ------------------------------------------------------------------------------------------------------------------------------------------


int bilheteria(){
	
	const float preco_int = 30;
    const float preco_meia = preco_int / 2;
    int i;

    cadastro cad;

    //CADASTRO INICIAL
    
    system("cls");
    
    cabecalho();

    printf("\n\t\t\t\t\t\t\t\t\tBILHETERIA\n\n\n"); 
    
    printf("\n CADASTRO\n\n\n");
    printf(" Nome completo: ");
    scanf(" %[^\n]s", cad.nome);
    
    int validacao = 0;
    while (!validacao) {
        printf("\n Data de nascimento (DD/MM/AAAA): ");
        scanf("%s", cad.data_nascimento);    
        validacao = verifyData(cad.data_nascimento);
	        if (!validacao) {
	            printf("\n\n \t\t\t\t\t\t Data inválida. Digite no formato DD/MM/AAAA com as barras. \n");
            	printf(" \t\t\t\t\t\t\t\t\tEx: 27/03/2000 \n\n\n");
	        }
    }
    
    validacao = 0;
    while (!validacao) {
        printf("\n CPF (XXX.XXX.XXX-XX): ");
        scanf("%s", cad.cpf);
        validacao = verifyCPF(cad.cpf);
	        if (!validacao) {
	            printf("\n\n \t\t\t\t\tCPF inválido. Digite no formato XXX.XXX.XXX-XX com os pontos e o hífen. \n");
            	printf(" \t\t\t\t\t\t\t\tEx: 123.456.789-10 \n\n\n");;
	        }
    }

	validacao = 0;
	while (!validacao){
		printf("\n E-mail: ");
    	scanf(" %99[^\n]s", cad.email);
    	validacao = verifyEmail(cad.email);
	        if (!validacao) {
	            printf("\n\n \t\t\t\t\t\t\tE-mail inválido. Digite no formato xxxxx@xxx.com. \n");
            	printf(" \t\t\t\t\t\t\t\t\tEx: joao@gmail.com \n\n\n");;
	        }
	}
    
    
    validacao = 0;
    while (!validacao) {
        printf("\n Senha (mínimo 8 caracteres): ");
        getPassword(cad.senha, sizeof(cad.senha));
        validacao = verifySenha(cad.senha);
        if (!validacao) {
            printf("\n\n \t\t\t\t\tSenha inválida. Digite uma senha com no mínimo 8 caracteres. \n");
            continue;
        }
        printf("\n");
        printf("\n Repita sua senha: ");
        getPassword(cad.senharpt, sizeof(cad.senharpt));
        int validador = strcmp(cad.senha, cad.senharpt);
        if (validador == 0) break;
        else {
        	printf("\n\n \t\t\t\t\t\t As senhas não são iguais. Tente novamente.\n\n\n");
			validacao = 0;	
		}
    }

    //SELEÇÃO DOS ARTISTAS
    cad.opcao_art = 1;
    cad.qtd_art = 1;
    int vrf;
    
    while (1) {
        system("cls");
        cabecalho();
    	printf("\n\t\t\t\t\t\t\t\tBILHETERIA\n\n\n");  
        if (cad.opcao_art < 1 || cad.opcao_art > 2 || vrf == 1) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
        if (cad.qtd_art < 1 || cad.qtd_art > 5) printf("\n INSIRA UMA QUANTIDADE VÁLIDA.\n\n");
        printf("\n ARTISTAS\n\n\n");
        printf(" 1. Ernesto Nazareth\n\n 2. Dilermando Reis\n\n 3. Heitor Villa-Lobos\n\n 4. Caetano Veloso\n\n 5. Tom Jobim\n\n\n");
        printf(" Digite quantos artistas deseja ver: ");
        
        if (scanf("%d", &cad.qtd_art) != 1) {
	        while (getchar() != '\n');	
	        system("cls");
	    	continue;
    	}
        
        if (cad.qtd_art < 1 || cad.qtd_art > 5) continue;

        if (cad.qtd_art == 5) {
            for (i = 0; i < 5; i++) cad.art[i] = 1;
            break;
        }

        printf("\n\n Digite o número correspondente dos artistas que deseja ver:\n");

        for (i = 0; i < 5; i++) cad.art[i] = 0;
		
		vrf = 0;
		
        for (i = 0; i < cad.qtd_art; i++) {
            printf("\n %d° artista: ", i + 1);
            
            if (scanf("%d", &cad.opcao_art) != 1) {
		        while (getchar() != '\n');	
		        system("cls");
		        vrf = 1;
		    	break;
	    	}
            
            if (cad.opcao_art < 1 || cad.opcao_art > 5) break;
            int in;
            for (in = 0; in < 5; in++) {
                if (cad.opcao_art == in + 1) cad.art[in] = 1;
            }
        }
		if (vrf == 1) continue;
        if (cad.opcao_art >= 1 && cad.opcao_art <= 5) break;
        else continue;
    }

    //MODALIDADE DE INGRESSO
    cad.opcao_mod = 1;
    while (1) {
        system("cls");
        cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tBILHETERIA\n\n\n");  
        if (cad.opcao_mod < 1 || cad.opcao_mod > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
        printf("\n VALORES\n\n\n");
        printf(" 1. Entrada Inteira: R$%.2f\n\n 2. Meia-Entrada: R$%.2f\n\n", preco_int, preco_meia);
        printf(" Obs.: Crianças com até 5 anos são isentas.\n\n\n");
        printf(" Digite qual opção deseja: ");
        if (scanf("%d", &cad.opcao_mod) != 1) {
	        while (getchar() != '\n');	
	        system("cls");
	    	continue;
    	}
        if (cad.opcao_mod < 1 || cad.opcao_mod > 2) continue;
        else break;
    }

    //MÉTODO DE PAGAMENTO
    cad.opcao_pag = 1;
    while (1) {
        system("cls");
        cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tBILHETERIA\n\n\n"); 
        if (cad.opcao_pag < 1 || cad.opcao_pag > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
        printf("\n PAGAMENTO\n\n\n");
        printf(" 1. Boleto\n\n 2. PIX\n\n\n");
        printf(" Digite qual opção deseja: ");
        if (scanf("%d", &cad.opcao_pag) != 1) {
	        while (getchar() != '\n');	
	        system("cls");
	    	continue;
    	}
        if (cad.opcao_pag < 1 || cad.opcao_pag > 2) continue;
        else break;
    }

    //CONFIRMAÇÃO DOS DADOS
    int confirmacao = 1;
    while (1) {
        system("cls");
        cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tBILHETERIA\n\n\n"); 
        if (confirmacao < 1 || confirmacao > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
        printf("\n CONFIRMAÇÃO DE COMPRA\n ---------------------------------------------------------------\n\n");

        printf(" Nome: %s\n\n", cad.nome);
        printf(" Data de nascimento: %s\n\n", cad.data_nascimento);
        printf(" CPF: %s\n\n", cad.cpf);
        printf(" E-mail: %s\n\n", cad.email);
        printf(" ---------------------------------------------------------------\n\n");
        printf(" Quantidade de artistas: %d\n\n", cad.qtd_art);

        char artista[5][100] = {"Ernesto Nazareth", "Dilermando Reis", "Heitor Villa-Lobos", "Caetano Veloso", "Tom Jobim"};

        for (i = 0; i < 5; i++) {
            if (cad.art[i] == 1) {
                printf(" %s\n", artista[i]);
            }
        }
        printf(" \n---------------------------------------------------------------\n\n");

        printf(" Modalidade: ");
        if (cad.opcao_mod == 1) printf("Entrada Inteira.");
        else printf("Meia-Entrada.");
        printf("\n\n ---------------------------------------------------------------\n\n");

        printf(" Pagamento: ");
        if (cad.opcao_pag == 1) printf("Boleto.");
        else printf("PIX.");
        printf("\n\n ---------------------------------------------------------------\n\n");
        
        printf(" Total: ");
        if (cad.opcao_mod == 1) printf("R$%.2f",preco_int);
        else printf("R$%.2f",preco_meia);
        printf("\n\n ---------------------------------------------------------------\n\n");
        

        printf(" Deseja continuar?\n\n 1. Sim\n 2. Não\n\n");
        printf(" Escolha uma opção: ");
        int opcao;
        if (scanf("%d", &opcao) != 1) {
	        while (getchar() != '\n');	
	        system("cls");
	    	continue;
    	}
        if (confirmacao < 1 || confirmacao > 2) continue;
        else if (confirmacao == 2) return 1;
        else break;
    }
	
	FILE *arqCad = fopen("BancoDeDados.csv", "a+");
	
	if (arqCad != NULL) {
	
    //GERAÇÃO DO TICKET
    srand(time(NULL));

    int pt1 = 0;

    pt1 = (rand() % 900) + 100;

    int pt3 = 0;
    char linha[1000];

    while (fgets(linha, sizeof(linha), arqCad) != NULL) {
        pt3++;
    }

    char str_pt1[50];
    char str_pt2[50];
    char str_pt3[50];

    sprintf(str_pt1, "%d", pt1);
    sprintf(str_pt2, "%d", cad.qtd_art);
    sprintf(str_pt3, "%d", pt3);

    strcpy(cad.ticket, str_pt1);
    strcat(cad.ticket, str_pt2);
    strcat(cad.ticket, str_pt3);

    system("cls");
    cabecalho();
    printf("\n\t\t\t\t\t\t\t\t\tBILHETERIA\n\n\n"); 
    printf(" Sua compra foi confirmada!\n\n");
    printf(" Seu ticket é: %s\n\n\n", cad.ticket);
    
   	char mododepagamento[20];
	char opcaodepagamento[20];
	
	if (cad.opcao_mod == 1)strcpy(mododepagamento, "Inteira");
	else strcpy(mododepagamento, "Meia");
	
	if (cad.opcao_pag == 1) strcpy(opcaodepagamento, "Boleto");
	else strcpy(opcaodepagamento, "PIX");

	fprintf(arqCad, "%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d;%s;%s;%s;%d\n", cad.nome, cad.data_nascimento, cad.cpf, cad.email, cad.senha,
            cad.art[0], cad.art[1], cad.art[2], cad.art[3], cad.art[4], cad.qtd_art,
            mododepagamento, opcaodepagamento, cad.ticket, 0);

    system("pause");

    

    fclose(arqCad);

	} else {
	    printf("Erro ao abrir o arquivo de cadastro.\n");
	}

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------



//CONTATOS --------------------------------------------------------------------------------------------------------------------------------------------

int contatos() {
	
	char escolha;
	do {
		
	    system("cls");
	    
	    cabecalho();
	
	    printf("\n\t\t\t\t\t\t\t\t      CONTATOS\n\n\n");
	    printf("Para entrar em contato conosco, siga uma destas opções:\n\n");
	    printf("1. Telefone: (11) 2127-3810\n\n");
	    printf("2. E-mail: contato@museumpb.com.br\n\n");
	    printf("3. Redes Sociais:\n");
	    printf("   Twitter: @MuseuMPB_Oficial\n");
	    printf("   Instagram: @MuseuMPB_Oficial\n");
	    printf("   Facebook: MuseuMPBOficial\n");
	    printf("   YouTube: MuseuMPBCanal\n");
	
	    printf("\n\n\nDeseja retornar ao menu?\n\n");
	    printf("1 - Sim \n\n");
	    printf("2 - Não \n\n\n");
	    printf("Escolha uma opção: ");
	    scanf(" %c", &escolha);
	
	    switch (escolha) {
	        case '1':
	            break;
	        case '2':
	            sair();
	            break;
	        default:
	            continue;
	    }break;
    } while (escolha != '2');
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------


int terminal(){
	
	system("cls");
	
	char musica[50],artistas[50];
    
    
    //ARMAZENANDO A BD EM VARIÁVEIS ###################################################################################################################
    
    
    FILE *arqCad = fopen("BancoDeDados.csv", "r");
    

	if (arqCad == NULL) {
	 	printf("Erro ao abrir o arquivo de perguntas.\n");
	 	system("pause");
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
	
	
    //ARMAZENANDO AS MUSICAS EM VARIÁVEIS #############################################################################################################
	
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
	

	//INSERÇÃO DE TICKET ##############################################################################################################################
	
	
    int linhauser;

    while (1) {
    	
    	char ticketuser[20];
    	
    	cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n"); 
    	
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
					printf("\nTicket já foi utilizado.\n\n");
					system("pause");
					system("cls");
					continue;
				}
            	system("cls");
            	break;
			}	
			else {
				printf("\nTicket incorreto.\n\n");
				system("pause");
				system("cls");	
			}
        } else {
            printf("\nTicket incorreto.\n\n");
            system("pause");
            system("cls");
        }
    }
   
   
	//INSERÇÃO DE SENHA ##############################################################################################################################
    
    
    while (1) {
    	
    	cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
		 
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
    
    
    //IMPEDIR NOVOS ACESSOS COM O MESMO TICKET #######################################################################################################
    
    
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
    	
    	cabecalho();
    	printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
		
    	printf("Escolha um artista: \n\n");
		
		if(strcmp(artista1[linhauser],"1")==0)printf("Setor 1. %s\n",artista1[0]);
		if(strcmp(artista2[linhauser],"1")==0)printf("Setor 2. %s\n",artista2[0]);
		if(strcmp(artista3[linhauser],"1")==0)printf("Setor 3. %s\n",artista3[0]);
		if(strcmp(artista4[linhauser],"1")==0)printf("Setor 4. %s\n",artista4[0]);
		if(strcmp(artista5[linhauser],"1")==0)printf("Setor 5. %s\n",artista5[0]);
		printf("\nDigite o setor que deseja visitar, ou ""S"" para sair:\n");
		
		char opcao;
		char opcaomusica;
		
		printf("\n= ");
    	scanf(" %c",&opcao);
    	
    	if(opcao=='s'||opcao =='S'){
    		char opend;
    		system("cls");
    		cabecalho();
    		printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
    		printf("Ao optar por sair, não será possível entrar na exposição novamente. Deseja realmente sair?\n\n");
    		printf("1 - Sim\n2 - Não\n\n");
    		printf("Escolha uma opção: ");
    		scanf(" %c",&opcao);
    		if(opcao=='1') return 0;
    		else {system("cls");continue;}
		}
		
		if (opcao!='1'&&opcao!='2'&&opcao!='3'&&opcao!='4'&&opcao!='5'){
			system("cls");
			continue;
		}
		
    	system("cls");	
    	
    	while(1){
    		
    		system("cls");
    		cabecalho();
    		printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
    		
    		printf("Escolha uma música: \n\n");
    		
    		if (opcao == '1') {
    			strcpy(artistas,artista1[0]);	
				for (i=0;i<3;i++){
					printf("%d - %s\n",i+1,musE[i]);
				}
				printf("4 - Voltar\n\n= ");
				scanf(" %c",&opcaomusica);
				
				switch (opcaomusica){
					
					case '1': 
							strcpy (musica,"ApanheiTeCavaquinho");
							break;
					case '2': 
							strcpy (musica,"Brejero");
							break;
					case '3': 
							strcpy (musica,"Odeon");
							break;
					case '4': 
							break;
					default :
							system("cls");
							cabecalho();
    						printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
							printf("Selecione uma opção válida.\n\n");
							continue;
				}
				
				if (opcaomusica == '4') break;
	
	    	}
	    	
    		if (opcao == '2') {
    			strcpy(artistas,artista2[0]);	
				for (i=0;i<3;i++){
					printf("%d - %s\n",i+1,musD[i]);
				}
				printf("4 - Voltar\n\n= ");
				scanf(" %c",&opcaomusica);
				
				switch (opcaomusica){
					
					case '1': 
							strcpy (musica,"AbismoDeRosas");
							break;
					case '2': 
							strcpy (musica,"NoiteDeLua");
							break;
					case '3': 
							strcpy (musica,"SeElaPerguntar");
							break;
					case '4': 
							break;
					default :
							system("cls");
							cabecalho();
    						printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
							printf("Selecione uma opção válida.\n\n");
							continue;
				}
				
				if (opcaomusica == '4') break;
			
	    	}
	    	
    		if (opcao == '3') {
    			strcpy(artistas,artista3[0]);	
				for (i=0;i<3;i++){
					printf("%d - %s\n",i+1,musH[i]);
				}
				printf("4 - Voltar\n\n= ");
				scanf(" %c",&opcaomusica);
				
				switch (opcaomusica){
					
					case '1': 
							strcpy (musica,"ChoroN1");
							break;
					case '2': 
							strcpy (musica,"EstudoN1");
							break;
					case '3': 
							strcpy (musica,"PreludioN1");
							break;
					case '4': 
							break;
					default :
							system("cls");
							cabecalho();
    						printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
							printf("Selecione uma opção válida.\n\n");
							continue;
				}
				
				if (opcaomusica == '4') break;
			
	    	}
	    	
    		if (opcao == '4') {
    			strcpy(artistas,artista4[0]);	
				for (i=0;i<3;i++){
					printf("%d - %s\n",i+1,musC[i]);
				}
				printf("4 - Voltar\n\n= ");
				scanf(" %c",&opcaomusica);
				
				switch (opcaomusica){
					
					case '1': 
							strcpy (musica,"AlegriaAlegria");
							break;
					case '2': 
							strcpy (musica,"CoraçãoVagabundo");
							break;
					case '3': 
							strcpy (musica,"DesdeSamba");
							break;
					case '4': 
							break;
					default :
							system("cls");
							cabecalho();
    						printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
							printf("Selecione uma opção válida.\n\n");
							continue;
				}
				
				if (opcaomusica == '4') break;
				
	    	}
	    	
	    	if (opcao == '5') {
    			strcpy(artistas,artista5[0]);	
				for (i=0;i<3;i++){
					printf("%d - %s\n",i+1,musT[i]);
				}
				printf("4 - Voltar\n\n= ");
				scanf(" %c",&opcaomusica);
				
				switch (opcaomusica){
					
					case '1': 
							strcpy (musica,"EuSeiQueVouTeAmar");
							break;
					case '2': 
							strcpy (musica,"GarotadeIpanema");
							break;
					case '3': 
							strcpy (musica,"Wave");
							break;
					case '4': 
							break;
					default :
							system("cls");
							cabecalho();
    						printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
							printf("Selecione uma opção válida.\n\n");
							continue;
				}
				
				if (opcaomusica == '4') break;
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
			cabecalho();
    		printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
			printf("Música: %s\n\n",id[3]);
			printf("Descrição: %s\n\n\n",pergunta[3]);
			for(i=0;i<3;i++){
				while(1){
					printf("Pergunta %d: %s\n\n",i+1, pergunta[i]);
					printf("1 - %s\n2 - %s\n\n",alt1[i],alt2[i]);
					printf("= ");	   	 	
			   	 	
			   	 	if (scanf("%d", &opcaoart[i]) != 1) {
				        while (getchar() != '\n');	
				        system("cls");
				    	cabecalho();
    					printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
				    	printf("Selecione uma opção válida.\n\n");
				    	continue;
			    	}
			    	
			    	if (opcaoart[i]<1||opcaoart[i]>2){
			    		system("cls");
			    		cabecalho();
    					printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
			    		printf("Selecione uma opção válida.\n\n");
			    		continue;
					}

					printf("\n\n\nAleternativa selecionada: ");
					if (opcaoart[i]==1){
						printf("%s\n\n%s\n\n\n",alt1[i],sobre1[i]);
						system("pause");
						system("cls");
						cabecalho();
    					printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
						break;
					} 
					if (opcaoart[i]==2){
						printf("%s\n\n%s\n\n",alt2[i],sobre2[i]);
						system("pause");
						system("cls");
						cabecalho();
    					printf("\n\t\t\t\t\t\t\t\t\tEXPOSIÇÃO\n\n\n");
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
		
		if (opcaomusica=='4'){
			system("cls");
			continue;
		}
		break;
	}
}



