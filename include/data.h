#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;
namespace data {
  map<string, string> colors = {
    { "black", "\033[30m" },
    { "red", "\033[31m" },
    { "green", "\033[32m" },
    { "yellow", "\033[33m" },
    { "blue", "\033[34m" },
    { "cyan", "\033[36m" },
    { "white", "\033[37m" }
  };

  map<string, string> status_delivery = {
    { "ACCEPT", "1" },
    { "PARTNER_CONFIRM", "2" },
    { "PARTNER_PROCESS", "3" },
    { "DRIVER_CONFIRM", "4" },
    { "DRIVER_DELIVER", "5" },
    { "FINISH", "6" },
  };

  map<string, string> label_status_delivery = {
    { "ACCEPT", "Pesanan Diterima" },
    { "PARTNER_CONFIRM", "Pesanan Dikonfirmasi Partner" },
    { "PARTNER_PROCESS", "Pesanan Diproses Partner" },
    { "DRIVER_CONFIRM", "Pesanan Dikonfirmasi Driver" },
    { "DRIVER_DELIVER", "Pesanan Diantar Driver" },
    { "FINISH", "Pesanan Diterima Pengguna" },
  };
}