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
cmake refactor (introduce libs)
UTs for controller and model layer
memory leaks inspection
add icon (https://stackoverflow.com/questions/63697778/how-to-use-glib-compile-resources-with-cmake, Gio::Resources (gtkmm tutorial))
------------
v 0.2
error dialogs
open multiple files (merge)
------------
v. 0.3
settings/bookmarks from file
projects (files and greps)
load/save grep hierarchy
------------
v. 0.4
dialogs with progress (when grepping)
------------
v. 0.5
multithreaded grep
