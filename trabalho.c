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
              ro0, //endereço do primeiro operando registrador da instrução
              ro1, //endereço do primeiro operando registrador da instrução
              e,
              l,
              g;


int main (){
//ALOCAR MEMÓRIA PARA TESTES
memory [0]= 0x13;
memory [1]= 0x0;
memory [2]= 0x0;
memory [3]= 0x1e;
memory [4]= 0x13;
memory [5]= 0x20;
memory [6]= 0x0;
memory [7]= 0x24;
memory [8]= 0x2;
memory [9]= 0x4;
memory [10]= 0x0;
memory [11]= 0x0;
memory [12]= 0x16;
memory [30]= 0x0;
memory [31]= 0x0;
memory [32]= 0x0;
memory [33]= 0xf;

mbr=0;
printf("mbr inicio: %x\n", mbr);
pc=0;
mar=pc;


//ALOCANDO INSTRUÇÃO NO MBR
mbr= memory[mar++] << 8;             // 0000 0000 0000 0000 0000 0000 0001 0011
mbr= (mbr | memory [mar++]) << 8;    // 0000 0000 0000 0000 0001 0011 0000 0000
mbr= (mbr | memory [mar++]) << 8;
mbr= (mbr | memory [mar++]);
printf("mbr alocado: %08x\n", mbr);


//DECODIFICAÇÃO DA INSTRUÇÃO
ir=mbr >> 24;                       //desloca 24 bits a direita ->> 0000 0000 0000 0000 0000 0000 0001 0011
printf("IR: %02x \n", ir);

ro0=(mbr & 0x00e00000) >>21;       //por tudo está agrupado em grupo de 4 o valor acaba mudando--> 1010=a 101=5
printf("Ro0: %02x\n",ro0); 


mar=(mbr & 0x001fffff);
printf("Mar: %08x\n", mar);


//execução da instrução 
if(ir==0x13){

mbr= memory[mar++] << 8;             
mbr= (mbr | memory [mar++]) << 8;    
mbr= (mbr | memory [mar++]) << 8;
mbr= memory [mar++];



}
return 0;


}






//entrada por arquivo texto que ele irá explicar mais pra frente

//gcc trabalho.c -o a.out -lm
//./a.out