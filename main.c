#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define NUM_INSTRUCOES 28

typedef struct {
    const char nome[10];
    unsigned int codigo;
    unsigned int formato;
} InstrucaoInfo;

InstrucaoInfo instrucoes[NUM_INSTRUCOES] = {
    {"hlt", 0x00, 0x0000},
    {"nop", 0x01, 0x0000},
    {"add", 0x02, 0x03},
    {"sub", 0x03, 0x03},
    {"mul", 0x04, 0x03},
    {"div", 0x05, 0x03},
    {"cmp", 0x06, 0x03},
    {"movrr", 0x07, 0x03},
    {"and", 0x08, 0x03},
    {"or", 0x09, 0x03},
    {"xor", 0x0a, 0x03},
    {"not", 0x0b, 0x21},
    {"je", 0x0c, 0x21},
    {"jne", 0x0d, 0x21},
    {"jl", 0x0e, 0x21},
    {"jle", 0x0f, 0x21},
    {"jg", 0x10, 0x21},
    {"jge", 0x11, 0x21},
    {"jmp", 0x12, 0x21},
    {"ld", 0x13, 0x21},
    {"st", 0x14, 0x21},
    {"movi", 0x15, 0x21},
    {"addi", 0x16, 0x21},
    {"subi", 0x17, 0x21},
    {"muli", 0x18, 0x21},
    {"divi", 0x19, 0x21},
    {"lsh", 0x1a, 0x21},
    {"rsh", 0x1b, 0x21}
};

//GLOBAL VAR
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

FILE *arquivo;
char *token;
char str[100];
char tipoinstrucao[10];
const char s[2] = ";";
unsigned int contador=0;
char compara[10];
char flag[10];
char flagedimm[10];

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
        printf("  %02x:0x%02x", i, var);
        if (i % 7 == 6) {
            printf("\n");
        }
    }
}

void guardarMemoria(unsigned int mar2 ,unsigned int palavra){
    memory [mar2++]=(palavra>>24) & 0xff; 
    memory [mar2++]=(palavra>>16) & 0xff;    
    memory [mar2++]=(palavra>>8) & 0xff;
    memory [mar2]=palavra & 0xff;
}

void Instrucao(int mar2) {
    char *token1;
    unsigned int count = 0, endImm = 0, tipo;
    unsigned int palavra = 0x00;

    token1 = strtok(token, " ,");

    while (token1) {
        if (count == 0) {
            strcpy(compara, token1);
        } else if (count == 1) {
            palavra = (palavra << 24) | (unsigned int) strtol(token1, NULL, 16);
        } else if (count == 2) {
            endImm = (unsigned int) strtol(token1, NULL, 16);
        }
        token1 = strtok(NULL, " ,");
        count++;
    }

    for (int i = 0; i < NUM_INSTRUCOES; i++) {
        if (strcmp(compara, instrucoes[i].nome) == 0) {
            palavra = (instrucoes[i].codigo << 24) | ((palavra & instrucoes[i].formato) << (32 - __builtin_popcount(instrucoes[i].formato)));
            if (instrucoes[i].formato == 0x21) {
                palavra |= (endImm & 0x001FFFFF);
            }
            guardarMemoria(mar2, palavra);
            return;
        }
    }

    printf("Instrução desconhecida: %s\n", compara);
}

