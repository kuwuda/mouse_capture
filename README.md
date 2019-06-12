# mouse_capture
Hacky script / program for SwayWM which locks a mouse to a given output

Requires [Interception tools](https://gitlab.com/interception/linux/tools), Sway, jq, and slurp (currently).

The script works by intercepting evdev input and ignoring all input that would cause the mouse to leave a given screen.
It's currently very janky, requiring the use of slurp to get initial cursor position, and passing that as an argument to mon_lock

# Compilation / installation
```
git clone https://github.com/kuwuda/mouse_capture.git
cd mouse_capture
g++ -o mon_lock main.c
```
Move it and the script to whatever folder's convenient to you, change DEVNODE in the script to be your input device
(will change this later), and probably bind the script call to a key to be more useful.
