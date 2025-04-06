#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

#include "point.h"

using namespace std;

// Función para comparar puntos por coordenada X
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Función para comparar puntos por coordenada Y
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Función para calcular la distancia euclidiana
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Función recursiva para encontrar la menor distancia
// Recibe los puntos ordenados por X y dos vectores auxiliares para evitar allocaciones
double MinDistance(const vector<Point>& pointsX, int inicio, int final, vector<Point>& pointsY, vector<Point>& stripY) {
    int n = final - inicio;

    if (n <= 3) {
        double minD = numeric_limits<double>::max();
        for (int i = inicio; i < final; ++i) {
            for (int j = i + 1; j < final; ++j) {
                minD = min(minD, distance(pointsX[i], pointsX[j]));
            }
        }
        // Para el caso base, también ordenamos los puntos correspondientes en pointsY
        sort(pointsY.begin() + inicio, pointsY.begin() + final, compareY);
        return minD;
    }

    int mid = inicio + n / 2;
    double midX = pointsX[mid].x;

    // Dividir el vector pointsY en dos mitades
    // Sin nuevas allocaciones
    int leftSize = 0;
    for (int i = inicio; i < final; ++i) {
        if (pointsY[i].x <= midX) {
            pointsY[inicio + leftSize++] = pointsY[i];
        }
    }
    int rightSize = n - leftSize;
    // Los elementos restantes ya están en la parte derecha de pointsY

    double dL = MinDistance(pointsX, inicio, mid, pointsY, stripY);
    double dR = MinDistance(pointsX, mid, final, pointsY, stripY);
    double dLR = min(dL, dR);

    // Construir el intervalo de puntos cercanos al eje medio
    int stripCount = 0;
    for (int i = inicio; i < final; ++i) {
        if (abs(pointsY[i].x - midX) < dLR) {
            stripY[stripCount++] = pointsY[i];
        }
    }

    // Encontrar la distancia mínima en la franja
    for (int i = 0; i < stripCount; ++i) {
        for (int j = i + 1; j < stripCount && (stripY[j].y - stripY[i].y) < dLR; ++j) {
            dLR = min(dLR, distance(stripY[i], stripY[j]));
        }
    }

    // Fusionar las mitades ordenadas de pointsY (inplace merge)
    // Esto es más eficiente que usar el sort(Intervalo.begin(), Intervalo.end(), compareY); del otro codigo dado que ya están ordenadas por Y
    // Y evita la necesidad de reallocar memoria    
    inplace_merge(pointsY.begin() + inicio, pointsY.begin() + inicio + leftSize, pointsY.begin() + final, compareY);

    printf("dL: %f, dR: %f, dLR: %f\n", dL, dR, dLR); // Debugging
    return dLR;
}

// Función principal
double MinDistanceOptimized(vector<Point>& points) {
    int n = points.size();
    if (n < 2) {
        cerr << "Se necesitan al menos 2 puntos." << endl;
        return numeric_limits<double>::max();
    }

    //Ordenar los puntos por coordenada X
    vector<Point> pointsX = points;
    sort(pointsX.begin(), pointsX.end(), compareX);

    //Inicializar el vector pointsY ordenado por Y y el vector auxiliar stripY
    vector<Point> pointsY = pointsX;
    vector<Point> stripY(n);

    //Llamar a la función recursiva optimizada
    return MinDistance(pointsX, 0, n, pointsY, stripY);
}   