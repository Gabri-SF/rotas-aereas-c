# ✈️ Sistema de Gestão de Rotas e Aeroportos

Este projeto é um sistema desenvolvido em **C** para a gestão e pesquisa de rotas aéreas entre aeroportos. Permite calcular distâncias, procurar voos diretos ou com escalas (até 2) e ordenar resultados por tempo ou distância.

## 🚀 Funcionalidades

- **Parsing de Dados:** Leitura de ficheiros de texto para carregar aeroportos e rotas.
- **Pesquisa Inteligente:** - Voos diretos.
  - Voos com 1 escala (com validação de tempo de ligação).
  - Voos com 2 escalas.
- **Interface CLI Avançada:** Implementação de `getopt` para uma navegação profissional via terminal.
- **Ordenação:** Algoritmos para ordenar por tempo (crescente/decrescente) e distância total.

## 🛠️ Como Compilar

Certifica-te de que tens o `gcc` instalado. O projeto inclui um `Makefile` para facilitar:

```bash
make