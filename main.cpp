
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

#include <giomm.h>
#include <gtkmm.h>
#include <iostream>
#include "radiobuttons.hpp"
#include "util.hpp"

auto main(int argc, char *argv[]) -> int {
    auto app = Gtk::Application::create(argc, argv, "org.smac89.gtkmm.example");
    auto button_window = example::from_file("../radio.glade");
//    auto button_window = create_default(450, 300);

    app->signal_window_added().connect([&button_window](Gtk::Window* child) {
        std::cout << "New window added: " << child->get_name() << std::endl;
        child->grab_focus();
    });

    app->signal_startup().connect([&button_window]() {
        std::cout << "The app has started!!" << std::endl;
        button_window->show_all_children();

        auto file = Gio::File::create_for_path(".");
        std::cout << "The folder exists: "
                  << std::boolalpha << file->query_exists()
                  << std::endl;

        if (file->query_exists()) {
            std::cout << "Name of folder is :" << file->get_parse_name()
                      << std::endl;
        }
    });

    app->signal_shutdown().connect([]() {
        std::cout << "Goodbye!!" << std::endl;
    });

    //Shows the window and returns when it is closed.
    return app->run(*button_window);
}
