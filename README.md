# Lab1_3var

Команды для запуска ноды после сборки:

source devel/setup.bash

rosrun client_server server

Команды для отслеживания сообщений в топике:

rostopic echo /my_topic

Команды для обращения к сервису:

rosservice call /glass_bridge 'l'

rosservice call /glass_bridge 'r'


