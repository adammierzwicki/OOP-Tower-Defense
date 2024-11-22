#include <iostream>
#include <utility>
#include <windows.h>  

class Settings { //todo: implement as singleton
    private:
        int difficulty = 1;
        std::pair<int, int> screen_resolution = std::make_pair(800, 600);
        bool auto_save = true;
    
    public:
        void setSettings() { //todo: add more try excepts
            std::cout << "Enter difficulty (1-3): ";
            std::cin >> this->difficulty;
            std::cout << "Enter screen resolution (width height): ";
            int w, h;
            std::cin >> w >> h;
            this->screen_resolution = std::make_pair(w, h);
            std::cout << "Enable auto save? (y/n): ";
            char c;
            try {
                std::cin >> c;
            }
            catch (std::exception& e) {
                system("Color 04");
                std::cout << "Invalid input. Autosave remains on." << std::endl;
                system("Color 07");
            }

            if (c == 'y') {
                this->auto_save = true;
            }
            else if (c == 'n') {
                this->auto_save = false;
            }
            else {
                system("Color 04");
                std::cout << "Invalid input. Autosave remains on." << std::endl;
                system("Color 07");
            }
            std::cout << "Settings changed to:" << std::endl;
            getCurrentSettings();
        }
        void getCurrentSettings() {

            std::cout << "Difficulty: " << this->difficulty << std::endl;
            std::cout << "Screen resolution: " << this->screen_resolution.first << "x" << this->screen_resolution.second << std::endl;
            std::cout << "Auto save: " << (this->auto_save ? "on" : "off") << std::endl;
        }
};

int main() {
    Settings settings;
    settings.setSettings();
    settings.getCurrentSettings();
    return 0;
}