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


void Print() {
    system("clear||cls");
    printf("\n                      Máquina de Von Neuman\n\n");
    //printf("Estágio: %s\n", phase);
    printf(
            "%s: 0x%x%10s: 0x%x%10s: 0x%x%10s: "
            "0x%x%10s: 0x%x%10s: 0x%x%10s: %d%10s: "
            "0x%x%10s: 0x%x%10s: 0x%x%10s: 0x%x"
            "%10s :%c%10s :%c%10s :%c",
            "R0", reg[0],
            "R1", reg[1],
            "R2", reg[2],
            "R3", reg[3],
            "RO0", ro0,
            "RO1", ro1,
            "\nIR", ir,
            "MBR", mbr,
            "MAR", mar,
            "IMM", imm,
            "PC", pc,
            "\nE", e,
            "L", l,
            "G", g);
    int p;
    printf("\n\nMemória:\n");
    for (p = 0; p < 154; p++) {
        short int mem = memory[p];
        if (mem < 0) {
            mem = mem - 65280;
        }
        printf("  %03x:0x%03x", p, mem);
        if (p % 7 == 6) {
            printf("\n");
        }
    }
}

void Busca (){
    mar=pc;
    mbr= memory[mar++] << 8;            
    mbr= (mbr | memory [mar++]) << 8;    
    mbr= (mbr | memory [mar++]) << 8;
    mbr= (mbr | memory [mar++]);
    ir=mbr >> 24;  
}

