#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "./data.h"
#include "./utility.h"
#include "./struct.h"
#include "./table.h"
#include "./menu.h"


using namespace std;
using namespace structure;

namespace user {
  const string DELIVERY_PATH = "../files/deliveries.csv";
  const string PARTNER_PATH = "../files/partners.csv";
  const string DRIVER_PATH = "../files/drivers.csv";

  const int DELIVERY_TABLE_COLUMNS_LENGTH = 6;
  string DELIVERY_TABLE_COLUMNS[] = {"No.", "ID", "Resto", "Driver", "Total", "Status"};


  vector<string> delivery_data(vector<string> delivery) {
    vector<string> partner = utility::find(PARTNER_PATH, 0, delivery[3], true);
    vector<string> driver = utility::find(PARTNER_PATH, 0, delivery[3], true);
    vector<string> status = utility::find(PARTNER_PATH, 0, delivery[3], true);
    cout << partner[1] << endl;
    vector<string> data = {
      delivery[0],
    };

    return data;
  }

  Node *deliveries() {
    Node *list = utility::list(DELIVERY_PATH);
    Node *filtered = NULL;

    // * ONLY ONE ITEM
    if(list->next == NULL) {
      if(list->data[1] == auth.id) {
        vector<string> data = delivery_data(list->data);
        utility::linkedListAddFirst(filtered, data);
      }
    }

    while(list->next != NULL) {
      if(list->data[1] == auth.id) {
        vector<string> data = delivery_data(list->data);
        utility::linkedListAddFirst(filtered, data);
      }
      list = list->next;
    }

    return filtered;
  }

  void ongoing() {
    utility::header("Mangan - Order Berlangsung");
    Node *deliveries = user::deliveries();
    TextTable table = utility::table(2, DELIVERY_TABLE_COLUMNS, deliveries);
    cout << table;
  }

  void history() {
    utility::header("Mangan - Histori");
    utility::notify("success", "Histori");
  }

  void profile() {
    utility::header("Mangan - Profile");
    utility::notify("success", "Profile");
  }

  void index() {
    bool is_running = true;
    bool is_list_running = false;
    int choice, list_choice;
    while(is_running) {
      choice = menu::user();
      switch (choice) {
        case 1:
          user::ongoing();
          break;
        case 3:
          user::history();
          break;
        case 4:
          user::profile();
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