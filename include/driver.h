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
using namespace structure;

namespace driver {

  const string MENU_PATH = "../files/menus.csv";
  const string USER_PATH = "../files/users.csv";
  const string DELIVERY_DETAIL_PATH = "../files/delivery_details.csv";
  const string DELIVERY_PATH = "../files/deliveries.csv";
  const string DRIVER_PATH = "../files/drivers.csv";


  string DELIVERY_TABLE_COLUMNS[] = {"No.", "ID", "Pengguna", "Alamat", "Menu", "Waktu Pesan", "Waktu Dikirim", "Ongkir", "Total", "Status"};


  vector<string> transform(vector<string> data) {
    vector<string> driver;
    vector<string> transformed;
    int total = 0;
    vector<string> menus;

    Node *delivery_details = utility::search(DELIVERY_DETAIL_PATH, { 1 }, data[0], true);
    vector<string> user = utility::find(USER_PATH, 0, data[1], true);

    if(delivery_details->next == NULL) {
      total += stoi(delivery_details->data[3]) * stoi(delivery_details->data[4]);
    }
    while(delivery_details->next != NULL) {
      vector<string> menu = utility::find(MENU_PATH, 0, delivery_details->data[2], true);
      total += stoi(delivery_details->data[3]) * stoi(delivery_details->data[4]);
      menus.push_back(menu[1]);
      delivery_details = delivery_details->next;
    }

    if(data[2] != "0") {
      driver = utility::find(DRIVER_PATH, 0, data[2], true);
    }
    sort(menus.begin(), menus.end() );
    menus.erase( unique( menus.begin(), menus.end() ), menus.end() );
    transformed.push_back(data[0]);
    transformed.push_back(user[1]);
    transformed.push_back(user[3]);
    transformed.push_back(utility::join(menus, ", "));
    transformed.push_back(data[9]);
    transformed.push_back(data[10]);
    transformed.push_back("Rp. " + data[8]);
    transformed.push_back("Rp. " + to_string(total));
    transformed.push_back(data::label_status_delivery[data[11]]);
    transformed.push_back(utility::join(data, ","));
    return transformed;
  }

  void order() {
    utility::header("Mangan - 🏃 Daftar Order");

    Node *deliveries = NULL;
    Node *list = utility::search(DELIVERY_PATH, { 2 }, auth.id, false, true);
    utility::MergeSort(&list, 0, 2);


    if(list == NULL) {
      utility::notify("error", "Tidak ada order");
    } else {
      while(list->next != NULL) {
        vector<string> data = list->data;
        vector<string> transformed = driver::transform(data);
        utility::linkedListAddFirst(deliveries, transformed);
        list = list->next;
      }

      if(list->next == NULL) {
        vector<string> data = list->data;
        vector<string> transformed = driver::transform(data);
        utility::linkedListAddFirst(deliveries, transformed);
      }
    
      TextTable table = utility::table(10, DELIVERY_TABLE_COLUMNS, deliveries);
      utility::notify("success", "Untuk Kembali");
    }
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::driver();
      switch (choice) {
        case 1:
          driver::order();
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