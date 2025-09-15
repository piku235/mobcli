# 🛠️ mobcli

Command-line client for interacting with the Mobilus Cosmo GTW.

**Available commands:**

```
sub               subscribes to all device events
network-settings  prints cosmo gtw network settings
device-settings   prints cosmo gtw settings
device-list       lists linked devices
current-state     prints current states of linked devices
session           prints the current session information
call-events       used to send a command to specific linked device
```

## Build

This project uses **CMake** as its build system.

To build the project:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```
