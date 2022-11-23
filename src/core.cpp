#include <iostream>

#include "../include/utility.h"
#include "../include/menu.h"
#include "../include/struct.h"
#include "../include/auth.h"
#include "../include/user/auth.h"
#include "../include/partner/auth.h"
#include "../include/driver/auth.h"

using namespace std;


structure::Auth auth;

int main() {
  bool is_running = true;
  bool is_wbp_list_running = false;
  bool is_main_running = false;
  bool is_master_running = false;
  bool is_login = false;
  int landing_choice, login_choice , main_choice, wbp_list_choice;
  bool is_login_running = false;


  user_auth::regist();
  while(is_running) {
    landing_choice = menu::landing();
    switch (landing_choice) {
      case 1:
        is_login_running = true;
        while(is_login_running) {
          login_choice = menu::login();
          switch (login_choice) {
            case 1:
              is_login = user_auth::login();
              if(is_login) {
                utility::notify("success", "Berhasil login!");
                user::index();
              } else {
                utility::notify("error", "Akun tidak terdaftar!");
              }
              break;
            case 2:
              partner_auth::login();
              break;
            case 3:
              driver_auth::login();
              break;
            case 4:
              is_login_running = false;
              break;
            default:
              if(landing_choice != 5) {
                utility::notify("error", "Pilihan tidak ada!");
              }
              break;
          }
        }
        break;
      case 2:
        user_auth::regist();
        break;
      case 3:
        partner_auth::regist();
        break;
      case 4:
        utility::header("Mangan - Tentang");
        utility::notify("info", "Untuk Kembali", true);
        break;
      case 5:
        is_running = false;
        utility::notify("info", "Terima kasih!");
      default:
        if(landing_choice != 5) {
          utility::notify("error", "Pilihan tidak ada!");
        }
        break;
    }
  }
  return 0;
}

