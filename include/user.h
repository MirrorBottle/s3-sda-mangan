#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>
#include <math.h>
#include <algorithm>

#include "./data.h"
#include "./utility.h"
#include "./struct.h"
#include "./table.h"
#include "./menu.h"


using namespace std;
using namespace structure;


#define PI 3.14159265358979323846
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180

namespace user {
  const string MENU_PATH = "../files/menus.csv";
  const string USER_PATH = "../files/users.csv";
  const string DELIVERY_DETAIL_PATH = "../files/delivery_details.csv";
  const string DELIVERY_PATH = "../files/deliveries.csv";


  string DELIVERY_TABLE_COLUMNS[] = {"No.", "ID", "Waktu Pesan", "Waktu Dikirim", "Driver", "Ongkir", "Total", "Status"};
  string DELIVERY_DETAIL_TABLE_COLUMNS[] = {"No.", "ID", "Menu", "Jumlah", "Total"};
  string MENU_TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Deskripsi", "Harga"};
  string DELIVERY_DETAIL_COLUMNS[] = {"No.", "ID Menu", "Nama", "Harga", "Total"};


  vector<string> transform(vector<string> data) {
    vector<string> driver;
    vector<string> transformed;
    int total = 0;

    Node *delivery_details = utility::search(DELIVERY_DETAIL_PATH, { 1 }, data[1], true);
    if(delivery_details->next == NULL) {
      total += stoi(delivery_details->data[3]) * stoi(delivery_details->data[4]);
    }
    while(delivery_details->next != NULL) {
      total += stoi(delivery_details->data[3]) * stoi(delivery_details->data[4]);
      delivery_details = delivery_details->next;
    } 

    if(data[2] != "0") {
      driver = utility::find(USER_PATH, 0, data[2], true);
    }
    transformed.push_back(data[0]);
    transformed.push_back(data[9]);
    transformed.push_back(data[10]);
    transformed.push_back(driver.empty() ? "-" : driver[1]);
    transformed.push_back("Rp. " + data[8]);
    transformed.push_back("Rp. " + to_string(total));
    transformed.push_back(data::label_status_delivery[data[11]]);

    return transformed;
  }

  vector<string> transform_detail(vector<string> data) {
    vector<string> menu = utility::find(MENU_PATH, 0, data[1], true);
    vector<string> transformed;
    int total = stoi(data[3]) * stoi(data[4]);
    transformed.push_back(data[0]);
    transformed.push_back(menu[1]);
    transformed.push_back(data[3]);
    transformed.push_back("Rp. " + to_string(total));
    return transformed;
  }

  void list() {
    utility::header("Mangan - 🏃 Daftar Order");

    Node *deliveries = NULL;
    Node *list = utility::search(DELIVERY_PATH, { 1 }, auth.id, false, true);
    utility::MergeSort(&list, 0, 2);
  
    while(list->next != NULL) {
      vector<string> data = list->data;
      vector<string> transformed = user::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
      list = list->next;
    }

    if(list->next == NULL) {
      vector<string> data = list->data;
      vector<string> transformed = user::transform(data);
      utility::linkedListAddFirst(deliveries, transformed);
    }
  
    TextTable table = utility::table(8, DELIVERY_TABLE_COLUMNS, deliveries);
    cout << table;

    string order_id;
    vector<string> order;
    int list_choice = menu::user_list();

    if(list_choice < 3) {
      cout << "Masukkan ID Order: "; cin >> order_id;
      order = utility::find(DELIVERY_PATH, 0, order_id, true);
    }
  
    if(list_choice == 1 && !order.empty()) {
      bool is_confirmed = utility::confirm("Pesananmu akan dinyatakan selesai, ok? (y/t): ", false);
      if(is_confirmed) {
        string end_at = utility::today();
        string data[] = {
          order[0],
          order[1],
          order[2],
          order[3],
          order[4],
          order[5],
          order[6],
          order[7],
          order[8],
          order[9],
          end_at,
          "3"
        };
        utility::update(DELIVERY_PATH, 0, 12, order[0], data);
        utility::notify("success", "Untuk Kembali");
      }
    }

    if(list_choice == 2 && !order.empty()) {
      Node *delivery_details = NULL;
      Node *list = utility::search(DELIVERY_DETAIL_PATH, { 1 }, order[0], false, true);
      utility::MergeSort(&list, 0, 2);
    
      while(list->next != NULL) {
        vector<string> data = list->data;
        vector<string> transformed = user::transform_detail(data);
        utility::linkedListAddFirst(delivery_details, transformed);
        list = list->next;
      }

      if(list->next == NULL) {
        vector<string> data = list->data;
        vector<string> transformed = user::transform_detail(data);
        utility::linkedListAddFirst(delivery_details, transformed);
      }
    
      TextTable deliveryDetailTable = utility::table(8, DELIVERY_TABLE_COLUMNS, delivery_details);
      cout << deliveryDetailTable;
    }
  }


  float get_distance() {
    vector<string> user = utility::find(USER_PATH, 0, auth.id, true);
    double haversine;
    double temp;
    double distance;

    double user_lat  =  stod(user[5]) * GRADOS_RADIANES;
    double user_long = stod(user[6]) * GRADOS_RADIANES;
    double resto_lat  = data::resto_detail["latitude"]  * GRADOS_RADIANES;
    double resto_long = data::resto_detail["longitude"] * GRADOS_RADIANES;

    haversine = (pow(sin((1.0 / 2) * (resto_lat - user_lat)), 2)) + ((cos(user_lat)) * (cos(resto_lat)) * (pow(sin((1.0 / 2) * (resto_long - user_long)), 2)));
    temp = 2 * asin(min(1.0, sqrt(haversine)));
    distance = RADIO_TERRESTRE * temp / 1000;

    float value = (int)(distance * 100 + .5);
    return (float)value / 100;
  }


