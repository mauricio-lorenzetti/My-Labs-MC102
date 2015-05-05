/* Nome: Miguel Henrique Nicodemus de Souza Pinto 
 * RA: 156777
 * Laboratorio 15a - Bitcoins */

#include <stdio.h>

#define MAX 9
#define TamCodigo 9
   
int calculaSoma(int codigo_verificacao[],int numero_seguranca, int operacoes[], int k);
int verifica(int Codigo[], int Operacoes[], int NSeguranca);

int main()
{
    int flag, i;
    int codigo_verificacao[MAX], numero_seguranca;
    int operacoes[MAX - 1];
    char le[MAX + 1];
        
    scanf("%s", le);
    
    for (i = 0; i < MAX; i++)
    {
        codigo_verificacao[i] = le[i] - '0';
    }    
    scanf("%d", &numero_seguranca);
    
    flag = calculaSoma(codigo_verificacao, numero_seguranca, operacoes, 0);
    
    if (flag)
    {
        printf("Transferencia aceita\n");
    }
    
    else
    {
        printf("Transferencia abortada\n");
    }
    
    return 0;           
}    

int calculaSoma(int codigo_verificacao[],int numero_seguranca, int operacoes[], int k)
{
    int i;
    int testaSoma = 0;
    
    if (k == 8) 
    {   
        testaSoma = verifica(codigo_verificacao, operacoes, numero_seguranca);
        if (testaSoma)
        {
            return 1;
        }               
    }
    else 
    {
        for (i = 0; i < 3; i++)
        {
            operacoes[k] = i;
            if (calculaSoma(codigo_verificacao, numero_seguranca, operacoes, k + 1))
            {
                return 1;
            }
        }  
    }  
    return 0;
}

/*Funcao para verificar se a combinacao encontrada soma o numero de seguranca:*/
int verifica(int Codigo[], int Operacoes[], int NSeguranca){
    int i,Parcela,Soma = 0;
    /*Comecamos sempre com o primeiro digito do codigo:*/
    Parcela = Codigo[0];
    
    /*E agora percorremos o vetor de operacoes:*/
    for(i = 0;i < TamCodigo - 1;i++){
        /*Verificar as possibilidades do vetor operacoes:*/
        switch(Operacoes[i]){
            /*Caso nao tenha operacao, o proximo algarismo faz parte da parcela atual:*/
            case 2:
                /*Adicionar esse novo digito ao numero, mas para fazr isso adequadamente,
                 * precisamos saber o seu sinal:*/
                if (Parcela >= 0){
                    Parcela = Parcela*10 + Codigo[i + 1];
                }else{
                    Parcela = Parcela*10 - Codigo[i + 1];
                }
                break;
            /*caso seja uma soma, adicionamos a parcela que esta sendo calculada para a
             * soma total, e comecamos a calcular a proxima parcela:*/
            case 0:
                /*Atualizar a soma total:*/
                Soma += Parcela;
                /*Recomecar o calculo da parcela com o digito atual:*/
                Parcela = Codigo[i + 1];
                break;
            /*Caso seja um subtracao, adicionamos a parcela que esta sendo calculada para a
             * soma total, e comecamos a calcular a proxima parcela:*/
            case 1:
                /*Atualizar a soma total:*/
                Soma += Parcela;
                /*Recomecar o calculo da parcela com o digito atual negativo:*/
                Parcela = -Codigo[i + 1];
                break;
        
        }
    }
    Soma += Parcela;
    printf("Soma: %d\n", Soma);
    /*Terminado o loop na variavel soma, temos a soma das parcelas para a combinacao
     * de operacoes encontradas, verificamos se eh igual ao numero de seguranca:*/
     if (Soma == NSeguranca)
        return 1;
     
     return 0;
}