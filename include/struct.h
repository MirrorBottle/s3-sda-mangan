#pragma once
#include <iostream>
#include <string>

using namespace std;
namespace structure {
  struct kamar {
    string kode;
    string nama;
  };
  struct wbp {
    string kode;
    string nama;
  };

  struct kunjungan {
    string kode;
    string kode_wbp;
    string kode_kamar;
    string tanggal;
    string nama_pengunjung;
    string nik_pengunjung;
    int status;
    string jam_mulai;
    string jam_selesai;
    string catatan;
    kamar kamar;
    wbp wbp;
  };

  struct Node {
    vector<string> data;
    Node *next;
  };

  struct Auth {
    int id = 0;
    bool is_login = false;
    string role = 'admin';
  }
}

