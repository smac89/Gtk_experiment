#include <string>
#include <utility>
#include <functional>
#include <memory>
#include <gdkmm/types.h>
#include <gtkmm.h>
#include <iostream>
#include "radiobuttons.hpp"

namespace example {
    RadioButtons::RadioButtons() :
            m_Box_Top(Gtk::Orientation::ORIENTATION_VERTICAL),
            m_Box1(Gtk::Orientation::ORIENTATION_VERTICAL, 10),
            m_Box2(Gtk::Orientation::ORIENTATION_VERTICAL, 10),
            m_RadioButton1("button1"),
            m_RadioButton2("button2"),
            m_RadioButton3("button3"),
            m_Button_Close(Gtk::StockID("gtk-close")),
            m_Button_LeftChild("Launch left"),
            m_Button_RightChild("Launch right") {}

    RadioButtons::RadioButtons(const int &width, const int &height)
            : RadioButtons() {
        set_default_size(width, height);
    }

    RadioButtons::~RadioButtons() {
        std::cout << "Freed the window!!" << std::endl;
    }

    void RadioButtons::on_button_clicked() {
        hide(); //to close the application.
    }
}


