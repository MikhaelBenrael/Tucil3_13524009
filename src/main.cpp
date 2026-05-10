#include "IceSlider.h"

int main() {
    IceSlider game;
    string filename;
    
    cout << ">> Masukan file input :\n";
    cin >> filename;

    if (!game.loadMap(filename)) {
        cout << "Gagal membaca file " << filename << endl;
        return 1;
    }

    cout << ">> Algoritma apa yang anda pilih? (UCS/GBFS/A*/BFS)\n";
    string algo; cin >> algo;

    int h_type = 1;
    if (algo == "A*" || algo == "GBFS") {
        cout << ">> Heuristic apa yang anda pilih?\n";
        cout << "1. Manhattan (H1)\n2. Euclidean (H2)\n3. Chebyshev (H3)\nPilihan (1/2/3): ";
        cin >> h_type;
    }

    game.solve(algo, h_type);
    return 0;
}