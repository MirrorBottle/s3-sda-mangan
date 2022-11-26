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

namespace admin_delivery {
  const string MENU_PATH = "../files/menus.csv";
  const string USER_PATH = "../files/users.csv";
  const string DELIVERY_DETAIL_PATH = "../files/delivery_details.csv";
  const string DELIVERY_PATH = "../files/deliveries.csv";
  const string DRIVER_PATH = "../files/drivers.csv";


  string DELIVERY_TABLE_COLUMNS[] = {"No.", "ID", "Pengguna", "Alamat", "Menu", "Waktu Pesan", "Waktu Dikirim", "Ongkir", "Total", "Status"};
  string MENU_TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Deskripsi", "Harga"};
  string DELIVERY_DETAIL_COLUMNS[] = {"No.", "ID Menu", "Nama", "Harga", "Total"};


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
      driver = utility::find(USER_PATH, 0, data[2], true);
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

  void waiting() {
    utility::header("Mangan - 🏃 Order Menunggu");

    Node *deliveries = NULL;
    Node *list = utility::search(DELIVERY_PATH, { 11 }, "1", false, true);
    utility::MergeSort(&list, 0, 2);
  
    while(list->next != NULL) {
      vector<string> data = list->data;
      vector<string> transformed = admin_delivery::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
      list = list->next;
    }

    if(list->next == NULL) {
      vector<string> data = list->data;
      vector<string> transformed = admin_delivery::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
    }
  
    TextTable table = utility::table(10, DELIVERY_TABLE_COLUMNS, deliveries);

    cout << table;
    int waiting_menu = menu::admin_waiting();

    string driver_id = "0";
    string status = waiting_menu == 1 ? "2" : "4";

    if(waiting_menu == 1) {
      cout << "Masukkan ID Driver"; cin >> driver_id;
    }
    
    if(waiting_menu == 1 || waiting_menu == 2) {
      string data[] = {
        list->data[0],
        list->data[1],
        driver_id,
        list->data[3],
        list->data[4],
        list->data[5],
        list->data[6],
        list->data[7],
        list->data[8],
        list->data[9],
        list->data[10],
        status
      };
      utility::update(DELIVERY_PATH, 0, 12, list->data[0], data);
      utility::notify("success", "Untuk Kembali");
    }
  }

  void ongoing() {
    utility::header("Mangan - ⏳ Order Diterima");

    Node *deliveries = NULL;
    Node *list = utility::search(DELIVERY_PATH, { 11 }, "2", false, true);
    utility::MergeSort(&list, 0, 2);
  
    

    if(utility::count(list) < 1) {
      utility::cout("red", "Tidak ada data!");
    } else {
      while(list->next != NULL) {
        vector<string> data = list->data;
        vector<string> transformed = admin_delivery::transform(data);
        utility::linkedListAddFirst(deliveries, transformed);
        list = list->next;
      }

      if(list->next == NULL) {
        vector<string> data = list->data;
        vector<string> transformed = admin_delivery::transform(data);
        utility::linkedListAddFirst(deliveries, transformed);
      }
      TextTable table = utility::table(10, DELIVERY_TABLE_COLUMNS, deliveries);
      cout << table;
    }
    utility::notify("success", "Untuk Kembali");
  }

  void history() {
    utility::header("Mangan - 🍖 Order");

    Node *deliveries = NULL;
    Node *list = utility::list(DELIVERY_PATH);
    utility::MergeSort(&list, 0, 2);
  
    while(list->next != NULL) {
      vector<string> data = list->data;
      vector<string> transformed = admin_delivery::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
      list = list->next;
    }

    if(list->next == NULL) {
      vector<string> data = list->data;
      vector<string> transformed = admin_delivery::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
    }
  
    TextTable table = utility::table(10, DELIVERY_TABLE_COLUMNS, deliveries);

    cout << table;

    utility::notify("success", "Untuk Kembali");
  }
}