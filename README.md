# test-multimeter

сборка под ubuntu

SERVER:
В папке server собираем через командную строку: 
 make all - собирает 
 make clean - очищает
запускаем ./server

CLIENT:
Qt 5_15 
1. В папке client открываем прокет черз Qt Creator
2. Указываем свой пусть к серверу в файле client_socket.cpp:
  #define NAME_SERVER "/home/vboxuser/Public/server_socket.server"
3. собираем и запускаем

Собиралось и запускалось на Ubuntu 22.04.1 LTS, которая стояла на  VirtualBox 7.0
