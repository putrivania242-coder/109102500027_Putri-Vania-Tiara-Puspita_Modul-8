
#include "queue.h"
#include <iostream>
using namespace std;

void createQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(Queue Q) {
    return Q.head == nullptr;
}

Node* alokasi(Paket P) {
    Node *N = new Node;
    N->info = P;
    N->next = nullptr;
    return N;
}

void dealokasi(Node *P) {
    delete P;
}

void enqueue(Queue &Q, Node *P) {
    if (P == nullptr) {
        return;
    }

    P->next = nullptr;

    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

Node* dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) {
        return nullptr;
    }

    Node *P = Q.head;
    Q.head = Q.head->next;

    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }

    P->next = nullptr;
    return P;
}

Node* findElm(Queue Q, string kode) {
    Node *P = Q.head;

    while (P != nullptr) {
        if (P->info.kode == kode) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

Node* fFindElm(Queue Q, string kode) {
    Node *P = Q.head;

    while (P != nullptr) {
        if (P->info.kode == kode) {
            return P;
        }

        P = P->next;
    }

    return nullptr;
}

int nbList(Queue Q) {
    int jumlah = 0;
    Node *P = Q.head;

    while (P != nullptr) {
        jumlah++;
        P = P->next;
    }

    return jumlah;
}

void printInfo(Queue Q) {
    Node *P = Q.head;

    if (isEmptyQueue(Q)) {
        cout << "Kosong";
        return;
    }

    while (P != nullptr) {
        cout << P->info.kode << " (" 
             << P->info.berat << " gram)";

        if (P->next != nullptr) {
            cout << " -> ";
        }

        P = P->next;
    }
}

void delAll(Queue &Q) {
    while (!isEmptyQueue(Q)) {
        Node *P = dequeue(Q);
        dealokasi(P);
    }
}
