//
// Created by Reyno VAN DER WESTHUIZEN on 2017/06/09.
//

#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

class Window {
    public:
        Window();
        Window(int width, int height);
        Window(const Window& window);
        void operator = (const Window& window);
        ~Window();

        int getWidth();
        int getHeight();
        void setWidth(int width);
        void setHeight(int height);
    private:
        int width;
        int height;
};

#endif
