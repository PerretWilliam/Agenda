#include <string>
#include <vector>
#include <functional>
#include <forward_list>
#include <filesystem>

#include "../includes/date.hpp"

namespace fs = std::filesystem;

namespace diary
{
  enum struct STATE
  {
    LAUNCH,
    LOAD_AGENDA,
    MENU,
    CHOICE,
    CREATE_AGENDA,
    ADD_EVENT,
    DEL_EVENT,
    EXIT
  };

  struct Event
  {
    std::string id;
    std::string title;
    std::string description;
    date::Date date_begin;
    date::Date date_end;
  };

  struct Diary
  {
    std::string title;
    std::string description;
    std::forward_list<Event> events;
    bool is_modify;
  };

  struct Global
  {
    STATE state;
    Diary diary;
    fs::path export_path = fs::current_path() / "export";
  };

  struct Entry
  {
    char input;
    std::string label;
    std::function<void(Global &)> launch;
  };

  struct Menu
  {
    std::string label;
    std::vector<Entry> entrys;
  };

  void clear_screen();
  void print_error(const std::string &msg);
  std::string getUID(std::size_t len);

  // File
  bool diary_exist(const std::string &diary_name);
  void open_file(std::string file_name);
  void create_export_directory(const Global &global);

  // Inputs
  void getUserInput(char &c, const std::string &msg);
  std::string create_title(const std::string &msg);
  std::string create_description(const std::string &msg);
  bool ask_same_date();
  bool ask_load_diary(Global &global);
  bool ask_delete_diary(Global &global);

  // Events
  void print_events(const Global &global);
  Event create_event();
  void add_event(Global &global);
  void delete_event(Global &global);

  // Diary
  void print_diary(const Global &global);
  Diary create_diary();

  // HTML export
  void export_description_HTML(std::ofstream &file, const std::string description);
  void export_event_HTML(std::ofstream &file, const Event &event);
  void export_diary_HTML(const Global &global);

  // Save
  void save_event(std::ofstream &file, Event event);
  void save_diary(const Global global);
  void confirm_save(const Global &global);

  // Load
  std::string load_description(std::ifstream &file);
  Diary load_diary(const fs::path &diary_path);

  // Menus
  bool is_menu_or_entry_valid(const std::vector<Menu> &menus, size_t menu_index, size_t entry_index);
  std::vector<diary::Menu> initialize_menu();
  void show_menu(const Menu &menu);
  void print_choice_menu(const std::string &msg);
  void start_menu(Global &global, const std::vector<diary::Menu> &menus);
  void main_menu(Global &global, const std::vector<diary::Menu> &menus);
}