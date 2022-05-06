#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <math.h>
#include <stdbool.h>

unsigned char memory [154]; //memória RAM
unsigned int  mbr, //contém a palavra a ser armazenada na memória e recebe a palavra lida
              mar, //endereço a ser lido ou escrito da memória
              imm, //operando imediato da instrução 
              pc,  //contém o endereço da próxima palavra de instrução a ser buscada na memória 
              reg[8];
unsigned char ir,  //opcode da instrução a ser executada
              ro0, //endereço do primeiro operando registrador da instrução
              ro1, //endereço do primeiro operando registrador da instrução
              e,
              l,
              g;  
FILE *arquivo;
char *token;
char str[100];
const char s[2] = ";";
const char u[2] = ",";
unsigned int contador=0;

void Print() {
    //system("clear||cls");
    printf("\n\t\t-------------------------- MÁQUINA DE VON NEUMANN ---------------------------\n\n\n");
    printf("CPU:\n");
    printf("R0:  0x%08x \t\tR1:  0x%08x \t\tR2:  0x%08x \t\tR3:  0x%08x\nR4:  0x%08x \t\tR5:  0x%08x \t\tR6:  0x%08x \t\tR7:  0x%08x\nMBR: 0x%08x \t\tMAR: 0x%08x \t\tIMM: 0x%08x \t\tPC:  0x%08x\nIR:  0x%02x \t\t\tRO0: 0x%x \t\t\tRO1: 0x%x\nE:   0x%x \t\t\tL:   0x%x\t\t\tG:   0x%x",reg[0],reg[1],reg[2],reg[3],reg[4],reg[5],reg[6],reg[7],mbr,mar,imm,pc,ir,ro0,ro1,e,l,g);
    int i;
    printf("\n\nMemória:\n");
    for (i = 0; i < 154; i++) {
        short int var = memory[i];
        /*if (var < 0) {
            var = var - 65280;
        }*/
        printf("  %02x:0x%02x", i, var);
        if (i % 7 == 6) {
            printf("\n");
        }
    }
}

void Instrucao (){
    char *token1, ro0;
    unsigned int count =0, controle;

    token1= strtok(token,u);
    while(token1){

        printf("TOKEN INSTRUÇÃO: %s\n",token1);
        token1 = strtok(NULL,",");

    }
}

void Entrada(){
    unsigned int mar2, inteiro, i=1;
    unsigned int tipopalavra;
    unsigned char tipo,valor;


    // ABRE O ARQUIVO 
    arquivo = fopen("teste.txt", "rt");
    if (arquivo == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    

    // PERCORRE ARQUIVO
    while (!feof(arquivo)){ 
        token = fgets(str, 100, arquivo);  
        token = strtok(str, s);
        printf("Linha %d : %s\n",i,token);

        while(token) {
            printf("token: %s\n",token);
            if(contador==0){
                mar2 = (int)strtol(token,NULL,16);
                printf("Print endereço:%i ---- %x\n", mar2,mar2);
            }else if (contador==1){
                tipopalavra = (*token=='i') ? 1:0;
                printf("Print tipo:%i ---- %x\n", tipopalavra,tipopalavra);
            }
            else if(contador==2){
                if(tipopalavra==0){
                    inteiro=(int) strtol(token,NULL,16);
                    memory [mar2++]=(inteiro>>24) & 0x0000000f; 
                    memory [mar2++]=(inteiro>>16) & 0x00000f00;    
                    memory [mar2++]=(inteiro>>8) & 0x000f0000;
                    memory [mar2]=inteiro;
                    printf("Print dado guardado:%x\n", inteiro);
                }else{
                Instrucao();
                }
            }

            token = strtok(NULL ,";");
            contador++;
        }
        contador= 0;
    }
    fclose(arquivo);
}


/*void Alocar(){
    unsigned char *pl1, ro0; // aux recebe ro0
    unsigned int count = 0, memImm;

    pl1 = strtok(pl," ,");
    while(pl1){
        if(count == 0){
            strcpy(mine,pl1);
        }
        if (count== 1){
            ro0 = (int)strtol(pl1,NULL,16);
        }
        if(count == 2){
            memImm = (int)strtol(pl1,NULL,16);
        }
        pl1 = strtok(NULL," ,r");
        count++;
    }
}*/
/*#include <string.h>
#include <stdio.h>

int main () {
   char str[80] = "This is - www.tutorialspoint.com - website";
   const char s[2] = "-";
   char *token;
   
   /* get the first token */
   //token = strtok(str, s);
   
   /* walk through other tokens */
   /*while( token != NULL ) {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0);
}*/

/*#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *pf;
    char string[100];
    if((pf = fopen("arquivo.txt","w")) ==NULL)
    {
        printf("\nNao consigo abrir o arquivo ! ");
        exit(1);
    }
    do
    {
        printf("\nDigite uma nova string. Para terminar, digite <enter>: ");
        gets(string);
        fputs(string, pf);
        putc('\n', pf);
        if(ferror(pf))
        {
            perror("Erro na gravacao");
            fclose(pf);
            exit(1);
        }
    } while (strlen(string) > 0);
    fclose(pf);
}*/

int main(){
    Entrada();
    //Print();
    return 0;
}
    