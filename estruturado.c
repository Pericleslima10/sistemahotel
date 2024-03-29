#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 2

typedef struct {
    int codigo_quarto;
    int camas_solteiro;
    int camas_casal;
    char tipo_quarto[6];
    double preco_diaria;
    char status[1];
} Quarto;

typedef struct {
    char nome_cliente[50];
    char cpf_cliente[13];
    int data_nasc;
    int idade_cliente;
    char endereco[100];
    char cidade[100];
    char estado[2];
} Cliente;

typedef struct {
    int codigo_reserva;
    char cpf_reserva[13];
    int data_checkin;
    int data_checkout;
    char tipo_quarto[6];
    int codigo_quarto;
} Reserva;

typedef struct {
    int codigo_reserva;
    char cpf_cliente[13];
    int data_checkin;
    int data_checkout;
    char status[10];
    double preco_diaria;
} Hospedagem;

void reservas();
void clientes();
void hospedagem();
void quartos1();
void novocliente();
void criarArquivo();
void alterarcliente();
void removercliente();
void novoquarto();
void alterarquarto();

int main() {
    int opcao;

    do {
        printf("\nMENU\n");
        printf("1. Reservas\n");
        printf("2. Clientes\n");
        printf("3. Hospedagem\n");
        printf("4. Quartos\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                //cadastrarQuarto();
                reservas();
                break;
            case 2:
                //listarQuartos();
                clientes();
                break;
            case 3:
                //listarQuartos();
                hospedagem();
                break;
            case 4:
                //listarQuartos();
                quartos1();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);

    return 0;
}

void reservas(){
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

        switch (opcao1) {
            case 1:
                //quartosdisponiveis();
                reservas();
                break;
            case 2:
                //reservarquarto();
                break;
            case 3:
                //cancelarreserva();
                break;
            case 4:
                //buscarreserva();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao1 != 9);
}

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
    
    
    
     FILE *arquivoq = fopen("quartos.csv", "w");
    if (arquivoq == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }
    fprintf(arquivoq, "CODIGO QUARTO\n");
    fclose(arquivoq);
    
    
    
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

void hospedagem(){
    int opcao1;
    do {
        printf("\nMENU\n");
        printf("1. Check-in de cliente\n");
        printf("2. Check-out de cliente\n");
        printf("3. Buscar Hospedagem\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao1);

        switch (opcao1) {
            case 1:
                //quartosdisponiveis();z
                reservas();
                break;
            case 2:
                //reservarquarto();
                break;
            case 3:
                //cancelarreserva();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao1 != 9);
}

   
void quartos1() {
    int opcao1;
    
    // Verifica se o arquivo existe, se não existir, cria-o
    FILE *verificar = fopen("quartos.csv", "r");
    if (verificar == NULL) {
        criarArquivo();
    } else {
        fclose(verificar);
    }
    
    do {
        printf("\nMENU\n");
        printf("1. Novo Quarto\n");
        printf("2. Alterar Quarto\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao1);

        switch (opcao1) {
            case 1:
                novoquarto();
                break;
            case 2:
                alteraquarto();
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
   
    // Abre o arquivo para escrita no modo de adição
    FILE *arquivoquarto = fopen("quartos.csv", "a");
    if (arquivoquarto == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    // Escreve os dados do quarto no arquivo
    fprintf(arquivoquarto, "%d\n", quarto.codigo_quarto);
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
            printf("Digite o novo codigo do quarto: ");
            scanf("%d", &codigo_quarto);

            fseek(arquivoquarto, posicao_inicial, SEEK_SET);

            // Escrevemos os dados atualizados do quarto no arquivo
            fprintf(arquivoquarto, "%d\n", codigo_quarto);
            printf("Quarto com codigo %d alterado com sucesso.\n", codquarto);
            fclose(arquivoquarto);
            return;
        }
        posicao_inicial = ftell(arquivoquarto);
    }

    printf("Quarto com codigo %d não encontrado.\n", codquarto);
    fclose(arquivoquarto);
}
