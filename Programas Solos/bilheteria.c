#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>

// INSERÇÂO DE OCULTAÇÂO NAS CARACTERES (SENHAS)
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

typedef struct {
    char nome[200], data_nascimento[11], cpf[15], email[100], senha[100], senharpt[100], ticket[200];
    int qtd_art, opcao_art, opcao_mod, opcao_pag, uso;
    int art[5];
} cadastro;

int main() {

    setlocale(LC_ALL, "Portuguese");

    const float preco_int = 30;
    const float preco_meia = preco_int / 2;
    int i;

    FILE *arqCad = fopen("cadastro.csv", "a+");

    if (arqCad != NULL) {

        cadastro cad;

        //CADASTRO INICIAL
        printf("\n CADASTRO\n --------\n\n");
        printf(" Nome completo: ");
        scanf(" %[^\n]s", cad.nome);
        while (1) {
            printf("\n Data de nascimento (DD/MM/AAAA): ");
            scanf("%s", cad.data_nascimento);
            if (strlen(cad.data_nascimento) == 10) {
                break;
            } else {
                printf("\n\n Data inválida. Digite no formato DD/MM/AAAA com as barras. \n");
                printf(" Ex: 27/03/2000 \n\n\n");
            }
        }
        while (1) {
            printf("\n CPF (XXX.XXX.XXX-XX): ");
            scanf("%s", cad.cpf);
            if (strlen(cad.cpf) == 14) break;
            else {
                printf("\n\n CPF inválido. Digite no formato XXX.XXX.XXX-XX com os pontos e o hífen. \n");
                printf(" Ex: 123.456.789-10 \n\n\n");
            }
        }

        printf("\n E-mail: ");
        scanf(" %99[^\n]s", cad.email);
        while (1) {
            printf("\n Senha: ");
            getPassword(cad.senha, sizeof(cad.senha));
            printf("\n");
            printf("\n Repita sua senha: ");
            getPassword(cad.senharpt, sizeof(cad.senharpt));
            int validador = strcmp(cad.senha, cad.senharpt);
            if (validador == 0) break;
            else printf("\n\n As senhas não são iguais. Tente novamente.\n\n\n");
        }

        //SELEÇÃO DOS ARTISTAS
        cad.opcao_art = 1;
        cad.qtd_art = 1;
        while (1) {
            system("cls");
            if (cad.opcao_art < 1 || cad.opcao_art > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
            if (cad.qtd_art < 1 || cad.qtd_art > 5) printf("\n INSIRA UMA QUANTIDADE VÁLIDA.\n\n");
            printf("\n ARTISTAS\n\n\n");
            printf(" 1. Ernesto Nazareth\n\n 2. Dilermando Reis\n\n 3. Heitor Villa-Lobos\n\n 4. Caetano Veloso\n\n 5. Tom Jobim\n\n\n");
            printf(" Digite quantos artistas deseja ver: ");
            scanf("%d", &cad.qtd_art);
            if (cad.qtd_art < 1 || cad.qtd_art > 5) continue;

            if (cad.qtd_art == 5) {
                for (i = 0; i < 5; i++) cad.art[i] = 1;
                break;
            }

            printf("\n\n Digite o número correspondente dos artistas que deseja ver:\n");

            for (i = 0; i < 5; i++) cad.art[i] = 0;

            for (i = 0; i < cad.qtd_art; i++) {
                printf("\n %d° artista: ", i + 1);
                scanf("%d", &cad.opcao_art);
                if (cad.opcao_art < 1 || cad.opcao_art > 5) break;
                int in;
                for (in = 0; in < 5; in++) {
                    if (cad.opcao_art == in + 1) cad.art[in] = 1;
                }
            }

            if (cad.opcao_art < 1 || cad.opcao_art > 5) continue;
            else break;
        }

        //MODALIDADE DE INGRESSO
        cad.opcao_mod = 1;
        while (1) {
            system("cls");
            if (cad.opcao_mod < 1 || cad.opcao_mod > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
            printf("\n VALORES\n\n\n");
            printf(" 1. Entrada Inteira: R$%.2f\n\n 2. Meia-Entrada: R$%.2f\n\n", preco_int, preco_meia);
            printf(" Obs.: Crianças com até 5 anos são isentas.\n\n\n");
            printf(" Digite qual opção deseja: ");
            scanf("%d", &cad.opcao_mod);
            if (cad.opcao_mod < 1 || cad.opcao_mod > 2) continue;
            else break;
        }

        //MÉTODO DE PAGAMENTO
        cad.opcao_pag = 1;
        while (1) {
            system("cls");
            if (cad.opcao_pag < 1 || cad.opcao_pag > 2) printf("\n INSIRA UMA OPCAO VÁLIDA.\n\n");
            printf("\n PAGAMENTO\n\n\n");
            printf(" 1. Boleto\n\n 2. PIX\n\n\n");
            printf(" Digite qual opção deseja: ");
            scanf("%d", &cad.opcao_pag);
            if (cad.opcao_pag < 1 || cad.opcao_pag > 2) continue;
            else break;
        }

        //CONFIRMAÇÃO DOS DADOS
        int confirmacao = 1;
        while (1) {
            system("cls");
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
            if (cad.opcao_mod == 1) printf("Boleto.");
            else printf("PIX.");
            printf("\n\n ---------------------------------------------------------------\n\n");

            printf(" Deseja continuar?\n\n 1. Sim\n 2. Não\n\n = ");
            scanf("%d", &confirmacao);
            if (confirmacao < 1 || confirmacao > 2) continue;
            else if (confirmacao == 2) return 1;
            else break;
        }

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
        printf(" Sua compra foi confirmada!\n\n");
        printf(" Seu ticket é: %s\n\n", cad.ticket);

        system("pause");

        fprintf(arqCad, "%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d;%s;%d;%d\n", cad.nome, cad.data_nascimento, cad.cpf, cad.email, cad.senha,
                cad.art[0], cad.art[1], cad.art[2], cad.art[3], cad.art[4], cad.qtd_art,
                cad.opcao_mod, cad.opcao_pag, cad.ticket, 0, 1);

        fclose(arqCad);

    } else {
        printf("Erro ao abrir o arquivo de cadastro.\n");
    }

    return 0;
}

