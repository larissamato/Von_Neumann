#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//SERÁ UTILIZADO VARIÁVEIS GLOBAIS
unsigned char memory [6];
unsigned int mbr; //contém a palavra a ser armazenada na memória e recebe a palavra lida
unsigned int mar; //endereço a ser lido ou escrito da memória
unsigned char ir; //opcode da instrução
unsigned char ro0, ro1; //endereço operando registrador da instrução
unsigned int imm; //operando imediato da instrução 
unsigned int pc; //contém o endereço da próxima palavra de instrução a ser buscada na memória 
unsigned char e,l,g; //não sei
unsigned int registradores[8];
unsigned int i=0;

int main (){

}






//entrada por arquivo texto que ele irá explicar mais pra frente

//gcc trabalho.c -o a.out -lm
//./a.out