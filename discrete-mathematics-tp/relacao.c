#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeIdentifiers
{
    int element;
    int positionInAdjMatrix;
} NodeIdentifiers;

char isReflexive(int **matrix, int matrixLength)
{
    char isReflexive = 'V';
    for (int i = 0; i < matrixLength; i++)
    {
        if (matrix[i][i] != 1)
        {
            isReflexive = 'F';
            break;
        }
    }
    return isReflexive;
}

char isIrreflexive(int **matrix, int matrixLength)
{
    char isIrreflexive = 'V';
    for (int i = 0; i < matrixLength; i++)
    {
        if (matrix[i][i] == 1)
        {
            isIrreflexive = 'F';
            break;
        }
    }
    return isIrreflexive;
}

int **getNonReflexivePairs(int matrixLength, int **matrix)
{
    int **reflexivePairs;
    reflexivePairs = (int **)malloc(sizeof(int *) * matrixLength);
    for (int i = 0; i < matrixLength; i++)
    {
        reflexivePairs[i] = (int *)malloc(sizeof(int) * matrixLength);
    }

    // SE A POSICAO ESTA MARCADA COM -4, ISSO SIGNIFICA QUE ELA REPRESENTA UM CASO QUE FERE A PROPRIDADE DE TRANSITIVIDADE
    for (int i = 0; i < matrixLength; i++)
    {
        if (matrix[i][i] != 1)
        {
            reflexivePairs[i][i] = -4;
        }
    }
    return reflexivePairs;
}

int **getNonIrreflexivePairs(int matrixLength, int **matrix)
{
    int **irreflexivePairs;
    irreflexivePairs = (int **)malloc(sizeof(int *) * matrixLength);
    for (int i = 0; i < matrixLength; i++)
    {
        irreflexivePairs[i] = (int *)malloc(sizeof(int) * matrixLength);
    }

    // SE A POSICAO ESTA MARCADA COM -5, ISSO SIGNIFICA QUE ELA REPRESENTA UM CASO QUE FERE A PROPRIDADE DE TRANSITIVIDADE
    for (int i = 0; i < matrixLength; i++)
    {
        if (matrix[i][i] == 1)
        {
            irreflexivePairs[i][i] = -5;
        }
    }
    return irreflexivePairs;
}

int **resolveSymmetryMatrix(int **matrix, int matrixLength)
{
    // * ALOCA MATRIZ AUXILIAR
    int **aux;
    aux = (int **)malloc(sizeof(int *) * matrixLength);
    for (int i = 0; i < matrixLength; i++)
    {
        aux[i] = (int *)malloc(sizeof(int) * matrixLength);
    }
    // AS POSICOES QUE AFETAM A CONDICAO DE SIMETRIA, SAO MARCADAS COM -1
    // AS POSICOES QUE AFETAM A CONDICAO DE ANTI SIMETRIA SAO MARCADAS COM -2
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if ((
                    (i != j && matrix[i][j] != matrix[j][i]) ||
                    (i == j && matrix[i][j] != matrix[j][i])) &&
                matrix[i][j] != 1)
            {
                // NAO PODE SER SIMETRICA
                aux[i][j] = -1;
            }
            else if (i != j && matrix[i][j] == 1 && matrix[j][i] == 1)
            {
                // NAO PODE SER ANTI SIMETRICA
                aux[i][j] = -2;
            }
        }
    }
    return aux;
}

void *resolveSymmetryCases(int **symmetricMatrix, int matrixLength, char *cases)
{
    strcpy(cases, "VVF");
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if (symmetricMatrix[i][j] == -1)
            {
                cases[0] = 'F';
            }
            if (symmetricMatrix[i][j] == -2)
            {
                cases[1] = 'F';
            }
        }
    }
    if (cases[0] == 'F' && cases[1] == 'F')
    {
        cases[2] = 'V';
    }
}

void printPairs(int **matrix, int value, NodeIdentifiers *nodeIdentifiers, int matrixLength)
{
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if (matrix[i][j] == value)
            {
                printf("(");
                int newX = nodeIdentifiers[i].element;
                int newY = nodeIdentifiers[j].element;
                printf("%d,", newX);
                printf("%d", newY);
                printf("); ");
            }
        }
    }
    printf("\n");
}

