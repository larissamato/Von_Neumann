# Introdução

Essa implementação simula uma CPU com o conjunto de instruções ISA (Instruction Set Architecture), ele mostra o conteúdo dos registradores no fim de cada ciclo de instrução da Máquina de von Neumann ao ser clicado enter. 

## Diagrama da CPU com os registradores arquiteturais:

![](https://github.com/larissamato/Von_Neumann/blob/master/imagens/diagrama.png)

## Função de cada registrador arquitetural:

1. **MBR – Memory Buffer Register**– contém a palavra a ser armazenada na memória. Também é o registrador usado para receber uma palavra lida da memória. Todo o tráfego de e para a memória RAM deve passar pelo MBR.
2. **MAR – Memory Address Register** – especifica o endereço de memória da palavra a ser lida da ou escrita na memória. Todo endereço de memória deve ser indicado nesse registrador antes da execução da instrução. 
3. **IR – Instruction Register** – contém o opcode da instrução a ser executada. 
4. **RO0 – Register Operand 0** – contém o endereço do primeiro operando registrador da instrução. 
5. **RO1 – Register Operand 1** – contém o endereço do segundo operando registrador da instrução. 
6. **IMM – Immediate** – contém o operando imediato da instrução.  
7. **PC – Program Counter** – contém o endereço da próxima palavra de instrução a ser buscada na memória. Caso não haja nenhum desvio, halt ou nop, o PC deve ser incrementado em cada ciclo de instrução. 
8.  **E, L e G** – registradores internos que armazenam as flags ‘equal to’, ‘lower than’ e ‘greater than’.
9. **r0 a r7** – registradores de propósito-geral (GPRs) utilizados para manter temporariamente os operandos na ALU. 

## Nomeclatura do conjunto de instruções: 

![](https://github.com/larissamato/Von_Neumann/blob/master/imagens/instru%C3%A7%C3%B5es.png)

![](https://github.com/larissamato/Von_Neumann/blob/master/imagens/instru%C3%A7%C3%B5es2.png)

## Codificação das instruções:

![](https://github.com/larissamato/Von_Neumann/blob/master/imagens/codifica%C3%A7%C3%A3o.png)

## Exemplo e binário e hexadecimal:

![](https://github.com/larissamato/Von_Neumann/blob/master/imagens/exemplo.png)