  void order() {
    bool is_ordering = false;
    utility::header("Mangan - 🍖 Cari Mangan");
    Node *menu = utility::list(MENU_PATH);
    TextTable table = utility::table(5, MENU_TABLE_COLUMNS, menu);
    utility::cout("cyan", "\nBerikut daftar menu kami:");
    cout << table;
    utility::cout("cyan", "\nJadi, ingin makan apa hari ini?");
    int order_menu = menu::user_order();
    if(order_menu == 1) {
      is_ordering = true;
      while(is_ordering) {
        system("cls");
        utility::header("Mangan - 🍖 Cari Mangan");
        utility::cout("cyan", "\nBerikut daftar menu kami:");
        cout << table;
        utility::cout("warning", "\nOK, masukkan pesananmu ya!");  
        utility::cout("yellow", "Masukkan ID Menu secara berurutan (contoh: 1,2)");

        string input_menu_ids, input_menu_totals;
        float distance = user::get_distance();
        float fee = trunc(distance * data::resto_detail["fee"]);

        utility::cout("cyan", "Berikut ongkos pengirimanmu: Rp." + to_string(fee) + "(" + to_string(distance)  + " KM)");

        cout << "ID Menu: "; cin >> input_menu_ids;
        cout << "Jumlah Pesanan: "; cin >> input_menu_totals;


        input_menu_ids.erase(remove(input_menu_ids.begin(), input_menu_ids.end(), ' '), input_menu_ids.end());
        input_menu_totals.erase(remove(input_menu_totals.begin(), input_menu_totals.end(), ' '), input_menu_totals.end());

        vector<int> menu_ids = utility::split_ids(input_menu_ids);
        vector<int> menu_totals = utility::split_ids(input_menu_totals);

        if(menu_ids.size() == menu_totals.size()) {
          vector<vector<string>> delivery_details;

          for(int i = 0; i < menu_ids.size(); i++) {
            vector<string> menu = utility::find(MENU_PATH, 0, to_string(menu_ids[i]), true);
            if(!menu.empty()) {
              vector<string> data;
              string total = to_string(menu_totals[i] * stoi(menu[3]));
              data.push_back(to_string(menu_ids[i]));
              data.push_back(menu[1]);
              data.push_back("Rp. " + menu[3]);
              data.push_back(to_string(menu_totals[i]));
              data.push_back("Rp. " + total);
              data.push_back(total);
              data.push_back(menu[3]);
              delivery_details.push_back(data);
            }
          }

          if(delivery_details.size() == 0) {
            utility::notify("error", "Tidak ada pesanan terdaftar!");
          } else {
            Node *delivery_details_list = utility::linkedListTransform(delivery_details);
            TextTable table = utility::table(6, DELIVERY_DETAIL_COLUMNS, delivery_details_list);
            cout << table;

            bool is_confirmed = utility::confirm("Jika iya maka pesanan akan segera diproses, loh! (y/t): ", false);
            if(is_confirmed) {
              string cur_time = utility::today();
              vector<string> user = utility::find(USER_PATH, 0, auth.id, true);
              vector<string> latest_delivery = utility::latest(DELIVERY_PATH);

              string delivery_id = latest_delivery.empty() ? "1" : to_string(stoi(latest_delivery[0]) + 1);
              string delivery_data = utility::join({
                delivery_id,
                auth.id,
                "0",
                to_string(data::resto_detail["latitude"]),
                to_string(data::resto_detail["longitude"]),
                user[5],
                user[6],
                to_string(distance),
                to_string(fee),
                utility::today(),
                "-",
                "1"
              }, ",");

              string delivery_details_data;
              
              vector<string> latest_delivery_detail = utility::latest(DELIVERY_DETAIL_PATH);

              int delivery_detail_id = latest_delivery_detail.empty() ? 1 : stoi(latest_delivery[0]) + 1;
              for(int i = 0; i < delivery_details.size(); i++) {
                string delivery_detail_data = utility::join({
                  to_string(delivery_detail_id),
                  delivery_id,
                  delivery_details[i][0],
                  delivery_details[i][3],
                  delivery_details[i][6]
                }, ",");
                if(i == delivery_details.size() - 1) {
                  delivery_details_data += delivery_detail_data;
                } else {
                  delivery_details_data += delivery_detail_data + "\n";
                }
                delivery_detail_id++;
              }

              fstream file;
              file.open(DELIVERY_PATH, ios::app);
              file << "\n" << delivery_data;
              file.close();

              file.open(DELIVERY_DETAIL_PATH, ios::app);
              file << "\n" << delivery_details_data;
              file.close();

              utility::notify("success", "Pesanan diterima! Ditunggu, ya!");
              is_ordering = true;

            } else {
              utility::notify("error", "Pesanan dibatalkan!");
              is_ordering = false;
            }
          }
        } else {
          utility::notify("error", "Jumlah menu dan pesanan tidak sama!");
        }
      }
    }
  }

  void index() {
    // user::order();
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::user();
      switch (choice) {
        case 1:
          user::list();
          break;
        case 2:
          user::order();
          break;
        case 3:
          is_running = false;
          break;
        default:
          utility::notify("error", "Pilihan tidak ada!");
          break;
      }
    }
  }
}