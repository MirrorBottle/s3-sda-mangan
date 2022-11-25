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

namespace admin_user {

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
      choice = menu::admin_user();
      switch (choice) {
        case 1:
          admin_user::ongoing();
          break;
        case 3:
          admin_user::history();
          break;
        case 4:
          admin_user::profile();
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