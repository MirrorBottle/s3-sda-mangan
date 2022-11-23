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


using namespace std;
using namespace structure;

namespace driver_auth {
  const string PATH = "../files/drivers.csv";

  string path() {
    return PATH; 
  }

  bool login() {
    bool is_login = false;
    string phone_number, password;
    string cur_password, cur_phone_number, hashed;
    utility::header("Mangan - Login Driver");
    cout << "No. HP: "; cin >> phone_number;
    cout << "Password: "; cin >> password;
    Node* list = utility::list(PATH);
    while (list != NULL){
      cur_phone_number = utility::toLower(list->data[3]);
      cur_password = list->data[5];
      hashed = to_string(utility::hash(password));
      if(cur_phone_number == phone_number && cur_password == hashed) {
        is_login = true;
        auth.id = list->data[0];
        auth.name = list->data[1];
        break;
      }
      list = list->next;
    }
    return is_login;
  }
}