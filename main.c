#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include<ctype.h>
#define MAX 10000 // quantidade de linhas no arquivo .txt  para ordenação

typedef struct Imagem // nome da estrutura
{
    char *nome_img ;
    int tamanho;
    char *data;
    char *hora;
}dados; // tipo de dado

void lerDados_bubble();
void lerDados_insertion();
void lerDados_selection();
void lerDados_quick();
void bubble (struct Imagem * p_dados, int tam);
void bubble_d(struct Imagem * p_dados, int tam);  // ordenar decrescente
void insertion( struct Imagem *p_dados,int n);
void insertion_d( struct Imagem *p_dados,int n);// ordenar decrescente
void selection( struct Imagem *p_dados, int n);
void selection_d( struct Imagem *p_dados, int n);// ordenar decrescente
int comparador( struct Imagem *valor1  , struct Imagem * valor2);
int comparador_d( struct Imagem *valor1  , struct Imagem * valor2);// ordenar decrescente
int buscaBinaria( struct Imagem *p_dados, int n, int tam);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao=0;
    do
    {
        printf("\n\tALGORITMOS DE ORDENAÇÃO\n");
        printf("\t-------------------------------\n");
        printf("\t1 - BUBBLE SORT\n");
        printf("\t2 - INSERTION SORT\n");
        printf("\t3 - SELECTION SORT\n");
        printf("\t4 - QUICKSORT\n");
        printf("\t5 - SAIR\n");
        printf("\t-------------------------------\n");
        printf("\tEscolha a opção desejada: ");
        scanf("%d",&opcao);
        system("cls");
        switch(opcao)
        {
        case 1:
            system("cls");
            lerDados_bubble();
            system("pause");
            system("cls");
            return main();
            break;
        case 2:
            system("cls");
            lerDados_insertion();
            system("pause");
            system("cls");
            return main();
            break;
        case 3:
            system("cls");
            lerDados_selection();
            system("pause");
            system("cls");
            return main();
            break;
                  break;
        case 4:
            system("cls");
            lerDados_quick();
            system("pause");
            system("cls");
            return main();
            break;
        case 5:
            system("cls");
            printf("\t\t\n\nvocê pediu para sair, fechando programa...\n");
            Sleep(1000);
            exit(0);
            break;
        default:
            printf("\n\nVocê deve escolher uma opção inválida\n\n");
            system("pause");
            system("cls");

        }
    }while(opcao !=5);

    return 0;
}

