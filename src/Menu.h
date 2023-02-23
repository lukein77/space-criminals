#ifndef _MENU_H_DEFINED_
#define _MENU_H_DEFINED_

#include "common.h"
#include "App.h"

class Menu {
    protected:
        int currentOption;
        int numOptions;
        char *labels[MAX_MENU_OPTIONS];
        Texture background;
    public:
        virtual void choose() = 0;
        void selectPrevious() { currentOption = (currentOption - 1) % numOptions; }
        void selectNext() { currentOption = (currentOption + 1) % numOptions; }
        int getCurrentOption() { return currentOption; }
        int getNumOptions() { return numOptions; }
        char *getLabel(int option) { return labels[option]; }
        Texture *getBackground() { return &background; }
};


class MainMenu : public Menu {
    public:
        MainMenu();
        ~MainMenu() {}
        void choose();
};

#endif