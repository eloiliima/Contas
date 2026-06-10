#include <stdio.h>

typedef struct {
    int conta;
    char nome[20];
    double saldo;
} Cliente;

int main() {
    FILE *f = fopen("dados.dat", "wb+");
    int op, pos, num;
    Cliente c;

    if (!f) return 1;

    do {
        printf("\n1-Cadastrar em Posição Expecifica \n 2-Consultar Pelo Número da Conta \n 3-Saldo \n  4-Encerrar Cliente \n 5-Listar Clientes \n 6-Repetir Listagem \n 7-Sair\nOpcao: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Posição, Conta, Nome, Saldo: ");
                scanf("%d %d %s %lf", &pos, &c.conta, c.nome, &c.saldo);
                fseek(f, pos * sizeof(Cliente), SEEK_SET);
                fwrite(&c, sizeof(Cliente), 1, f);
                break;

            case 2:
                printf("Digite o Número da Conta: ");
                scanf("%d", &num);
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta == num) printf("Nome: %s | Saldo: %.2f\n", c.nome, c.saldo);
                }
                break;

            case 3:
                printf("Digite o Número da Conta: ");
                scanf("%d", &num);
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta == num) {
                        printf("Novo Saldo: ");
                        scanf("%lf", &c.saldo);
                        fseek(f, -sizeof(Cliente), SEEK_CUR);
                        fwrite(&c, sizeof(Cliente), 1, f);
                        break;
                    }
                }
                break;

            case 4:
                printf("Posicao para remover: ");
                scanf("%d", &pos);
                c.conta = 0;
                fseek(f, pos * sizeof(Cliente), SEEK_SET);
                fwrite(&c, sizeof(Cliente), 1, f);
                break;

            case 5:
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(num != 0) printf("Conta: %d | Nome: %s | Saldo: %.2f\n", c.conta, c.nome, c.saldo);
                }
                break;

            case 6:
                rewind(f);
                printf("Repetir Listagem\n");
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta != 0) printf("Conta: %d | Nome: %s\n", c.conta, c.nome);
                }
                break;
        }
    } while(op != 7);

    fclose(f);
    return 0;
}
