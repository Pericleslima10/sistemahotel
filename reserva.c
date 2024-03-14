#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reserva.h"
#include "cliente.h"
#include "quartos.h"
#define TAM_MAXIMO 100
#define MAX_BUFFER_SIZE 1024

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

            buscarReserva();

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
    char cpf[13];
    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    FILE *arquivo = fopen("clientes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }

    int cliente_encontrado = 0; // Variável para indicar se o cliente foi encontrado

    // Verifica se o CPF existe no arquivo
    char cpf_arquivo[13];
    while (fscanf(arquivo, "%*[^;];%[^;];%*d;%*d;%*[^;];%*[^;];%*s\n", cpf_arquivo) != EOF) {
        if (strcmp(cpf, cpf_arquivo) == 0) {
            cliente_encontrado = 1;

            
            break;
        }
    }

    fclose(arquivo);

    if (cliente_encontrado) {

        fazerReserva(cpf);

    } else {
        printf("Cliente não encontrado.\n");
    }
}

void criarArquivoReservas() {
	//verica se o arquivo ja existi
    FILE *arquivoreservas = fopen("reservas.csv", "w");
    if (arquivoreservas == NULL) {
        printf("Erro ao criar o arquivo.\n");//indica o retorno da função fopen se for null erro ao criar o arquivo
        exit(1);
    }
    fprintf(arquivoreservas, "CODIGO RESERVA;CPF CLIENTE;DATA CHECKIN;DATA CHECKOUT;TIPO QUARTO;CODIGO QUARTO\n");//
    fclose(arquivoreservas);
    
}

int gerarNumReserva() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios com o tempo atual
    return rand(); // Retorna um número aleatório
}

void fazerReserva(char *cpf) {
    Reserva reserva;
    reserva.codigo_reserva = gerarNumReserva() / 100000;

    
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
    fprintf(arquivo, "%d;%s;%d;%d;%s;%d;\n", reserva.codigo_reserva,cpf, reserva.data_checkin,
    reserva.data_checkout,reserva.tipo_quarto,reserva.codigo_quarto);
    printf("O seu numero da reserva gerado é: %d\n", reserva.codigo_reserva);

    fclose(arquivo);
    
}

void mostrarQuartos() {
    FILE *arquivoq = fopen("quartos.csv", "r");
    if (arquivoq == NULL) {
        printf("Erro ao abrir o arquivo de quartos.\n");
        criarArquivoq();
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
//     char cpf_cliente[13]; // Aumentei para 15 para incluir o caractere nulo
//     int checkin;

//     printf("Digite o código da reserva que deseja cancelar: ");
//     scanf("%d", &codigo_reserva);

//     printf("Digite o CPF do cliente para confirmar o cancelamento: ");
//     scanf("%s", cpf_cliente);

//     printf("Digite o CPF do cliente para confirmar o cancelamento: ");
//     scanf("%d", checkin);

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
//     }else{
//       printf("Cpf ou codigo da reserva invalidos\n");
//         printf("Digite CPF ou Codigo de reservas existentes !\n");

//     }

//     char linha[100]; // Linha temporária para armazenar cada linha do arquivo
//     int cod;
//     char cpf[15]; // Variável para armazenar o CPF lido de cada linha
//     int data_checkin;

//     // Lê linha por linha do arquivo original
//     while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
//         sscanf(linha, "%d;%[^;];%d", &cod, cpf,data_checkin); // Extrai o código de reserva e o CPF da linha

//         // Se o código de reserva na linha for diferente do código a ser removido, ou se o CPF não corresponder, escreve no arquivo temporário
//         if (cod != codigo_reserva || strcmp(cpf, cpf_cliente) != 0 && data_checkin != checkin ) {
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
    char cpf_cliente[15]; // aumentei para 15 para incluir o caractere nulo
    int checkin;

    printf("Digite o código da reserva que deseja cancelar: ");
    scanf("%d", &codigo_reserva);

    printf("Digite o CPF do cliente para confirmar o cancelamento: ");
    scanf("%s", cpf_cliente);

    printf("Digite a data de check-in (AAAAMMDD): ");
    scanf("%d", &checkin);

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
    int data_checkin;

    // Lê linha por linha do arquivo original
    while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
        sscanf(linha, "%d;%[^;];%d", &cod, cpf, &data_checkin); // Extrai o código de reserva e o CPF da linha

        // Se o código de reserva na linha for diferente do código a ser removido, ou se o CPF ou a data de check-in não corresponderem, escreve no arquivo temporário
        if (cod != codigo_reserva || strcmp(cpf, cpf_cliente) != 0 || data_checkin != checkin) {
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




Reserva encontrar_reserva_por_cpf(char cpf[], FILE *file) {
    Reserva reserva;
    char buffer[MAX_BUFFER_SIZE];

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        sscanf(buffer, "%d;%[^;];%d;%d;%[^;];%d",
               &reserva.codigo_reserva, reserva.cpf_reserva, &reserva.data_checkin,
               &reserva.data_checkout, reserva.tipo_quarto, &reserva.codigo_quarto);

        if (strcmp(reserva.cpf_reserva, cpf) == 0) {
            return reserva;
        }
    }

    // Retorna uma reserva com cpf -1 se não encontrar
    reserva.codigo_reserva = -1;
    return reserva;
}

void buscarReserva(){

    FILE *file;
            char cpf[13];

            printf("Por favor, digite o CPF da reserva: ");
            scanf("%s", cpf);

            file = fopen("reservas.csv", "r");
            if (file == NULL) {
                printf("Erro ao abrir o arquivo de reservas.\n");
                
            }

    Reserva reserva_encontrada = encontrar_reserva_por_cpf(cpf, file);
    if (reserva_encontrada.codigo_reserva != -1) {
        printf("Reserva encontrada:\n");
        printf("Código Reserva: %d\n", reserva_encontrada.codigo_reserva);
        printf("CPF Reserva: %s\n", reserva_encontrada.cpf_reserva);
        printf("Data Check-in: %d\n", reserva_encontrada.data_checkin);
        printf("Data Check-out: %d\n", reserva_encontrada.data_checkout);
        printf("Tipo de Quarto: %s\n", reserva_encontrada.tipo_quarto);
        printf("Código do Quarto: %d\n", reserva_encontrada.codigo_quarto);
    } else {
        printf("Nenhuma reserva encontrada para o CPF fornecido.\n");
    }

    fclose(file);



}