void lerDados_bubble(){
    int i=0, count=0, busca_tam=0;
    clock_t inicio,fim;
    double time_bubble=0;
    char resp = 's';
    FILE * f, *s; // f= ponteiro para arquivo  e s = ponteiro pra saída do arquivo

    dados * p_dados = malloc( MAX *sizeof(dados));
     srand(time(NULL));
    //dados * p_dados = calloc( MAX, sizeof(dados));
           f= fopen("dados.txt", "r");
            if(f == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            s= fopen("ordenados.txt", "w");
            if(s == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            for(i=0; i<MAX; i++){
                char * nome_img = malloc(sizeof(char)* (MAX+1));
                nome_img[MAX] = '\0';
                int tamanho;
                char  *data = malloc(sizeof(char)* (MAX+1));
                data [MAX] = '\0';
                char * hora = malloc(sizeof(char)* (MAX+1));
                hora [MAX] = '\0';
           fscanf(f, "%s %d %s %s", nome_img, &tamanho, data, hora);

            p_dados[count].nome_img = nome_img;
            p_dados[count].tamanho = tamanho;
            p_dados[count].data = data;
            p_dados[count].hora= hora;
            count++;
        }
        /*printf("\n\n\t----LEITURA DO ARQUIVO---\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for (i =0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }*/
           inicio=clock();
           bubble(p_dados,count);  // chamada da função ordena
           //bubble_d(p_dados,count);  // chamada da função ordenar decrescente
           fim = clock();
           time_bubble =  (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); //((double)(fim-inicio))/CLK_TCK; // caso a função de tempo não funcionar troque
           for(i=0; i<MAX; i++){
            fprintf(s, "%s\t\t%d\t\t %s\t\t %s\n", p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data, p_dados[i].hora);
           }
        printf("\n\n****LEITURA DO ARQUIVO ORDENADOS POR TAMANHO DA IMAGEM KB****\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for(i=0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }
           printf("\n\n");
           printf("\t%3.4f Segundos para Ordenar -> %d imagens por tamanho em  KB com o Bubble Sort\n\n",time_bubble,MAX);
           printf("\nOs dados foram ordenados com sucesso, agora basta abrir diretório na raíz do seu projeto, arquivo foi criado com sucesso \n ");
           printf("\n\n");
           printf("Deseja realizar alguma busca por Imagem (s/n) :");
           scanf(" %c",&resp);
            resp= toupper(resp);
            fflush(stdin);
            printf("\n");
            if(resp == 'S'){
           printf("\nInforme tamanho da imagem que deseja realizar a busca: ");
           scanf("%d",&busca_tam);
           buscaBinaria(p_dados,MAX,busca_tam); // chamada da função busca
            }else{
            system("cls");
            return main();
            }
           fclose(f);
           fclose(s);
}
void lerDados_insertion(){
    int i=0, count=0, busca_tam;
    clock_t inicio,fim;
    double time_insertion=0;
    char resp = 's';
    FILE * f, *s; // f= ponteiro para arquivo  e s = ponteiro pra saída do arquivo

    dados * p_dados = malloc( MAX * sizeof(dados));
     srand(time(NULL));
    //dados * p_dados = calloc( MAX, sizeof(dados));
           f= fopen("dados.txt", "r");
            if(f == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            s= fopen("ordenados.txt", "w");
            if(s == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            for(i=0; i<MAX; i++){
                char * nome_img = malloc(sizeof(char)* (MAX+1));
                nome_img[MAX] = '\0';
                 int tamanho;
                char  *data = malloc(sizeof(char)* (MAX+1));
                data [MAX] = '\0';
                char * hora = malloc(sizeof(char)* (MAX+1));
                hora [MAX] = '\0';

           fscanf(f, "%s %d %s %s", nome_img, &tamanho, data, hora);

            p_dados[count].nome_img = nome_img;
            p_dados[count].tamanho = tamanho;
            p_dados[count].data = data;
            p_dados[count].hora= hora;
            count++;
        }
        /*printf("\n\n\t----LEITURA DO ARQUIVO---\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for (i =0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }*/
           inicio=clock();
           insertion(p_dados, count); // chamada da função ordena
           //insertion_d(p_dados,count);   // chamada da função ordenar decrescente
           fim = clock();
           time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
          for(i=0; i<MAX; i++){
            fprintf(s, "%s\t\t%d\t\t%s\t\t%s \n", p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
           }
        printf("\n\n****LEITURA DO ARQUIVO ORDENADOS POR TAMANHO DA IMAGEM KB****\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
         for(i=0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data, p_dados[i].hora);
        }
           printf("\n\n");
           printf("\t%3.4f Segundos para Ordenar -> %d imagens por tamanho em  KB com o Insertion Sort\n\n",time_insertion,MAX);
           printf("\nOs dados foram ordenados com sucesso, agora basta abrir diretório na raíz do seu projeto, arquivo foi criado com sucesso \n ");
           printf("\n\n");
           printf("Deseja realizar alguma busca por Imagem (s/n) :");
            scanf(" %c",&resp);
            resp= toupper(resp);
            fflush(stdin);
            printf("\n");
            if(resp == 'S'){
           printf("\nInforme tamanho da imagem que deseja realizar a busca: ");
           scanf("%d",&busca_tam);
           buscaBinaria(p_dados,MAX,busca_tam); // chamada da função busca
            }else{
            system("cls");
            return main();
            }
           fclose(f);
           fclose(s);
}
void lerDados_selection(){
    int i=0, count=0, busca_tam=0;
    clock_t inicio,fim;
    double time_selection=0;
    char resp = 's';
    FILE * f, *s; // f= ponteiro para arquivo  e s = ponteiro pra saída do arquivo

    dados * p_dados = malloc( MAX *sizeof(dados));
     srand(time(NULL));
    //dados * p_dados = calloc( MAX, sizeof(dados));
           f= fopen("dados.txt", "r");
            if(f == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            s= fopen("ordenados.txt", "w");
            if(s == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            for(i=0; i<MAX; i++){
                char * nome_img = malloc(sizeof(char)* (MAX+1));
                nome_img[MAX] = '\0';
                int tamanho;
                char  *data = malloc(sizeof(char)* (MAX+1));
                data [MAX] = '\0';
                char * hora = malloc(sizeof(char)* (MAX+1));
                hora [MAX] = '\0';

           fscanf(f, "%s %d %s %s", nome_img, &tamanho, data, hora);

            p_dados[count].nome_img = nome_img;
            p_dados[count].tamanho = tamanho;
            p_dados[count].data = data;
            p_dados[count].hora= hora;
            count++;
        }
        /*printf("\n\n\t----LEITURA DO ARQUIVO---\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for (i =0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }*/
           inicio=clock();
           selection(p_dados, count);  // chamada da função ordena
           //selection_d(p_dados, count);  // chamada da função ordenar decrescente
           fim = clock();
           time_selection =(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
           for(i=0; i<MAX; i++){
            fprintf(s, "%s\t\t%d\t\t%s\t\t%s\n", p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
           }
        printf("\n\n****LEITURA DO ARQUIVO ORDENADOS POR TAMANHO DA IMAGEM KB****\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
         for(i=0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }
           printf("\n\n");
           printf("\t%3.4f Segundos para Ordenar -> %d imagens por tamanho em  KB com o Selection Sort\n\n",time_selection,MAX);
           printf("\nOs dados foram ordenados com sucesso, agora basta abrir diretório na raíz do seu projeto, arquivo foi criado com sucesso \n ");
           printf("\n\n");
           printf("Deseja realizar alguma busca por Imagem (s/n) :");
            scanf(" %c",&resp);
            resp= toupper(resp);
            fflush(stdin);
            printf("\n");
            if(resp == 'S'){
           printf("\nInforme tamanho da imagem que deseja realizar a busca: ");
           scanf("%d",&busca_tam);
           buscaBinaria(p_dados,MAX,busca_tam);
            }else{
            system("cls");
            return main();
            }
           fclose(f);
           fclose(s);
}
void lerDados_quick(){
    int i=0, count=0, busca_tam=0;
    struct Imagem;
    clock_t inicio,fim;
    double time_quick=0;
    char resp = 's';
    FILE * f, *s; // f= ponteiro para arquivo  e s = ponteiro pra saída do arquivo

    dados * p_dados = malloc( MAX *sizeof(dados));
     srand(time(NULL));
    //dados * p_dados = calloc( MAX, sizeof(dados));
           f= fopen("dados.txt", "r");
            if(f == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            s= fopen("ordenados.txt", "w");
            if(s == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }
            for(i=0; i<MAX; i++){
                char * nome_img = malloc(sizeof(char)* (MAX+1));
                nome_img[MAX] = '\0';
                int tamanho;
                char  *data = malloc(sizeof(char)* (MAX+1));
                data [MAX] = '\0';
                char * hora = malloc(sizeof(char)* (MAX+1));
                hora [MAX] = '\0';

           fscanf(f, "%s %d %s %s", nome_img, &tamanho, data, hora);

            p_dados[count].nome_img = nome_img;
            p_dados[count].tamanho = tamanho;
            p_dados[count].data = data;
            p_dados[count].hora= hora;
            count++;
        }
        /*printf("\n\n\t----LEITURA DO ARQUIVO---\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for (i =0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }*/
           inicio=clock();
           qsort(p_dados,MAX,sizeof(dados),comparador);  // chamada da função ordenar
          // qsort(p_dados,MAX,sizeof(dados),comparador_d);  // chamada da função ordenar decrescente
           fim = clock();
           time_quick =(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
          for(i=0; i<MAX; i++){
            fprintf(s, "%s\t\t%d\t\t%s\t\t%s\n", p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
           }
        printf("\n\n****LEITURA DO ARQUIVO ORDENADOS POR TAMANHO DA IMAGEM KB****\n\n");
        printf("#\tNOME\t\tTAMANHO\t\tDATA\t\t\tHORA\n");
        printf("------------------------------------------------------------------------\n");
        for(i=0; i<MAX; i++){
            printf("%d\t%s\t\t%dKB\t\t%s\t\t%s \n",i+1, p_dados[i].nome_img, p_dados[i].tamanho, p_dados[i].data,p_dados[i].hora);
        }
           printf("\n\n");
           printf("\t %3.4f Segundos para Ordenar -> %d imagens por tamanho em  KB com o QuickSort Sort\n\n",time_quick,MAX);
           printf("\nOs dados foram ordenados com sucesso, agora basta abrir diretório na raíz do seu projeto, arquivo foi criado com sucesso \n ");
           printf("\n\n");
           printf("Deseja realizar alguma busca por Imagem (s/n) :");
            scanf(" %c",&resp);
            resp= toupper(resp);
            fflush(stdin);
            printf("\n");
            if(resp == 'S'){
           printf("\nInforme tamanho da imagem que deseja realizar a busca: ");
           scanf("%d",&busca_tam);
           buscaBinaria(p_dados,MAX,busca_tam);
            }else{
            system("cls");
            return main();
            }
           fclose(f);
           fclose(s);
}
void bubble (struct Imagem * p_dados, int tam){
   int i, j;
   struct Imagem tmp;
    for (i = tam-1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            if(p_dados[j].tamanho > p_dados[j+1].tamanho) {
                tmp = p_dados[j];
                p_dados[j] = p_dados[j+1];
                p_dados[j+1] = tmp;
            }
        }
    }
}
void bubble_d(struct Imagem * p_dados, int tam){ // ordenar decrescente
   int i, j;
   struct Imagem tmp;
    for (i = tam-1; i >= 1; i--) {
        for (j = 0; j < i; j++) {
            if(p_dados[j].tamanho < p_dados[j+1].tamanho) {
                tmp = p_dados[j];
                p_dados[j] = p_dados[j+1];
                p_dados[j+1] = tmp;
            }
        }
    }
}
void insertion( struct Imagem *p_dados,int n)
{
    int i, j;
    struct Imagem  aux;
     for(i=1; i<MAX; i++){
            aux = p_dados[i];
            for(j=i-1 ; (j>=0) && (p_dados[j].tamanho > aux.tamanho);){
            p_dados[j+1] = p_dados[j];
            j--;
            }
            p_dados[j+1]= aux;
        }
}
void insertion_d( struct Imagem *p_dados,int n) // ordenar decrescente
{
    int i, j;
    struct Imagem  aux;
     for(i=1; i<MAX; i++){
            aux = p_dados[i];
            for(j=i-1 ; (j>=0) && (aux.tamanho > p_dados[j].tamanho );){
            p_dados[j+1] = p_dados[j];
            j--;
            }
            p_dados[j+1]= aux;
        }
}
void selection( struct Imagem *p_dados, int n){
  int i,j,i_menor;
  struct Imagem temp;

        for (i = 0; i <n-1; i++) {
        i_menor = i;
        for (j = (i+1); j < n; j++) {
            if(p_dados[j].tamanho < p_dados[i_menor].tamanho) {
                i_menor = j;
            }
        }
        if (i != i_menor) {
            temp = p_dados[i];
            p_dados[i] = p_dados[i_menor];
            p_dados[i_menor] = temp;
        }
    }
}
void selection_d( struct Imagem *p_dados, int n){ // ordenar decrescente
  int i,j,i_menor;
  struct Imagem temp;

        for (i = 0; i <n-1; i++) {
        i_menor = i;
        for (j = (i+1); j < n; j++) {
            if(p_dados[j].tamanho > p_dados[i_menor].tamanho) {
                i_menor = j;
            }
        }
        if (i != i_menor) {
            temp = p_dados[i];
            p_dados[i] = p_dados[i_menor];
            p_dados[i_menor] = temp;
        }
    }
}
int comparador( struct Imagem *valor1  , struct Imagem * valor2){
    //int i;
    if(valor1->tamanho  == valor2->tamanho){ // poderia ser tbm -> valor1[i].tamanho  == valor2[i].tamanho
        return;
    }else if ( valor1->tamanho > valor2->tamanho){ //valor1[i].tamanho > valor2[i].tamanho
        return 1;
    }else {
        return -1;
    }
}
int comparador_d( struct Imagem *valor1  , struct Imagem * valor2){ // ordenar decrescente
    //int i;
    if(valor1->tamanho  == valor2->tamanho){ // poderia ser tbm -> valor1[i].tamanho  == valor2[i].tamanho
        return;
    }else if ( valor1->tamanho > valor2->tamanho){ //valor1[i].tamanho > valor2[i].tamanho
        return -1;
    }else {
        return 1;
    }
}
int buscaBinaria( struct Imagem *p_dados, int n, int tam){
    int esq, dir, meio, elem=0;
    esq=0;
    dir= n-1;
    FILE * s;
    s= fopen("ordenados.txt", "r");
            if(s == NULL)
            {
                printf("\n ARQUIVO INCOSISTENTE \n");
                return 1;
            }

    while((esq <= dir) && (!elem)){
        meio = (esq+dir)/2;
            if(p_dados[meio].tamanho == tam){
                elem =1;
            }else if( tam < p_dados[meio].tamanho){
               dir = meio - 1; /* procura na part esquerda*/
            }else{
             esq= meio +1; /* procura na part direita */
              }
        }
        if(elem){
          printf("\n\n** Imagem por tamanho %dKB encontrada **\n\n",p_dados[meio].tamanho);
          printf("posição-> %d  Nome: %s  Tamanho:%dKB  Data:%s  Hora:%s \n\n",meio+1, p_dados[meio].nome_img, p_dados[meio].tamanho, p_dados[meio].data, p_dados[meio].hora);
          }else{
            printf("\n\n **Imagem por Tamanho %dKB não encontrada!** \n\n",tam);
          }
    }

