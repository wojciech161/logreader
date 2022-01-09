#include "MenuBuilder.hpp"
#include "MainWindow.hpp"

namespace
{
const char* ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Open</attribute>"
    "          <attribute name='action'>actions.open</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>actions.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Tools</attribute>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Grep</attribute>"
    "        <attribute name='action'>actions.grep</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;g</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Find</attribute>"
    "        <attribute name='action'>actions.find</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;f</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Mark</attribute>"
    "        <attribute name='action'>actions.mark</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;m</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Bookmark</attribute>"
    "        <attribute name='action'>actions.bookmark</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;b</attribute>"
    "      </item>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_About</attribute>"
    "        <attribute name='action'>actions.about</attribute>"
    "      </item>"
    "    </submenu>"
    "  </menu>"
    "</interface>";
} // namespace

namespace view
{
Gtk::MenuBar* MenuBuilder::build()
{
    refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        g_warning("Building menus and toolbar failed: %s", ex.what().c_str());
    }
    auto object = refBuilder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu)
    {
        g_warning("GMenu not found\n");
    }
    else
    {
        return Gtk::make_managed<Gtk::MenuBar>(gmenu);
    }
    return nullptr;
}
} // namespace view
