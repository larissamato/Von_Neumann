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
memory [4]= 0x16;
memory [5]= 0x0;
memory [6]= 0x0;
memory [7]= 0x14;
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



for(int i=0; i<2;i++){
    //ALOCANDO INSTRUÇÃO NO MBR
    mar=pc;
    mbr= memory[mar++] << 8;             // 0000 0000 0000 0000 0000 0000 0001 0011
    mbr= (mbr | memory [mar++]) << 8;    // 0000 0000 0000 0000 0001 0011 0000 0000
    mbr= (mbr | memory [mar++]) << 8;
    mbr= (mbr | memory [mar++]);
    printf("mbr alocado: %08x\n", mbr);


    //DECODIFICAÇÃO DA INSTRUÇÃO
    ir=mbr >> 24;                           //desloca 24 bits a direita ->> 0000 0000 0000 0000 0000 0000 0001 0011
    printf("IR: %02x \n", ir);

    //IF PARA O LOAD
    if (ir==0x13){
        ro0=(mbr & 0x00e00000) >>21;       //por tudo está agrupado em grupo de 4 o valor acaba mudando--> 1010=a 101=5
        printf("Ro0: %02x\n",ro0); 
        mar=(mbr & 0x001fffff); //máscara 0000 0000 0001 1111 1111 1111 1111 1111 
        printf("Mar: %08x\n", mar);
    }else if (ir==0x16){
        //addi
        ro0=(mbr & 0x00e00000) >>21; 
        printf("Ro0 segunda: %02x\n",ro0); 
        imm=(mbr & 0x001fffff);
        printf("Imm segunda: %08x\n", imm);

    }

    //EXECUÇÃO DA INSTRUÇÃO
    if(ir==0x13){

    mbr= memory[mar++] << 8;             
    mbr= (mbr | memory [mar++]) << 8;    
    mbr= (mbr | memory [mar++]) << 8;
    mbr= memory [mar++];
    reg[ro0]=mbr;

    printf("reg: %08x\n", reg[ro0]);
    pc +=4;
    } else if(ir==0x16){
        reg[ro0]=imm+reg[ro0];
        pc +=4;
        printf("final: %08x\n", reg[ro0]);

    }

}
return 0;


}


/*



//entrada por arquivo texto que ele irá explicar mais pra frente

//gcc trabalho.c -o a.out -lm
//./a.out