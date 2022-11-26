#pragma once

#include <iostream>
#include <tuple>
#include <ctype.h>

#include "../include/struct.h"
#include "../include/utility.h"
#include "../include/auth.h"

using namespace std;

namespace menu {
  int check(string choice) {
    try {
      int int_choice = stoi(choice);
      return int_choice;
    } 
    catch (...) {
      cin.clear(); 
      return 0;
    }
  }

  int landing() {
    string choice;
    utility::header("Mangan - Antaran Ketika Lapar");
    cout  << "1. 🔑 Masuk" << endl
          << "2. 📝 Menjadi Pengguna" << endl
          << "3. ❔ Tentang" << endl
          << "4. ❌ Tutup" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int login() {
    string choice;
    utility::header("Mangan - Masuk Sebagai?");
    cout  << "1. 😄 Pengguna" << endl
          << "2. 🛵 Driver" << endl
          << "3. ⬅  Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  // * FOR USER
  int user() {
    string choice;
    utility::header("Mangan - Hi, Sahabat Lapar!!", "Bagaimana kabarmu, " + auth.name);
    cout  << "1. 🏃 Daftar Order" << endl
          << "2. 🍖 Cari Mangan" << endl
          << "3. ⬅  Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int user_order() {
    string choice;
    cout  << "1. 📝 Buat Pesanan" << endl
          << "2. ⬅  Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int user_list() {
    string choice;
    cout  << "1. ✅ Selesaikan Pesanan" << endl
          << "2. 📝 Detail Pesanan" << endl
          << "3. ⬅  Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  // * FOR DRIVER
  int driver() {
    string choice;
    utility::header("Mangan - Hi, Driver Mangan!!", "Siap bekerja, " + auth.name + "?");
    cout  << "1. 🏃 Daftar Order" << endl
          << "2. ⬅  Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }
  // * FOR ADMIN
  int admin() {
    string choice;
    utility::header("Mangan - Hi, Admin!!");
    cout  << "1. 🏃 Order Menunggu" << endl
          << "2. ⏳ Order Diterima" << endl
          << "3. 🍖 Order" << endl
          << "4. 😄 Pengguna" << endl
          << "5. 🛵 Driver" << endl
          << "6. 🥣 Menu" << endl
          << "7. ⬅  Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int admin_waiting() {
    string choice;
    cout  << "1. ✅ Terima Pesanan Pertama" << endl
          << "2. ❎ Tolak Pesanan Pertama" << endl
          << "3. ⬅  Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int admin_driver() {
    string choice;
    utility::header("Mangan - 🛵 Manajamen Driver");
    cout  << "1. 📖 Daftar Driver" << endl
          << "2. ➕ Tambah Driver" << endl
          << "3. 📝 Ubah Driver" << endl
          << "4. ❌ Hapus Driver" << endl
          << "5. ⬅ Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int admin_user() {
    string choice;
    utility::header("Mangan - 😄 Manajamen Pengguna");
    cout  << "1. 📖 Daftar Pengguna" << endl
          << "2. ➕ Tambah Pengguna" << endl
          << "3. 📝 Ubah Pengguna" << endl
          << "4. ❌ Hapus Pengguna" << endl
          << "5. ⬅ Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int admin_menu() {
    string choice;
    utility::header("Mangan - 🥣 Manajamen Menu");
    cout  << "1. 📖 Daftar Menu" << endl
          << "2. ➕ Tambah Menu" << endl
          << "3. 📝 Ubah Menu" << endl
          << "4. ❌ Hapus Menu" << endl
          << "5. ⬅ Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int admin_delivery() {
    string choice;
    utility::header("Mangan - 🛵 Manajamen Pesanan");
    cout  << "1. 📖 Daftar Pesanan" << endl
          << "3. 📝 Ubah Pesanan" << endl
          << "4. ❌ Hapus Pesanan" << endl
          << "5. ⬅ Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  // ** FOR OTHERS
  int searching() {
    string choice;
    utility::cout("black", "\nApa yang ingin anda lakukan :");
    utility::cout("yellow", "1. Sorting     2. Searching    3. Reset    4. Kembali");
    cout << "Pilih : "; cin >> choice;
    return check(choice);
  }

  tuple<int, int> sorting(string columns[], int length) {
    int column, type;
    utility::cout("yellow", "Daftar kolom: ");
    for(int i = 1; i < length; i++) { 
      utility::cout("yellow", to_string(i) + ". " + columns[i]);
    }
    cout << "\nPilih kolom: "; cin >> column;
    cout << "Pilih tipe (1 = asc, 2 = desc): "; cin >> type;
    return make_tuple(column, type);
  }

}