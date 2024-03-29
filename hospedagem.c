#include "hospedagem.h"
#include "reserva.h"
#include "quartos.h"
#include "tempo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void check_in_cliente()
{
    // Implementação para o check-in do cliente
    // Deve perguntar por informações e atualizar os registros de hospedagem e de quarto
    printf("Realizando check-in do cliente.\n");
    int codigoReserva;
    Hospedagem hospedagem;

    printf("Digite o código da reserva para check-in: ");
    scanf("%d", &codigoReserva);
    getchar(); // Limpa buffer de entrada

    // Função fictícia - implementar de acordo com a lógica de negócios
    int encontrado = buscaReserva(codigoReserva, &hospedagem);
    FILE *arquivo = fopen("hospedagens.csv", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de hospedagens.\n");
        return;
    }

    if (encontrado)
    {
        char data_check_in[13];
        printf("Check-in realizado com sucesso!\n");
        DataToString(hospedagem.data_check_in, data_check_in, false);
        fprintf(arquivo, "%d;%s;%s;%s;%s;%f\n", hospedagem.id_reserva, hospedagem.cpf_cliente, data_check_in, "", hospedagem.status, 0.0);
        atualizarStatusQuarto(hospedagem.codigo_quarto, 'I');
    }
    else
    {
        printf("Reserva não encontrada ou já finalizada.\n");
    }
}

void check_out_cliente()
{
    // Implementação para o check-out do cliente
    // Deve calcular o valor total da estadia, atualizar o status do quarto e finalizar a hospedagem
    printf("Realizando check-out do cliente.\n");
    int idReserva;
    printf("Digite o código da reserva para check-out: ");
    scanf("%d", &idReserva);
    getchar(); // Limpa buffer de entrada
    int idQuarto = obterIdQuarto(idReserva);
    double diaria = obterPrecoDiariaQuarto(idQuarto);
    atualizarStatusQuarto(idQuarto, 'A');
    double precoTotal = calcularPrecoTotal(idReserva, diaria);
    finalizarHospedagem(idReserva, precoTotal);
}

void buscar_hospedagens_cliente() {
    printf("Buscando hospedagens do cliente.\n");
    printf("Digite o CPF do cliente: ");
    char cpf[12];
    scanf("%11s", cpf); // Ajuste para ler no máximo 11 caracteres
    getchar(); // Consome o '\n' deixado pelo scanf

    FILE *arquivo = fopen("hospedagens.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de hospedagens.\n");
        return;
    }

    Hospedagem hospedagem;
    char linha[256];
    int encontrou = 0;
    char checkIn[11];
    char checkOut[11];
    char status[20]; // Buffer para status

    printf("Hospedagens para o CPF %s:\n", cpf);
    // Pula a linha do cabeçalho
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d;%11[^;];%10[^;];%10[^;];%19[^;];%lf",
               &hospedagem.id_reserva, hospedagem.cpf_cliente, checkIn, checkOut, status, &hospedagem.preco_total);

        if (strcmp(hospedagem.cpf_cliente, cpf) == 0) {
            encontrou = 1;
            printf("Reserva ID: %d\n", hospedagem.id_reserva);
            printf("Data de check-in: %s\n", checkIn);
            printf("Data de check-out: %s\n", checkOut);
            printf("Status: %s\n", status); // Mostra o status
            printf("Valor pago: %.2f\n\n", hospedagem.preco_total);
        }
    }

    if (!encontrou) {
        printf("Nenhuma hospedagem encontrada para o CPF fornecido.\n");
    }

    fclose(arquivo);
}

void menu_hospedagem()
{
    int opcao;
    do
    {
        printf("\nMenu de Hospedagem\n");
        printf("1. Check-in de cliente\n");
        printf("2. Check-out de cliente\n");
        printf("3 .Buscar hospedagens do cliente\n");
        printf("4. Voltar para o menu principal\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            check_in_cliente();
            break;
        case 2:
            check_out_cliente();
            break;
        case 3:
            buscar_hospedagens_cliente();
            break;
        case 4:
            printf("Retornando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, por favor tente novamente.\n");
        }
    } while (opcao != 9);
}

