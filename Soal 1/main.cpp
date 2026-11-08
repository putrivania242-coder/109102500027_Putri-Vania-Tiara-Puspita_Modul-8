
#include <iostream>
#include <sstream>
#include <string>
#include <new>
#include "queue.h"
using namespace std;

int totalTerkirim = 0;
long long beratTerkirim = 0;

bool kodeValid(string kode) {
    return kode.length() >= 1 && kode.length() <= 10;
}

bool paketAda(Queue A, Queue B, string kode) {
    return findElm(A, kode) != nullptr ||
           findElm(B, kode) != nullptr;
}

long long totalBerat(Queue Q) {
    long long total = 0;
    Node *P = Q.head;

    while (P != nullptr) {
        total += P->info.berat;
        P = P->next;
    }

    return total;
}

void tampilRekap(Queue A, Queue B) {
    cout << "Jumlah paket A: " << nbList(A) << endl;
    cout << "Total berat A: " << totalBerat(A) << " gram" << endl;

    cout << "Jumlah paket B: " << nbList(B) << endl;
    cout << "Total berat B: " << totalBerat(B) << " gram" << endl;

    cout << "Jumlah terkirim: " << totalTerkirim << endl;
    cout << "Total berat terkirim: " << beratTerkirim << " gram" << endl;
}

int main() {
    Queue A, B;
    string perintah, kode, tambahan;
    int berat, n;

    createQueue(A);
    createQueue(B);

    cout << "=== SISTEM SORTIR DAN PENGIRIMAN PAKET ===" << endl;
    cout << "Perintah: MASUK, PINDAH, KIRIM, CARI, LIHAT, REKAP, BERSIHKAN, SELESAI" << endl;

    while (true) {
        cout << "\nPerintah: ";
        getline(cin, perintah);

        stringstream ss(perintah);
        string cmd;
        ss >> cmd;

        if (cmd == "MASUK") {
            Paket P;

            if (!(ss >> P.kode >> P.berat) || (ss >> tambahan)) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            if (!kodeValid(P.kode) || P.berat < 1 || P.berat > 5000) {
                cout << "Ditolak: kode harus 1-10 karakter dan berat 1-5000 gram." << endl;
                continue;
            }

            if (paketAda(A, B, P.kode)) {
                cout << "Ditolak: kode paket sudah aktif." << endl;
                continue;
            }

            Node *N = nullptr;

            try {
                N = alokasi(P);
            } catch (bad_alloc &) {
                cout << "Ditolak: alokasi memori gagal." << endl;
                continue;
            }

            enqueue(A, N);
            cout << "Paket berhasil masuk ke A." << endl;
        }

        else if (cmd == "PINDAH") {
            if (!(ss >> n) || (ss >> tambahan)) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            if (n <= 0 || n > nbList(A)) {
                cout << "Ditolak: jumlah harus positif dan tidak melebihi paket di A." << endl;
                continue;
            }

            bool alamatTetap = true;

            for (int i = 0; i < n; i++) {
                string kodePindah = A.head->info.kode;

                Node *sebelum = fFindElm(A, kodePindah);
                Node *P = dequeue(A);

                enqueue(B, P);

                Node *sesudah = fFindElm(B, kodePindah);

                if (sebelum != sesudah) {
                    alamatTetap = false;
                }
            }

            cout << n << " paket berhasil dipindahkan ke B." << endl;

            if (alamatTetap) {
                cout << "Uji fFindElm: alamat node tetap sama setelah dipindahkan." << endl;
            } else {
                cout << "Uji fFindElm: alamat node berubah." << endl;
            }
        }

        else if (cmd == "KIRIM") {
            if (!(ss >> n) || (ss >> tambahan)) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            if (n <= 0 || n > nbList(B)) {
                cout << "Ditolak: jumlah harus positif dan tidak melebihi paket di B." << endl;
                continue;
            }

            for (int i = 0; i < n; i++) {
                Node *P = dequeue(B);

                cout << "Terkirim: " << P->info.kode
                     << " (" << P->info.berat << " gram)" << endl;

                totalTerkirim++;
                beratTerkirim += P->info.berat;

                dealokasi(P);
            }
        }

        else if (cmd == "CARI") {
            if (!(ss >> kode) || (ss >> tambahan)) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            Node *P = findElm(A, kode);

            if (P != nullptr) {
                int posisi = 1;
                Node *C = A.head;

                while (C != P) {
                    posisi++;
                    C = C->next;
                }

                cout << "Lokasi: A" << endl;
                cout << "Posisi: " << posisi << endl;
                cout << "Berat: " << P->info.berat << " gram" << endl;
            } else {
                P = findElm(B, kode);

                if (P != nullptr) {
                    int posisi = 1;
                    Node *C = B.head;

                    while (C != P) {
                        posisi++;
                        C = C->next;
                    }

                    cout << "Lokasi: B" << endl;
                    cout << "Posisi: " << posisi << endl;
                    cout << "Berat: " << P->info.berat << " gram" << endl;
                } else {
                    cout << "TIDAK DITEMUKAN" << endl;
                }
            }
        }

        else if (cmd == "LIHAT") {
            if (ss >> tambahan) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            cout << "Queue A: ";
            printInfo(A);
            cout << endl;

            cout << "Queue B: ";
            printInfo(B);
            cout << endl;
        }

        else if (cmd == "REKAP") {
            if (ss >> tambahan) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            tampilRekap(A, B);
        }

        else if (cmd == "BERSIHKAN") {
            if (ss >> tambahan) {
                cout << "Ditolak: format perintah tidak valid." << endl;
                continue;
            }

            delAll(A);
            delAll(B);

            cout << "Seluruh paket di A dan B berhasil dibersihkan." << endl;
        }

        else if (cmd == "SELESAI") {
            delAll(A);
            delAll(B);

            cout << "Sisa node berhasil dibebaskan." << endl;
            cout << "Program selesai." << endl;
            break;
        }

        else {
            cout << "Perintah tidak dikenal." << endl;
        }
    }

    return 0;
}
