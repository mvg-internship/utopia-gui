# utopia-gui
GUI for the Utopia EDA

### Install QT

to install the application, you need to install Qt below installation instructions : 
1) Update the package index by running the following command
sudo apt update
2) Install the Qt5 development tools by running the following command
sudo apt install qt5-default
3) Verify that Qt5 is installed properly by running the following command
qmake —version
Or using vpn you can download it from the official site:
1) Go to the Qt website at https://www.qt.io/download.
2) Click on the "Download" button on the homepage.
3) Scroll down to the "All Downloads" section and click on "Go open source".
4) Select the version of Qt that you want to download by clicking on the appropriate button.
5) On the following page, select your platform (e.g. "Linux"), your architecture (e.g. "64-bit"), and your distribution (e.g. "Ubuntu").
6) Click on the "Download" button to begin downloading the Qt installer. 
### Downloading libraries and Basicviz
1) https://github.com/libsdl-org/SDL/releases/tag/release-2.26.5

  cmake . #(the correct command will appear)
  
  mkdir build
  
  cd build
  
  correct command
  
  make
  
2) https://github.com/libsdl-org/SDL_ttf/releases

  ./configure && make && sudo make install
  
  sudo apt-get install libsdl2-ttf-dev
  
3) https://github.com/yaksase/basicviz
  cmake -S . -B build # -G Ninja, etc.
  cd build
  make                # ninja, etc.

### Upload GraphViz

sudo apt install graphviz graphviz-dev

### Before running you also need to set two environment variables

  1)sudo nano ~/.bashrc

  2)export Basicviz=/path/to/Basicviz-main/build/src/main
  
  export UTOPIA_HOME=/path/to/Utopia-Eda

  3)Ctr+O

  4)Enter

  5)Ctr+x
  
  6)source ~/.bashrc
  
### Compiling from Command Line

  cmake .


  make 

## test

cd test_gui

./test_gui
