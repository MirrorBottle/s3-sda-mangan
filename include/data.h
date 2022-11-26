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
    { "1", "Daftar Tunggu" },
    { "2", "Diterima" },
    { "3", "Selesai" },
    { "4", "Ditolak" },
  };

  map<string, double> resto_detail {
    { "latitude", -0.4682104 },
    { "longitude", 117.1590505 },
    { "fee", 1500 }
  };
}