void printSymmetryCases(int **symmetric, char *cases, NodeIdentifiers *nodeIdentifiers, int matrixLength)
{
    char isSymmetric = cases[0];
    char isAntiSymmetric = cases[1];
    char isAsymmetric = cases[2];
    if (isSymmetric == 'V')
    {
        printf("Simetrica: %c \n", isSymmetric);
        printf("Anti-simetrica: %c \n", isAntiSymmetric);
        printPairs(symmetric, -2, nodeIdentifiers, matrixLength);
        printf("Assimetrica: %c \n", isAsymmetric);
    }

    if (isAntiSymmetric == 'V')
    {
        printf("Simetrica: %c \n", isSymmetric);
        printPairs(symmetric, -1, nodeIdentifiers, matrixLength);
        printf("Anti-simetrica: %c \n", isAntiSymmetric);
        printf("Assimetrica: %c \n", isAsymmetric);
    }

    if (isAsymmetric == 'V')
    {
        printf("Simetrica: %c \n", isSymmetric);
        printPairs(symmetric, -1, nodeIdentifiers, matrixLength);
        printf("Anti-simetrica: %c \n", isAntiSymmetric);
        printPairs(symmetric, -2, nodeIdentifiers, matrixLength);
        printf("Assimetrica: %c \n", isAsymmetric);
    }
}

void resolveReflexivityCases(int **matrix, int matrixLength, char reflexive, NodeIdentifiers *nodeIdentifiers)
{
    if (reflexive == 'V')
    {
        printf("Reflexiva: V\n");
    }
    if (reflexive == 'F')
    {
        int **nonReflexivePairs = getNonReflexivePairs(matrixLength, matrix);
        printf("Reflexiva: F\n");
        printPairs(nonReflexivePairs, -4, nodeIdentifiers, matrixLength);
    }
}

void resolveIrreflexivityCases(int **matrix, int matrixLength, char irreflexive, NodeIdentifiers *nodeIdentifiers)
{
    if (irreflexive == 'V')
    {
        printf("Irreflexiva: V\n");
    }
    if (irreflexive == 'F')
    {
        int **nonReflexivePairs = getNonIrreflexivePairs(matrixLength, matrix);
        printf("Irreflexiva: F\n");
        printPairs(nonReflexivePairs, -5, nodeIdentifiers, matrixLength);
    }
}

void resolveEquivalenceRelation(char reflexive, char *cases, char transitive)
{
    printf("Relação de equivalência: ");
    if (reflexive == 'V' && cases[0] == 'V' && transitive == 'V')
    {
        printf("V\n");
    }
    printf("F\n");
}

void resolvePartialOrder(char reflexive, char *cases, char transitive)
{
    printf("Relação de equivalência: ");
    if (reflexive == 'V' && cases[1] == 'V' && transitive == 'V')
    {
        printf("V\n");
    }
    printf("F\n");
}

void resolveTransitiveClosure(int **matrix, int matrixLength, NodeIdentifiers *nodeIdentifiers, int **missingTransitiveCases)
{
    printf("Fecho transitivo da relação: ");
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if (missingTransitiveCases[i][j] == -3)
            {
                matrix[i][j] = 1;
            }
        }
    }
    printPairs(matrix, 1, nodeIdentifiers, matrixLength);
}

char isTransitive(int **matrix, int matrixLength)
{
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if (i != j && matrix[i][j] == 1)
            {
                for (int k = 0; k < matrixLength; k++)
                {
                    if ((j != k) && (matrix[j][k] == 1 && matrix[i][k] != 1))
                    {
                        return 'F';
                    }
                }
            }
        }
    }
    return 'V';
}

int **resolveTransitivityCases(int **matrix, int matrixLength)
{
    int **aux;
    aux = (int **)malloc(sizeof(int *) * matrixLength);
    for (int i = 0; i < matrixLength; i++)
    {
        aux[i] = (int *)malloc(sizeof(int) * matrixLength);
    }

    // SE A POSICAO ESTA MARCADA COM -3, ISSO SIGNIFICA QUE ELA REPRESENTA UM CASO QUE FERE A PROPRIDADE DE TRANSITIVIDADE
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            if (i != j && matrix[i][j] == 1)
            {
                for (int k = 0; k < matrixLength; k++)
                {
                    if ((j != k) && (matrix[j][k] == 1 && matrix[i][k] != 1))
                    {
                        aux[i][k] = -3;
                    }
                }
            }
        }
    }
    return aux;
}

