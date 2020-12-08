// Autor: Rodrigo Mendes Leme                    Numero USP: 3151151
// Curso: computacao                             Data: 7/06/2001
// Professora: Cristina
// Exercicio Programa 1
// Compilador usado: GCC-Linux
// Descricao: ordena em ordem crescente ou decrescente uma ou mais sequencias
//            de numeros inteiros, conforme opcao do usuario.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void ordena_vetores(int *vetores[], int *backup[], int t, int n,
                    double *tempo_insertion, double *tempo_quick,
                    double *tempo_merge, double *tempo_heap);
void restaura(int vetor[], int backup[], int n);
void insertion(int a[], int l, int r);
void quicksort(int a[], int l, int r);
int partition(int a[], int l, int r);
void mergesort(int a[], int l, int r);
void merge(int a[], int l, int m, int r);
void heapsort(int a[], int l, int r);
void rebaixa(int a[], int k, int n);

// Funcao: main

int main(void)
{
  int i,
      j,
      n,              // Tamanho das sequencias
      t,              // Numero de sequencias
      tipo_teste,     // Tipo de teste que sera implementado
      ordem,          // Ordem original das sequencias
      **vetores,      // Vetor que contem as sequencias a serem ordenadas
      **backup;       // Vetor que contem as sequencias originais
  double tempo_insertion,     // Tempo de execucao do insertion sort
         tempo_quick,         // Tempo de execucao do quicksort
         tempo_merge,         // Tempo de execucao do mergesort
         tempo_heap;          // Tempo de execucao do heapsort

  printf("Digite o tamanho das sequencias: ");
  scanf("%d",&n);
  printf("\nTipo de teste (0 = dados ordenados; 1 = dados aleatorios): ");
  scanf("%d",&tipo_teste);
  if (tipo_teste == 0)       // Dados ordenados
  {
    printf("\nOrdem dos dados (0 = crescente; 1 = decrescente): ");
    scanf("%d",&ordem);

    backup     = (int **) malloc(sizeof(int *));
    backup[0]  = (int *) malloc((n + 1) * sizeof(int));
    vetores    = (int **) malloc(sizeof(int *));
    vetores[0] = (int *) malloc((n + 1) * sizeof(int));

    if (ordem == 0)          // Ordem crescente
      for (i = 1; i <= n; i++)
        vetores[0][i] = backup[0][i] = i;
    else                     // Ordem decrescente
      for (i = 1; i <= n; i++)
        vetores[0][i] = backup[0][i] = n - i + 1;

    ordena_vetores(vetores,backup,1,n,&tempo_insertion,&tempo_quick,
                   &tempo_merge,&tempo_heap);
    printf("\nTipo de teste: sequencia ");
    if (ordem == 0)
      printf("crescente\n");
    else
      printf("decrescente\n");
    printf("   n = %d\n",n);
    printf("Tempos de execucao:\n");
    printf("   Insertion sort: %g s\n",tempo_insertion);
    printf("   Quicksort: %g s\n",tempo_quick);
    printf("   Mergesort: %g s\n",tempo_merge);
    printf("   Heapsort: %g s\n",tempo_heap);
    printf("Razoes tempo/complexidade:\n");
    if (ordem == 0)
    {
      printf("   Insertion sort: %g/n = %g/%d = %g\n",tempo_insertion,
             tempo_insertion,n,tempo_insertion / n);
      printf("   Quicksort: %g/sqr(n) = %g/%d = %g\n",tempo_quick,tempo_quick,
             n * n,tempo_quick / (n * n));
    }
    else
    {
      printf("   Insertion sort: %g/sqr(n) = %g/%d = %g\n",tempo_insertion,
             tempo_insertion,n * n,tempo_insertion / (n * n));
      printf("   Quicksort: %g/sqr(n) = %g/%d = %g\n",tempo_quick,tempo_quick,
             n * n,tempo_quick / (n * n));
    }
    printf("   Mergesort: %g/nlogn = %g/%g = %g\n",tempo_merge,tempo_merge,
           n * (log(n) / log(2)),tempo_merge / n * (log(n) / log(2)));
    printf("   Heapsort: %g/nlogn = %g/%g = %g\n",tempo_heap,tempo_heap,
           n * (log(n) / log(2)),tempo_heap / n * (log(n) / log(2)));
  }                          // Dados aleatorios
  else
  {
    srand(time(0));
    printf("\nDigite o numero de testes: ");
    scanf("%d",&t);

    backup = (int **) malloc(t * sizeof(int *));
    for (i = 0; i <= t - 1; i++)
      backup[i] = (int *) malloc((n + 1) * sizeof(int));

    vetores = (int **) malloc(t * sizeof(int *));
    for (i = 0; i <= t - 1; i++)
      vetores[i] = (int *) malloc((n + 1) * sizeof(int));

    for (i = 0; i <= t - 1; i++)
      for (j = 1; j <= n; j++)
        vetores[i][j] = backup[i][j] = (rand() % n) + 1;

    ordena_vetores(vetores,backup,t,n,&tempo_insertion,&tempo_quick,
                   &tempo_merge,&tempo_heap);
    printf("\nTipo de teste: sequencias aleatorias\n");
    printf("   n = %d\n",n);
    printf("   t = %d\n",t);
    printf("Tempos de execucao:\n");
    printf("   Insertion sort: %g s\n",tempo_insertion);
    printf("   Quicksort: %g s\n",tempo_quick);
    printf("   Mergesort: %g s\n",tempo_merge);
    printf("   Heapsort: %g s\n",tempo_heap);
    printf("Razoes tempo/complexidade:\n");
    printf("   Insertion sort: %g/sqr(n) = %g/%d = %g\n",tempo_insertion,
           tempo_insertion,n * n,tempo_insertion / (n * n));
    printf("   Quicksort: %g/nlogn = %g/%g = %g\n",tempo_quick,tempo_quick,
           n * (log(n) / log(2)),tempo_quick / n * (log(n) / log(2)));
    printf("   Mergesort: %g/nlogn = %g/%g = %g\n",tempo_merge,tempo_merge,
           n * (log(n) / log(2)),tempo_merge / n * (log(n) / log(2)));
    printf("   Heapsort: %g/nlogn = %g/%g = %g\n",tempo_heap,tempo_heap,
           n * (log(n) / log(2)),tempo_heap / n * (log(n) / log(2)));
  }
  return 0;
}

