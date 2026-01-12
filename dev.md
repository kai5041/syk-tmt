syk-tmt will always be located at C:\\Users\NAME\.smt on Windows, ~/.smt on Unix systems.

## Directory structure

### Single-user directory structure
```sh
/ # root
/syk-tmt # the executable
/bin/ # system-wide self-contained programs
/bin/OS # system-wide links to OS-specific programs
/home # home of the user
/mnt/DRIVE_LETTER # mount points of external mediums
/sca/ # Self-Contained Application
```

### Single-user directory structure
```sh
/ # root
/syk-tmt # the executable
/bin/USER/ # system-wide self-contained programs, user-local self-contained programs
/home/USER/ # home of each user
/mnt/DRIVE_LETTER # mount points of external mediums
/sca/USER/ # Self-Contained Application of each user

# ~ maps to /home/USER/
```



Mandatory commands to implement:
- `cd [dir]`
- `mkdir [dir]`
- `cls`

Mandatory functionalities:
- arrow up: command history up
- arrow down: command history down
