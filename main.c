#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 1000 /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, unsigned int n) {
    int tabr[n];
    for (int i = 0; i < n; i++)
    {
        tabr[i] = i+ rand() % 34324632;
    }
    // TODO: implement
}

void fill_decreasing(int *t, unsigned int n) {
    int pom;
    pom = n + 1;
    int tabm[n];
    for (int i = 0; i < n; i++)
    {
        tabm[i] = pom;
        pom -= 1;
    }// TODO: implement
}

void fill_vshape(int *t, unsigned int n) {
   int pom = 0;
   int taba[n];
    for (int i = n; i > 0; i--)
    {
        if (n % 2 == 0)
        {
            if (i <(n / 2))
            {
                pom += 1;
                taba[i] = pom;

            }
            if (i >= (n / 2))
            {
                pom -= 1;
                taba[i] = pom;
            }
        }
        else
        {
            if (i <= (n / 2))
            {
                pom += 1;
                taba[i] = pom;

            }
            if (i > (n / 2))
            {
                pom -= 1;
                taba[i] = pom;
            }
        } // TODO: implement
}

void selection_sort(int *t, unsigned int n) {
  int k;
  int tab[n];
    for( int i = 0; i < n; i++ )
    {
        k = i;
        for( int j = i + 1; j < n; j++ )
            if( tab[ j ] < tab[ k ] )
                k = j;

        swap( tab[ k ], tab[ i ] );
    }  // TODO: implement
}

void insertion_sort(int *t, unsigned int n) {
   int pom, j, tab[n];
    for(int i=1; i<n; i++)
    {
        pom=tab[i];
        for ( j=i-1; j>=0 && tab[j]>pom; j--)
        {
            tab[j+1] = tab[j];
        }
        tab[j+1]=pom;
    } // TODO: implement
}

void quick_sort(int *t, unsigned int n) {
   int lewy, prawy,tab[n];
    lewy=0;
    prawy=n-1;
    
    
    if(prawy <= lewy) return;
    int i, j, k, x;
    int tab[n];
    k=lewy+int((prawy-lewy+1)* rand()/(RAND_MAX+1.0));
    x=tab[k];
    i = lewy - 1;
    j = prawy + 1;

    while(1)
    {
        while(x>tab[++i]);

        while(x<tab[--j]);

        if( i <= j)
            swap(tab[i],tab[j]);
        else
            break;
    }

    if(j > lewy)
        quick_sort_(tab, lewy, j);

    if(i < prawy)
        quick_sort_(tab, i, prawy); // TODO: implement
}
void przywaracanie_kopca(int tab[], int n, int i)
{

    int k = i;
    int lewy=2*i+1;
    int prawy= 2*i+2;

    if(lewy<n && tab[1]>tab[k])
        k=lewy;
    if(prawy<n && tab[prawy]> tab[k])
        k=prawy;
    if (k != i)
    {
        swap(tab[i], tab[k]);
        przywaracanie_kopca(tab, n, k);
    }
}
void heap_sort(int *t, unsigned int n) {
    int tab[n];
    for(int i=n/2-1; i>=0; i--)
        przywaracanie_kopca(tab, n, i);

    for(int i=n-1; i>=0; i--)
    {
        swap(tab[0], tab[i]);
        przywaracanie_kopca(tab, i, 0);
    }// TODO
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
