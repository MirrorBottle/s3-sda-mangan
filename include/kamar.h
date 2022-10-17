#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "./utility.h"
#include "./struct.h"
#include "./table.h"
#include "./menu.h"

using namespace std;
namespace kamar {
  
  const string PATH = "../files/kamar.csv";
  const int TABLE_COLUMNS_LENGTH = 3;
  string TABLE_COLUMNS[] = {"No.", "Kode Kamar", "Nama Kamar"};
  

  string path() {
    return PATH; 
  }

  void list() {
    utility::header("VISITME - DAFTAR KAMAR");
    vector<vector<string>> content = utility::list(PATH);
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, content.size(), TABLE_COLUMNS, content);
    cout << table;
  }

  structure::kamar get(vector<string> data) {
    structure::kamar kamar;
    kamar.kode = data[0];
    kamar.nama = data[1];
    return kamar;
  }

  void store(structure::kamar kamar) {
    fstream file;
    file.open(PATH, ios::app);
    file<< kamar.kode << ","
        << kamar.nama << "\n";
    file.close();
  }

  void create() {
    structure::kamar kamar;
    utility::header("VISITME - TAMBAH KAMAR");
    cout << "Kode Kamar: "; cin >> kamar.kode;
    cout << "Nama Kamar: "; cin >> kamar.nama;
    vector<vector<string>> list = utility::search(PATH, { 0 }, kamar.kode);

    if(list.size() < 1) {
      kamar::store(kamar);
      utility::notify("success", "Kamar berhasil ditambahkan!");
    } else {
      utility::notify("error", "Kamar dengan kode berikut sudah ada!");
    }
  }

  void update(string identifier, structure::kamar kamar) {
    string data[] = {kamar.kode, kamar.nama};
    utility::update(PATH, 0, 2, identifier, data);
  }

  void edit() {
    string code;
    utility::header("VISITME - UBAH KAMAR");
    cout << "Masukkan Kode Kamar: "; cin >> code;
    
    vector<vector<string>> list = utility::search(PATH, { 0 }, code);

    if(list.size() > 0) {
      utility::notify("success", "Kamar ditemukan");
      utility::header("VISITME - UBAH KAMAR");

      vector<string> old_kamar = list.front();
      structure::kamar new_kamar;

      utility::cout("yellow", "*Apabila tidak ada perubahan maka isi dengan '-'!");

      cout << "Nama Kamar [" + old_kamar[1] + "]: "; cin >> new_kamar.nama;
      new_kamar.kode = old_kamar[0];
      new_kamar.nama = new_kamar.nama != "-" ? new_kamar.nama : old_kamar[1];

      kamar::update(code, new_kamar);
      utility::notify("success", "Kamar berhasil diubah!");
    } else {
      utility::notify("error", "Kamar dengan kode tersebut tidak ada!");
    }
  }

  void destroy() {
    string code;
    bool is_confirmed;
    utility::header("VISITME - HAPUS KAMAR");
    cout << "Kode Kamar: "; cin >> code;
    
    vector<vector<string>> list = utility::search(PATH, { 0 }, code);

    if(list.size() > 0) {
      is_confirmed = utility::confirm("kamar");
      if(is_confirmed) {
        utility::destroy(PATH, 0, 2, code);
        utility::notify("success", "Kamar berhasil dihapus!");
      }
    } else {
      utility::notify("error", "Kamar dengan kode tersebut tidak ada!");
    }
  }

  void sort() {
    int column, type;
    utility::header("VISITME - SORTING KAMAR");
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
    utility::header("VISITME - CARI KAMAR");
    cout << "Kata kunci pencarian: "; cin >> keyword;
    vector<vector<string>> list = utility::search(PATH, { 0 }, keyword, true);
    if(list.size() > 0) {
      TextTable table = utility::table(TABLE_COLUMNS_LENGTH, list.size(), TABLE_COLUMNS, list);
      cout << table;
    } else {
      utility::notify("error", "Data tidak ditemukan!");
    }
  }

  void schedule() {
    string today = utility::today();
    string start_time = data::operational["start"];
    string end_time = data::operational["end"];
    vector<vector<string>> list = utility::list(PATH);

    int total_hours = stoi(end_time) - stoi(start_time);
    vector<string> hours;

    hours.push_back(start_time);

    int cur_hour = stoi(start_time);
    for(int hourIdx; hourIdx < total_hours; hourIdx++) {
      cur_hour = cur_hour + 1;
      string hour = cur_hour < 10 ? "0" + to_string(cur_hour) : to_string(cur_hour);
      hours.push_back(hour + ":00");
    }
    hours.push_back(end_time);
    
    string columns[] = {
      "No",
      "Nama Kamar",
      "09:00",
      "10:00",
      "11:00",
      "12:00",
      "13:00",
      "14:00",
      "15:00"
    };

    vector<vector<string>> today_visits = utility::search("../files/kunjungan.csv", { 2 }, today);
    vector<vector<string>> schedules;

    for(int roomIdx = 0; roomIdx < list.size(); roomIdx++) {

      vector<string> schedule;
      structure::kamar kamar = kamar::get(list[roomIdx]);
      
      schedule.push_back(kamar.nama);

      vector<vector<string>> this_room_visits;

      for(int visitIdx = 0; visitIdx < today_visits.size(); visitIdx++) {
        vector<string> today_visit = today_visits[visitIdx];
        if(today_visit[5] == "2" && today_visit[8] == kamar.kode) {
          this_room_visits.push_back(today_visit);
        }
      }

      for(int colIdx = 0; colIdx < hours.size(); colIdx++) {
        bool is_found = false;
        string hour = hours[colIdx];
        

        for(int visitIdx = 0; visitIdx < this_room_visits.size(); visitIdx++) {
          vector<string> visit = this_room_visits[visitIdx];
          bool isInsideStart = utility::isTimeLater(hour, visit[6]);
          bool isInsideEnd = utility::isTimeLater(visit[7], hour);
          if(isInsideStart && isInsideEnd) {
            schedule.push_back(visit[0]);
            is_found = true;
          }
        }
        if(!is_found) {
          schedule.push_back("-");
        }
      }

      schedules.push_back(schedule);
    }

    utility::header("VISITME - JADWAL KETERSEDIAAN KAMAR");
    utility::cout("yellow", "Tanggal Hari Ini: " + today);
    TextTable table = utility::table(hours.size() + 1, schedules.size(), columns, schedules);
    cout << table;
    cout << endl;
    utility::notify("success", "Untuk Kembali");
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::kamar();

      switch (choice) {
        case 1:
          is_list_running = true;
          kamar::list();
          while(is_list_running) {
            list_choice = menu::searching();
            switch (list_choice) {
              case 1:
                kamar::sort();
                break;
              case 2:
                kamar::search();
                break;
              case 3:
                kamar::list();
                break;
              case 4:
                is_list_running = false;
                break;
            }
          }
          break;
        case 2:
          kamar::create();
          break;
        case 3:
          kamar::edit();
          break;
        case 4:
          kamar::destroy();
          break;
        case 5:
          is_running = false;
          break;
        default:
          utility::notify("error", "Pilihan tidak ada!");
          break;
      }
    }
  }
}