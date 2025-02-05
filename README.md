## TSP MadDevs


### На линукс:
1) скачать SFLM:   
`sudo apt-get install libsfml-dev`

2) Может еще что то докачать, не помню

3) Запустить: `make`
---

### На Windows 

### Install sflm on Windows using vcpkg
    1) `git clone https://github.com/microsoft/vcpkg.git`
    2) `cd vcpkg; .\bootstrap-vcpkg.bat`
    3) add to Path `vcpkg.exe` location
    4) `vcpkg install sfml`

---
## Входные данные

В `main.cc` радиус `radius` считается в пикселях и должен быть меньше `window_size`:

**radius < window_size/2**

`price` - роли не играет, так как считалась только длина маршрута в пикселях

В `path` находится путь из `start` в `end`.


![screens](screens/graph_view_100.png)


Некоторые точки выходят за границы круга - проблема отображения, согласно координатам они входят в окружность заданного радиуса

