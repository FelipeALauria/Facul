#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 16 // Número máximo de páginas por processo

// Estrutura para representar uma página
typedef struct {
    int pageNumber;   // Número da página
    bool useBit;      // Bit de uso
    bool referenceBit; // Bit de referência
} Page;

// Estrutura para representar a tabela de páginas de um processo
typedef struct {
    Page pages[MAX_PAGES]; // Tabela de páginas
    int pageCount;         // Número de páginas atualmente alocadas
    int pointer;           // Ponteiro para o algoritmo de segunda chance
} PageTable;

// Inicializa a tabela de páginas
void initializePageTable(PageTable *table) {
    table->pageCount = 0;
    table->pointer = 0;
    for (int i = 0; i < MAX_PAGES; i++) {
        table->pages[i].pageNumber = -1; // Página não alocada
        table->pages[i].useBit = false;
        table->pages[i].referenceBit = false;
    }
}

// Função para alocar uma página
void allocatePage(PageTable *table, int pageNumber) {
    if (table->pageCount < MAX_PAGES) {
        // Aloca a página diretamente se houver espaço
        table->pages[table->pageCount].pageNumber = pageNumber;
        table->pages[table->pageCount].useBit = true;
        table->pages[table->pageCount].referenceBit = true;
        table->pageCount++;
    } else {
        // Aplica o algoritmo de segunda chance para substituir uma página
        while (true) {
            Page *currentPage = &table->pages[table->pointer];
            if (!currentPage->useBit && !currentPage->referenceBit) {
                // Substitui a página
                currentPage->pageNumber = pageNumber;
                currentPage->useBit = true;
                currentPage->referenceBit = true;
                table->pointer = (table->pointer + 1) % MAX_PAGES;
                break;
            } else {
                // Dá uma segunda chance à página
                currentPage->useBit = false;
                table->pointer = (table->pointer + 1) % MAX_PAGES;
            }
        }
    }
}

// Exibe o estado atual da tabela de páginas
void displayPageTable(PageTable *table) {
    printf("Tabela de Páginas:\n");
    for (int i = 0; i < table->pageCount; i++) {
        printf("Página %d: Número=%d, Uso=%d, Referência=%d\n",
               i, table->pages[i].pageNumber, table->pages[i].useBit, table->pages[i].referenceBit);
    }
}

int main() {
    PageTable table;
    initializePageTable(&table);

    // Simulação de alocação de páginas
    allocatePage(&table, 1);
    allocatePage(&table, 2);
    allocatePage(&table, 3);
    allocatePage(&table, 4);
    allocatePage(&table, 5);
    allocatePage(&table, 6);
    allocatePage(&table, 7);
    allocatePage(&table, 8);
    allocatePage(&table, 9);
    allocatePage(&table, 10);
    allocatePage(&table, 11);
    allocatePage(&table, 12);
    allocatePage(&table, 13);
    allocatePage(&table, 14);
    allocatePage(&table, 15);
    allocatePage(&table, 16);

    // Substituição de página
    allocatePage(&table, 17);

    // Exibe o estado final da tabela de páginas
    displayPageTable(&table);

    return 0;
}