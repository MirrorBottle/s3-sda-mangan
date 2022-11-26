#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "../data.h"
#include "../utility.h"
#include "../struct.h"
#include "../table.h"
#include "../menu.h"


using namespace std;
using namespace structure;

namespace admin_menu {
  const string PATH = "../files/menus.csv";

  const int TABLE_COLUMNS_LENGTH = 5;
  string TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Deskripsi", "Harga"};

  void list() {
    utility::header("Mangan - 📖 Daftar Menu");
    Node *list = utility::list(PATH);
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, TABLE_COLUMNS, list);
    cout << table;
  }
  
  void sort() {
    int column, type;
    utility::header("Mangan - 📖 Daftar Menu");
    tie(column, type) = menu::sorting(TABLE_COLUMNS, TABLE_COLUMNS_LENGTH);
    column = column - 1;
    if(column >= 0 && column < TABLE_COLUMNS_LENGTH) {
      Node *list = utility::sort(PATH, column, type);
      TextTable table = utility::table(TABLE_COLUMNS_LENGTH, TABLE_COLUMNS, list);
      cout << table;
    } else {
      utility::notify("error", "Pilihan kolom tidak ada!");
    }
  }

  void search() {
    utility::header("Mangan - 📖 Daftar Menu");
    string keyword = utility::search_keyword();
    Node *list = utility::search(PATH, { 0 }, keyword, true);
    if(list == NULL) {
      utility::notify("error", "Data tidak ditemukan!");
    } else {
      TextTable table = utility::table(TABLE_COLUMNS_LENGTH, TABLE_COLUMNS, list);
      cout << table;
    }
  }

  void create() {
    string id, name, description, price;
    utility::header("Mangan - ➕ Tambah Menu");
    cout << "Nama Menu: "; cin >> name;
    cout << "Deskripsi Singkat: "; fflush(stdin); getline(cin, description);
    cout << "Harga: "; cin >> price;
    
    vector<string> latest = utility::latest(PATH);
    id = to_string(stoi(latest[0]) + 1);

    string data = id + "," + name + "," + description + "," + price;
    fstream file;
    file.open(PATH, ios::app);
    file << "\n" << data;
    file.close();

    utility::notify("success", "Menu berhasil ditambahkan!");
  }

  void edit() {
    string id, name, description, price, avail;
    utility::header("Mangan - 📝 Ubah Menu");

    admin_menu::list();
    cout << "ID Menu: "; cin >> id;

    vector<string> menu = utility::find(PATH, 0, id);

    if(!menu.empty()) {
      utility::notify("success", "Menu ditemukan");
      utility::header("Mangan - 📝 Ubah Menu");
      utility::cout("yellow", "*Apabila tidak ada perubahan maka isi dengan '-'!");

      cout << "Nama Menu [" + menu[1] + "]: "; cin >> name;
      cout << "Deskripsi Singkat [" + menu[2] + "]: "; fflush(stdin); getline(cin, description);
      cout << "Harga [Rp. " + menu[3] + "]: "; cin >> price;
      id = menu[0];
      name = name != "-" ? name : menu[1];
      description = description != "-" ? description : menu[2];
      price = price != "-" ? price : menu[3];

      string data[] = {id, name, description, price};

      utility::update(PATH, 0, TABLE_COLUMNS_LENGTH - 1, id, data);

      utility::notify("success", "Menu berhasil dubah!");

    } else {
      utility::notify("error", "Menu tidak ditemukan!");
    }
  }

  void destroy() {
    string id;
    bool is_confirmed;
    utility::header("Mangan - ❌ Hapus Menu");
    admin_menu::list();
    cout << "ID Menu: "; cin >> id;
    
    vector<string> menu = utility::find(PATH, 0, id);
    if(!menu.empty()) {
      utility::destroy(PATH, 0, id);
      utility::notify("success", "Menu berhasil dihapus!");

    } else {
      utility::notify("error", "Menu tidak ditemukan!");
    }
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::admin_menu();
      switch (choice) {
        case 1:
          is_list_running = true;
          admin_menu::list();
          while(is_list_running) {
            list_choice = menu::searching();
            switch (list_choice) {
              case 1:
                admin_menu::sort();
                break;
              case 2:
                admin_menu::search();
                break;
              case 3:
                admin_menu::list();
                break;
              case 4:
                is_list_running = false;
                break;
            }
          }
          break;
        case 2:
          admin_menu::create();
          break;
        case 3:
          admin_menu::edit();
          break;
        case 4:
          admin_menu::destroy();
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