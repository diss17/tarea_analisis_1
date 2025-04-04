#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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

// Función para calcular la distancia euclidiana entre dos puntos
double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

// Función recursiva para encontrar la menor distancia en un rango de puntos
double MinDistance(vector<Point>& points, int inicio, int final) {
    // Caso base: si hay 1 o 2 puntos
    if (final - inicio == 1) {
        return 1e9; // Infinito (no hay distancia válida)
    }
    if (final - inicio == 2) {
        return distance(points[inicio], points[inicio + 1]);
    }

    // Dividir el conjunto de puntos en dos mitades
    int mid = (inicio + final) / 2;
    double midX = points[mid].x;

    // Calcular la menor distancia en las mitades izquierda y derecha
    double dIzq = MinDistance(points, inicio, mid);
    double dDer = MinDistance(points, mid, final);
    double dLR = min(dIzq, dDer);

    // Construir el intervalo de puntos cercanos al eje medio
    vector<Point> Intervalo;
    for (int i = inicio; i < final; ++i) {
        if (abs(points[i].x - midX) < dLR) {
            Intervalo.push_back(points[i]);
        }
    }

    // Ordenar el intervalo por coordenada Y
    sort(Intervalo.begin(), Intervalo.end(), compareY);

    // Calcular la menor distancia en el intervalo
    double minIntervaloDist = dLR;
    int IntervaloSize = Intervalo.size();
    for (int i = 0; i < IntervaloSize; ++i) {
        for (int j = i + 1; j < IntervaloSize && (Intervalo[j].y - Intervalo[i].y) < minIntervaloDist; ++j) {
            double dist = distance(Intervalo[i], Intervalo[j]);
            if (dist < minIntervaloDist) {
                minIntervaloDist = dist;
            }
        }
    }

    return min(dLR, minIntervaloDist);
}

// Función principal para encontrar la menor distancia
double MinDistance(vector<Point>& points) {
    // Ordenar los puntos por coordenada X
    vector<Point> OrderPoints = points;
    sort(OrderPoints.begin(), OrderPoints.end(), compareX);

    // Llamar a la función recursiva
    return MinDistance(OrderPoints, 0, OrderPoints.size());
}