
#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

struct Paket {
    string kode;
    int berat;
};

struct Node {
    Paket info;
    Node *next;
};

struct Queue {
    Node *head;
    Node *tail;
};

void createQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
Node* alokasi(Paket P);
void dealokasi(Node *P);
void enqueue(Queue &Q, Node *P);
Node* dequeue(Queue &Q);
Node* findElm(Queue Q, string kode);
Node* fFindElm(Queue Q, string kode);
int nbList(Queue Q);
void printInfo(Queue Q);
void delAll(Queue &Q);

#endif
