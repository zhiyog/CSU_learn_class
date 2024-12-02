#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 320
#define MAX_LINES 100
#define PAGE_SIZE 20

typedef struct {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int startLine;
    int endLine;
} ActiveRegion;

void insertLine(ActiveRegion *activeRegion, int lineNum, char *text) {
    if (lineNum > activeRegion->endLine || lineNum < activeRegion->startLine - 1) {
        printf("Invalid line number!\n");
        return;
    }

    if (activeRegion->endLine == MAX_LINES - 1) {
        printf("Active region is full! Cannot insert line.\n");
        return;
    }

    int insertIndex = lineNum - activeRegion->startLine + 1;
    memmove(activeRegion->lines[insertIndex + 1], activeRegion->lines[insertIndex],
            sizeof(char) * (MAX_LINE_LENGTH * (activeRegion->endLine - lineNum + 1)));

    strncpy(activeRegion->lines[insertIndex], text, MAX_LINE_LENGTH);
    activeRegion->endLine++;
}

void deleteLines(ActiveRegion *activeRegion, int startLine, int endLine) {
    if (startLine > activeRegion->endLine || endLine < activeRegion->startLine) {
        printf("Invalid line range!\n");
        return;
    }

    int deleteStartIndex = startLine - activeRegion->startLine;
    int deleteCount = endLine - startLine + 1;
    memmove(activeRegion->lines[deleteStartIndex], activeRegion->lines[deleteStartIndex + deleteCount],
            sizeof(char) * (MAX_LINE_LENGTH * (activeRegion->endLine - endLine)));

    activeRegion->endLine -= deleteCount;
}

void switchActiveRegion(ActiveRegion *activeRegion, char *outputFile) {
    FILE *file = fopen(outputFile, "w");
    if (file == NULL) {
        printf("Failed to open output file!\n");
        return;
    }

    for (int i = 0; i <= activeRegion->endLine; i++) {
        fprintf(file, "%s\n", activeRegion->lines[i]);
    }

    fclose(file);

    activeRegion->startLine = activeRegion->endLine + 1;
    activeRegion->endLine = activeRegion->startLine - 1;
}

void displayActiveRegion(ActiveRegion *activeRegion) {
    int currentPage = 0;
    int totalPages = (activeRegion->endLine - activeRegion->startLine + 1) / PAGE_SIZE;

    while (currentPage <= totalPages) {
        printf("Page %d:\n", currentPage + 1);
        for (int i = 0; i < PAGE_SIZE; i++) {
            int lineIndex = activeRegion->startLine + currentPage * PAGE_SIZE + i;
            if (lineIndex <= activeRegion->endLine) {
                printf("%4d %s\n", lineIndex, activeRegion->lines[lineIndex - activeRegion->startLine]);
            }
        }

        char choice;
        if (currentPage < totalPages) {
            printf("Press 'Enter' to continue to the next page, or 'q' to quit displaying.\n");
        } else {
            printf("End of active region. Press 'q' to quit displaying.\n");
        }

        choice = getchar();
        if (choice == 'q') {
            break;
        }

        currentPage++;
    }
}

int main() {
    char inputFile[100], outputFile[100];
    ActiveRegion activeRegion;
    activeRegion.startLine = 0;
    activeRegion.endLine = -1;

    printf("Enter the input file name: ");
    fgets(inputFile, sizeof(inputFile), stdin);
    inputFile[strcspn(inputFile, "\n")] = '\0';

    printf("Enter the output file name: ");
    fgets(outputFile, sizeof(outputFile), stdin);
    outputFile[strcspn(outputFile, "\n")] = '\0';

    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && activeRegion.endLine < MAX_LINES - 1) {
        line[strcspn(line, "\n")] = '\0';
        strncpy(activeRegion.lines[++activeRegion.endLine], line, MAX_LINE_LENGTH);
    }

    fclose(file);

    char command;
    do {
        printf("\nEnter a command (i-insert, d-delete, n-switch, p-display, q-quit): ");
        command = getchar();
        getchar();  // Consume the newline character

        switch (command) {
            case 'i': {
                int lineNum;
                printf("Enter line number: ");
                scanf("%d", &lineNum);
                getchar();  // Consume the newline character

                char text[MAX_LINE_LENGTH];
                printf("Enter text to insert: ");
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';

                insertLine(&activeRegion, lineNum, text);
                displayActiveRegion(&activeRegion);
                break;
            }
            case 'd': {
                int startLine, endLine;
                printf("Enter start line number: ");
                scanf("%d", &startLine);
                getchar();  // Consume the newline character

                printf("Enter end line number (optional): ");
                if (scanf("%d", &endLine) != 1) {
                    endLine = startLine;
                    getchar();  // Consume the newline character
                } else {
                    getchar();  // Consume the newline character
                }

                deleteLines(&activeRegion, startLine, endLine);
                displayActiveRegion(&activeRegion);
                break;
            }
            case 'n':
                switchActiveRegion(&activeRegion, outputFile);
                printf("Switched active region.\n");
                break;
            case 'p':
                displayActiveRegion(&activeRegion);
                break;
            case 'q':
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid command! Please try again.\n");
                break;
        }
    } while (command != 'q');

    return 0;
}
