#include <stdio.h>

typedef struct {
    int conta;
    char nome[20];
    double saldo;
} Cliente;

int main() {
    FILE *f = fopen("dados.dat", "rb+");
    if (!f) f = fopen("dados.dat", "wb+");
    
    int op, pos, num;
    Cliente c;
    if (!f) return 1;

    do {
        printf("MENU \n 1. Cadastrar um novo cliente em uma posicao especifica \n 2. Consultar um cliente pelo numero da conta \n 3. Atualizar o saldo de um cliente \n 4. Encerra conta \n 5. Listar todos os clientes \n 6. Restaurar a leitura do arquivo para repetir a listagem \n 7. Encerrar");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("\nPosicao: "); scanf(" %d", &pos);
                printf("\nConta: ");   scanf(" %d", &c.conta);
                printf("\nNome: ");    scanf(" %s", c.nome);
                printf("\nSaldo: ");   scanf(" %lf", &c.saldo);
                fseek(f, pos * sizeof(Cliente), SEEK_SET);
                fwrite(&c, sizeof(Cliente), 1, f);
                break;

            case 2:
                printf("\nConta: "); scanf(" %d", &num);
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta == num) printf("\nNome: %s | Saldo: %.2f\n", c.nome, c.saldo);
                }
                break;

            case 3:
                printf("\nConta: "); scanf(" %d", &num);
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta == num) {
                        printf("Novo Saldo: "); scanf(" %lf", &c.saldo);
                        fseek(f, -sizeof(Cliente), SEEK_CUR);
                        fwrite(&c, sizeof(Cliente), 1, f);
                        break;
                    }
                }
                break;

            case 4:
                printf("\nPosicao: "); scanf(" %d", &pos);
                c.conta = 0; c.saldo = 0; c.nome[0] = '\0';
                fseek(f, pos * sizeof(Cliente), SEEK_SET);
                fwrite(&c, sizeof(Cliente), 1, f);
                break;

            case 5:
                rewind(f);
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta != 0) printf("\nConta: %d | Nome: %s | Saldo: %.2f\n", c.conta, c.nome, c.saldo);
                }
                break;

            case 6:
                rewind(f);
                printf("\nListagem Repetida\n");
                while(fread(&c, sizeof(Cliente), 1, f)) {
                    if(c.conta != 0) printf("Conta: %d | Nome: %s\n", c.conta, c.nome);
                }
                break;
        }
    } while(op != 7);

    fclose(f);
    return 0;
}