void printTransitiveCases(int **transitiveMatrix, int length, NodeIdentifiers *nodeIndentifiers, char isTransitive)
{
    printf("Transitiva: %c\n", isTransitive);
    if (isTransitive == 'F')
    {
        printPairs(transitiveMatrix, -3, nodeIndentifiers, length);
    }
}

int resolveCases(int **matrix, int matrixLength, NodeIdentifiers *nodeIdentifiers)
{
    char reflexive = isReflexive(matrix, matrixLength);
    char irreflexive = isIrreflexive(matrix, matrixLength);
    resolveReflexivityCases(matrix, matrixLength, reflexive, nodeIdentifiers);
    resolveIrreflexivityCases(matrix, matrixLength, irreflexive, nodeIdentifiers);

    int **symmetricMatrix = resolveSymmetryMatrix(matrix, matrixLength);
    char symmetricCases[3];
    resolveSymmetryCases(symmetricMatrix, matrixLength, symmetricCases);
    printSymmetryCases(symmetricMatrix, symmetricCases, nodeIdentifiers, matrixLength);

    char transitive = isTransitive(matrix, matrixLength);
    int **missingTransitiveCases = resolveTransitivityCases(matrix, matrixLength);
    printTransitiveCases(missingTransitiveCases, matrixLength, nodeIdentifiers, transitive);

    resolveEquivalenceRelation(reflexive, symmetricCases, transitive);
    resolvePartialOrder(reflexive, symmetricCases, transitive);
    resolveTransitiveClosure(matrix, matrixLength, nodeIdentifiers, missingTransitiveCases);
}

NodeIdentifiers *getNodeIndetifiers(int len, char *buffer)
{
    NodeIdentifiers *nodes = (NodeIdentifiers *)malloc(sizeof(NodeIdentifiers) * len);
    int position = 0;
    int lenq = strlen(buffer);

    char *firstNodeIdentificator = strtok(buffer, " ");
    firstNodeIdentificator = strtok(NULL, " ");
    while (firstNodeIdentificator != NULL)
    {
        nodes[position].element = atoi(firstNodeIdentificator);
        nodes[position].positionInAdjMatrix = position;
        firstNodeIdentificator = strtok(NULL, " ");
        position++;
    }

    return nodes;
}

int getAdjacencyValue(NodeIdentifiers *nodeIdentifiers, int length, char *value)
{
    int intergerValue = atoi(value);
    for (int i = 0; i < length; i++)
    {
        if (nodeIdentifiers[i].element == intergerValue)
        {
            return nodeIdentifiers[i].positionInAdjMatrix;
        }
    }
}

int main()
{
    FILE *myFile;
    int myMatrixLength = 0;
    NodeIdentifiers *nodeIdentifiers;
    int **adjcencyMatrix;
    int lines, columns = 0;
    int isFirstLine = 1;
    int i = 0;

    char fileLine[20];

    myFile = fopen("input.txt", "r");

    while (!feof(myFile))
    {
        fgets(fileLine, 20, myFile);
        if (isFirstLine == 1)
        {
            myMatrixLength = fileLine[0] - '0';
            nodeIdentifiers = getNodeIndetifiers(myMatrixLength, fileLine);
            adjcencyMatrix = (int **)malloc(sizeof(int *) * myMatrixLength);
            for (int i = 0; i < myMatrixLength; i++)
            {
                adjcencyMatrix[i] = (int *)malloc(sizeof(int) * myMatrixLength);
            }
            isFirstLine = 0;
        }
        else
        {
            char *lineNumber;
            char *columnNumber;
            lineNumber = strtok(fileLine, " ");
            columnNumber = strtok(NULL, " ");
            if (lineNumber != NULL && columnNumber != NULL)
            {
                int linePosition = getAdjacencyValue(nodeIdentifiers, myMatrixLength, lineNumber);
                int columnPosition = getAdjacencyValue(nodeIdentifiers, myMatrixLength, columnNumber);
                adjcencyMatrix[linePosition][columnPosition] = 1;
                i++;
            }
        }
    }
    fclose(myFile);
    resolveCases(adjcencyMatrix, myMatrixLength, nodeIdentifiers);
    return 1;
}