int buscaReserva(int codigoReserva, Hospedagem *hospedagem)
{
    FILE *arquivo = fopen("reservas.csv", "r");
    if (!arquivo)
    {
        printf("Arquivo reserva.csv não pode ser aberto.\n");
        return 0;
    }

    char linha[256];
    int reservaEncontrada = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        int codigo;
        char cpf[12]; // Tamanho do CPF com espaço para o terminador nulo
        char data_checkin[11], data_checkout[11], tipo_quarto[10];
        int codigo_quarto;

        // Atualizado para ler todos os campos do CSV
        if (sscanf(linha, "%d;%11[^;];%10[^;];%10[^;];%9[^;];%d",
                   &codigo, cpf, data_checkin, data_checkout, tipo_quarto, &codigo_quarto) == 6)
        {
            if (codigo == codigoReserva)
            {
                reservaEncontrada = 1;
                hospedagem->id_reserva = codigo;
                strcpy(hospedagem->cpf_cliente, cpf);
                strcpy(hospedagem->status, "Ativa");
                hospedagem->data_check_in = hoje();
                hospedagem->codigo_quarto = codigo_quarto;
                hospedagem->preco_total = 0.0;
                break;
            }
        }
    }

    fclose(arquivo);
    return reservaEncontrada;
}

void atualizarStatusQuarto(int codigoQuarto, char novoStatus)
{
    FILE *arquivo = fopen("quartos.csv", "r+");
    if (!arquivo)
    {
        printf("Não foi possível abrir o arquivo dos quartos.\n");
        return;
    }

    char linha[256];
    long posicaoAnterior;
    int id, solteiro, casal;
    char tipo[10], status[2];
    float preco;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        posicaoAnterior = ftell(arquivo) - strlen(linha) - 1; // Guarda a posição antes de ler a linha
        sscanf(linha, "%d;%d;%d;%9[^;];%f;%1s", &id, &solteiro, &casal, tipo, &preco, status);

        if (id == codigoQuarto)
        {
            fseek(arquivo, posicaoAnterior, SEEK_SET);
            fprintf(arquivo, "%d;%d;%d;%s;%.2f;%c\n", id, solteiro, casal, tipo, preco, novoStatus);
            break;
        }
    }

    fclose(arquivo);
}

int quantidadeHospedagensCSV()
{
    char nomeArquivo[] = "Hospedagens.csv";
    FILE *csv;
    char linha[1000];
    csv = fopen(nomeArquivo, "r");
    if (csv != NULL)
    {
        // lendo o cabeçalho do arquivo
        fscanf(csv, " %[^\n]s", linha);
        int contadorLinha = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF)
        {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    }
    else
    {
        // arquivo não existe
        return 0;
    }
}

int obterIdQuarto(int idReserva)
{
    FILE *arquivo = fopen("reservas.csv", "r");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir o arquivo de reservas");
        return 0; // Retorna -1 para indicar erro
    }

    char linha[1024];
    int id, codigoQuarto;
    char buffer[1024]; // Buffer para ler os outros campos que não serão utilizados

    // Lê cada linha do arquivo de reservas
    while (fgets(linha, sizeof(linha), arquivo))
    {
        // A função sscanf vai ler o ID da reserva e pular os outros campos até chegar no código do quarto
        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%d", &id, buffer, buffer, buffer, buffer, &codigoQuarto) == 6)
        {
            if (id == idReserva)
            {
                fclose(arquivo);
                return codigoQuarto; // Retorna o ID do quarto
            }
        }
    }

    fclose(arquivo);
    return 0;
}

float obterPrecoDiariaQuarto(int idQuarto)
{
    FILE *arquivo = fopen("quartos.csv", "r");
    if (arquivo == NULL)
    {
        perror("Não foi possível abrir o arquivo de quartos");
        return 0.0f;
    }

    char linha[1024];
    int id;
    int solteiro, casal; // Presumindo que estes são inteiros
    char tipo[10];
    float preco;
    char status[2]; // Presumindo que status é uma string "0" ou "1"

    // Lê cada linha do arquivo de quartos
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "%d;%d;%d;%[^;];%f;%s", &id, &solteiro, &casal, tipo, &preco, status) == 6)
        {
            if (id == idQuarto)
            {
                fclose(arquivo);
                return preco; // Retorna o preço da diária do quarto
            }
        }
    }

    fclose(arquivo);
    return 0.0f; // Retorna 0.0 se o quarto não foi encontrado
}

