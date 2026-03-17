#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  int numero_magico, chute;

  // Define a semente para gerar números aleatórios
  srand(time(NULL));

  // Gera um número aleatório entre 0 e 10
  numero_magico = rand() % 11;

  printf("Adivinhe o número mágico entre 0 e 10!\n");

  do {
    printf("Digite um número: ");
    scanf("%d", &chute);

    if (chute == numero_magico) {
      printf("Certo! %d é o número mágico.\n", numero_magico);
    } else if (chute > numero_magico) {
      printf("Errado, muito alto.\n");
    } else {
      printf("Errado, muito baixo.\n");
    }
  } while (chute != numero_magico);

  return 0;
}
