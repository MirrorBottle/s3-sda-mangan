#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "utility.h"
#include "struct.h"
#include "table.h"
#include "menu.h"

extern structure::Auth auth;



using namespace std;
using namespace structure;

namespace auth_controller {
  const string PATH = "../files/users.csv";
  const int TABLE_COLUMNS_LENGTH = 6;
  string TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Email", "Alamat", "Kontak"};

  string path() {
    return PATH; 
  }

  bool login() {
    bool is_login = false;
    string email, password;
    string cur_password, cur_email, hashed;
    utility::header("Mangan - Login");
    cout << "Masukkan Email: "; cin >> email;
    cout << "Masukkan Password: "; cin >> password;
    Node* list = utility::list(PATH);
    while (list != NULL){
      cur_email = utility::toLower(list->data[2]);
      cur_password = list->data[7];
      hashed = to_string(utility::hash(password));
      if(cur_email == email && cur_password == hashed) {
        is_login = true;
        auth.id = list->data[0];
        auth.name = list->data[1];
        auth.role = list->data[8];
        break;
      }
      list = list->next;
    }
    return is_login;
  }

  void regist() {
    bool is_email_not_exist = false;
    string res, coordinates, url;
    string latitude = "0";
    string longitude = "0";
    string id, name, email, address, phone_number, password;

    Node *head = utility::sort(PATH, 0, 1);
    vector<string> latest_user = utility::latest(PATH);
    utility::header("Mangan - Registrasi", "📝 Cukup isi data dirimu dan lokasimu ya!");

    while(!is_email_not_exist) {
      cout << "Email: "; cin >> email;
      vector<string> email_found = utility::find(PATH, 2, email, true);
      is_email_not_exist = email_found.empty();

      if(!is_email_not_exist) {
        utility::notify("error", "Email sudah ada!");
      }
    }

    cout << "Nama: "; fflush(stdin); getline(cin, name);
    cout << "No. HP: "; cin >> phone_number;
    cout << "Alamat: "; fflush(stdin); getline(cin, address);
    cout << "Link Lokasi (contoh: https://goo.gl/maps/ZA8YcgaHsDSJgDH97): "; fflush(stdin); getline(cin, url);
    
    cout << "Password: "; cin >> password;

    utility::cout("cyan", "Sedang mengambil data lokasimu...");
    string invoke = "curl --request POST -s -o data.txt --data \"uri=" + url + "\" https://s3-sda-mangan.vercel.app";
    system(invoke.c_str());
    
    fstream file;//Retrieving response from data.txt

    file.open("data.txt", ios::in);
    while (getline (file, res)) {
      coordinates = res;
    }
    file.close(); 
    remove("data.txt");//Deleting file after the output is shown

    coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), '['), coordinates.end());
    coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), ']'), coordinates.end());

    string delimiter = ",";
    latitude = coordinates.substr(0, coordinates.find(delimiter));
    longitude = coordinates.erase(0, coordinates.find(delimiter) + delimiter.length());
    
    utility::cout("success", "Berhasil mengambil data lokasi!");
  
    id = to_string(stoi(latest_user[0]) + 1);

    string hashed_password = to_string(utility::hash(password));

    string data = id + "," + name + "," + email + "," + address + "," + phone_number + "," + latitude + "," + longitude + "," + hashed_password + ",user";
    file.open(PATH, ios::app);
    file << "\n" << data;
    file.close();

    auth.id = id;
    auth.name = name;
    auth.role = "user";
    utility::notify("success", "Yey, Kamu sudah terdaftar, nih!");
  }
}