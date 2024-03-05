#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#include "cliente.h"
#include "quartos.h"



#define TAM_MAXIMO 100
#define TAM_CPF 12



typedef struct {
    int codigo_reserva;
    char cpf_reserva[12];
    int data_checkin;
    int data_checkout;
    char tipo_quarto[6];
    int codigo_quarto;
} Reserva;

// Array para armazenar os clientes
Cliente clientesteste[TAM_MAXIMO];
int num_clientes = 0;




void reservas(){
   // Verifica se o arquivo existe, se não existir, cria-o
    FILE *verificar = fopen("reservas.csv", "r");
    if (verificar == NULL) {
        criarArquivoReservas();
    } else {
        fclose(verificar);
    }
 carregarClientes();
    int opcao1;
    do {
        printf("\nMENU\n");
        printf("1. Quartos disponiveis para reserva\n");
        printf("2. Reservar Quarto\n");
        printf("3. Cancelar reserva\n");
        printf("4. Buscar reserva\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao1);
        getchar();

        switch (opcao1) {
            case 1:
                mostrarQuartos();
                break;
            case 2:
             verificarCpf();
                break;
            case 3:
            cancelarReserva();
                break;
            case 4:
                buscarReservas();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao1 != 9);
}

// Função para carregar os clientes do arquivo clientes.csv
void carregarClientes() {
    FILE *arquivo = fopen("clientes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }

    while (fscanf(arquivo, "%[^;];%[^;];%d;%d;%[^;];%[^;];%s\n", clientesteste[num_clientes].nome_cliente,
                  clientesteste[num_clientes].cpf_cliente, &clientesteste[num_clientes].data_nasc,
                  &clientesteste[num_clientes].idade_cliente, clientesteste[num_clientes].endereco,
                  clientesteste[num_clientes].cidade, clientesteste[num_clientes].estado) != EOF) {
        num_clientes++;
    }

    fclose(arquivo);
}

// Função para fazer uma reserva
void verificarCpf() {
    char cpf[TAM_CPF];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    FILE *arquivo = fopen("clientes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }

    int cliente_encontrado = 0; // Variável para indicar se o cliente foi encontrado

    // Verifica se o CPF existe no arquivo
    char cpf_arquivo[TAM_CPF];
    while (fscanf(arquivo, "%*[^;];%[^;];%*d;%*d;%*[^;];%*[^;];%*s\n", cpf_arquivo) != EOF) {
        if (strcmp(cpf, cpf_arquivo) == 0) {
            cliente_encontrado = 1;

            
            break;
        }
    }

    fclose(arquivo);

    if (cliente_encontrado) {

        fazerReserva();




    } else {
        printf("Cliente não encontrado.\n");
    }
}


void criarArquivoReservas() {
	//verica se o arquivo ja existi
    FILE *arquivo = fopen("reservas.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");//indica o retorno da função fopen se for null erro ao criar o arquivo
        exit(1);
    }
    fprintf(arquivo, "CODIGO RESERVA;CPF CLIENTE;DATA CHECKIN;DATA CHECKOUT;TIPO QUARTO;CODIGO QUARTO\n");//
    fclose(arquivo);
    
}

void fazerReserva() {
    Reserva reserva;


    printf(" Digite o codigo da reserva: \n");
    scanf("%d", &reserva.codigo_reserva);
    
    printf("Digite o cpf do cliente CPF: \n");
    scanf("%s", reserva.cpf_reserva);
    
    printf("Digite a data de checkin \n");
    scanf("%d", &reserva.data_checkin);
    
    printf("Digite a data de checkout: \n");
    scanf("%d", &reserva.data_checkout);

	printf("Digite o tipo do quarto: \n");
    scanf("%s",reserva.tipo_quarto);
    
    printf("Digite o codigo do quarto: \n");
    scanf("%d", &reserva.codigo_quarto);
    


    // Abre o arquivo para escrita no modo de adição
    FILE *arquivo = fopen("reservas.csv", "a");
    if (arquivo == NULL) {//verifica se é possivel abrir o arquivo
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    // Escreve os dados do cliente no arquivo
    fprintf(arquivo, "%d;%s;%d;%d;%s;%d;\n", reserva.codigo_reserva, reserva.cpf_reserva, reserva.data_checkin,
    reserva.data_checkout,reserva.tipo_quarto,reserva.codigo_quarto);
    fclose(arquivo);
    

}


// void mostrarQuartos() {
//     FILE *arquivoq = fopen("quartos.csv", "r");
//     if (arquivoq == NULL) {
//         printf("Erro ao abrir o arquivo de quartos.\n");
//         exit(1);
//     }

//     Quarto quarto;
//     printf("Quartos Disponíveis:\n");
//     printf("CODIGO QUARTO | CAMAS SOLTEIRO | CAMAS CASAL | TIPO QUARTO | PREÇO DIARIA | STATUS\n");
//     while (fscanf(arquivoq, "%d;%d;%d;%5s;%lf;%s\n", &quarto.codigo_quarto, &quarto.camas_solteiro, &quarto.camas_casal, quarto.tipo_quarto, &quarto.preco_diaria, quarto.status) == 6) {
//         printf("%d | %d | %d | %s | %.2lf | %s\n", quarto.codigo_quarto, quarto.camas_solteiro, quarto.camas_casal, quarto.tipo_quarto, quarto.preco_diaria, quarto.status);
//     }
    
//     fclose(arquivoq);
// }


void mostrarQuartos() {
    FILE *arquivoq = fopen("quartos.csv", "r");
    if (arquivoq == NULL) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        exit(1);
    }

    Quarto quarto;
    printf("Quartos Disponíveis:\n");
    printf("CODIGO QUARTO | CAMAS SOLTEIRO | CAMAS CASAL | TIPO QUARTO | PREÇO DIARIA | STATUS\n");
    while (fscanf(arquivoq, "%d;%d;%d;%5s;%lf;%1s\n", &quarto.codigo_quarto, &quarto.camas_solteiro, &quarto.camas_casal, quarto.tipo_quarto, &quarto.preco_diaria, quarto.status) == 6) {
        if (strcmp(quarto.status, "I") != 0) { // Verifica se o status é diferente de "I"
            printf("%d | %d | %d | %s | %.2lf | %s\n", quarto.codigo_quarto, quarto.camas_solteiro, quarto.camas_casal, quarto.tipo_quarto, quarto.preco_diaria, quarto.status);
        }
    }
    
    fclose(arquivoq);
}


// void cancelarReserva() {
//     int codigo_reserva;

//     printf("Digite o código da reserva que deseja cancelar: ");
//     scanf("%d", &codigo_reserva);

//     char temp_file[] = "temporario.csv";

//     // Abre o arquivo original para leitura
//     FILE *arquivo_entrada = fopen("reservas.csv", "r");
//     if (arquivo_entrada == NULL) {
//         printf("Erro ao abrir o arquivo de reservas.\n");
//         exit(1);
//     }

//     // Abre um arquivo temporário para escrita
//     FILE *arquivo_temporario = fopen(temp_file, "w");
//     if (arquivo_temporario == NULL) {
//         printf("Erro ao criar arquivo temporário.\n");
//         exit(1);
//     }

//     char linha[100]; // Linha temporária para armazenar cada linha do arquivo
//     int cod;
//     // Lê linha por linha do arquivo original
//     while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
//         sscanf(linha, "%d;", &cod); // Extrai o código de reserva da linha

//         // Se o código de reserva na linha for diferente do código a ser removido, escreve no arquivo temporário
//         if (cod != codigo_reserva) {
//             fprintf(arquivo_temporario, "%s", linha);
//         }
//     }

//     // Fecha os arquivos
//     fclose(arquivo_entrada);
//     fclose(arquivo_temporario);

//     // Remove o arquivo original
//     remove("reservas.csv");
//     // Renomeia o arquivo temporário para o nome do arquivo original
//     rename(temp_file, "reservas.csv");

//     printf("Reserva com código %d excluída com sucesso.\n", codigo_reserva);
// }

void cancelarReserva() {
    int codigo_reserva;
    char cpf_cliente[12]; // Aumentei para 15 para incluir o caractere nulo

    printf("Digite o código da reserva que deseja cancelar: ");
    scanf("%d", &codigo_reserva);

    printf("Digite o CPF do cliente para confirmar o cancelamento: ");
    scanf("%s", cpf_cliente);

    char temp_file[] = "temporario.csv";

    // Abre o arquivo original para leitura
    FILE *arquivo_entrada = fopen("reservas.csv", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        exit(1);
    }

    // Abre um arquivo temporário para escrita
    FILE *arquivo_temporario = fopen(temp_file, "w");
    if (arquivo_temporario == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        exit(1);
    }

    char linha[100]; // Linha temporária para armazenar cada linha do arquivo
    int cod;
    char cpf[15]; // Variável para armazenar o CPF lido de cada linha
    // Lê linha por linha do arquivo original
    while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
        sscanf(linha, "%d;%[^;];", &cod, cpf); // Extrai o código de reserva e o CPF da linha

        // Se o código de reserva na linha for diferente do código a ser removido, ou se o CPF não corresponder, escreve no arquivo temporário
        if (cod != codigo_reserva || strcmp(cpf, cpf_cliente) != 0) {
            fprintf(arquivo_temporario, "%s", linha);
        }
    }

    // Fecha os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_temporario);

    // Remove o arquivo original
    remove("reservas.csv");
    // Renomeia o arquivo temporário para o nome do arquivo original
    rename(temp_file, "reservas.csv");

    printf("Reserva com código %d excluída com sucesso.\n", codigo_reserva);
}


// void buscarReservas() {
//     char cpf_cliente[TAM_CPF];
//     printf("Digite o CPF do cliente para buscar as reservas: ");
//     scanf("%s", cpf_cliente);
//     getchar();

//     FILE *arquivo_reservas = fopen("reservas.csv", "r");
//     if (arquivo_reservas == NULL) {
//         printf("Erro ao abrir o arquivo de reservas.\n");
//         exit(1);
//     }

//     Reserva reserva;
//     int encontrou_reserva = 0;

//     printf("\nReservas do cliente com CPF %s:\n", cpf_cliente);
//     printf("CODIGO RESERVA | CPF CLIENTE | DATA CHECKIN | DATA CHECKOUT | TIPO QUARTO | CODIGO QUARTO\n");

//     // Lê cada linha do arquivo de reservas
//     while (fscanf(arquivo_reservas, "%d;%[^;];%d;%d;%[^;];%d;\n", &reserva.codigo_reserva, reserva.cpf_reserva,
//                   &reserva.data_checkin, &reserva.data_checkout, reserva.tipo_quarto, &reserva.codigo_quarto) == 6) {
//         // Se o CPF na reserva é igual ao CPF fornecido, exibe a reserva
//         if (strcmp(reserva.cpf_reserva, cpf_cliente) == 0) {
//             printf("%d | %s | %d | %d | %s | %d\n", reserva.codigo_reserva, reserva.cpf_reserva,
//                    reserva.data_checkin, reserva.data_checkout, reserva.tipo_quarto, reserva.codigo_quarto);
//             encontrou_reserva = 1; // Marca que pelo menos uma reserva foi encontrada
//         }
//     }

//     // Se nenhuma reserva foi encontrada para o CPF fornecido
//     if (!encontrou_reserva) {
//         printf("Nenhuma reserva encontrada para o cliente com CPF %s.\n", cpf_cliente);
//     }

//     fclose(arquivo_reservas);
// }
    
void buscarReservas() {
    char cpf_cliente[TAM_CPF];
    printf("Digite o CPF do cliente para buscar as reservas: ");
    scanf("%s", cpf_cliente);
    getchar();

    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        exit(1);
    }

    Reserva reserva;
    int encontrou_reserva = 0;

    printf("\nReservas do cliente com CPF %s:\n", cpf_cliente);
    printf("CODIGO RESERVA | CPF CLIENTE | DATA CHECKIN | DATA CHECKOUT | TIPO QUARTO | CODIGO QUARTO\n");

    // Lê cada linha do arquivo de reservas
    while (fscanf(arquivo_reservas, "%d;%[^;];%d;%d;%[^;];%d;\n", &reserva.codigo_reserva, reserva.cpf_reserva,
                  &reserva.data_checkin, &reserva.data_checkout, reserva.tipo_quarto, &reserva.codigo_quarto) == 6) {
        // Se o CPF na reserva é igual ao CPF fornecido, exibe a reserva
        if (strcmp(reserva.cpf_reserva, cpf_cliente) == 0) {
            printf("%d | %s | %d | %d | %s | %d\n", reserva.codigo_reserva, reserva.cpf_reserva,
                   reserva.data_checkin, reserva.data_checkout, reserva.tipo_quarto, reserva.codigo_quarto);
            encontrou_reserva = 1; // Marca que pelo menos uma reserva foi encontrada
        }
    }

    // Se nenhuma reserva foi encontrada para o CPF fornecido
    if (!encontrou_reserva) {
        printf("Nenhuma reserva encontrada para o cliente com CPF %s.\n", cpf_cliente);
    }

    fclose(arquivo_reservas);
}

