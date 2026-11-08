
#include "queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

void createQueue(Queue &Q) {
    Q.head = 0;
    Q.count = 0;
    Q.nomorBerikutnya = 1;
    Q.totalPergeseran = 0;
}

bool isEmptyQueue(Queue Q) {
    return Q.count == 0;
}

bool isFullQueue(Queue Q) {
    return Q.count == MAX;
}

int nbList(Queue Q) {
    return Q.count;
}

void enqueue(Queue &Q, int nilai) {
    int posisi = (Q.head + Q.count) % MAX;

    Q.data[posisi].nomor = Q.nomorBerikutnya;
    Q.data[posisi].nilai = nilai;

    Q.nomorBerikutnya++;
    Q.count++;
}

Rekaman dequeue(Queue &Q) {
    Rekaman hasil = Q.data[Q.head];

    Q.head = (Q.head + 1) % MAX;
    Q.count--;

    if (Q.count == 0) {
        Q.head = 0;
    }

    return hasil;
}

void printInfo(Queue Q) {
    cout << "\nData FIFO: ";

    if (isEmptyQueue(Q)) {
        cout << "Kosong";
    } else {
        for (int i = 0; i < Q.count; i++) {
            int posisi = (Q.head + i) % MAX;
            cout << Q.data[posisi].nomor << ":"
                 << Q.data[posisi].nilai << " ";
        }
    }

    cout << "\n\nKondisi fisik array:\n";

    for (int i = 0; i < MAX; i++) {
        bool terisi = false;

        for (int j = 0; j < Q.count; j++) {
            int posisi = (Q.head + j) % MAX;

            if (posisi == i) {
                terisi = true;
                break;
            }
        }

        cout << "Index " << i << ": ";

        if (terisi) {
            cout << Q.data[i].nomor << ":" << Q.data[i].nilai;
        } else {
            cout << "Kosong";
        }

        cout << endl;
    }

    cout << "Head: " << Q.head << endl;
    cout << "Count: " << Q.count << endl;
    cout << "Total pergeseran: " << Q.totalPergeseran << endl;
}

void ringkas(Queue Q) {
    int jumlah = nbList(Q);
    int total = 0;

    cout << "\nJumlah data: " << jumlah;
    cout << "\nTotal nilai: ";

    if (jumlah == 0) {
        cout << "0";
        cout << "\nMinimum: TIDAK ADA";
        cout << "\nMaksimum: TIDAK ADA";
        cout << "\nRata-rata: TIDAK ADA\n";
        return;
    }

    int posisiAwal = Q.head;
    int minimum = Q.data[posisiAwal].nilai;
    int maksimum = Q.data[posisiAwal].nilai;

    for (int i = 0; i < jumlah; i++) {
        int posisi = (Q.head + i) % MAX;
        int nilai = Q.data[posisi].nilai;

        total += nilai;

        if (nilai < minimum) {
            minimum = nilai;
        }

        if (nilai > maksimum) {
            maksimum = nilai;
        }
    }

    cout << total;
    cout << "\nMinimum: " << minimum;
    cout << "\nMaksimum: " << maksimum;
    cout << "\nRata-rata: " << fixed << setprecision(2)
         << static_cast<double>(total) / jumlah << endl;
}

void delAll(Queue &Q) {
    Q.head = 0;
    Q.count = 0;
}
