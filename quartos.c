#include "quartos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 2



void quartos() {
    int opcao1;
    
    // Verifica se o arquivo existe, se não existir, cria-o
    FILE *verificar = fopen("quartos.csv", "r");
    if (verificar == NULL) {
        criarArquivoq();
    } else {
        fclose(verificar);
    }
    
    do {
        printf("\nMENU\n");
        printf("1. Novo Quarto\n");
        printf("2. Alterar Quarto\n");
        printf("3. Deletar Quarto\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao1);
        getchar();

        switch (opcao1) {
            case 1:
                novoquarto();
                break;
            case 2:
                alteraquarto();
                break;
                case 3:
                deletarQuarto();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao1 != 9);
}

void novoquarto() {
    Quarto quarto;

    printf("Digite o codigo do quarto: ");
    scanf("%d", &quarto.codigo_quarto);
   


    printf("Digite a quantidade de camas de solteiro: ");
    scanf("%d", &quarto.camas_solteiro);
   


    printf("Digite a quantidade de camas de casal: ");
    scanf("%d", &quarto.camas_casal);

    printf("Digite o tipo de quarto: ");
    scanf("%s",quarto.tipo_quarto);//CRIAR UMA IF AQUI PARA SETAR VALOR SINGLE OU DUPLO
   
    printf("Digite o preco da diaria: ");
    scanf("%lf", &quarto.preco_diaria);


    printf("Digite  :  A - Ativo | I - Inativo ");
    scanf("%s",quarto.status);
    



    // Abre o arquivo para escrita no modo de adição
    FILE *arquivoquarto = fopen("quartos.csv", "a");
    if (arquivoquarto == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    // Escreve os dados do quarto no arquivo
    fprintf(arquivoquarto, "%d;%d;%d;%s;%.2f;%s\n", quarto.codigo_quarto,quarto.camas_solteiro,quarto.camas_casal,quarto.tipo_quarto,quarto.preco_diaria,quarto.status);
    
    
    fclose(arquivoquarto);


}


void alteraquarto() {
    int codquarto;
    printf("Informe o codigo do quarto que deseja alterar: ");
    scanf("%d", &codquarto);

    FILE *arquivoquarto = fopen("quartos.csv", "r+");
    if (arquivoquarto == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[100]; // Linha temporária para armazenar cada linha do arquivo
    long int posicao_inicial = ftell(arquivoquarto);

    while (fgets(linha, sizeof(linha), arquivoquarto) != NULL) {
        int codigo_quarto;
        sscanf(linha, "%d", &codigo_quarto);
        if (codigo_quarto == codquarto) {
            // Se encontrarmos o quarto, permitimos a alteração
            int camas_solteiro;
            int camas_casal;
            char tipo_quarto[20]; // Aumente o tamanho do array para acomodar "SINGLE", "DUPLO" ou "TRIPLO"
            float preco_diario;
            char status[2]; // "A" ou "I" (Ativo ou Inativo)

            sscanf(linha, "%d;%d;%d;%[^;];%f;%s", &codigo_quarto, &camas_solteiro, &camas_casal, tipo_quarto, &preco_diario, status);

            printf("Digite a quantidade de camas de solteiro: ");
            scanf("%d", &camas_solteiro);

            printf("Digite a quantidade de camas de casal: ");
            scanf("%d", &camas_casal);

            printf("Digite o tipo de quarto (SINGLE/DUPLO/TRIPLO): ");
            scanf("%s", tipo_quarto);

            fseek(arquivoquarto, posicao_inicial, SEEK_SET);

            // Escrevemos os dados atualizados do quarto no arquivo
            fprintf(arquivoquarto, "%d;%d;%d;%s;%f;%s\n", codquarto, camas_solteiro, camas_casal, tipo_quarto, preco_diario, status);
            printf("Quarto com codigo %d alterado com sucesso.\n", codquarto);
            fclose(arquivoquarto);
            return;
        }
        posicao_inicial = ftell(arquivoquarto);
    }

    printf("Quarto com codigo %d não encontrado.\n", codquarto);
    fclose(arquivoquarto);
}

void criarArquivoq() {
	//verica se o arquivo ja existi
     FILE *arquivoq = fopen("quartos.csv", "w");
    if (arquivoq == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }
    fprintf(arquivoq, "CODIGO QUARTO;CAMAS SOLTEIRO;CAMAS CASAL;TIPO DE QUARTO;PREÇO DIARIA;STATUS\n");
    fclose(arquivoq);
    
   


int codigo_quarto;
    int camas_solteiro;
    int camas_casal;
    char tipo_quarto[6];
    double preco_diaria;
    char status[1];

}

void deletarQuarto() {
    int codigo_quarto;
    printf("Informe o codigo do quarto que deseja excluir: ");
    scanf("%d", &codigo_quarto); // Corrigido para ler um inteiro

    // Abre o arquivo para leitura
    FILE *arquivo_entrada = fopen("quartos.csv", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        exit(1);
    }

    // Abre um arquivo temporário para escrita
    FILE *arquivo_temporario = fopen("temporarioquartos.csv", "w");
    if (arquivo_temporario == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        exit(1);
    }

    char linha[100]; // Linha temporária para armazenar cada linha do arquivo
    int codigoQuartoArquivo; // Corrigido para ser um único inteiro
    while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
        sscanf(linha, "%d", &codigoQuartoArquivo); // Corrigido para ler um único inteiro

        // Se o código do quarto na linha for diferente do código a ser removido, escreve no arquivo temporário
        if (codigoQuartoArquivo != codigo_quarto) {
            fprintf(arquivo_temporario, "%s", linha); // Corrigido para escrever a linha original
        }
    }

    // Fecha os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_temporario);

    // Remove o arquivo original
    remove("quartos.csv");
    // Renomeia o arquivo temporário para o nome do arquivo original
    rename("temporarioquartos.csv", "quartos.csv");

    printf("Quarto com Codigo %d removido com sucesso.\n", codigo_quarto);
}
