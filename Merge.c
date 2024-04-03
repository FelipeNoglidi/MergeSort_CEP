#include <stdio.h>
#include <string.h>
#define SRC_FILE "cep_ordenado.dat"

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; 
};

int main (int argc, char **argv) {

    FILE *f;
    Endereco e;
    int c;
    int qt;

    if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

    f = fopen("cep_ordenado.dat", "r");

    if (f == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    fseek(f, 0, SEEK_END );
    int maxReg = ftell(f)/sizeof(Endereco);
    int inicio = 0;
    int fim = maxReg - 1;
    
    printf("Tamanho da Estrutura: %ld\n", sizeof(Endereco));
    c = 0;

    while(inicio <= fim) {
        c++;

        int meio = (inicio + fim)/2;

        fseek(f, meio * sizeof(Endereco), SEEK_SET);
        qt = fread(&e, sizeof(Endereco), 1, f);

        e.logradouro[71] = '\0';

        if (strncmp(argv[1], e.cep, 8) == 0) {

			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n%.2s\n", e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep, e.lixo);
            break;
        }

        else if (strncmp(argv[1], e.cep, 8) > 0 ) { inicio = meio + 1; }

        else { fim = meio -1;}

        if(fim < inicio) {printf("Registro nao encontrado no arquivo.\n");}

    }

    printf("Total lido: %d\n", c);
    fclose(f);
    return 0;
    
}