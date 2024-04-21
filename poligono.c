#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
3
1.0 2.0
3.0 8.0
5.0 1.0

A saida deveria ser: A area do poligono e 13.00
*/

typedef struct {
    float X;
    float Y;
} Ponto;

//Funcao para calcular a area de um triangulo dado seus vertices A,B, C
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {

    float det = A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y); // Calculando o determinante

    //retornando a area do triangulo - valor absoluto do determinante dividido por 2.
    return fabs(det) / 2.0;
}

//funcao para ler os vertices do poligono do arquivo
Ponto *LerVertices(char *nome_arquivo, int *num_vertices) {

    FILE *arquivo;
    int i;
    Ponto *vertices;

    //abrindo o arquivo para leitura
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo solicitado\n");
        exit(1);
    }

    //lendo o numero de vertices
    fscanf(arquivo, "%d", num_vertices);

    //alocando memoria para armazenar os vertices
    vertices = (Ponto *)malloc(*num_vertices * sizeof(Ponto));

    if (vertices == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }

    //lendo as coordenadas dos vertices
    for (i = 0; i < *num_vertices; i++) {

        fscanf(arquivo, "%f %f", &(vertices[i].X), &(vertices[i].Y));
    }

    fclose(arquivo);

    return vertices;
}

//funcao para calcular a area total do poligono
float CalcularAreaPoligono(Ponto *vertices, int num_vertices) {

    int i;
    float area_total = 0.0;

    //calculando a area total do poligono e tbm dividindo o mesmo em triangulos
    for (i = 1; i < num_vertices - 1; i++) {

        area_total += AreaTriangulo(vertices[0], vertices[i], vertices[i + 1]);
    }

    return area_total;
}

int main() {

    char nome_arquivo[] = "vertices.txt";
    int num_vertices;
    float area_poligono;
    Ponto *vertices;

    //ler os vertices do poligono do arquivo
    vertices = LerVertices(nome_arquivo, &num_vertices);

    //funcao para calcular a area do poligono
    area_poligono = CalcularAreaPoligono(vertices, num_vertices);

    //exibe a area do poligono
    printf("Calculo realizado!\nA area do poligono e: [%.2f]\n", area_poligono); // Utilizei [] para facilitar a visualizacao

    //liberando a memoria alocada para os vertices
    free(vertices);

    return 0;
}
