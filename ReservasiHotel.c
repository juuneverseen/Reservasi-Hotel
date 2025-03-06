#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User {
    char username[50];
    char password[50];
    int saldo;
};

struct Kamar {
    char tipe[50];
    int harga;
};

struct Reservasi {
    char nama[50];
    char tipeKamar[50];
    int jumlahMalam;
    int totalHarga;
};

struct User users[100];
struct Kamar kamar[100];
struct Reservasi reservasi[100];

int userCount = 0, kamarCount = 0, reservasiCount = 0;

void LoadData() {
    FILE *file = fopen("users.dat", "rb");
    if (file != NULL) {
        userCount = 0;
        while (fread(&users[userCount], sizeof(struct User), 1, file)) {
            userCount++;
        }
        fclose(file);
    }

    file = fopen("rooms.dat", "rb");
    if (file != NULL) {
        kamarCount = 0;
        while (fread(&kamar[kamarCount], sizeof(struct Kamar), 1, file)) {
            kamarCount++;
        }
        fclose(file);
    }

    file = fopen("reservations.dat", "rb");
    if (file != NULL) {
        reservasiCount = 0;
        while (fread(&reservasi[reservasiCount], sizeof(struct Reservasi), 1, file)) {
            reservasiCount++;
        }
        fclose(file);
    }
}

void Registrasi() {
    struct User newUser ;
    printf("\nRegistrasi User\n");
    printf("Masukkan Username: ");
    scanf("%s", newUser .username);

    if (strcmp(newUser .username, "Admin") == 0) {
        printf("Maaf, Username Admin tidak diperbolehkan!\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, newUser .username) == 0) {
            printf("Username sudah digunakan!\n");
            return;
        }
    }

    printf("Masukkan Password: ");
    scanf("%s", newUser .password);
    newUser .saldo = 0; 

    FILE *file = fopen("users.dat", "ab");
    if (file != NULL) {
        fwrite(&newUser , sizeof(struct User), 1, file);
        fclose(file);
        users[userCount++] = newUser ; 
        printf("Registrasi berhasil!\n");
    } else {
        printf("Gagal menyimpan data user!\n");
    }
}

int LoginAdmin() {
    char username[50], password[50];
    int attempts = 0;

    while (attempts < 3) {
        printf("\nLogin Admin\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "Admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("Login admin berhasil!\n");
            return 1;
        } else {
            attempts++;
            printf("Login gagal! Sisa percobaan: %d\n", 3 - attempts);
        }
    }

    printf("Anda telah melebihi batas percobaan!\n");
    return 0;
}

int LoginUser () {
    char username[50], password[50];

    printf("\nLogin User\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; 
        }
    }

    printf("Login gagal! Username atau password salah.\n");
    return -1; 
}

void LihatAkunUser () {
    printf("\nDaftar Akun User:\n");
    for (int i = 0; i < userCount; i++) {
        printf("Username: %s, Password: %s\n", users[i].username, users[i].password);
    }
}

void TambahTipeKamar() {
    struct Kamar newKamar;
    printf("\nTambah Tipe Kamar\n");
    printf("Masukkan Tipe Kamar: ");
    scanf("%s", newKamar.tipe);
    printf("Masukkan Harga Per Hari: ");
    scanf("%d", &newKamar.harga);

    
    FILE *file = fopen("rooms.dat", "ab");
    if (file != NULL) {
        fwrite(&newKamar, sizeof(struct Kamar), 1, file);
        fclose(file);
        kamar[kamarCount++] = newKamar; 
        printf("Tipe kamar berhasil ditambahkan!\n");
    } else {
        printf("Gagal menyimpan data tipe kamar!\n");
    }
}