double calcularPrecoTotal(int idReserva, double diaria)
{
    printf("Abrindo o arquivo de hospedagens...\n");
    FILE *arquivo = fopen("hospedagens.csv", "r");
    if (arquivo == NULL)
    {
        printf("Não foi possível abrir o arquivo de hospedagens.\n");
        return 0.0;
    }

    printf("Procurando pela reserva com ID %d...\n", idReserva);
    char linha[256];
    int id;
    DATA dataCheckIn, dataCheckOut;
    double precoTotal;
    char cpfCliente[12], status[10], dataInStr[11], dataOutStr[11];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%lf", &id, cpfCliente, dataInStr, dataOutStr, status, &precoTotal))
        {
            printf("Linha lida: %s\n", linha);
            if (id == idReserva)
            {
                StringToData(dataInStr, &dataCheckIn);
                dataCheckOut = hoje();       
                int dias = DataDiff(dataCheckOut, dataCheckIn);
                precoTotal = dias * diaria;
                fclose(arquivo);
                return precoTotal;
            }
        }
        else
        {
            printf("Não foi possível ler os dados da linha corretamente.\n");
        }
    }

    fclose(arquivo);
    printf("Nenhuma reserva correspondente encontrada.\n");
    return 0.0;
}

void finalizarHospedagem(int idReserva, double precoTotal)
{
    printf("Iniciando a finalização da hospedagem para a reserva %d.\n", idReserva);

    FILE *arquivoLeitura = fopen("hospedagens.csv", "r");
    FILE *arquivoEscrita = fopen("hospedagem_temp.csv", "w");

    if (!arquivoLeitura || !arquivoEscrita)
    {
        perror("Erro ao abrir arquivos");
        if (arquivoLeitura)
            fclose(arquivoLeitura);
        if (arquivoEscrita)
            fclose(arquivoEscrita);
        return;
    }

    char linha[256];
    int id;
    char linhaAtualizada[256]; // Para armazenar a linha modificada
    DATA dataCheckOut = hoje();
    char dataCheckOutStr[11]; // Formato DD/MM/AAAA
    char cpfCliente[12], dataCheckInStr[11];
    // Converte DATA para string
    DataToString(dataCheckOut, dataCheckOutStr, false); // Certifique-se de que esta função insere a data no formato correto

    bool isHeader = true; // Supõe que a primeira linha é cabeçalho

    while (fgets(linha, sizeof(linha), arquivoLeitura) != NULL)
    {
        if (isHeader)
        {
            // Apenas pula a primeira linha (cabeçalho)
            fputs(linha, arquivoEscrita); // Copia o cabeçalho para o arquivo temporário
            isHeader = false;             // Desativa a flag, todas as próximas linhas são dados
            continue;
        }

        sscanf(linha, "%d;", &id);
        if (id == idReserva)
        {
            sscanf(linha, "%d;%11[^;];%10[^;];", &id, cpfCliente, dataCheckInStr);
            snprintf(linhaAtualizada, sizeof(linhaAtualizada), "%d;%s;%s;%s;Finalizada;%.2f\n",
                     idReserva, cpfCliente, dataCheckInStr, dataCheckOutStr, precoTotal);

            fputs(linhaAtualizada, arquivoEscrita); // Escreve a linha modificada no arquivo temporário
        }
        else
        {
            fputs(linha, arquivoEscrita);
        }
    }

    fclose(arquivoLeitura);
    fclose(arquivoEscrita);

    printf("Atualizações finalizadas. Substituindo o arquivo original pelo temporário.\n");

    // Substitui o arquivo original pelo arquivo temporário atualizado
    remove("hospedagens.csv");
    rename("hospedagem_temp.csv", "hospedagens.csv");

    printf("Hospedagem finalizada com sucesso para a reserva %d.\n", idReserva);
}