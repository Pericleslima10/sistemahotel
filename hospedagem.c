#include "hospedagem.h"
#include "reserva.h"
#include "quartos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (encontrado)
    {

        printf("Check-in realizado com sucesso!\n");
        fprintf(arquivo, "%d;%s;%s;%s;%s;%f\n", hospedagem.id_reserva, hospedagem.cpf_cliente, hospedagem.data_check_in, "", hospedagem.status, 0.0);                 
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
}

void buscar_hospedagens_cliente()
{
    // Implementação para buscar as hospedagens de um cliente
    // Deve pedir o CPF do cliente e mostrar todas as hospedagens relacionadas
    printf("Buscando hospedagens do cliente.\n");
}

void menu_hospedagem()
{
    int opcao;
    do
    {
        printf("\nMenu de Hospedagem\n");
        printf("1. Check-in de cliente\n");
        printf("2. Check-out de cliente\n");
        printf("3. Buscar hospedagens do cliente\n");
        printf("9. Voltar para o menu principal\n");
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
        case 9:
            printf("Retornando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, por favor tente novamente.\n");
        }
    } while (opcao != 9);
}

int buscaReserva(int codigoReserva, Hospedagem *hospedagem) {
    FILE *arquivo = fopen("reservas.csv", "r");
    if (!arquivo) {
        printf("Arquivo reservas.csv não pode ser aberto.\n");
        return 0;
    }

    char linha[256];
    int reservaEncontrada = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        int codigo;
        char cpf[14]; // Tamanho do CPF com espaço para o terminador nulo
        char data_checkin[11], data_checkout[11], tipo_quarto[10];
        int codigo_quarto;
        
        // Atualizado para ler todos os campos do CSV
        if (sscanf(linha, "%d;%13[^;];%10[^;];%10[^;];%9[^;];%d",
                   &codigo, cpf, data_checkin, data_checkout, tipo_quarto, &codigo_quarto) == 6) {
            if (codigo == codigoReserva) {
                reservaEncontrada = 1;
                hospedagem->id_reserva = codigo;
                strcpy(hospedagem->cpf_cliente, cpf);
                // Outros campos podem ser preenchidos conforme necessário
                hospedagem->data_check_in = hoje(); // Atribuição direta assume que hoje() retorna uma struct DATA
                strcpy(hospedagem->status, "Ativa");
                tornarQuartoIndisponivel(codigo_quarto);
                // Presume-se que preço total será calculado em outro ponto do processo
                hospedagem->preco_total = 0.0;
                break;
            }
        }
    }

    fclose(arquivo);
    return reservaEncontrada;
}

void tornarQuartoIndisponivel(int codigoQuarto) {
    FILE *arquivo = fopen("quartos.csv", "r+");
    if (!arquivo) {
        printf("Não foi possível abrir o arquivo dos quartos.\n");
        return;
    }

    char linha[256];
    long posicaoAnterior;
    int id, solteiro, casal, status;
    char tipo[10];
    float preco;

    while (fgets(linha, sizeof(linha), arquivo)) {
        posicaoAnterior = ftell(arquivo) - strlen(linha) - 1; // Guarda a posição antes de ler a linha
        sscanf(linha, "%d;%d;%d;%9[^;];%f;%d", &id, &solteiro, &casal, tipo, &preco, &status);
        
        if (id == codigoQuarto) {
            fseek(arquivo, posicaoAnterior, SEEK_SET); // Retorna à posição inicial da linha
            fprintf(arquivo, "%d;%d;%d;%s;%.2f;0\n", id, solteiro, casal, tipo, preco); // Escreve a linha com status 0
            printf("Quarto %d tornou-se indisponível.\n", codigoQuarto);
            break;
        }
    }

    fclose(arquivo);
}