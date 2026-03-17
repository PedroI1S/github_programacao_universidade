#include <stdio.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_CIDADE 30
#define MAX_UF 3
#define MAX_CEP 9

typedef struct {
    int cod;
    char nome[MAX_NOME];
    char cep[MAX_CEP];
    char cidade[MAX_CIDADE];
    char uf[MAX_UF];
} Cadastro;

// Função para limpar o buffer do stdin
void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    
}

int main() {
    Cadastro c;
    FILE *arq;
    char opcao;

    arq = fopen("cadastro.dat", "ab");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    do {
        printf("Entre com o codigo: ");
        scanf("%d", &c.cod);
        limparBuffer();

        printf("Entre com o nome: ");
        fgets(c.nome, MAX_NOME, stdin);
        c.nome[strcspn(c.nome, "\n")] = '\0';

        printf("Entre com o CEP: ");
        fgets(c.cep, MAX_CEP, stdin);
        c.cep[strcspn(c.cep, "\n")] = '\0';

        printf("Entre com a cidade: ");
        fgets(c.cidade, MAX_CIDADE, stdin);
        c.cidade[strcspn(c.cidade, "\n")] = '\0';

        printf("Entre com o estado (UF): ");
        fgets(c.uf, MAX_UF, stdin);
        c.uf[strcspn(c.uf, "\n")] = '\0';

        if (fwrite(&c, sizeof(Cadastro), 1, arq) != 1) {
            printf("Erro ao gravar registro\n");
            break;
        }

        printf("Deseja inserir outro registro? (S/N): ");
        scanf(" %c", &opcao);
        limparBuffer();
    } while (opcao == 'S' || opcao == 's');
    fclose(arq);
}
