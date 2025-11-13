#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao para limpar a tela do terminal
void limparTela(){
#ifdef _WIN32 // se caso o sistema for windows ele utiliza esse codigo
    system ("cls");
#else // se for outro sistema coisa usa esse codigo
    system ("clear")
#endif

}

float lerNota (const char *mensagem){ // funcao para ler notas dos alunos
	float nota;
	int verif;

	do {
	    printf("%s",mensagem);
	    verif = scanf("%f", &nota);             // esse trecho verifica se a entrada do usuario e valida como tipo float,
	    if (verif != 1){                        // se caso o usuario digitar uma letra o (verif) limpa o buffer de char (\n)
            printf("digite apenas numeros!\n"); // e repete ate o usuario digitar certo
            while (getchar() != '\n');          //


		}
	}while (verif != 1);

	return nota;
}

void adc() { // funcao para adicionar alunos e suas notas
    char nome[50];
    char situacao [25];
    float n1, n2, n3, media;
    char opcao;

    FILE *arquivo; // abertura de arquivo para inicializar escrita

    do { // loop para fazer a adicao
        arquivo = fopen("bancoDados.txt", "a+"); // abertura em modo a+ ( Abre um arquivo texto para gravação e leitura.
        if (arquivo == NULL) {                   // Os dados serão adicionados no fim do arquivo se ele já existir, ou um novo arquivo será)
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        printf("Digite o nome do aluno:\n");
        scanf(" %[^\n]", nome); // permite nomes com espaço

        n1 = lerNota("digite a nota da NP1\n"); // aqui e usado para escrever as notas na funcao lerNota
        n2 = lerNota("digite a nota da NP2\n");
        n3 = lerNota("digite a nota do PIM\n");

        media = (n1 + n2 + n3) / 3.0; // calculo de medias dos alunos

        // validando se esta aprovado
        if (media <= 5){
            printf("reprovou\n");
            strcpy(situacao, "reprovou");
        }
        else if (media >= 7){
            printf("aprovado\n");
            strcpy(situacao, "aprovado");
        }else {
            printf("recuperacao\n");
             strcpy(situacao, "recuperacao");
        }

        limparTela(); // chamado da funcao de limpar tela do terminal

        printf("Media do aluno:%s :%.2f | situacao: %s\n\n", nome, media, situacao);

        // salva no arquivo
        fprintf(arquivo, "%s %.2f %.2f %.2f %.2f %s\n", nome, n1, n2, n3, media, situacao);

        fclose(arquivo);// aqui ele garante que apos a digitacao o nome e salvo automaticamente

        printf("Deseja adicionar outro aluno? (s/n):\n");
        scanf(" %c", &opcao);
        limparTela();

    } while (opcao == 's' || opcao == 'S'); // aqui serve para adicionar outra vez, caso o usuario digite S ou s o sistema aceita gracas a comparacao

    printf("Todos os alunos foram salvos com sucesso!\n");
}

void ver() {
    char linha[1000], nome[100];
    float n1, n2, n3, media;
    char situacao [25];
    FILE *arquivo;

    arquivo = fopen("bancoDados.txt", "r");// abertura de arquivo no tipo de leitura

    if (arquivo == NULL) { //caso o arquivo nao seja aberto aprace esse erro
        printf("Nenhum aluno cadastrado ainda.\n");
        return;
    }

    printf("\n--- Alunos cadastrados ---\n");
    printf("%-20s | %-6s | %-6s | %-6s | %-6s | %-6s \n", "Nome", "NP1", "NP2", "PIM", "Media","situacao");
    printf("---------------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) { // loop para leitura das linhas dos arquivos
        if (sscanf(linha, "%[^0-9] %f %f %f %f %s", nome, &n1, &n2, &n3, &media, situacao) == 6) {
            nome[strcspn(nome, "0123456789")] = '\0';
            printf("%-20s | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-20s\n", nome, n1, n2, n3, media,situacao);
        }
    }

    fclose(arquivo);
    printf("---------------------------------------------------------------------\n");
}

void menu(){ // funcao menu, serve para chamar as outras funcoes do sistema
 int escolha;

    do { //
        printf("\n--- Menu ---\n");
        printf("1 - Adicionar aluno\n");
        printf("2 - Ver alunos cadastrados\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                limparTela();
                adc();
                break;
            case 2:
                limparTela();
                ver();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default: // caso o usuario digite qualquer coisa diferente ele aparece essa mensagem
                printf("Opcao invalida!\n");
        }
    } while (escolha != 3);

}

int main() {
    menu(); // funcao menu sendo chamada

    return 0;
}
