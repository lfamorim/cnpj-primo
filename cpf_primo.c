#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define MAX_BASE 999999999
#define STEP_PERCENT (MAX_BASE / 1000)

bool eh_primo(unsigned long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (unsigned long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

void calcula_dv_cpf(int cpf[9], int dv[2]) {
    // Cálculo do primeiro dígito verificador
    int soma1 = 0;
    for (int i = 0; i < 9; i++) {
        soma1 += cpf[i] * (10 - i);
    }
    int resto1 = soma1 % 11;
    dv[0] = resto1 < 2 ? 0 : 11 - resto1;
    
    // Cálculo do segundo dígito verificador
    int soma2 = 0;
    for (int i = 0; i < 9; i++) {
        soma2 += cpf[i] * (11 - i);
    }
    soma2 += dv[0] * 2;
    int resto2 = soma2 % 11;
    dv[1] = resto2 < 2 ? 0 : 11 - resto2;
}

void printa_cpf(int cpf[11]) {
    fprintf(stderr, "%d%d%d.%d%d%d.%d%d%d-%d%d\n",
        cpf[0], cpf[1], cpf[2], cpf[3], cpf[4], cpf[5], cpf[6], cpf[7], cpf[8], cpf[9], cpf[10]);
}

bool cpf_valido(int cpf[11]) {
    // Verifica se todos os dígitos são iguais (CPF inválido)
    bool todos_iguais = true;
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todos_iguais = false;
            break;
        }
    }
    return !todos_iguais;
}

int main() {
    printf("Buscando CPFs que formam números primos...\n");
    
    #pragma omp parallel for schedule(dynamic)
    for (int base = 1; base <= MAX_BASE; base++) {
        int cpf[11];
        int temp = base;
        
        // Preenche os 9 primeiros dígitos do CPF
        for (int i = 8; i >= 0; i--) {
            cpf[i] = temp % 10;
            temp /= 10;
        }
        
        // Calcula os dígitos verificadores
        int dv[2];
        calcula_dv_cpf(cpf, dv);
        cpf[9] = dv[0];
        cpf[10] = dv[1];
        
        // Verifica se o CPF é válido (não contém todos os dígitos iguais)
        if (!cpf_valido(cpf)) {
            continue;
        }
        
        // Converte o CPF para um número inteiro
        unsigned long long numero = 0;
        for (int i = 0; i < 11; i++) {
            numero = numero * 10 + cpf[i];
        }
        
        // Verifica se o número é primo
        if (eh_primo(numero)) {
            #pragma omp critical
            {
                printa_cpf(cpf);
            }
        }
        
        // Mostra o progresso (apenas na thread 0)
        if (base % STEP_PERCENT == 0 && omp_get_thread_num() == 0) {
            fprintf(stdout, "Progresso: %.1f%%\r", (base / (float)MAX_BASE) * 100);
            fflush(stdout);
        }
    }
    
    printf("\nBusca concluída!\n");
    return 0;
}
