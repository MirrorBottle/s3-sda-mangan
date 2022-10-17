#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <tuple>

#include "./utility.h"
#include "./struct.h"
#include "./wbp.h"
#include "./menu.h"
#include "./kamar.h"

using namespace std;

namespace kunjungan {
  const string PATH = "../files/kunjungan.csv";
  const int TABLE_COLUMNS_LENGTH = 11;
  string TABLE_COLUMNS[] = {"No.", "Kode", "WBP", "Tanggal", "Nama", "NIK", "Status", "Jam Mulai", "Jam Selesai", "Kode Kamar", "Catatan"};

  string path() {
    return PATH;
  }

  vector<vector<string>> formatter(vector<vector<string>> list) {

    vector<vector<string>> formatted;
    for(int rowIdx = 0; rowIdx < list.size(); rowIdx++) {
      vector<string> row = list[rowIdx];

      string col_data;

      for(int colIdx = 0; colIdx < TABLE_COLUMNS_LENGTH - 1; colIdx++) {
        col_data = row[colIdx];
        if(colIdx == 1) {
          vector<string> wbp = utility::find(wbp::path(), { 0 }, col_data);
          row[colIdx] = col_data + " [" + wbp[1] + "]";
        }

        if(colIdx == 5) {
          int status = stoi(col_data);
          row[colIdx] = data::label_status_kunjungan[status];
        }

        if(colIdx == 8) {
          if(col_data != "-") {
            vector<string> kamar = utility::find(kamar::path(), { 0 }, col_data);
            row[colIdx] = col_data + " [" + kamar[1] + "]";
          }
        }
      }
      

      formatted.push_back(row);
    }
    return formatted;
  }
  void list() {
    utility::header("VISITME - DAFTAR KUNJUNGAN");
    vector<vector<string>> content = utility::list(PATH);
    vector<vector<string>> list = kunjungan::formatter(content);
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, list.size(), TABLE_COLUMNS, list);
    cout << table;
  }

  structure::kunjungan get(vector<string> data) {
    string path_wbp = wbp::path();
    string path_kamar = kamar::path();
    
    structure::kunjungan kunjungan;

    kunjungan.kode = data[0];
    kunjungan.kode_wbp = data[1];
    kunjungan.tanggal = data[2];
    kunjungan.nama_pengunjung = data[3];
    kunjungan.nik_pengunjung = data[4];
    kunjungan.status = stoi(data[5]);
    kunjungan.jam_mulai = data[6];
    kunjungan.jam_selesai = data[7];
    kunjungan.kode_kamar = data[8];
    kunjungan.catatan = data[9];

    vector<string> wbp = utility::find(path_wbp , { 0 }, kunjungan.kode_wbp);
    kunjungan.wbp.kode = wbp[0];
    kunjungan.wbp.nama = wbp[1];

    if(kunjungan.kode_kamar != "-") {
      vector<string> kamar = utility::find(path_kamar , { 0 }, kunjungan.kode_kamar);
      kunjungan.kamar.kode = kamar[0];
      kunjungan.kamar.nama = kamar[1];
    }

    return kunjungan;
  }

  void store(structure::kunjungan kunjungan) {
    fstream fout;
    string today = utility::today();
    vector<string> latest = utility::latest(PATH);
    int number = latest.empty() ? 0 : stoi(latest[0].substr(3, latest[0].find("-")));
    string next_number = number > 9 ? to_string(number + 1) : "0" + to_string(number + 1);
    kunjungan.kode = "KN-" + next_number;
    kunjungan.tanggal = today;
    kunjungan.status = data::status_kunjungan["menunggu"];

    kunjungan.jam_mulai = "-";
    kunjungan.jam_selesai = "-";
    kunjungan.kode_kamar = "-";
    kunjungan.catatan = "-";

    fout.open(PATH, ios::out | ios::app);
    fout<< kunjungan.kode << ","
        << kunjungan.kode_wbp << ","
        << kunjungan.tanggal << ","
        << kunjungan.nama_pengunjung << ","
        << kunjungan.nik_pengunjung << ","
        << kunjungan.status << ","
        << kunjungan.jam_mulai << ","
        << kunjungan.jam_selesai << ","
        << kunjungan.kode_kamar << ","
        << kunjungan.catatan << "\n";
    fout.close();

    utility::notify("success", "Berhasil Melakukan Registrasi, Kode Kunjungan: [" + kunjungan.kode + "]");
  }

  structure::wbp get_wbp() {
    vector<string> wbp;
    string kode_wbp;
  
    cout << "Masukkan Kode WBP: "; cin >> kode_wbp;
    wbp = utility::find(wbp::path(), { 0 }, kode_wbp);

    if(wbp.empty()) {
      utility::notify("error", "Kode WBP tidak terdaftar!");
      get_wbp();
    }

    utility::cout("green", "WBP Ditemukan: [" + wbp[1] + "]!");
    structure::wbp found_wbp = wbp::get(wbp);
    return found_wbp;
  }

  void create() {
    bool is_not_exist = true;
    bool check_wbp = false;
    string today = utility::today();
    structure::kunjungan kunjungan;
    structure::wbp wbp;
    utility::header("VISITME - REGISTRASI KUNJUNGAN");
    utility::cout("yellow", "*Kunjungan hanya bisa dilakukan sekali sehari!");
    utility::cout("yellow", "*Cek status kunjungan anda secara berkala!\n");


    cout << "Masukkan NIK Anda: "; cin >> kunjungan.nik_pengunjung;

    // ** CHECK IF USER ALREADY REGIST TODAY
    vector<vector<string>> list = utility::search(PATH, { 4 }, kunjungan.nik_pengunjung);

    for(int index = 0; index < list.size(); index++) {
      vector<string> row = list[index];
      if(row[2] == today) {
        is_not_exist = false;
      }
    }

    if (is_not_exist) {
      wbp = get_wbp();
      kunjungan.kode_wbp = wbp.kode;
      cout << "Masukkan Nama Anda: "; fflush(stdin);
      getline(cin, kunjungan.nama_pengunjung);
      kunjungan::store(kunjungan);
    } else {
      utility::notify("error", "Anda sudah melakukan registrasi!");
    }
  }

  void check() {
    string keyword;
    utility::header("VISITME - CEK STATUS KUNJUNGAN");
    cout << "Masukkan Kode Kunjungan / NIK Anda: "; cin >> keyword;
    vector<vector<string>> list = utility::search(PATH, { 0, 4 }, keyword, false, true);

    utility::header("VISITME - CEK STATUS KUNJUNGAN");
    if(list.size() > 0) {
      for(int index = 0; index < list.size(); index++) {
        string description;
        vector<string> row = list[index];

        structure::kunjungan kunjungan = kunjungan::get(row);
        if(index == 0) {
          cout << "Nama Pengunjung: " << kunjungan.nama_pengunjung << endl;
          cout << "NIK Pengunjung: " << kunjungan.nik_pengunjung << endl << endl;
        }

        string label_status = data::label_status_kunjungan[kunjungan.status];
        string label_color = data::color_status_kunjungan[kunjungan.status];

        switch (kunjungan.status) {
          case 1:
            description = "Kunjungan masih dalam tahap validasi. Mohon cek kembali nanti.";
            break;
          case 2:
            description = "Kamar: " + kunjungan.kamar.nama +  ", Jam: " + kunjungan.jam_mulai + " - " + kunjungan.jam_selesai;
            break;
          case 3:
            description = kunjungan.catatan;
            break;
        }
        utility::cout("cyan", kunjungan.kode, false);
        cout << " " << kunjungan.tanggal << " ";
        utility::cout(label_color, label_status);
        cout << "Keterangan: " << description << endl << endl;
      }
      utility::notify("success", "Berhasil menampilkan daftar kunjungan!");
    } else {
      utility::notify("error", "Tidak ada kunjungan!");
    }
  }

  vector<vector<string>> validate_formatter(vector<vector<string>> list) {
    vector<vector<string>> formatted;
    for(int rowIdx = 0; rowIdx < list.size(); rowIdx++) {
      vector<string> row = list[rowIdx];
      vector<string> wbp = utility::find(wbp::path(), { 0 }, row[1]);

      row[1] = row[1] + " [" + wbp[1] + "]";
      formatted.push_back(row);
    }
    return formatted;
  }

  tuple<structure::kamar, string, string> get_availability(string kode_kunjungan) {
    
    string kode_kamar, jam_mulai, jam_selesai;
    string today = utility::today();

    cout << "Masukkan Kode kamar: "; cin >> kode_kamar;
    vector<string> kamar = utility::find(kamar::path(), { 0 }, kode_kamar);

    // ** CHECK IF IS THERE A ROOM
    if(kamar.empty()) {
      utility::notify("error", "Kode kamar tidak terdaftar!");
      get_availability(kode_kunjungan);
    }

    // ** GET START AND AND TIME
    cout << "Masukkan jam mulai (hh:mm): "; cin >> jam_mulai;
    cout << "Masukkan jam selesai (hh:mm): "; cin >> jam_selesai;

    // ** GET TODAY VISITS
    structure::kamar found_kamar = kamar::get(kamar);
    vector<vector<string>> today_visits = utility::search(PATH, { 2 }, today);

    if(!today_visits.empty()) {
      
      for(int visitIdx = 0; visitIdx < today_visits.size(); visitIdx++) {
        structure::kunjungan curr_today_visit = kunjungan::get(today_visits[visitIdx]);

        if(curr_today_visit.kode != kode_kunjungan && curr_today_visit.status == 2 && curr_today_visit.kode_kamar == found_kamar.kode) {
          bool isInsideStart = utility::isTimeLater(jam_mulai, curr_today_visit.jam_mulai);
          bool isInsideEnd = utility::isTimeLater(curr_today_visit.jam_selesai, jam_selesai);

          if(isInsideStart && isInsideEnd)  {
            utility::notify("error", "Kamar sudah terisi!");
            get_availability(kode_kunjungan);
          }
        }
      }
    }
    utility::cout("green", "Kamar ditemukan dan tersedia: [" + kamar[1] + "]!");
    return make_tuple(found_kamar, jam_mulai, jam_selesai);
  }

  void update(string identifier, structure::kunjungan kunjungan) {
    string data[] = {
        kunjungan.kode, 
        kunjungan.kode_wbp,
        kunjungan.tanggal,
        kunjungan.nama_pengunjung,
        kunjungan.nik_pengunjung,
        to_string(kunjungan.status),
        kunjungan.jam_mulai,
        kunjungan.jam_selesai,
        kunjungan.kode_kamar,
        kunjungan.catatan
      };
      utility::update(PATH, 0, 10, identifier, data);
  }

  void validate() {
    utility::header("VISITME - VALIDASI KUNJUNGAN");

    string kode;
    string validate_table_columns[] = {"No.", "Kode", "WBP", "Tanggal", "Nama", "NIK"};
    int validate_columns_length = 6;

    vector<vector<string>> content = utility::search(PATH, { 5 }, "1");

    vector<vector<string>> list = kunjungan::validate_formatter(content);
    TextTable table = utility::table(validate_columns_length, list.size(), validate_table_columns, list);
    utility::cout("yellow", "Kunjungan yang belum divalidasi: ");

    cout << table << endl;
    cout << "Masukkan kode kunjungan: "; cin >> kode;

    vector<string> kunjungan_raw = utility::find(PATH, { 0 }, kode);

    if(!kunjungan_raw.empty()) {
      structure::kunjungan kunjungan = kunjungan::get(kunjungan_raw);
      structure::kamar kamar;
      utility::notify("success", "Kunjungan ditemukan!");
      utility::header("VISITME - VALIDASI KUNJUNGAN");

      string status, jam_mulai, jam_selesai, kode_kamar, catatan;
      bool is_status_validate_pass, is_room_not_available = true;

      while(!is_status_validate_pass) {
        utility::cout("white", "Pilih status kunjungan ", false);
        utility::cout("green", "2 [DITERIMA] ", false);
        utility::cout("white", "/", false);
        utility::cout("red", " 3 [DITOLAK]: ", false);
        cin >> status;

        if(status == "2" || status == "3") {
          is_status_validate_pass = true;
        }
      }

      if(status == "2") {
        tie(kamar, jam_mulai, jam_selesai) = get_availability(kode);
        kunjungan.kode_kamar = kamar.kode;
        kunjungan.jam_mulai = jam_mulai;
        kunjungan.jam_selesai = jam_selesai;
        kunjungan.status = 2;

        utility::notify("success", "Kunjungan berhasil divalidasi");
      } else {
        cout << "Masukkan catatan penolakan: "; cin >>catatan;
        kunjungan.status = 3;
        kunjungan.catatan = catatan;
        utility::notify("success", "Kunjungan berhasil ditolak!");
      }
      kunjungan::update(kunjungan.kode, kunjungan);
      
    } else {
      utility::notify("error", "Kode Kunjungan Tidak Ada!");
    }
    
  }

  void edit() {
    string code;
    utility::header("VISITME - UBAH KUNJUNGAN");
    utility::cout("yellow", "*Kunjungan yang bisa diubah hanya kunjungan yang sudah berlalu!");
    cout << "Masukkan Kode Kunjungan: "; cin >> code;
    
    vector<string> kunjungan_raw = utility::find(PATH, { 0 }, code);
    if(!kunjungan_raw.empty()) {
      utility::notify("success", "Kunjungan ditemukan");
      utility::header("VISITME - UBAH KUNJUNGAN");

      structure::kunjungan old_kunjungan = kunjungan::get(kunjungan_raw);
      structure::kunjungan new_kunjungan = old_kunjungan;

      utility::cout("yellow", "*Apabila tidak ada perubahan maka isi dengan '-'!");

      cout << "Nama Pengunjung [" + old_kunjungan.nama_pengunjung + "]: "; cin >> new_kunjungan.nama_pengunjung;
      cout << "NIK Pengunjung [" + old_kunjungan.nik_pengunjung + "]: "; cin >> new_kunjungan.nik_pengunjung;
      
      new_kunjungan.nama_pengunjung = new_kunjungan.nama_pengunjung != "-" ? new_kunjungan.nama_pengunjung : old_kunjungan.nama_pengunjung;
      new_kunjungan.nik_pengunjung = new_kunjungan.nik_pengunjung != "-" ? new_kunjungan.nik_pengunjung : old_kunjungan.nik_pengunjung;

      kunjungan::update(old_kunjungan.kode, new_kunjungan);
      utility::notify("success", "Kunjungan berhasil diubah!");
    } else {
      utility::notify("error", "Kunjungan dengan kode tersebut tidak ada!");
    }
  }

  void destroy() {
    string code;
    bool is_confirmed;
    utility::header("VISITME - HAPUS KUNJUNGAN");
    cout << "Kode Kunjungan: "; cin >> code;
    
    vector<vector<string>> list = utility::search(PATH, { 0 }, code);

    if(list.size() > 0) {
      is_confirmed = utility::confirm("kunjungan");
      if(is_confirmed) {
        utility::destroy(PATH, 0, 2, code);
        utility::notify("success", "Kunjungan berhasil dihapus!");
      }
    } else {
      utility::notify("error", "Kunjungan dengan kode tersebut tidak ada!");
    }
  }

  void sort() {
    int column, type;
    utility::header("VISITME - SORTING KUNJUNGAN");
    tie(column, type) = menu::sorting(TABLE_COLUMNS, TABLE_COLUMNS_LENGTH);
    column = column - 1;
    if(column >= 0 && column < TABLE_COLUMNS_LENGTH) {
      vector<vector<string>> list = utility::sort(PATH, column, type);
      TextTable table = utility::table(TABLE_COLUMNS_LENGTH, list.size(), TABLE_COLUMNS, list);
      cout << table;
    } else {
      utility::notify("error", "Pilihan kolom tidak ada!");
    }
  }

  void search() {
    string keyword;
    utility::header("VISITME - CARI KUNJUNGAN");
    cout << "Kata kunci pencarian: "; cin >> keyword;
    vector<vector<string>> list = utility::search(PATH, { 0 }, keyword, true);
    if(list.size() > 0) {
      TextTable table = utility::table(TABLE_COLUMNS_LENGTH, list.size(), TABLE_COLUMNS, list);
      cout << table;
    } else {
      utility::notify("error", "Data tidak ditemukan!");
    }
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::kunjungan();

      switch (choice) {
        case 1:
          is_list_running = true;
          kunjungan::list();
          while(is_list_running) {
            list_choice = menu::searching();
            switch (list_choice) {
              case 1:
                kunjungan::sort();
                break;
              case 2:
                kunjungan::search();
                break;
              case 3:
                kunjungan::list();
                break;
              case 4:
                is_list_running = false;
                break;
            }
          }
          break;
        case 2:
          kunjungan::edit();
          break;
        case 3:
          kunjungan::destroy();
          break;
        case 4:
          is_running = false;
          break;
        default:
          utility::notify("error", "Pilihan tidak ada!");
          break;
      }
    }
  }
}