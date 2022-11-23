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
#include "../auth.h"

#include "./partner.h"
#include "./delivery.h"
#include "./main.h"

using namespace std;
using namespace structure;

namespace user_auth {
  const string PATH = "../files/users.csv";
  const int TABLE_COLUMNS_LENGTH = 6;
  string TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Email", "Alamat", "Kontak"};

  string path() {
    return PATH; 
  }

  void regist() {
    string coordinates;
    string res;
    string url;
  
    utility::header("Mangan - Registrasi", "📝 Cukup isi data dirimu dan lokasimu ya!");

    string invoke = "curl --request POST -s -o data.txt --data \"uri=" + url + "\" https://s3-sda-mangan.vercel.app";
    system(invoke.c_str());
    
    ifstream file("data.txt");//Retrieving response from data.txt
    while (getline (file, res)) {
      coordinates = res;
    }
    file.close(); 
    remove("data.txt");//Deleting file after the output is shown

    coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), '['), coordinates.end());
    coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), ']'), coordinates.end());

    string delimiter = ",";
    string latitude = coordinates.substr(0, coordinates.find(delimiter));
    string longitude = coordinates.erase(0, coordinates.find(delimiter) + delimiter.length());

    cout << latitude << "-" << longitude << endl;
  }

  bool login() {
    bool is_login = false;
    string username, password;
    string cur_password, cur_username, hashed;
    utility::header("Mangan - Login Pengguna");
    cout << "Masukkan Email: "; cin >> username;
    cout << "Masukkan Password: "; cin >> password;
    Node* list = utility::list(PATH);
    while (list != NULL){
      cur_username = utility::toLower(list->data[2]);
      cur_password = list->data[7];
      hashed = to_string(utility::hash(password));
      if(cur_username == username && cur_password == hashed) {
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