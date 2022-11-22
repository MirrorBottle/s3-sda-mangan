
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

namespace user_delivery {
  void create() {
    utility::header("Mangan - Pesan Mangan");
    utility::notify("success", "Pesan Mangan");
  }

  void detail() {
    utility::header("Mangan - Detail Pesanan");
    utility::notify("success", "Detail Pesanan");
  }

  void rating() {
    utility::header("Mangan - Beri Rating");
    utility::notify("success", "Beri Rating");
  }

  void receive() {
    utility::header("Mangan - Terima Pesanan");
    utility::notify("success", "Terima Pesanan");
  }
}