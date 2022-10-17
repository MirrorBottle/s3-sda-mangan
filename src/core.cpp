#include <iostream>

#include "../include/utility.h"
#include "../include/kamar.h"
#include "../include/wbp.h"
#include "../include/kunjungan.h"
#include "../include/menu.h"
#include "../include/operator.h"

using namespace std;

int main() {
  bool is_running = true;
  bool is_wbp_list_running = false;
  bool is_main_running = false;
  bool is_master_running = false;
  bool is_login = false;
  int guess_choice, master_choice , main_choice, wbp_list_choice;

  while(is_running) {
    guess_choice = menu::guess();
    switch (guess_choice) {
      case 1:
        kunjungan::create();
        break;
      case 2:
        kunjungan::check();
        break;
      case 3:
        is_wbp_list_running = true;
        wbp::list();
        while(is_wbp_list_running) {
          wbp_list_choice = menu::searching();;
          switch (wbp_list_choice) {
            case 1:
              wbp::sort();
              break;
            case 2:
              wbp::search();
              break;
            case 3:
              wbp::list();
              break;
            case 4:
              is_wbp_list_running = false;
              break;
          }
        }
        break;
      case 4:
        is_login = op::login();
        if(is_login) {
          utility::notify("success", "Berhasil login!");
          is_main_running = true;
          while(is_main_running) {
            main_choice = menu::main();
            switch (main_choice) {
              case 1:
                kunjungan::validate();
                break;
              case 2:
                kamar::schedule();
                break;
              case 3:
                is_master_running = true;
                while(is_master_running) {
                  master_choice = menu::master();
                  switch (master_choice) {
                    case 1:
                      kunjungan::index();
                      break;
                    case 2:
                      wbp::index();
                      break;
                    case 3:
                      kamar::index();
                      break;
                    case 4:
                      is_master_running = false;
                      break;
                  }
                }
                break;
              case 4:
                is_main_running = false;
                utility::notify("info", "Terima kasih!");
                break;
            }
          }
        } else {
          utility::notify("error", "Akun tidak terdaftar!");
        }
        break;
      case 5:
        is_running = false;
        utility::notify("info", "Terima kasih!");
      default:
        if(guess_choice != 5) {
          utility::notify("error", "Pilihan tidak ada!");
        }
        break;
    }
  }
  return 0;
}

