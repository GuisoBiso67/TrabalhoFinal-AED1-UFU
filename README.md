# TrabalhoFinal-AED1-UFU
# 📺 Sistema de Gerenciamento de Séries — Lista Duplamente Ligada

> Trabalho Final da disciplina de **Algoritmos e Estruturas de Dados 1 (AED1)** — Universidade Federal de Uberlândia (UFU).  
> Sistema de gerenciamento de perfis de usuários e seus históricos de séries assistidas, implementado em **C** utilizando **Listas Duplamente Ligadas aninhadas**.

---

## 📋 Sumário

- [Sobre o Projeto](#-sobre-o-projeto)
- [Estrutura de Dados](#-estrutura-de-dados)
- [Funcionalidades](#️-funcionalidades)
- [Complexidade das Operações](#-complexidade-das-operações)
- [Estrutura de Arquivos](#-estrutura-de-arquivos)
- [Como Compilar e Executar](#️-como-compilar-e-executar)
- [Exemplos de Uso](#-exemplos-de-uso)
- [Decisões de Projeto](#-decisões-de-projeto)
- [Autores](#-autores)

---

## 📖 Sobre o Projeto

Este sistema simula uma plataforma simplificada de acompanhamento de séries — semelhante a um Letterboxd ou MyAnimeList — onde cada **usuário** possui um perfil próprio e uma **lista pessoal de séries assistidas**.

A proposta central é demonstrar na prática o uso de **Listas Duplamente Ligadas aninhadas**:

- Uma **lista principal** armazena os perfis dos usuários.
- Cada nó de usuário contém uma **lista interna** com as séries que aquele usuário já assistiu.

Essa estrutura permite navegação eficiente nos dois sentidos (anterior e próximo), tanto na lista de usuários quanto na lista de séries de cada perfil.

---

## 🧠 Estrutura de Dados

### Visão Geral

```
Lista de Usuários (Duplamente Ligada)
│
├── [Usuário 1] ──► Lista de Séries (Duplamente Ligada)
│                    ├── Breaking Bad
│                    ├── Dark
│                    └── Stranger Things
│
├── [Usuário 2] ──► Lista de Séries (Duplamente Ligada)
│                    ├── Game of Thrones
│                    └── The Boys
│
└── [Usuário N] ──► Lista de Séries (Duplamente Ligada)
                     └── ...
```

### Nó de Usuário

```c
typedef struct usuario {
    // dados do perfil (nome, id, etc.)
    struct serie   *listaSeries;   // ponteiro para a lista de séries
    struct usuario *ant;           // ponteiro para o usuário anterior
    struct usuario *prox;          // ponteiro para o próximo usuário
} Usuario;
```

### Nó de Série

```c
typedef struct serie {
    // dados da série (título, gênero, nota, etc.)
    struct serie *ant;   // ponteiro para a série anterior
    struct serie *prox;  // ponteiro para a próxima série
} Serie;
```

### Por que Lista Duplamente Ligada?

| Característica | Lista Simples | Lista Duplamente Ligada |
|---|---|---|
| Navegação para frente | ✅ | ✅ |
| Navegação para trás | ❌ | ✅ |
| Remoção sem percurso extra | ❌ | ✅ |
| Uso de memória | Menor | Levemente maior |

A lista duplamente ligada foi escolhida por permitir **remoção direta** de qualquer nó sem precisar percorrer a lista desde o início para encontrar o nó anterior, além de possibilitar percurso nos dois sentidos.

---

## ⚙️ Funcionalidades

### Gerenciamento de Usuários
- ✅ Cadastrar novo usuário
- ✅ Remover usuário (e todas as suas séries)
- ✅ Buscar usuário por nome/ID
- ✅ Listar todos os usuários cadastrados

### Gerenciamento de Séries por Usuário
- ✅ Adicionar série ao perfil de um usuário
- ✅ Remover série do perfil de um usuário
- ✅ Listar todas as séries de um usuário
- ✅ Buscar série no perfil de um usuário

### Utilitários
- ✅ Liberar toda a memória alocada dinamicamente
- ✅ Navegação bidirecional nas listas

---

## 📈 Complexidade das Operações

| Operação | Complexidade |
|---|---|
| Inserção no início/fim da lista | O(1) |
| Busca por elemento | O(n) |
| Remoção (com ponteiro direto) | O(1) |
| Remoção (com busca) | O(n) |
| Listagem completa | O(n) |
| Liberar lista completa | O(n) |

> **n** = número de elementos na lista (usuários ou séries, dependendo do contexto).

---

## 📁 Estrutura de Arquivos

```
TrabalhoFinal-AED1-UFU/
│
├── code/                   # Código-fonte do projeto
│   ├── main.c              # Ponto de entrada e menu principal
│   ├── usuario.c           # Implementação das funções de usuário
│   ├── usuario.h           # Definição da struct e assinaturas de usuário
│   ├── serie.c             # Implementação das funções de série
│   ├── serie.h             # Definição da struct e assinaturas de série
│   └── CMakeLists.txt      # Configuração de build com CMake
│
├── report/                 # Relatório do trabalho
│
└── README.md               # Este arquivo
```

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos

- GCC (GNU Compiler Collection) instalado
- Linux, macOS ou Windows com MinGW/WSL

### Opção 1 — Compilação direta com GCC

```bash
# Clone o repositório
git clone https://github.com/GuisoBiso67/TrabalhoFinal-AED1-UFU.git
cd TrabalhoFinal-AED1-UFU/code

# Compile todos os arquivos
gcc main.c usuario.c serie.c -o sistema_series

# Execute
./sistema_series
```

### Opção 2 — Usando CMake

```bash
cd TrabalhoFinal-AED1-UFU
mkdir build && cd build
cmake ../code
make
./sistema_series
```

### Opção 3 — Usando uma IDE

Abra a pasta `code/` em qualquer IDE com suporte a C (CLion, VS Code, Code::Blocks) e execute diretamente pelo ambiente.

---

## 💡 Exemplos de Uso

Ao iniciar o programa, um menu interativo é exibido:

```
==============================
  Sistema de Gerenciamento de Séries
==============================
[1] Cadastrar usuário
[2] Remover usuário
[3] Listar usuários
[4] Adicionar série a um usuário
[5] Remover série de um usuário
[6] Listar séries de um usuário
[0] Sair
==============================
Escolha uma opção:
```

**Exemplo de fluxo:**
1. Cadastrar o usuário `"Guilherme"`
2. Adicionar as séries `"Breaking Bad"` e `"Dark"` ao perfil de Guilherme
3. Listar as séries do usuário Guilherme
4. Remover a série `"Dark"`
5. Verificar a lista atualizada

---

## 🔍 Decisões de Projeto

### Listas aninhadas vs. outras estruturas

Optou-se por listas aninhadas (lista de usuários contendo listas de séries) em vez de uma única tabela ou vetor bidimensional por algumas razões:

- **Flexibilidade**: cada usuário pode ter um número diferente de séries sem desperdício de memória.
- **Inserção e remoção dinâmicas**: não há necessidade de realocar memória como aconteceria em vetores.
- **Modularidade**: a lógica de usuários e séries fica completamente separada, facilitando manutenção.

### Duplamente ligada vs. simplesmente ligada

A lista duplamente ligada foi preferida pois:

- Permite **remover um nó do meio** da lista de forma eficiente, sem percorrer do início.
- Facilita operações que precisam voltar ao elemento anterior.
- O custo extra de memória (um ponteiro `ant` a mais por nó) é justificável para ganhar essa flexibilidade.

---

## 👨‍💻 Autores

<table>
  <tr>
    <td align="center">
      <b>Guilherme Silva Cotrim</b><br/>
      <a href="https://github.com/GuisoBiso67">@GuisoBiso67</a>
    </td>
    <td align="center">
      <b>Gabriela Andrade Martins Cunha</b><br/>
      UFU — Ciência da Computação
    </td>
  </tr>
</table>

---

## 📚 Referências

- Cormen, T. H. et al. **Algoritmos: Teoria e Prática**. 3ª ed. Elsevier, 2012.
- Ziviani, N. **Projeto de Algoritmos com Implementações em C e Pascal**. 3ª ed. Cengage Learning, 2010.
- Material didático da disciplina AED1 — UFU.

---

<div align="center">
  <i>Desenvolvido para a disciplina de Algoritmos e Estruturas de Dados 1 — UFU, Uberlândia/MG</i>
</div>