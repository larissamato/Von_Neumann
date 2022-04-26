#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


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
bool flagexecucao=true;
unsigned int flagrepeticao=false;
unsigned int flagguarda=0;

int main (){
//ALOCAR MEMÓRIA PARA TESTES
memory [0]= 0x13;
memory [1]= 0x00;
memory [2]= 0x00;
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
memory [13]= 0x0;
memory [14]= 0x0;
memory [15]= 0x14;
memory [16]= 0x14;
memory [17]= 0x0;
memory [18]= 0x0;
memory [19]= 0x26;
memory [20]= 0x0;
memory [21]= 0x0;
memory [22]= 0x0;
memory [23]= 0x1;
memory [24]= 0x0;
memory [25]= 0x0;
memory [26]= 0x0;
memory [27]= 0x0;
memory [28]= 0x0;
memory [29]= 0x0;
memory [30]= 0x0;
memory [31]= 0x0;
memory [32]= 0x0;
memory [33]= 0xf;
memory [36]= 0x0;
memory [37]= 0x0;
memory [38]= 0x0;
memory [39]= 0x8;

mbr=0;
ir=1;

printf("mbr inicio: %x\n", mbr);



while(flagexecucao){
int i;
i=i+1;
    printf("\t\t\t\t RODADA %d\n", i);
    //ALOCANDO INSTRUÇÃO NO MBR
    mar=pc;
    printf("mar%x\n",mar);
    mbr= memory[mar++] << 8;             // 0000 0000 0000 0000 0000 0000 0001 0011
    mbr= (mbr | memory [mar++]) << 8;    // 0000 0000 0000 0000 0001 0011 0000 0000
    mbr= (mbr | memory [mar++]) << 8;
    mbr= (mbr | memory [mar++]);
    printf("mbr alocado: %08x\n", mbr);


    //DECODIFICAÇÃO DA INSTRUÇÃO
    ir=mbr >> 24;                    //desloca 24 bits a direita ->> 0000 0000 0000 0000 0000 0000 0001 0011
    printf("IR: %02x \n", ir);

    if (ir==0x00){
        printf("Parada!!!\n");
        flagexecucao=false;
    }
    else if(ir==0x01){
        printf("oi");
    }
    else if(ir==0x2 || ir==0x3|| ir==0x4 || ir==0x5 || ir==0x6 || ir==0x7 || ir==0x8 || ir==0x9 || ir==0xa){

        ro0=(mbr & 0x00e00000) >>21; 
        ro1=(mbr & 0x001e0000) >>18; 

    }
    else if(ir==0xb){
        ro0=(mbr & 0x00e00000) >>21; 
    }

    else if (ir==0x13){

        if(flagrepeticao==false)
        {
            ro0=(mbr & 0x00e00000) >>21;       //por tudo está agrupado em grupo de 4 o valor acaba mudando--> 1010=a 101=5
            printf("Ro0: %02x\n",ro0); 
            mar=(mbr & 0x001fffff); //máscara 0000 0000 0001 1111 1111 1111 1111 1111 
            printf("Mar: %08x\n", mar);
        }
        else if (flagrepeticao==true)
        {
            //ro1=(mbr & 0x001e0000) >>18;       //por tudo está agrupado em grupo de 4 o valor acaba mudando--> 1010=a 101=5
            ro1=(mbr & 0x00e00000) >>21;  
            printf("Ro1: %02x\n",ro1);     
            mar=(mbr & 0x001fffff); //máscara 0000 0000 0001 1111 1111 1111 1111 1111 
            printf("Mar: %08x\n", mar);
        }      
    }
     else if(ir==14){
            ro0=(mbr & 0x00e00000) >>21;      
            printf("Ro0: %02x\n",ro0); 
            mar=(mbr & 0x001fffff); 
            printf("Mar: %08x\n", mar);

        }
        else if (ir==0x15 || ir==0x16 || ir==0x17 || ir==0x18 || ir==0x19 || ir==0x1a || ir==0x1b){
        //addi
        ro0=(mbr & 0x00e00000) >>21; 
        printf("Ro0: %02x\n",ro0); 
        imm=(mbr & 0x001fffff);
        printf("Imm: %08x\n", imm);

    }

    //EXECUÇÃO DA INSTRUÇÃO
    if(ir==0x13){

        if(flagrepeticao==false)
        {
            mbr= memory[mar++] << 8;             
            mbr= (mbr | memory [mar++]) << 8;    
            mbr= (mbr | memory [mar++]) << 8;
            mbr= memory [mar++];
            reg[ro0]=mbr;
            flagrepeticao=true;
            printf("reg: %08x\n", reg[ro0]);

            pc +=4;
        }
        else if(flagrepeticao==true)
        {
            mbr= memory[mar++] << 8;             
            mbr= (mbr | memory [mar++]) << 8;    
            mbr= (mbr | memory [mar++]) << 8;
            mbr= memory [mar++];
            reg[ro1]=mbr; 
            printf("reg ro1: %08x\n", reg[ro1]);
           pc +=4;
        }

    }
    else if(ir==0x14)
    {
    mbr=reg[ro0];
    //printf("%08x",mbr); 
    memory [mar++]=mbr>>8; 
    memory [mar++]=mbr>>8;    
    memory [mar++]=mbr>>8;
    memory [mar]=mbr;
    printf("%x",memory[mar]); 
    printf("\n");
    pc+=4;
    
    }
     else if(ir==0x15)
    {
        reg[ro0]=imm;
        printf("final: %08x\n", reg[ro0]);
        pc +=4;
    }  
    else if(ir==0x16)
    {
        reg[ro0]=reg[ro0]+imm;
        printf("final: %08x\n", reg[ro0]);
        pc +=4;
    } 
    else if(ir==0x17)
    {
        reg[ro0]=reg[ro0]-imm;
        printf("final: %08x\n", reg[ro0]);
        pc +=4;
    } 
    else if(ir==0x18)
    {
        reg[ro0]=imm*reg[ro0];
        printf("final: %08x\n", reg[ro0]);
        pc +=4;
    } 
    else if(ir==0x19)
    {
        reg[ro0]=reg[ro0]/imm;
        printf("final: %08x\n", reg[ro0]);
        pc +=4;
    }
      else if(ir==0x1a)
    {   
        printf("teste%x",reg[ro0]);
        reg[ro0]=reg[ro0]<<imm;
        printf("final: %012x\n", reg[ro0]);
        pc +=4;
    }
      else if(ir==0x1b)
    {   
        printf("teste%x",reg[ro0]);
        reg[ro0]=reg[ro0]>>imm;
        printf("final: %012x\n", reg[ro0]);
        pc +=4;
    }
    else if(ir==0x02)
    {
        reg[ro0]=reg[ro1]+reg[ro0];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x03)
    {
        reg[ro0]=reg[ro0]-reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x04)
    {
        reg[ro0]=reg[ro0]*reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x05)
    {
        reg[ro0]=reg[ro0]/reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x06)
    {
       if(reg[ro0]==reg[ro1]){
           e=1;
           printf("Registrador e:%x\n", e);
           pc+=4;
       }else if(reg[ro0]<reg[ro1]){
           l=1;
           g=0;
           e=0;
           printf("Registrador e:%x\n",e);
           printf("Registrador l:%x\n",l);
           printf("Registrador g:%x\n",g);
           pc+=4;
       }else if(reg[ro0]>reg[ro1]){
           l=0;
           g=1;
           e=0;
           printf("Registrador e:%x\n",e);
           printf("Registrador l:%x\n",l);
           printf("Registrador g:%x\n",g);
           pc+=4;
       }
    }

    else if(ir==0x07)
    {
        reg[ro0]=reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
     
    else if(ir==0x08)
    {
        reg[ro0]=reg[ro0]&reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x09)
    {
        reg[ro0]=reg[ro0]|reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x0a)
    {
        reg[ro0]=reg[ro0]^reg[ro1];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    else if(ir==0x0b)
    {
        reg[ro0]=!reg[ro0];
        printf("resultado: %x\n",reg[ro0]);
        pc +=4;
    }
    printf("----------------------------------------------------------------\n");
}
return 0;


}


/*
flagexecucao=true;
while(flagexecucao){
    if(ir==0xa){
        
    }
}
*/

//entrada por arquivo texto que ele irá explicar mais pra frente

//gcc trabalho.c -o a.out -lm
//./a.out