void Decodifica(){
     if (ir==0x00){
        flagexecucao=false;
    }else if(ir==0x01){
        pc+=1;
    }else if(ir==0x2 || ir==0x3|| ir==0x4 || ir==0x5 || ir==0x6 || ir==0x7 || ir==0x8 || ir==0x9 || ir==0xa){
        ro0=(mbr & 0x00e00000) >>21; 
        ro1=(mbr & 0x001e0000) >>18; 

    }else if(ir==0xb){
        ro0=(mbr & 0x00e00000) >>21; 

    }else if (ir==0xc || ir==0xd || ir==0xe || ir==0xf || ir==0x10 || ir==0x11 || ir==0x12){
        mar=(mbr & 0x001fffff); 

    }else if (ir==0x13){
        if(flagrepeticao==false)
        {
            ro0=(mbr & 0x00e00000) >>21; 
            mar=(mbr & 0x001fffff);
        }
        else if (flagrepeticao==true)
        {
            ro1=(mbr & 0x00e00000) >>21;      
            mar=(mbr & 0x001fffff);
        } 

    }else if(ir==0x14){
            ro0=(mbr & 0x00e00000) >>21;      
            mar=(mbr & 0x001fffff); 
            
    }else if (ir==0x15 || ir==0x16 || ir==0x17 || ir==0x18 || ir==0x19 || ir==0x1a || ir==0x1b){
        ro0=(mbr & 0x00e00000) >>21; 
        imm=(mbr & 0x001fffff);
    }
}
void Executa (){
    //add
     if(ir==0x02){
        reg[ro0]=reg[ro1]+reg[ro0];
        pc +=4;}
    //sub
    else if(ir==0x03){
        reg[ro0]=reg[ro0]-reg[ro1];
        pc +=4;}
    //mul
    else if(ir==0x04){
        reg[ro0]=reg[ro0]*reg[ro1];
        pc +=4;}
    //div
    else if(ir==0x05){
        reg[ro0]=reg[ro0]/reg[ro1];
        pc +=4;}
    //cmp
    else if(ir==0x06){
       if(reg[ro0]==reg[ro1]){
           e=1;
           pc+=4;
       }else if(reg[ro0]<reg[ro1]){
           l=1;
           g=0;
           e=0;
           pc+=4;
       }else if(reg[ro0]>reg[ro1]){
           l=0;
           g=1;
           e=0;
           pc+=4;
       }
    }
    //movr
    else if(ir==0x07){
        reg[ro0]=reg[ro1];
        pc +=4;}
    //and
    else if(ir==0x08){
        reg[ro0]=reg[ro0]&reg[ro1];
        pc +=4;}
    //or
    else if(ir==0x09){
        reg[ro0]=reg[ro0]|reg[ro1];
        pc +=4;}
    //xor
    else if(ir==0x0a){
        reg[ro0]=reg[ro0]^reg[ro1];
        pc +=4;}
    //not
    else if(ir==0x0b){
        reg[ro0]=!reg[ro0];
        pc +=4;}
    //je
    else if(ir==0x0c){   
        if(e==1){
        pc=mar;
        }else {
        pc+=4;
        }
    }
    //jne
    else if(ir==0x0d){
       if(e==0){
        pc=mar;
        }else{
        pc+=4;
        }
    }
    //jl
    else if(ir==0x0e){
        if(l==1){
        pc=mar;
        }else{
        pc+=4;
        }
    }
    //jle
    else if(ir==0x0f){
        if(e==1 || l==1){
        pc=mar;
        }else{
        pc+=4;
        }
    }
    //jg
    else if(ir==0x10){
        if(g==1){
        pc=mar;
        }else{
        pc+=4;
        }
    }
    //jge
    else if(ir==0x11){
        if(e==1 || g==1){
        pc=mar;
        }else{
        pc+=4;
        }
    }
    //jmp
    else if(ir==0x12){
        pc=mar;
    }
    //load
    else if(ir==0x13){
        if(flagrepeticao==false)
        {
            mbr= memory[mar++] << 8;             
            mbr= (mbr | memory [mar++]) << 8;    
            mbr= (mbr | memory [mar++]) << 8;
            mbr= memory [mar++];
            reg[ro0]=mbr;
            flagrepeticao=true;
            pc +=4;
        }
        else if(flagrepeticao==true)
        {
            mbr= memory[mar++] << 8;             
            mbr= (mbr | memory [mar++]) << 8;    
            mbr= (mbr | memory [mar++]) << 8;
            mbr= memory [mar++];
            reg[ro1]=mbr; 
            pc +=4;
        }
    }
    //store
    else if(ir==0x14){
    mbr=reg[ro0];
    memory [mar++]=(mbr>>24) & 0x0000000f; 
    memory [mar++]=(mbr>>16) & 0x00000f00;    
    memory [mar++]=(mbr>>8) & 0x000f0000;
    memory [mar]=mbr;
    pc+=4;
    
    }
    //movi
     else if(ir==0x15){
        reg[ro0]=imm;
        pc +=4;
    }  
    //addi
    else if(ir==0x16){
        reg[ro0]=reg[ro0]+imm;
        pc +=4;
    } 
    //subi
    else if(ir==0x17){
        reg[ro0]=reg[ro0]-imm;
        pc +=4;
    } 
    //muli
    else if(ir==0x18){
        reg[ro0]=imm*reg[ro0];
        pc +=4;
    } 
    //divi
    else if(ir==0x19){
        reg[ro0]=reg[ro0]/imm;
        pc +=4;
    }
    //lsh
    else if(ir==0x1a){   
        reg[ro0]=reg[ro0]<<imm;
        pc +=4;
    }
    //rsh
    else if(ir==0x1b){   
        reg[ro0]=reg[ro0]>>imm;
        pc +=4;
    }
}

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
memory [20]= 0x1;
memory [21]= 0x0;
memory [22]= 0x0;
memory [23]= 0x0;
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
memory [40]= 0x0;
memory [41]= 0x0;
memory [42]= 0x0;
memory [43]= 0x0;
memory [44]= 0x0;
mbr=0;

printf("mbr inicio: %x\n", mbr);

while(flagexecucao){
int i;
i=i+1;

    printf("\t\t\t\t RODADA %d\n", i);
    Print();
    Busca();
    Decodifica();
    Executa();

    printf("----------------------------------------------------------------\n");
}
return 0;
}


//gcc trabalho.c -o a.out -lm
//./a.out