void Entrada(){
    unsigned int mar2=0, inteiro, i=1;
    unsigned int tipopalavra;
    unsigned char tipo,valor;


    arquivo = fopen("teste.txt", "rt");
    if (arquivo == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    

    while (!feof(arquivo)){ 
        token = fgets(str, 100, arquivo);  
        token = strtok(str, s);

        while(token) {
            if(contador==0){
                mar2 = (int)strtol(token,NULL,16);
            }else if (contador==1){
                tipopalavra = (*token=='i') ? 1:0;
            }
            else if(contador==2){
                if(tipopalavra==0){
                    inteiro=(int) strtol(token,NULL,10);
                    memory [mar2++]=(inteiro>>24) & 0xff; 
                    memory [mar2++]=(inteiro>>16) & 0xff;    
                    memory [mar2++]=(inteiro>>8) & 0xff;
                    memory [mar2]=inteiro & 0xff;
                }else{
                Instrucao(mar2);
                }
            }

            token = strtok(NULL ,";");
            contador++;
        }
        contador= 0;
    }
    fclose(arquivo);
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

void executeArithmeticOperation(uint op) {
    switch (op) {
        case 0x02: reg[ro0] += reg[ro1]; break; // add
        case 0x03: reg[ro0] -= reg[ro1]; break; // sub
        case 0x04: reg[ro0] *= reg[ro1]; break; // mul
        case 0x05: reg[ro0] /= reg[ro1]; break; // div
        case 0x08: reg[ro0] &= reg[ro1]; break; // and
        case 0x09: reg[ro0] |= reg[ro1]; break; // or
        case 0x0a: reg[ro0] ^= reg[ro1]; break; // xor
        case 0x0b: reg[ro0] = !reg[ro0]; break; // not
        case 0x15: reg[ro0] = imm; break;       // movi
        case 0x16: reg[ro0] += imm; break;       // addi
        case 0x17: reg[ro0] -= imm; break;       // subi
        case 0x18: reg[ro0] *= imm; break;       // muli
        case 0x19: reg[ro0] /= imm; break;       // divi
        case 0x1a: reg[ro0] <<= imm; break;      // lsh
        case 0x1b: reg[ro0] >>= imm; break;      // rsh
        default: break;
    }
}

void executeComparison(uint op) {
    switch (op) {
        case 0x06:
            if (reg[ro0] == reg[ro1]) { e = 1; l = g = 0; }
            else if (reg[ro0] < reg[ro1]) { l = 1; g = e = 0; }
            else { g = 1; l = e = 0; }
            break;
        case 0x0c: if (e) pc = mar; else pc += 4; break; // je
        case 0x0d: if (!e) pc = mar; else pc += 4; break; // jne
        case 0x0e: if (l) pc = mar; else pc += 4; break; // jl
        case 0x0f: if (e || l) pc = mar; else pc += 4; break; // jle
        case 0x10: if (g) pc = mar; else pc += 4; break; // jg
        case 0x11: if (e || g) pc = mar; else pc += 4; break; // jge
        case 0x12: pc = mar; break; // jmp
        default: break;
    }
}

void executeMemoryOperation(uint op) {
    switch (op) {
        case 0x13:
            if (!flagrepeticao) {
                mbr = (memory[mar++] << 24) | (memory[mar++] << 16) | (memory[mar++] << 8) | memory[mar++];
                reg[ro0] = mbr;
                flagrepeticao = true;
            } else {
                mbr = (memory[mar++] << 24) | (memory[mar++] << 16) | (memory[mar++] << 8) | memory[mar++];
                reg[ro1] = mbr;
                flagrepeticao = false;
            }
            pc += 4;
            break;
        case 0x14:
            mbr = reg[ro0];
            memory[mar++] = (mbr >> 24) & 0xff;
            memory[mar++] = (mbr >> 16) & 0xff;
            memory[mar++] = (mbr >> 8) & 0xff;
            memory[mar] = mbr & 0xff;
            pc += 4;
            break;
        default: break;
    }
}

void Executa() {
    Clique();

    switch (ir) {
        case 0x02: case 0x03: case 0x04: case 0x05: case 0x08: case 0x09: case 0x0a: case 0x0b: case 0x15: case 0x16: case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b:
            executeArithmeticOperation(ir);
            pc += 4;
            break;
        case 0x06: case 0x0c: case 0x0d: case 0x0e: case 0x0f: case 0x10: case 0x11: case 0x12:
            executeComparison(ir);
            break;
        case 0x13: case 0x14:
            executeMemoryOperation(ir);
            break;
        default: break;
    }

    Print();
}

int main (){
  mbr=0;

  printf("mbr inicio: %x\n", mbr);

  while(flagexecucao){
    int i;
    i=i+1;

    Entrada();
    Busca();
    Decodifica();
    Executa();

    printf("----------------------------------------------------------------\n");
  }
  return 0;
}
