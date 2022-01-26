Application helpful in log analysis.

Features:
- Open multiple files (in tabs)
- Grep (tabs)
- Mark words
- Find
- Bookmark

Dependencies (ubuntu 20.04):
cmake
g++
libgtkmm-3.0-dev
libgtksourceviewmm-3.0-dev

Building (on root directory):
mkdir build && cd build
cmake ..
make

TODO/Ideas/Future plans:
v. 0.1
refactor (separate layers, unify operations, prevent the same function names in BaseTab (template function?))
model: Log, LogList, Bookmark, BookmarkList
functions: all ops unified (also open/grep), +NameGenerator
controller: new folder, all logic moved there
cmake refactor (introduce libs)
add icon (https://stackoverflow.com/questions/63697778/how-to-use-glib-compile-resources-with-cmake, Gio::Resources (gtkmm tutorial))
Readme with current functionality
push commit to remote
UTs for controller and model layer
memory leaks inspection
model as logId, fileId
------------
v 0.2
error dialogs
open multiple files (merge)
Reopen file
------------
v. 0.3
bookmark mapped to fileId, not logId
------------
v. 0.4
settings/bookmarks from configuration file, options menu
projects (files and greps)
load/save grep hierarchy
Previous finds/greps reminder (list in dialog)
------------
v. 0.5
dialogs with progress (when grepping)
multithreaded grep
