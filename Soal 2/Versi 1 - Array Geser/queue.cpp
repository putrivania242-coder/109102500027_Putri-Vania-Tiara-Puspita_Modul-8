
#include "queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

void createQueue(Queue &Q) {
    Q.head = -1;
    Q.tail = -1;
    Q.nomorBerikutnya = 1;
    Q.totalPergeseran = 0;
}

bool isEmptyQueue(Queue Q) {
    return Q.head == -1;
}

bool isFullQueue(Queue Q) {
    return Q.tail == MAX - 1;
}

int nbList(Queue Q) {
    if (isEmptyQueue(Q)) {
        return 0;
    }
    return Q.tail - Q.head + 1;
}

void enqueue(Queue &Q, int nilai) {
    Q.tail++;
    Q.data[Q.tail].nomor = Q.nomorBerikutnya;
    Q.data[Q.tail].nilai = nilai;
    Q.nomorBerikutnya++;
    
    if (Q.head == -1) {
        Q.head = 0;
    }
}

Rekaman dequeue(Queue &Q) {
    Rekaman hasil = Q.data[Q.head];

    for (int i = Q.head; i < Q.tail; i++) {
        Q.data[i] = Q.data[i + 1];
        Q.totalPergeseran++;
    }

    Q.tail--;

    if (Q.tail == -1) {
        Q.head = -1;
    }

    return hasil;
}

void printInfo(Queue Q) {
    cout << "\nData FIFO: ";

    if (isEmptyQueue(Q)) {
        cout << "Kosong";
    } else {
        for (int i = Q.head; i <= Q.tail; i++) {
            cout << Q.data[i].nomor << ":" << Q.data[i].nilai << " ";
        }
    }

    cout << "\n\nKondisi fisik array:\n";

    for (int i = 0; i < MAX; i++) {
        cout << "Index " << i << ": ";

        if (i >= Q.head && i <= Q.tail && !isEmptyQueue(Q)) {
            cout << Q.data[i].nomor << ":" << Q.data[i].nilai;
        } else {
            cout << "Kosong";
        }

        cout << endl;
    }

    cout << "Head: " << Q.head << endl;
    cout << "Tail: " << Q.tail << endl;
    cout << "Total pergeseran: " << Q.totalPergeseran << endl;
}

void ringkas(Queue Q) {
    int jumlah = nbList(Q);
    int total = 0;
    int minimum = 0;
    int maksimum = 0;

    cout << "\nJumlah data: " << jumlah;
    cout << "\nTotal nilai: ";

    if (jumlah == 0) {
        cout << "0";
        cout << "\nMinimum: TIDAK ADA";
        cout << "\nMaksimum: TIDAK ADA";
        cout << "\nRata-rata: TIDAK ADA\n";
        return;
    }

    minimum = Q.data[Q.head].nilai;
    maksimum = Q.data[Q.head].nilai;

    for (int i = Q.head; i <= Q.tail; i++) {
        int nilai = Q.data[i].nilai;
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
    Q.head = -1;
    Q.tail = -1;
}
