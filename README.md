# Tugas Kecil 3 IF2211 Strategi Algoritma 
**Penyelesaian Permainan *Ice Sliding Puzzle* Menggunakan Algoritma *Pathfinding***


## Penjelasan Singkat Program
Program ini adalah sebuah *solver* (penyelesaian) untuk permainan *Ice Sliding Puzzle* yang dibangun menggunakan bahasa pemrograman C++. Dalam permainan ini, sebuah aktor bergerak meluncur di atas lantai es yang licin, di mana aktor tidak dapat berhenti di tengah jalan kecuali menabrak rintangan. 

## Struktur Direktori
Tucil3_13524009/
├── bin/                    # Executable file
│   └── solver(.exe)
├── doc/                    # Dokumentasi
│   └── Laporan.pdf
├── src/                    # Source code
│   ├── header/
│   │   └── IceSlider.h
│   ├── cpp/
│   │   └── IceSlider.cpp
│   └── main.cpp
├── test/                   # File test case input
│   ├── input1.txt
│   ├── input2.txt
│   ├── input3.txt
│   ├── input4.txt
│   └── input5.txt
├── solve/                  # Output solusi (auto-generated)
│   └── solusi_*.txt
└── README.md

### Algoritma yang Diimplementasikan
Program ini mengimplementasikan empat buah algoritma pencarian (*pathfinding*):

1. **UCS (Uniform Cost Search):** Algoritma pencarian berdasarkan *cost* lintasan terendah.
2. **GBFS (Greedy Best-First Search):** Algoritma pencarian heuristik berfokus pada jarak terdekat menuju target.
3. **A* (A-Star):** Algoritma optimal yang menyeimbangkan *cost* lintasan aktual dan estimasi heuristik.
4. **BFS (Breadth-First Search) [Bonus]:** Algoritma pencarian buta berbasis antrean untuk rute dengan langkah pergerakan terminimal.

### Fungsi Heuristik
Program menyediakan tiga pilihan fungsi heuristik untuk algoritma A* dan GBFS:
- **Manhattan Distance (H1):** |x₁ - x₂| + |y₁ - y₂|
- **Euclidean Distance (H2):** √((x₁ - x₂)² + (y₁ - y₂)²)
- **Chebyshev Distance (H3):** max(|x₁ - x₂|, |y₁ - y₂|)

---

## Requirement Program
Program ini ditulis menggunakan **C++ Standard Template Library (STL)** tanpa *library* eksternal tambahan. 

### Kebutuhan Sistem
- *Compiler* C++ yang mendukung standar **C++11 ke atas** (contoh: MinGW / GCC / G++)

---

## Cara Mengkompilasi Program
### Untuk Windows / Linux / macOS:
```bash
g++ src/main.cpp src/cpp/IceSlider.cpp -I src/header -o bin/solver
```

Perintah ini akan menghasilkan *executable file*:
- **Windows:** `bin/solver.exe`
- **Linux/macOS:** `bin/solver`

---

## Cara Menjalankan dan Menggunakan Program

### 1. Menjalankan Program
Dari *root directory* proyek, jalankan file *executable*:

**Windows:**
```bash
./bin/solver.exe
```

**Linux / macOS:**
```bash
./bin/solver
```

### 2. Alur Penggunaan Program

#### a. Memasukkan Input
Program akan meminta *path* ke file matriks papan. Contoh:
Masukan file input :
test/input1.txt

#### b. Memilih Algoritma
Ketik salah satu nama algoritma yang ingin diuji:
Algoritma apa yang anda pilih? (UCS/GBFS/A*/BFS)
A*

#### c. Memilih Heuristik (Khusus A* dan GBFS)
Pilih angka (1/2/3) untuk heuristik yang diinginkan:
Heuristic apa yang anda pilih?
1. Manhattan (H1)
2. Euclidean (H2)
3. Chebyshev (H3)
Pilihan (1/2/3): 2

#### d. Playback 
Kontrol playback:
- **A** - Mundur satu step
- **D** - Maju satu step
- **J** - Lompat ke step tertentu
- **Q** - Keluar dari playback

## Author

**Mikhael Benrael Tampubolon**
- NIM: 13524009
- Program Studi: Teknik Informatika
- Institut Teknologi Bandung
- Tahun: 2026