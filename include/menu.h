#pragma once

#include <iostream>
#include <tuple>
#include <ctype.h>

#include "../include/utility.h"

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
    cout  << "1. Masuk" << endl
          << "2. Registrasi" << endl
          << "3. Menjadi Partner" << endl
          << "4. Tentang" << endl
          << "5. Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int login() {
    string choice;
    utility::header("Mangan - Masuk Sebagai?");
    cout  << "1. Pengguna" << endl
          << "2. Partner" << endl
          << "3. Partner" << endl
          << "4. Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }
  // ** FOR THE MAIN
  int guess() {
    string choice;
    utility::header("VISITME - KUNJUNGAN LAPAS");
    cout  << "1. Registrasi Kunjungan" << endl
          << "2. Cek Status Kunjungan" << endl
          << "3. Daftar WBP" << endl
          << "4. Masuk Sebagai Operator" << endl
          << "5. Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
    
  }
  int main() {
    string choice;
    utility::header("VISITME - MENU UTAMA");
    cout  << "1. Validasi Kunjungan" << endl
          << "2. Jadwal Ketersediaan Kamar" << endl
          << "3. Data Master" << endl
          << "4. Keluar" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int master() {
    string choice;
    utility::header("VISITME - DATA MASTER");
    cout  << "1. Kunjungan" << endl
          << "2. WBP" << endl
          << "3. Kamar" << endl
          << "4. Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  // ** FOR THE ENTITIES
  int kamar() {
    string choice;
    utility::header("VISITME - MANAJEMEN KAMAR");
    cout  << "1. Daftar Kamar" << endl
          << "2. Tambah Kamar" << endl
          << "3. Ubah Kamar" << endl
          << "4. Hapus Kamar" << endl
          << "5. Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int kunjungan() {
    string choice;
    utility::header("VISITME - MANAJEMEN KAMAR");
    cout  << "1. Daftar Kunjungan" << endl
          << "2. Ubah Kunjungan" << endl
          << "3. Hapus Kunjungan" << endl
          << "4. Kembali" << endl
          << "Pilih : "; cin >> choice;
    return check(choice);
  }

  int wbp() {
    string choice;
    utility::header("VISITME - MANAJEMEN WBP");
    cout  << "1. Daftar WBP" << endl
          << "2. Keluar" << endl
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