
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "./utility.h"
#include "./struct.h"
#include "./table.h"
#include "./menu.h"

using namespace std;
namespace op {
  
  const string PATH = "../files/operator.csv";
  
  bool login() {
    bool is_login = false;
    string username, password;
    string cur_password, cur_username, hashed;
    utility::header("VISITME - LOGIN OPERATOR");
    cout << "Masukkan username: "; cin >> username;
    cout << "Masukkan password: "; cin >> password;
    vector<vector<string>> list = utility::list(PATH);

    for(int row = 0; row < list.size(); row++) {
      cur_password = utility::toLower(list[row][1]);
      cur_username = utility::toLower(list[row][0]);
      hashed = to_string(utility::hash(password));
      if(cur_username == username && cur_password == hashed) {
        is_login = true;
      }
    }
    return is_login;
  }
}