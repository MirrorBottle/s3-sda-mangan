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

namespace admin_driver {
  const string PATH = "../files/users.csv";

  const int TABLE_COLUMNS_LENGTH = 6;
  string TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Email", "Alamat", "No. HP"};

  void list() {
    utility::header("Mangan - 📖 Daftar Driver");
    Node *list = utility::search(PATH, { 8 }, "driver");
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, TABLE_COLUMNS, list);
    cout << table;
  }
  
  void sort() {
    int column, type;
    utility::header("Mangan - 📖 Daftar Driver");
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
    utility::header("Mangan - 📖 Daftar Driver");
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
    string id, name, email, address, phone_number, password;
    utility::header("Mangan - ➕ Tambah Driver");
    cout << "Nama Driver: ";fflush(stdin);  getline(cin, name);
    cout << "Email: "; cin >> email;
    cout << "Alamat: "; fflush(stdin); getline(cin, address);
    cout << "No. HP: "; cin >> phone_number;
    cout << "Password: "; cin >> password;
    
    vector<string> latest = utility::latest(PATH);
    id = to_string(stoi(latest[0]) + 1);

    string hashed = to_string(utility::hash(password));

    string data = id + "," + name + "," + email + "," + address + "," + phone_number + ",-,-," + hashed + ",driver";
    fstream file;
    file.open(PATH, ios::app);
    file << "\n" << data;
    file.close();

    utility::notify("success", "Driver berhasil ditambahkan!");
  }

  void edit() {
    string id, name, email, address, phone_number;
    utility::header("Mangan - 📝 Ubah Driver");

    admin_driver::list();
    cout << "ID Driver: "; cin >> id;

    vector<string> driver = utility::find(PATH, 0, id);

    if(!driver.empty()) {
      utility::notify("success", "Driver ditemukan");
      utility::header("Mangan - 📝 Ubah Driver");
      utility::cout("yellow", "*Apabila tidak ada perubahan maka isi dengan '-'!");

      cout << "Nama Driver [" + driver[1] + "]: "; fflush(stdin);  getline(cin, name);
      cout << "Email [" + driver[2] + "]: "; cin >> email;
      cout << "Alamat [" + driver[3] + "]: "; fflush(stdin);  getline(cin, address);
      cout << "No. HP [" + driver[4] + "]: "; cin >> phone_number;


      id = driver[0];
      name = name != "-" ? name : driver[1];
      email = email != "-" ? email : driver[2];
      address = address != "-" ? address : driver[3];
      phone_number = phone_number != "-" ? phone_number : driver[4];

      string data[] = {id, name, email, address, phone_number};

      utility::update(PATH, 0, TABLE_COLUMNS_LENGTH - 1, id, data);

      utility::notify("success", "Driver berhasil diubah!");

    } else {
      utility::notify("error", "Driver tidak ditemukan!");
    }
  }

  void destroy() {
    string id;
    bool is_confirmed;
    utility::header("Mangan - ❌ Hapus Driver");
    admin_driver::list();
    cout << "ID Driver: "; cin >> id;
    
    vector<string> menu = utility::find(PATH, 0, id);
    if(!menu.empty()) {
      is_confirmed = utility::confirm("driver");
      if(is_confirmed) {
        utility::destroy(PATH, 0, id);
        utility::notify("success", "Driver berhasil dihapus!");
      }

    } else {
      utility::notify("error", "Driver tidak ditemukan!");
    }
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::admin_driver();
      switch (choice) {
        case 1:
          admin_driver::list();
          utility::notify("success", "Untuk Kembali");
          break;
        case 2:
          admin_driver::create();
          break;
        case 3:
          admin_driver::edit();
          break;
        case 4:
          admin_driver::destroy();
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