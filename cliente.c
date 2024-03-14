

#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 2

void clientes(){
	
    int numClientes = 0;
    int opcao1;

    // Verifica se o arquivo existe, se não existir, cria-o
    FILE *verificar = fopen("clientes.csv", "r");
    if (verificar == NULL) {
        criarArquivo();
    } else {
        fclose(verificar);
    }

    do {
        printf("\nMENU\n");
        printf("1. Novo Cliente\n");
        printf("2. Alterar Cliente\n");
        printf("3. Remover Cliente\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao1);
        getchar();

        switch (opcao1) {
            case 1:
                novocliente();
                break;
            case 2:
                alterarcliente();
                break;
            case 3:
                removercliente();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao1 != 9);
}

void novocliente() {
    Cliente cliente;

    printf(" Digite o nome do cliente Nome: ");
    scanf("%s", cliente.nome_cliente);
    
    printf("Digite o cpf do cliente CPF: ");
    scanf("%s", cliente.cpf_cliente);
    
    printf("Data de Nascimento do cliente ");
    scanf("%d", &cliente.data_nasc);
    
    printf("Digite a idade do cliente: ");
    scanf("%d", &cliente.idade_cliente);

	printf("Digite o endereço do cliente: ");
    scanf("%s",cliente.endereco);
    
    printf("Digite a cidade do cliente: ");
    scanf("%s", cliente.cidade);
    
      printf("Digite a UF do estado do cliente  ");
    scanf("%s", cliente.estado);



    // Abre o arquivo para escrita no modo de adição
    FILE *arquivo = fopen("clientes.csv", "a");
    if (arquivo == NULL) {//verifica se é possivel abrir o arquivo
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    // Escreve os dados do cliente no arquivo
    fprintf(arquivo, "%s;%s;%d;%d;%s;%s;%s\n", cliente.nome_cliente, cliente.cpf_cliente, cliente.data_nasc,cliente.idade_cliente,cliente.endereco,cliente.cidade,cliente.estado);
    fclose(arquivo);
    

}

void criarArquivo() {
	//verica se o arquivo ja existi
    FILE *arquivo = fopen("clientes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");//indica o retorno da função fopen se for null erro ao criar o arquivo
        exit(1);
    }
    fprintf(arquivo, "NOME;CPF;DATA DE NASCIMENTO;IDADE;ENDERECO;CIDADE;ESTADO\n");//
    fclose(arquivo);
    
  
}

void alterarcliente() {
    char cpf[14];
    printf("Informe o CPF do cliente que deseja alterar: ");
    fflush(stdin); // Limpa o buffer do teclado
    fgets(cpf, sizeof(cpf), stdin); // Lê o CPF
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

    FILE *arquivo = fopen("clientes.csv", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[100]; // Linha temporária para armazenar cada linha do arquivo
    char cpf_cliente[13];
    long int posicao_inicial;

    // Armazenamos a posição inicial do arquivo
    posicao_inicial = ftell(arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Analisamos a linha para obter o CPF do cliente
        sscanf(linha, "%*[^;];%[^;];", cpf_cliente);
        if (strcmp(cpf_cliente, cpf) == 0) {
            // Se encontrarmos o CPF, permitimos a alteração
            
            
            char nome_cliente[50];
    		char cpf_cliente[13];
		    int data_nasc;
		    int idade_cliente;
		    char endereco[100];
		    char cidade[100];
		    char estado[2];
           
		    printf(" Digite o nome do cliente Nome: ");
		    scanf("%s", nome_cliente);
		    
		    printf("Digite o cpf do cliente CPF: ");
		    scanf("%s", cpf_cliente);
		    
		    printf("Data de Nascimento do cliente ");
		    scanf("%d", &data_nasc);
		    
		    printf("Digite a idade do cliente: ");
		    scanf("%d", &idade_cliente);
		
			printf("Digite o endereço do cliente: ");
		    scanf("%s",endereco);
		    
		    printf("Digite a cidade do cliente: ");
		    scanf("%s", cidade);
		    
		    printf("Digite a UF do estado do cliente  ");
		    scanf("%s", estado);
		           


            // Movemos o ponteiro do arquivo para a posição correta
            fseek(arquivo, posicao_inicial, SEEK_SET);

            // Escrevemos os dados atualizados do cliente no arquivo
            fprintf(arquivo, "%s;%s;%d;%d;%s;%s;%s\n", nome_cliente, cpf_cliente, data_nasc,idade_cliente,endereco,cidade,estado);

            printf("Cliente com CPF %s alterado com sucesso.\n", cpf);
            fclose(arquivo);
            return;
        }
        // Atualizamos a posição inicial para a próxima linha
        posicao_inicial = ftell(arquivo);
    }

    printf("Cliente com CPF %s não encontrado.\n", cpf);
    fclose(arquivo);
}

void removercliente() {
    char cpf[14];
    printf("Informe o CPF do cliente que deseja remover: ");
    fflush(stdin); // Limpa o buffer do teclado
    fgets(cpf, sizeof(cpf), stdin); // Lê o CPF
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha

    // Abre o arquivo para leitura
    FILE *arquivo_entrada = fopen("clientes.csv", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }

    // Abre um arquivo temporário para escrita
    FILE *arquivo_temporario = fopen("temporario.csv", "w");
    if (arquivo_temporario == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        exit(1);
    }

    char linha[100]; // Linha temporária para armazenar cada linha do arquivo
    char cpf_cliente[14];
    while (fgets(linha, sizeof(linha), arquivo_entrada) != NULL) {
        sscanf(linha, "%*[^;];%[^;];", cpf_cliente); // Extrai o CPF da linha

        // Se o CPF na linha for diferente do CPF a ser removido, escreve no arquivo temporário
        if (strcmp(cpf_cliente, cpf) != 0) {
            fprintf(arquivo_temporario, "%s", linha);
        }
    }

    // Fecha os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_temporario);

    // Remove o arquivo original
    remove("clientes.csv");
    // Renomeia o arquivo temporário para o nome do arquivo original
    rename("temporario.csv", "clientes.csv");

    printf("Cliente com CPF %s removido com sucesso.\n", cpf);
}