// Funcao: ordena_vetores
// Descricao: aplica diversos algoritmos de ordenacao em t vetores de tamanho
//            n, restaurando-os depois atraves de um vetor de backups. Devolve
//            o tempo de execucao para cada algoritmo.

void ordena_vetores(int *vetores[], int *backup[], int t, int n,
                    double *tempo_insertion, double *tempo_quick,
                    double *tempo_merge, double *tempo_heap)
{
  int i;
  clock_t t_f,
          t_i;
  long soma_insertion = 0,
       soma_quick     = 0,
       soma_merge     = 0,
       soma_heap      = 0;

  for (i = 0; i <= t - 1; i++)
  {
    t_i = clock();
    insertion(vetores[i],1,n);
    t_f = clock();
    soma_insertion += (t_f - t_i) / CLOCKS_PER_SEC;
    restaura(vetores[i],backup[i],n);

    t_i = clock();
    quicksort(vetores[i],1,n);
    t_f = clock();
    soma_quick += (t_f - t_i) / CLOCKS_PER_SEC;    
    restaura(vetores[i],backup[i],n);

    t_i = clock();
    mergesort(vetores[i],1,n);
    t_f = clock();
    soma_merge += (t_f - t_i) / CLOCKS_PER_SEC;
    restaura(vetores[i],backup[i],n);

    t_i = clock();
    heapsort(vetores[i],1,n);
    t_f = clock();
    soma_heap += (t_f - t_i) / CLOCKS_PER_SEC;
  }

  *tempo_insertion = soma_insertion / t;
  *tempo_quick     = soma_quick / t;
  *tempo_merge     = soma_merge / t;
  *tempo_heap      = soma_heap / t;
}

