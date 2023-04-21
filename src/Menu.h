#ifndef _MENU_H_DEFINED_
#define _MENU_H_DEFINED_

#include "common.h"
#include "App.h"

class Menu {
    protected:
        unsigned short currentOption;
        int numOptions;
        std::string labels[MAX_MENU_OPTIONS];
        Texture background;
    public:
        virtual void choose() = 0;
        void selectPrevious();
        void selectNext();
        int getCurrentOption() { return currentOption; }
        int getNumOptions() { return numOptions; }
        std::string getLabel(int option) { return labels[option]; }
        Texture *getBackground() { return &background; }
};


class MainMenu : public Menu {
    public:
        MainMenu();
        ~MainMenu() {}
        void choose();
};

#endif