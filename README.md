# Application helpful in log analysis.

## Features:
- Open multiple files (in tabs)
- Grep (tabs)
- Mark words
- Find
- Add/remove Bookmarks per tab

## Dependencies (ubuntu 20.04):
- cmake
- g++
- libgtkmm-3.0-dev
- libgtksourceviewmm-3.0-dev

## Building (on root directory):
```
mkdir build && cd build
cmake ..
make
```

## TODO/Ideas/Future plans:
###### v. 0.1
- [x] refactor (separate layers)
- [x] model: Log, LogList, Bookmark, BookmarkList, model as logId, fileId, ids in view(?)
- [x] controller: new folder, all logic moved there
- [x] Add check in controller if the same file is not opened/if the same grep is not present
- [ ] cmake refactor (introduce libs)
- [ ] add icon (https://stackoverflow.com/questions/63697778/how-to-use-glib-compile-resources-with-cmake, Gio::Resources (gtkmm tutorial))

###### v 0.2
- [ ] bookmark mapped to fileId, not logId (map in controller <filename, BookmarkList>, filename in every model::Log)
- [ ] Base dialog class not to copy/paste all settings, to make controller testable, dialog factory and common interface for all dialogs
- [ ] Closing dialogs (like grep/find) on ESC - should work like cancel
- [ ] Reopen file
- [ ] Previous finds/greps reminder (list in dialog)
- [ ] Previous search on F3
- [ ] Scrolling to the middle of text view when finding/clicking on bookmark (currently scroll is at the end)

###### v. 0.3
- [ ] Open file from app params / drag and drop
- [ ] Operation::run should return status
- [ ] error dialogs
- [ ] Search from beginning option in error dialog, when query is not found
- [ ] UTs for controller and model layer
- [ ] memory leaks inspection

###### v. 0.4
- [ ] settings/bookmarks/marks from configuration file, options menu
- [ ] automatic marks/bookmarks from settings when file/grep is opened
- [ ] load/save grep hierarchy
- [ ] Logger instead of stdout

###### v. 0.5
- [ ] Label with progress (when for example grepping...) Ready as default.
- [ ] multithreaded grep
- [ ] projects (files and greps)
- [ ] open multiple files (merge)