// Funcao: restaura
// Descricao: copia os elementos de backup em vetor (ambos de tamanho n).

void restaura(int vetor[], int backup[], int n)
{
  int i;

  for (i = 1; i <= n; i++)
    vetor[i] = backup[i];
}

// Funcao: insertion
// Descricao: ordena um vetor a de inteiros que mora em l..r.

void insertion(int a[], int l, int r)
{
  int i,
      j,
      v,
      t;

  for (i = r; i > l; i--)
    if (a[i] < a[i - 1])
    {
      t        = a[i - 1];
      a[i - 1] = a[i];
      a[i]     = t;
    }
  for (i = l + 2; i <= r; i++)
  {
    j = i;
    v = a[i];
    while (v < a[j - 1])
    {
      a[j] = a[j - 1];
      j--;
    }
    a[j] = v;
  }
}

// Funcao: quicksort
// Descricao: ordena um vetor a de inteiros que mora em l..r.

void quicksort(int a[], int l, int r)
{
  int i;

  if (r <= l)
    return;
  i = partition(a,l,r);
  if (i - l > r - i)
  {
    quicksort(a,i + 1,r);
    quicksort(a,l,i - 1);
  }
  else
  {
    quicksort(a,l,i - 1);
    quicksort(a,i + 1,r);
  }
}

// Funcao: partition
// Descricao: devolve um elemento i tal que de a[l..i - 1] os elementos de a
//            sao <= a[i], e de a[i + 1..r] sao >= a a[i].

int partition(int a[], int l, int r)
{
  int i = l - 1,
      j = r, 
      t,
      v = a[r];

  for (;;)
  {
    while (a[++i] < v);
    while (v < a[--j])
      if (j == l) 
        break;
    if (i >= j)
      break;
    t    = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  t    = a[i];
  a[i] = a[r];
  a[r] = t;
  return i;
}

// Funcao: mergesort
// Descricao: ordena um vetor a de inteiros que mora em l..r.

void mergesort(int a[], int l, int r)
{
  int m = (l + r) / 2;

  if (r <= l)
    return;
  else
  {
    mergesort(a,l,m);
    mergesort(a,m + 1,r);
    merge(a,l,m,r);
  }
}

// Funcao: merge
// Descricao: recebe vetores crescentes a[l..m] e a[m + 1..r] e rearranja o
//            vetor a[l..r] de modo que ele fique crescente.

void merge(int a[], int l, int m, int r)
{
  int aux[100000],
      i,
      j,
      k;

  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];
  for (j = m; j < r; j++)
    aux[r + m - j] = a[j + 1];
  for (k = l; k <= r; k++)
    if (aux[i] < aux[j])
      a[k] = aux[i++];
    else
      a[k] = aux[j--];
}

// Funcao: heapsort
// Descricao: ordena um vetor a de inteiros que mora em l..r.

void heapsort(int a[], int l, int r)
{
  int k,
      t,
      n = r - l + 1,
      *pq = a + l - 1;

  for (k = n / 2; k >= 1; k--)
    rebaixa(pq,k,n);
  while (n > 1)
  {
    t     = pq[1];
    pq[1] = pq[n];
    pq[n] = t;
    rebaixa(pq,1,--n);
  }
}

// Funcao: rebaixa
// Descricao: restaura a condicao de heap do vetor a de n elementos, rebaixando
//            a prioridade do elemento k.

void rebaixa(int a[], int k, int n)
{
  int j,
      t;

  while (2 * k <= n)
  {
    j = 2 * k;
    if (j < n && a[j] < a[j + 1])
      j++;
    if (a[k] >= a[j])
      break;
    t    = a[k];
    a[k] = a[j];
    a[j] = t;
    k    = j;
  }
}
