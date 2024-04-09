#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

// Dimensiones del laberinto
const int WIDTH = 20;
const int HEIGHT = 10;

// Representación del laberinto
vector<vector<char>> maze(HEIGHT, vector<char>(WIDTH, '#'));

// Posición del jugador
int playerX = 1;
int playerY = 1;

// Función para imprimir el laberinto
void printMaze() {
    // Imprimir el laberinto con los bordes y la posición del jugador
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == playerY && j == playerX) {
                cout << "C"; // Imprimir al jugador
            }
            else if (i == 1 && j == 9) {
                cout << " "; // Dejar vacía la posición (1, 9)
            }
            else {
                cout << maze[i][j]; // Imprimir los obstáculos
            }
        }
        cout << endl;
    }
}

// Función para generar el laberinto utilizando Recursive Backtracking
void generateMaze(int x, int y) {
    static int dx[] = { 1, 0, -1, 0 };
    static int dy[] = { 0, 1, 0, -1 };

    // Randomizar el orden de los movimientos
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        swap(dx[i], dx[r]);
        swap(dy[i], dy[r]);
    }

    // Intentar moverse en todas las direcciones
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i] * 2;
        int ny = y + dy[i] * 2;

        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && maze[ny][nx] == '#') {
            maze[y + dy[i]][x + dx[i]] = ' '; // Quitar el muro entre los espacios
            maze[ny][nx] = ' '; // Marcar el nuevo espacio
            generateMaze(nx, ny); // Llamar recursivamente para el nuevo espacio
        }
    }
}

int main() {
    // Inicializar la semilla para generar números aleatorios
    srand(time(nullptr));

    // Generar el laberinto
    generateMaze(1, 1);

    // Bucle principal del juego
    while (true) {
        system("cls"); // Limpiar la consola

        // Imprimir el laberinto
        printMaze();

        // Capturar la entrada del jugador
        char input = _getch();
        int newX = playerX;
        int newY = playerY;
        switch (input) {
        case 'w':
            newY--;
            break;
        case 's':
            newY++;
            break;
        case 'a':
            newX--;
            break;
        case 'd':
            newX++;
            break;
        case 'q':
            exit(0); // Salir del juego si el usuario presiona 'q'
        default:
            break;
        }

        // Verificar si la nueva posición es un obstáculo ('#')
        if (maze[newY][newX] != '#') {
            // Mover al jugador a la nueva posición
            playerX = newX;
            playerY = newY;

            // Verificar si el jugador ha ganado
            if (playerX == 1 && playerY == 9) {
                system("cls");
                cout << "¡Has ganado!" << endl;
                break; // Salir del bucle del juego
            }
        }
    }

    return 0;
}
