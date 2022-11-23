#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "../utility.h"
#include "../struct.h"
#include "../table.h"
#include "../menu.h"

#include "./partner.h"
#include "./delivery.h"


using namespace std;
using namespace structure;

namespace driver {
  void ongoing() {
    utility::header("Mangan - Order Berlangsung");
    utility::notify("success", "Order Berlangsung");
  }

  void open() {
    utility::header("Mangan - Order Open");
    utility::notify("success", "Order Open");
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
      choice = menu::driver();
      switch (choice) {
        case 1:
          driver::ongoing();
          break;
        case 2:
          driver::open();
          break;
        case 3:
          driver::history();
          break;
        case 4:
          driver::profile();
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