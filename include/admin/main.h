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

#include "./driver.h"
#include "./menu.h"
#include "./delivery.h"
#include "./user.h"

using namespace std;
using namespace structure;

namespace admin {

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
      choice = menu::admin();
      switch (choice) {
        case 1:
          admin_delivery::waiting();
          break;
        case 2:
          admin_delivery::ongoing();
          break;
        case 3:
          admin_delivery::history();
          break;
        case 4:
          admin_user::index();
          break;
        case 5:
          admin_driver::index();
          break;
        case 6:
          admin_menu::index();
          break;
        case 7:
          is_running = false;
          break;
        default:
          utility::notify("error", "Pilihan tidak ada!");
          break;
      }
    }
  }
}