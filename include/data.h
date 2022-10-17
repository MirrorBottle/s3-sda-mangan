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

  map<string, int> status_kunjungan = {
    { "menunggu", 1 },
    { "diterima", 2 },
    { "ditolak", 3 },
  };

  map<int, string> label_status_kunjungan = {
    { 1, "MENUNGGU" },
    { 2, "DITERIMA" },
    { 3, "DITOLAK " },
  };

  map<int, string> color_status_kunjungan = {
    { 1, "yellow" },
    { 2, "green" },
    { 3, "red" },
  };

  map<string, string> operational = {
    { "start", "09:00" },
    { "end", "16:00" }
  };
}