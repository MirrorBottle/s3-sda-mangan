#include <iostream>

#include "../include/utility.h"
#include "../include/menu.h"
#include "../include/struct.h"
#include "../include/auth.h"
#include "../include/user.h"
#include "../include/driver.h"
#include "../include/admin/main.h"
#include "../include/admin/menu.h"


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
  
  while(is_running) {

    landing_choice = menu::landing();
    switch (landing_choice) {
      case 1:
        is_login = auth_controller::login();
        if(is_login) {
          utility::notify("success", "Berhasil login!");

          if(auth.role == "admin") {
            admin::index();
          } else if (auth.role == "driver") {
            driver::index();
          } else {
            user::index();
          }
        } else {
          utility::notify("error", "Akun tidak terdaftar!");
        }
        break;
      case 2:
        auth_controller::regist();
        user::index();
        break;
      case 4:
        utility::header("Mangan - Tentang");
        cout << "Mangan adalah simulasi pesan makanan sebuah restoran";
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