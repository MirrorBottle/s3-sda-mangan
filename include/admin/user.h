#pragma once
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <tuple>

#include "../data.h"
#include "../utility.h"
#include "../struct.h"
#include "../table.h"
#include "../menu.h"


using namespace std;
using namespace structure;

namespace admin_user {
  const string PATH = "../files/users.csv";

  const int TABLE_COLUMNS_LENGTH = 6;
  string TABLE_COLUMNS[] = {"No.", "ID", "Nama", "Email", "Alamat", "No. HP"};

  void index() {
    utility::header("Mangan - 📖 Daftar Pengguna");
    Node *list = utility::search(PATH, { 8 }, "user");
    TextTable table = utility::table(TABLE_COLUMNS_LENGTH, TABLE_COLUMNS, list);
    cout << table;

    utility::notify("success", "Untuk Kembali");
  }
}