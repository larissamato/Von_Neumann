#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//SERÁ UTILIZADO VARIÁVEIS GLOBAIS
unsigned char memory [154]; //memória RAM
unsigned int  mbr, //contém a palavra a ser armazenada na memória e recebe a palavra lida
              mar, //endereço a ser lido ou escrito da memória
              imm, //operando imediato da instrução 
              pc,  //contém o endereço da próxima palavra de instrução a ser buscada na memória 
              reg[8];
unsigned char ir,  //opcode da instrução a ser executada
              ro0, //endereço operando registrador da instrução
              ro1, //endereço operando registrador da instrução
              e,
              l,
              g;


int main (){



}






//entrada por arquivo texto que ele irá explicar mais pra frente

//gcc trabalho.c -o a.out -lm
//./a.out