# Mangan.
## Tentang
Sistem Kunjungan Lapas Online untuk Projek Akhir Algoritma Pemrograman Online Informatika A 2021

## Anggota
1. **2109106002** Alif Maulana Setyawan
2. **2109106024** Ananta Yusra Putra Akmal
3. **2109106026** Bayu Setiawan

## Daftar CSV

1. users: id,name,email,address,phone_number,lat,long,password
1. partners: id,name,email,address,phone_number,password,lat,long
2. drivers: id,name,email,phone_number,password,plate_number
3. menus: id,user_id,name,description,price,is_available
4. deliveries: id,user_id,driver_id,partner_id,partner_lat,partner_long,destination_lat,destination_long,distance,fee,start_at,end_at
5. delivery_details: id,delivery_id,menu_id,amount,fee
6. delivery_histories: id,delivery_id,status,time,is_completed,description
7. delivery_ratings: id,delivery_id,ratings,comments,tip
8. settings: key,value
