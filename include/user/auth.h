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
#include "./main.h"

using namespace std;
using namespace structure;

namespace user_auth {
  const string PATH = "../../files/users.csv";
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
    // system(invoke.c_str());
    
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
  }

  void login() {
    utility::header("Mangan - Login Pengguna");
    user::index();
  }
}