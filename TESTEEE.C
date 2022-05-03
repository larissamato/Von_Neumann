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
char *resultado;
char linha[100];
const char s[2] = ";";
unsigned int contador=0;

void Print() {
    system("clear||cls");
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

void Entrada(){
//Declaração
unsigned int mar2, inteiro, i=0;
unsigned char tipo,valor;
// ABRE O ARQUIVO 
arquivo = fopen("teste.txt", "rt");
// SE HOUVER ALGUM ERRO NA ABERTURA
 if (arquivo == NULL)  
    {
          printf("Problemas na abertura do arquivo\n");
        return;
    }
 i = 1;
while (!feof(arquivo)){ 
    // LÊ AS LINHAS E COLOCA EM UM VETOR DE CARACTER
    resultado = fgets(linha, 100, arquivo);  
    // QUEBRA DE LINHA NA MARCAÇÃO ;
    resultado = strtok(linha, s);
    mar2 = (int)strtol(resultado,NULL,16);
    printf("Linha %d : %s\n",i,linha);
    i++; // CONTAGEM DA LINHA 
}
while(resultado !=NULL) {
    if(contador==1){
        tipo=*resultado;
    }else if(contador==2){
        if(tipo==0x64){
            inteiro=(int) strtol(resultado,NULL,16);
            memory[mar2++] = (inteiro & 0xff000000) >> 24;
            memory[mar2++] = (inteiro & 0x00ff0000) >> 16;
            memory[mar2++] = (inteiro & 0x0000ff00) >> 8;
            memory[mar2]   = (inteiro & 0x000000ff);
        }else{
            //Função para colocar instrução na memória.
        }
    }

           resultado = strtok(NULL ,";");
            contador++;
        }
            contador= 0;
 fclose(arquivo);
}


int main(){
Entrada();
             return 0;
}
    