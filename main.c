#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *arquivo;
char *resultado;
char linha[100];
const char s[2] = ";";
unsigned int contador=0;

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
            printf("Print TESTE:%d", inteiro);
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

void Clique() {
    int value;
    printf("\nPressione ENTER");

    do {
        value = getchar();
    } while (value != '\n'); // 13 é o codigo ASCII do ENTER
}

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

void Busca (){
    Print();
    Clique();
    mar=pc;
    mbr= memory[mar++] << 8;            
    mbr= (mbr | memory [mar++]) << 8;    
    mbr= (mbr | memory [mar++]) << 8;
    mbr= (mbr | memory [mar++]);
    ir=mbr >> 24;  
    Print();
}

void Decodifica(){
    Print();
    Clique();
     if (ir==0x00){
        flagexecucao=false;
        printf("Programa finalizado! Aperte enter para sair!");
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
    Print();
}
void Executa (){
    Clique();
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
    Print();
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
    Busca();
    Decodifica();
    Executa();

    printf("----------------------------------------------------------------\n");
}
return 0;
}


//gcc trabalho.c -o a.out -lm
//./a.out