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
    cout  << "1. 🏃 Order Berlangsung" << endl
          << "2. 🍖 Cari Mangan" << endl
          << "3. ⏳ Histori" << endl
          << "4. 😋 Profil" << endl
          << "5. ⬅  Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  // * FOR DRIVER
  int driver() {
    string choice;
    utility::header("Mangan - Hi, Driver Mangan!!", "Siap bekerja, " + auth.name + "?");
    cout  << "1. 🏃 Order Berlangsung" << endl
          << "2. ⏳ Histori" << endl
          << "3. ⬅  Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }
  // * FOR ADMIN

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