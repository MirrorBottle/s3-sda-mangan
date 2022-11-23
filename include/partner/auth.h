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

namespace partner_auth {
  const string PATH = "../files/partners.csv";

  string path() {
    return PATH; 
  }

  void regist() {
    bool is_email_not_exist = false;
    string res, coordinates, url;
    string latitude = "0";
    string longitude = "0";
    string id, name, email, address, phone_number, password;

    Node *head = utility::sort(PATH, 0, 1);
    vector<string> latest_user = utility::latest(PATH);
    utility::header("Mangan - Menjadi Partner", "📝 Cukup isi data restomu ya!");

    while(!is_email_not_exist) {
      cout << "Email Akun: "; cin >> email;
      is_email_not_exist = utility::search(PATH, 2, email, true) == -1;

      if(!is_email_not_exist) {
        utility::notify("error", "Email sudah ada!");
      }
    }

    cout << "Nama Resto: "; cin >> name;
    cout << "No. HP Resto: "; cin >> phone_number;
    cout << "Alamat Resto: "; fflush(stdin); getline(cin, address);
    cout << "Link Lokasi (contoh: https://goo.gl/maps/ZA8YcgaHsDSJgDH97): "; fflush(stdin); getline(cin, url);
    
    cout << "Password: "; cin >> password;
    string invoke = "curl --request POST -s -o data.txt --data \"uri=" + url + "\" https://s3-sda-mangan.vercel.app";
    utility::cout("blue", "Mengambil lokasi...");
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
    
    utility::cout("green", "Berhasil mengambil lokasi!");

    id = to_string(stoi(latest_user[0]) + 1);

    string hashed_password = to_string(utility::hash(password));

    string data = id + "," + name + "," + email + "," + address + "," + phone_number + "," + latitude + "," + longitude + "," + hashed_password;
    file.open(PATH, ios::app);
    file << "\n" << data;
    file.close();


    utility::notify("success", "Yey, Kamu sudah terdaftar, nih!");
  }

  bool login() {
    bool is_login = false;
    string phone_number, password;
    string cur_password, cur_phone_number, hashed;
    utility::header("Mangan - Login Partner");
    cout << "No. HP: "; cin >> phone_number;
    cout << "Masukkan Password: "; cin >> password;
    Node* list = utility::list(PATH);
    while (list != NULL){
      cur_phone_number = utility::toLower(list->data[3]);
      cur_password = list->data[7];
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