void LihatDataReservasi() {
    LoadData(); 
    int pilihan;
    printf("\nPilih Opsi:\n");
    printf("1. Mengurutkan berdasarkan abjad\n");
    printf("2. Mencari berdasarkan nama\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1: {
            if (reservasiCount <= 1) {
                printf("Tidak ada data reservasi atau hanya ada satu data reservasi!\n");
                break;
            }

            for (int i = 0; i < reservasiCount - 1; i++) {
                for (int j = 0; j < reservasiCount - i - 1; j++) {
                    if (strcmp(reservasi[j].nama, reservasi[j + 1].nama) > 0) {
                        struct Reservasi temp = reservasi[j];
                        reservasi[j] = reservasi[j + 1];
                        reservasi[j + 1] = temp;
                    }
                }
            }

            printf("\nData Reservasi yang diurutkan berdasarkan abjad:\n");
            for (int i = 0; i < reservasiCount; i++) {
                printf("Nama: %s, Tipe Kamar: %s, Jumlah Malam: %d, Total Harga: Rp%d\n",
                       reservasi[i].nama, reservasi[i].tipeKamar, 
                       reservasi[i].jumlahMalam, reservasi[i].totalHarga);
            }
            break;
        }

        case 2: {
            char cari[50];
            printf("\nMasukkan nama untuk mencari: ");
            scanf("%s", cari);

            int found = 0;
            for (int i = 0; i < reservasiCount; i++) {
                if (strcmp(reservasi[i].nama, cari) == 0) {
                    printf("Nama: %s, Tipe Kamar: %s, Jumlah Malam: %d, Total Harga: Rp%d\n",
                           reservasi[i].nama, reservasi[i].tipeKamar, 
                           reservasi[i].jumlahMalam, reservasi[i].totalHarga);
                    found = 1;
                }
            }

            if (!found) {
                printf("Data reservasi dengan nama '%s' tidak ditemukan.\n", cari);
            }
            break;
        }

        default:
            printf("Pilihan tidak valid!\n");
    }
}

void CekPendapatan() {
    int totalPendapatan = 0;
    for (int i = 0; i < reservasiCount; i++) {
        totalPendapatan += reservasi[i].totalHarga;
    }
    printf("\nTotal Pendapatan: Rp%d\n", totalPendapatan);
}

void LihatTipeKamar() {
    
    for (int i = 0; i < kamarCount - 1; i++) {
        for (int j = 0; j < kamarCount - i - 1; j++) {
            if (kamar[j].harga > kamar[j + 1].harga) {
                struct Kamar temp = kamar[j];
                kamar[j] = kamar[j + 1];
                kamar[j + 1] = temp;
            }
        }
    }

    printf("\nTipe Kamar (Urut dari Harga Termurah):\n");
    for (int i = 0; i < kamarCount; i++) {
        printf("%d. Tipe: %s, Harga: Rp%d\n", i + 1, kamar[i].tipe, kamar[i].harga);
    }
}

void CekSaldo(int userIndex) {
    printf("\nSaldo Anda: Rp%d\n", users[userIndex].saldo);
}

void TopUpSaldo(int userIndex) {
    int jumlah;
    printf("\nMasukkan jumlah top-up: Rp");
    scanf("%d", &jumlah);

    if (jumlah > 0) {
        users[userIndex].saldo += jumlah; 
        printf("Top-up berhasil! Saldo Anda sekarang: Rp%d\n", users[userIndex].saldo);
        
        
        FILE *file = fopen("users.dat", "rb+");
        if (file != NULL) {
            fseek(file, userIndex * sizeof(struct User), SEEK_SET);
            fwrite(&users[userIndex], sizeof(struct User), 1, file);
            fclose(file);
        } else {
            printf("Gagal membuka file data pengguna!\n");
        }
    } else {
        printf("Jumlah top-up tidak valid!\n");
    }
}

