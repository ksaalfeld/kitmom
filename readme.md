# Kitmom

Kitmom tidies your room once you've finished playing. This is essential
for every Tcl developer using starpacks to deploy a Tcl application.

On Windows when a starpack is executed the runtime creates
a temporary directory in:

    %LOCALAPPDATA%\Temp

for example named `TCL00000598`. When you load a DLL it gets silently
extracted from the stackpack, is put into this temporary directory and
is then loaded via Windows API functions. When the starpack application
exits these files remain in the temporary directory and start to clutter
the hard disk. Kitmom takes care of them.

Sometimes your starpack application need to manually extract some files e.g.
to open or view them using external applications. When you extract these
files into this temporary directory kitmom takes care of them as well.
It keeps your room clean and tidy.

# Usage

Simply put kimom library in your vfs when creating the starpack and load it:

    package require kitmom

To obtain the directory kitmom is going to erase use

    set dir [::kitmom::dir] 

All files put into this directory will be marked for deletion. You can also
throw your own toys in the temporary directory and mess around with them.
Kitmom does not remove files immediately when application exits.
Instead on Windows kitmom marks everything in the temporary
location for removal on next reboot.

When the application exits kitmom generates a file `kitmom.log` located in the
temporary directory containing everything that has been marked for removal.

# Compile

Tcl and C sources are located in

    kitmom/
    source/

They get compiled and copied to

    lib/kitmom/

Tcl library to link with and Tcl include files reside in

    tcl8.6/windows/32/include
    tcl8.6/windows/32/lib
    tcl8.6/windows/64/include
    tcl8.6/windows/64/lib

To compile the project put your compiler in `PATH` (or adjust `build.bat`) and execute

    build.bat

You may use TDM-GCC (64 bit) to compile the project

<http://tdm-gcc.tdragon.net/>

When in doubt use Windows 7 to compile things.

# Starpacks

A starpack is a single file executable containing all
your Tcl code and additional files bundled in a virtual file system.
On Windows a starpack may need to unpack some of the
bundled resources (e.g. DLLs) into a temporary location
so that Win32 API functions like `LoadLibrary()` can access them there.

More information on starpacks:

<http://kitcreator.rkeene.org>
