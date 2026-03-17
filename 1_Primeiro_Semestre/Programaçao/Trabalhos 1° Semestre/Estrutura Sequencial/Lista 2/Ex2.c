#include <stdio.h>

int main() {
  int mes; // variável para armazenar o mês
  printf("Digite o mês (1 a 12): "); // pede ao usuário para digitar o mês
  scanf("%d", &mes); // lê o valor digitado e armazena na variável mes
  if (mes < 1 || mes > 12) { // verifica se o mês é válido
    printf("Mês inválido.\n"); // se não for, imprime uma mensagem de erro
  } else { // se for válido, verifica qual é o trimestre correspondente
    switch (mes) { // usa um switch para cada caso possível de mês
      case 1: case 2: case 3: // se for janeiro, fevereiro ou março
        printf("Primeiro trimestre.\n"); // imprime que é o primeiro trimestre
        break; // sai do switch
      case 4: case 5: case 6: // se for abril, maio ou junho
        printf("Segundo trimestre.\n"); // imprime que é o segundo trimestre
        break; // sai do switch
      case 7: case 8: case 9: // se for julho, agosto ou setembro
        printf("Terceiro trimestre.\n"); // imprime que é o terceiro trimestre
        break; // sai do switch
      case 10: case 11: case 12: // se for outubro, novembro ou dezembro
        printf("Quarto trimestre.\n"); // imprime que é o quarto trimestre
        break; // sai do switch
    }
  }
  return 0; // encerra o programa
}
