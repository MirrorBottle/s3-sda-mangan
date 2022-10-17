#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "./utility.h"
#include "./struct.h"
#include "./table.h"
#include "./menu.h"

using namespace std;
namespace wbp {
  
  const string PATH = "../files/wbp.csv";
  const int TABLE_COLUMNS_LENGTH = 3;
  string TABLE_COLUMNS[] = {"No.", "Kode WBP", "Nama WBP"};
  

  string path() {
    return PATH;
  }

  structure::wbp get(vector<string> data) {
    structure::wbp wbp;
    wbp.kode = data[0];
    wbp.nama = data[1];
    return wbp;
  }

  void list() {
    utility::header("VISITME - DAFTAR WBP");
    vector<vector<string>> content = utility::list(PATH);
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, content.size(), TABLE_COLUMNS, content);
    cout << table;
  }

  void sort() {
    int column, type;
    utility::header("VISITME - SORTING WBP");
    utility::cout("yellow", "Daftar kolom: ");
    for(int i = 1; i < TABLE_COLUMNS_LENGTH; i++) { 
      utility::cout("yellow", to_string(i) + ". " + TABLE_COLUMNS[i]);
    }
    cout << "\nPilih kolom: "; cin >> column;
    cout << "Pilih tipe (1 = asc, 2 = desc): "; cin >> type;
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
    utility::header("VISITME - CARI WBP");
    cout << "Kata kunci pencarian: "; fflush(stdin);
    getline(cin, keyword);
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
      choice = menu::wbp();
      switch (choice) {
        case 1:
          is_list_running = true;
          wbp::list();
          
          while(is_list_running) {
            list_choice = menu::searching();
            switch (list_choice) {
              case 1:
                wbp::sort();
                break;
              case 2:
                wbp::search();
                break;
              case 3:
                wbp::list();
                break;
              case 4:
                is_list_running = false;
                break;
            }
          }
          break;
        case 2:
          is_running = false;
          break;
        default:
          utility::notify("error", "Pilihan tidak ada!");
          break;
      }
    }
  }
}