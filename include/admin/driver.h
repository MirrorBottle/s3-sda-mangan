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
  const string DELIVERY_PATH = "../files/deliveries.csv";
  const string PARTNER_PATH = "../files/partners.csv";
  const string DRIVER_PATH = "../files/drivers.csv";

  void ongoing() {
    utility::header("Mangan - Order Berlangsung");
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
      choice = menu::admin_driver();
      switch (choice) {
        case 1:
          admin_driver::ongoing();
          break;
        case 3:
          admin_driver::history();
          break;
        case 4:
          admin_driver::profile();
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