
#include "queue.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    Queue Q;
    createQueue(Q);

    string baris;

    cout << "PROGRAM BUFFER PENCATATAN HASIL UKUR\n";
    cout << "Ketik perintah (TULIS, AMBIL, LIHAT, RINGKAS, KOSONGKAN, SELESAI)\n";

    while (true) {
        cout << "\nPerintah: ";

        if (!getline(cin, baris)) {
            break;
        }

        stringstream ss(baris);
        string perintah;
        ss >> perintah;

        if (perintah == "TULIS") {
            int k;
            int nilai[MAX];
            string tambahan;

            if (!(ss >> k) || k < 1 || k > MAX) {
                cout << "Perintah TULIS ditolak.\n";
                continue;
            }

            bool valid = true;

            for (int i = 0; i < k; i++) {
                if (!(ss >> nilai[i])) {
                    valid = false;
                    break;
                }

                if (nilai[i] < -1000 || nilai[i] > 1000) {
                    valid = false;
                }
            }

            if (ss >> tambahan) {
                valid = false;
            }

            if (!valid || MAX - nbList(Q) < k) {
                cout << "Perintah TULIS ditolak.\n";
                continue;
            }

            for (int i = 0; i < k; i++) {
                enqueue(Q, nilai[i]);
            }

            cout << k << " data berhasil ditambahkan.\n";
        }

        else if (perintah == "AMBIL") {
            int k;
            string tambahan;

            if (!(ss >> k) || k < 1 || k > MAX || (ss >> tambahan)) {
                cout << "Perintah AMBIL ditolak.\n";
                continue;
            }

            if (nbList(Q) < k) {
                cout << "Perintah AMBIL ditolak. Data tidak cukup.\n";
                continue;
            }

            for (int i = 0; i < k; i++) {
                Rekaman hasil = dequeue(Q);
                cout << "Nomor: " << hasil.nomor
                     << ", Nilai: " << hasil.nilai << endl;
            }
        }

        else if (perintah == "LIHAT") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Perintah LIHAT ditolak.\n";
                continue;
            }

            printInfo(Q);
        }

        else if (perintah == "RINGKAS") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Perintah RINGKAS ditolak.\n";
                continue;
            }

            ringkas(Q);
        }

        else if (perintah == "KOSONGKAN") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Perintah KOSONGKAN ditolak.\n";
                continue;
            }

            delAll(Q);
            cout << "Buffer berhasil dikosongkan.\n";
        }

        else if (perintah == "SELESAI") {
            string tambahan;

            if (ss >> tambahan) {
                cout << "Perintah SELESAI ditolak.\n";
                continue;
            }

            cout << "Program selesai.\n";
            break;
        }

        else {
            cout << "Perintah tidak dikenal.\n";
        }
    }

    return 0;
}
