
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

namespace user_partner {
  void list() {
    utility::header("Mangan - Cari Mangan");
    utility::notify("success", "Cari Mangan");
  }

  void detail() {
    utility::header("Mangan - Menu Resto");
    utility::notify("success", "Menu Resto");
  }
}