Application helpful in log analysis.

Features:
- Open multiple files (in tabs)
- Grep (tabs)
- Mark words
- Find
- Add/remove Bookmarks per tab

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
refactor (separate layers)
model: Log, LogList, Bookmark, BookmarkList, model as logId, fileId, ids in view(?)
Add check in model/controller if the same file is not opened/if the same grep is not present
controller: new folder, all logic moved there
cmake refactor (introduce libs)
add icon (https://stackoverflow.com/questions/63697778/how-to-use-glib-compile-resources-with-cmake, Gio::Resources (gtkmm tutorial))
push commit to remote
UTs for controller and model layer
memory leaks inspection
------------
v 0.2
error dialogs
open multiple files (merge)
Reopen file
------------
v. 0.3
bookmark mapped to fileId, not logId
Scrolling to the middle of text view when finding/clicking on bookmark (currently scroll is at the end)
------------
v. 0.4
Label with progress (when for example grepping...) Ready as default.
settings/bookmarks/marks from configuration file, options menu
automatic marks/bookmarks from settings when file/grep is opened
projects (files and greps)
load/save grep hierarchy
Open file from app params, drag and drop
------------
v. 0.5
multithreaded grep
Previous finds/greps reminder (list in dialog)
