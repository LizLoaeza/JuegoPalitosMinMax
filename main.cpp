/*
    Juego de los palitos, hecho para la materia de inteligencia artificial.
    Por Elizabeth Loaeza Morales.
*/

#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int maxDepht = 10;
const int infinte = numeric_limits<int>::max();
int sticks;
int actPlayer;

vector<pair<int, int>> getTree(int sticks, int actPlayer) {
    vector<pair<int, int>> branches;
    for (int i = 1; i <= 3; i++) {
        if (i <= sticks) {
            branches.push_back(make_pair(sticks - i, actPlayer == 1 ? 2 : 1));
        }
    }
    return branches;
}


int miniMax(int sticks, int actPlayer, bool turn, int depht) {
    if (sticks == 1) {
        return turn ? -1 : 1;
    }
    if (depht == 0) {
        return 0;
    }
    int m = turn ? -1 : 1;
    vector<pair<int, int>> branches = getTree(sticks, actPlayer);
    for (const auto& v : branches) {
        int t = miniMax(v.first, v.second, depht - 1, !turn);
        if ((turn && t > m) || (!turn && t < m)) {
            m = t;
        }
    }
    return m;
}


int ia(int stick) {
    int m = -2;
    int bestMove = 1;
    vector<pair<int, int>> branches = getTree(stick, 1);
    for (const auto& v : branches) {
        int t = miniMax(v.first, v.second, maxDepht, false);
        if (t > m) {
            m = t;
            bestMove = stick - v.first;
        }
    }
    return bestMove;
}


int main() {
    srand(time(NULL));
    int sticks = 12 + rand() % 9;
    int actPlayer = rand() % 2 + 1;

    cout << "Palitos iniciales: " << sticks << endl;
    cout << (actPlayer == 1 ? "Humano" : "IA") << " inicia el juego." << endl;

    while (sticks > 0) {
        cout << "Palitos restantes: " << sticks << endl;

        int sticksOut;
        if (actPlayer == 1) {
            cout << "Humano, ingrese el numero de palitos que desea tomar, puede tomar solo 1, 2 o 3: ";
            cin >> sticksOut;
            while (sticksOut < 1 || sticksOut > 3 || sticksOut > sticks) {
                cout << " No sabe leer? ingrese un numero valido, puede tomar solo 1, 2 o 3: ";
                cin >> sticksOut;
            }
            sticks -= sticksOut;
            actPlayer = 2;
        } else {
            sticksOut = ia(sticks);
            sticks -= sticksOut;
            cout << "La IA toma " << sticksOut << " palito(s)." << endl;
            actPlayer = 1;
        }

        if (sticks == 1) {
            cout << (actPlayer == 1 ? "IA" : "Humano") << " gana!" << endl;
            break;
        }
    }

    return 0;
}
