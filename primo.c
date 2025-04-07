#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define MAX_BASE 99999999
#define STEP_PERCENT (MAX_BASE / 1000)

bool eh_primo(unsigned long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

void calcula_dv(int cnpj[12], int dv[2]) {
    int pesos1[12] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int pesos2[13] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2};
    int soma1 = 0, soma2 = 0;
    for (int i = 0; i < 12; i++) soma1 += cnpj[i] * pesos1[i];
    dv[0] = soma1 % 11;
    dv[0] = dv[0] < 2 ? 0 : 11 - dv[0];
    for (int i = 0; i < 12; i++) soma2 += cnpj[i] * pesos2[i];
    soma2 += dv[0] * pesos2[12];
    dv[1] = soma2 % 11;
    dv[1] = dv[1] < 2 ? 0 : 11 - dv[1];
}

void printa_cnpj(int cnpj[14]) {
    fprintf(stderr, "%d%d.%d%d%d.%d%d%d/%d%d%d%d-%d%d\n",
        cnpj[0], cnpj[1], cnpj[2], cnpj[3], cnpj[4], cnpj[5], cnpj[6], cnpj[7],
        cnpj[8], cnpj[9], cnpj[10], cnpj[11], cnpj[12], cnpj[13]);
}

int main() {
    #pragma omp parallel for schedule(dynamic)
    for (int base = 1; base <= MAX_BASE; base++) {
        int cnpj[14];
        int temp = base;
        for (int i = 7; i >= 0; i--) {
            cnpj[i] = temp % 10;
            temp /= 10;
        }
        cnpj[8] = 0;
        cnpj[9] = 0;
        cnpj[10] = 0;
        cnpj[11] = 1;

        int dv[2];
        calcula_dv(cnpj, dv);
        cnpj[12] = dv[0];
        cnpj[13] = dv[1];

        unsigned long long numero = 0;
        for (int i = 0; i < 14; i++) numero = numero * 10 + cnpj[i];

        if (eh_primo(numero)) {
            #pragma omp critical
            {
                    printa_cnpj(cnpj);
            }
        }

        // progresso (apenas 1 thread mostra)
        if (base % STEP_PERCENT == 0 && omp_get_thread_num() == 0) {
            fprintf(stdout, "Progresso: %.1f%%\r", (base / (float)MAX_BASE) * 100);
            fflush(stdout);
        }
    }


    return 0;
}
