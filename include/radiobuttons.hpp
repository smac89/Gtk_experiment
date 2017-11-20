//$Id: radiobuttons.h 2 2003-01-21 13:41:59Z murrayc $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_EXPERIMENT_RADIOBUTTONS_HPP
#define GTKMM_EXPERIMENT_RADIOBUTTONS_HPP

#include <string>
#include <memory>
#include <functional>
#include <gtkmm.h>

// Adding custom widgets to glade
// https://szilard.blogs.balabit.com/en/2012/06/how-to-add-custom-gtkmm-widget-to-glade/

namespace example {
    class RadioButtons : public Gtk::Window {
        friend std::shared_ptr<Gtk::Window> create_default();
        friend std::shared_ptr<Gtk::Window> create_default(int const&, int const&);
        friend std::shared_ptr<Gtk::Window> from_file(const std::string&);

    public:
        ~RadioButtons() override;
    protected:
        RadioButtons();
        RadioButtons(int const&, int const&);

        //Signal handlers:
        void on_button_clicked();

        //Child widgets:
        Gtk::Box m_Box_Top, m_Box1, m_Box2;
        Gtk::RadioButton m_RadioButton1, m_RadioButton2, m_RadioButton3;
        Gtk::Separator m_Separator;
        Gtk::Button m_Button_Close;
        Gtk::Button m_Button_LeftChild;
        Gtk::Button m_Button_RightChild;
    private:

    };

    extern std::shared_ptr<Gtk::Window> create_default();
    extern std::shared_ptr<Gtk::Window> create_default(int const&, int const&);
    extern std::shared_ptr<Gtk::Window> from_file(const std::string&);
}

#endif //GTKMM_EXPERIMENT_RADIOBUTTONS_HPP
