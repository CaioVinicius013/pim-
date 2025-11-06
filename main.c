#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcao para limpar a tela do terminar
void limparTela(){
#ifdef _WIN32 // se caso o sistema for windows ele utiliza esse codigo
    system ("cls");
#else // se for outra coisa usa esse codigo
    system ("clear")
#endif

}

float lerNota (const char *mensagem){
	float nota;
	int verif;

	do {
	    printf("%s",mensagem);
	    verif = scanf("%f", &nota);
	    if (verif != 1){
            printf("digite apenas numeros!\n");
            while (getchar() != '\n');


		}
	}while (verif != 1);

	return nota;
}

void adc() {
    char nome[50];
    char situacao [25];
    float n1, n2, n3, media;
    char opcao;

    FILE *arquivo;



    do {
        arquivo = fopen("bancoDados.txt", "a+");
        if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
        }
        printf("Digite o nome do aluno:\n");
        scanf(" %[^\n]", nome); // permite nomes com espaço

        n1 = lerNota("digite a nota da NP1");
        n2 = lerNota("digite a nota da NP2");
        n3 = lerNota("digite a nota do PIM");

        media = (n1 + n2 + n3) / 3.0;

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



        limparTela();

        printf("Media do aluno:%s :%.2f | situacao: %s\n\n", nome, media, situacao);

        // salva no arquivo
        fprintf(arquivo, "%s %.2f %.2f %.2f %.2f %s\n", nome, n1, n2, n3, media, situacao);


        fclose(arquivo);// aqui ele garante que apos a digitacao o nome e salvo automaticamente
        printf("Deseja adicionar outro aluno? (s/n):\n");
        scanf(" %c", &opcao);
        limparTela();

    } while (opcao == 's' || opcao == 'S');


    printf("Todos os alunos foram salvos com sucesso!\n");
}

void ver() {
    char linha[200], nome[100];
    float n1, n2, n3, media;
    FILE *arquivo;

    arquivo = fopen("bancoDados.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum aluno cadastrado ainda.\n");
        return;
    }

    printf("\n--- Alunos cadastrados ---\n");
    printf("%-20s | %-6s | %-6s | %-6s | %-6s | %-6s \n", "Nome", "NP1", "NP2", "PIM", "Media","situacao");
    printf("---------------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%[^0-9] %f %f %f %f", nome, &n1, &n2, &n3, &media) == 5) {
            nome[strcspn(nome, "0123456789")] = '\0';
            printf("%-20s | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", nome, n1, n2, n3, media);
        }
    }

    fclose(arquivo);
    printf("---------------------------------------------------------------------\n");
}

void menu(){
 int escolha;

    do {
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
            default:
                printf("Opçao invalida!\n");
        }
    } while (escolha != 3);

}

int main() {
    menu();

    return 0;
}
