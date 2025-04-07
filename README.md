# CNPJ Primo

Um programa que encontra CNPJs (Cadastro Nacional da Pessoa Jurídica) cujo valor numérico completo forma um número primo.

## Sobre o Projeto

Este projeto foi criado por diversão para encontrar uma peculiaridade matemática: CNPJs válidos cujo número completo (todos os 14 dígitos juntos) forma um número primo.

O programa:
- Gera todos os CNPJs possíveis com base sequencial (8 primeiros dígitos)
- Mantém os dígitos da filial como 0001 (9º ao 12º dígito)
- Calcula os dígitos verificadores corretamente (13º e 14º dígitos)
- Verifica se o número de 14 dígitos formado é um número primo
- Utiliza OpenMP para paralelização e melhor desempenho

## Requisitos

- Compilador C (GCC recomendado)
- Biblioteca OpenMP
- Biblioteca matemática (math.h)

## Como Compilar

Utilize o Makefile fornecido:

```bash
make
```

Isso irá gerar o executável `cnpj_primo`.

## Como Executar

```bash
./cnpj_primo
```

O programa mostrará o progresso da busca e imprimirá os CNPJs primos encontrados.

## Performance

O programa utiliza OpenMP para paralelização, aproveitando múltiplos núcleos de processamento para acelerar a busca.

## Contribuindo

Sinta-se à vontade para fazer um fork e melhorar o código. Algumas ideias:
- Otimização do algoritmo de verificação de números primos
- Suporte para outros tipos de documentos (como CPF)
- Interface gráfica ou web para visualização dos resultados
- Análise estatística dos resultados

## Licença

Este projeto é distribuído sob a licença MIT.
