
#ifndef QUEUE_H
#define QUEUE_H

const int MAX = 6;

struct Rekaman {
    int nomor;
    int nilai;
};

struct Queue {
    Rekaman data[MAX];
    int head;
    int tail;
    int nomorBerikutnya;
    int totalPergeseran;
};

void createQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
bool isFullQueue(Queue Q);
void enqueue(Queue &Q, int nilai);
Rekaman dequeue(Queue &Q);
int nbList(Queue Q);
void printInfo(Queue Q);
void ringkas(Queue Q);
void delAll(Queue &Q);

#endif