void PesanKamar(int userIndex) {
    int pilihan, jumlahMalam;

    LihatTipeKamar();
    printf("\nPilih nomor kamar yang ingin dipesan: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > kamarCount) {
        printf("Nomor kamar tidak valid!\n");
        return;
    }

    printf("Masukkan jumlah malam: ");
    scanf("%d", &jumlahMalam);

    int totalHarga = kamar[pilihan - 1].harga * jumlahMalam;
    if (users[userIndex].saldo < totalHarga) {
        printf("Saldo Anda tidak mencukupi untuk melakukan reservasi!\n");
        return;
    }

    users[userIndex].saldo -= totalHarga;

    
    struct Reservasi newReservasi;
    strcpy(newReservasi.nama, users[userIndex].username);
    strcpy(newReservasi.tipeKamar, kamar[pilihan - 1].tipe);
    newReservasi.jumlahMalam = jumlahMalam;
    newReservasi.totalHarga = totalHarga;

    FILE *reservasiFile = fopen("reservations.dat", "ab");
    if (reservasiFile != NULL) {
        fwrite(&newReservasi, sizeof(struct Reservasi), 1, reservasiFile);
        fclose(reservasiFile);
        printf("Reservasi berhasil dilakukan!\n");
    } else {
        printf("Gagal menyimpan reservasi!\n");
    }

    
    FILE *userFile = fopen("users.dat", "rb+");
    if (userFile != NULL) {
        fseek(userFile, userIndex * sizeof(struct User), SEEK_SET);
        fwrite(&users[userIndex], sizeof(struct User), 1, userFile);
        fclose(userFile);
    } else {
        printf("Gagal membuka file data pengguna!\n");
    }
}

void DataReservasiUser(int userIndex) {
    LoadData(); 
    printf("\nData Reservasi Anda:\n");
    int found = 0;

    for (int i = 0; i < reservasiCount; i++) {
        if (strcmp(reservasi[i].nama, users[userIndex].username) == 0) {
            printf("Tipe Kamar: %s, Jumlah Malam: %d, Total Harga: Rp%d\n",
                   reservasi[i].tipeKamar, reservasi[i].jumlahMalam,
                   reservasi[i].totalHarga);
            found = 1;
        }
    }

    if (!found) {
        printf("Anda belum memiliki reservasi.\n");
    }
}

void MenuAdmin() {
    int pilihan;
    do {
        printf("\nMenu Admin\n");
        printf("1. Lihat Akun User\n");
        printf("2. Tambah Tipe Kamar\n");
        printf("3. Lihat Data Reservasi\n");
        printf("4. Cek Pendapatan\n");
        printf("5. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                LihatAkunUser ();
                break;
            case 2:
                TambahTipeKamar();
                break;
            case 3:
                LihatDataReservasi();
                break;
            case 4:
                CekPendapatan();
                break;
            case 5:
                printf("Logout berhasil!\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (1);
}

void MenuUser (int userIndex) {
    int pilihan;
    do {
        printf("\nMenu User\n");
        printf("1. Lihat Tipe Kamar\n");
        printf("2. Cek Saldo\n");
        printf("3. Top Up Saldo\n");
        printf("4. Pesan Kamar\n");
        printf("5. Lihat Data Reservasi\n");
        printf("6. Logout\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                LihatTipeKamar();
                break;
            case 2:
                CekSaldo(userIndex);
                break;
            case 3:
                TopUpSaldo(userIndex);
                break;
            case 4:
                PesanKamar(userIndex);
                break;
            case 5:
                DataReservasiUser (userIndex);
                break;
            case 6:
                printf("Logout berhasil!\n");
                return;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (1);
}

void MenuLogin() {
    int pilihan;

    printf("\nMenu Login\n");
    printf("1. Login sebagai Admin\n");
    printf("2. Login sebagai User\n");
    printf("3. Kembali ke Menu Utama\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            if (LoginAdmin()) {
                MenuAdmin();
            }
            break;
        case 2: {
            int userIndex = LoginUser ();
            if (userIndex != -1) {
                MenuUser (userIndex);
            }
            break;
        }
        case 3:
            printf("Kembali ke menu utama\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
    }
}

int main() {
    LoadData(); 
    int pilihan;

    do {
        printf("\nMenu Utama\n");
        printf("1. Registrasi\n");
        printf("2. Login\n");
        printf("3. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                Registrasi();
                break;
            case 2:
                MenuLogin();
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 3);

    return 0;
}