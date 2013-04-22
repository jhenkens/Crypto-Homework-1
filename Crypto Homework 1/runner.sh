#! /bin/bash
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=256"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=512"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=1024"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=2048"
time ./runnable
echo "####### BEGINNING MODEXP OPTIMIZED"
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=256" -D"MODEXPMARY"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=512" -D"MODEXPMARY"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=1024" -D"MODEXPMARY"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=2048" -D"MODEXPMARY"
time ./runnable
echo "####### BEGINNING MULTI OPTIMIZED"
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=256" -D"MULTSHIFTADD"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=512" -D"MULTSHIFTADD"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=1024" -D"MULTSHIFTADD"
time ./runnable
clang++ main.cpp uint_var.cpp -o runnable -stdlib=libc++ -D"CS290BITLENGTH=2048" -D"MULTSHIFTADD"
time ./runnable
