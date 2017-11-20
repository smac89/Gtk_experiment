#ifndef GTKMM_EXPERIMENT_UTIL_HPP
#define GTKMM_EXPERIMENT_UTIL_HPP

#include "radiobuttons.hpp"

namespace example {
    static std::function<void()> on_click_widget(
            const std::shared_ptr<Gtk::Window> &parent,
            std::function<std::shared_ptr<Gtk::Window>()> create_child,
            std::function<void(std::shared_ptr<Gtk::Window> &)> callback) {

        return [&parent,
                window_factory=std::move(create_child),
                callback=std::move(callback)]() {
            auto application = parent->get_application();

            auto child = window_factory();
            child->set_transient_for(*parent);
            child->set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);

            application->add_window(*child);
            child->show_all();
            child->property_decorated() = false;
            child->property_visible() = true;

            callback(child);
        };
    }

    auto from_file(const std::string &glade_file) -> std::shared_ptr<Gtk::Window> {
        auto builder = Gtk::Builder::create_from_file(glade_file);

        Gtk::Window *window = nullptr;
        builder->get_widget("MainWindow", window);

        std::shared_ptr<Gtk::Window> win_wrapper(window);

        Gtk::Button *m_Button_Close = nullptr;
        builder->get_widget("m_Button_Close", m_Button_Close);

        Gtk::Button *m_Button_LeftChild = nullptr;
        builder->get_widget("m_Button_LeftChild", m_Button_LeftChild);

        Gtk::Button *m_Button_RightChild = nullptr;
        builder->get_widget("m_Button_RightChild", m_Button_RightChild);

        m_Button_Close->signal_clicked().connect([&win_wrapper]() {
            win_wrapper->hide();
        });

        m_Button_LeftChild->signal_clicked().connect(on_click_widget(
                win_wrapper, [&glade_file] { return from_file(glade_file); },
                [m_Button_LeftChild](const std::shared_ptr<Gtk::Window> &child) {
                    if (child) {
                        std::cout << "Child is showing: " << child->is_visible() << std::endl;
                        m_Button_LeftChild->property_sensitive() = false;
                        child->signal_hide().connect([&]() {
                            std::cout << "Left child was killed\n";
                            m_Button_LeftChild->property_sensitive() = true;
                        });
                    }
                }));

        m_Button_RightChild->signal_clicked().connect(on_click_widget(
                win_wrapper, [&glade_file] { return from_file(glade_file); },
                [m_Button_RightChild](const std::shared_ptr<Gtk::Window> &child) {
                    if (child) {
                        std::cout << "Child is showing: " << child->is_visible() << std::endl;
                        m_Button_RightChild->property_sensitive() = false;
                        child->signal_hide().connect([&]() {
                            std::cout << "Right child was killed\n";
                            m_Button_RightChild->property_sensitive() = true;
                        });
                    }
                }));

        return win_wrapper;
    }

    auto create_default() -> std::shared_ptr<Gtk::Window> {

        std::shared_ptr<RadioButtons> window(new RadioButtons);

        // Set title and border of the window
        window->set_title("radio buttons");
        window->property_window_position() = Gtk::WIN_POS_CENTER;

        // Put radio buttons 2 and 3 in the same group as 1:
        window->m_RadioButton2.join_group(window->m_RadioButton1);
        window->m_RadioButton3.join_group(window->m_RadioButton1);

        // Add outer box to the window (because the window
        // can only contain a single widget)
        window->add(window->m_Box_Top);

        //Put the inner boxes and the separator in the outer box:
        window->m_Box_Top.pack_start(window->m_Box1,
                                     Gtk::PackOptions::PACK_EXPAND_WIDGET);
        window->m_Box_Top.pack_start(window->m_Separator,
                                     Gtk::PackOptions::PACK_EXPAND_WIDGET);
        window->m_Box_Top.pack_start(window->m_Box2,
                                     Gtk::PackOptions::PACK_EXPAND_WIDGET);

        // Set the inner boxes' margins
        window->m_Box1.property_margin() = 10;
        window->m_Box2.property_margin() = 10;

        // Put the radio buttons in Box1:
        window->m_Box1.pack_start(window->m_RadioButton1,
                                  Gtk::PackOptions::PACK_EXPAND_WIDGET);
        window->m_Box1.pack_start(window->m_RadioButton2,
                                  Gtk::PackOptions::PACK_EXPAND_WIDGET);
        window->m_Box1.pack_start(window->m_RadioButton3,
                                  Gtk::PackOptions::PACK_EXPAND_WIDGET);

        // Set the second button active
        window->m_RadioButton2.set_active();

        // Put Close button in Box2:
        window->m_Box2.pack_start(window->m_Button_Close,
                                  Gtk::PackOptions::PACK_EXPAND_WIDGET);

        // Make the button the default widget
        window->m_Button_Close.set_can_default();
        window->m_Button_Close.grab_default();
        window->m_Button_Close.property_always_show_image() = true;

        // Connect the clicked signal of the button to
        // RadioButtons::on_button_clicked()
        window->m_Button_Close.signal_clicked().connect(
                sigc::mem_fun(*window, &RadioButtons::on_button_clicked));

        return window;
    }

    std::shared_ptr<Gtk::Window> create_default(const int& width, const int& height) {
        auto window = create_default();
        window->set_default_size(width, height);
        return window;
    }
}

#endif //GTKMM_EXPERIMENT_UTIL_HPP
