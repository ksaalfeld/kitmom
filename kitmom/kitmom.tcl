# kitmom.tcl --
#
#     Kitmom tidies your room once you've finished playing.
#
#     Simply put kimom in your vfs when creating a starpack and load it:
#
#         package require kitmom
#
#     A starpack is a single file executable containing all
#     your code and files bundled in a virtual file system.
#     On Windows a starpack may need to unpack some of the
#     bundled resources (e.g. DLLs) into a temporary location
#     so that Win32 API calls like LoadLibrary() see them.
#
#     On Windows kitmom marks everything in the temporary
#     location for removal on next reboot.
#     Moreover it tells you where the temporary location is
#     so you can throw your own toys in there and mess around.
#     On Linux it creates a suitable temporary location for you.
#
# Copyright (c) 2017 Klaus Saalfeld
#
# See "license.txt" for usage and redistribution
# and for DISCLAIMER OF ALL WARRANTIES.

package require Tcl 8.5


namespace eval ::kitmom {
   variable version 1.0.0
   namespace export dir
}


# ::kitmom::dir --
#
#     Returns the subdirectory we've create in a temporary location.
#     This place can be used as a temporary storage for our application.
#     If the package has not been initialized yet the function raises an error.
#
# Results:
#     Temporary location

proc ::kitmom::dir {} {
    # Get the temporary location
    if {![info exists ::kitmom::playdir]} {
        return -code error "Kitmom was not initialized properly"
    }
    return $::kitmom::playdir
}


# ::kitmom::init --
# 
#     Lookup the temporary location on the current system
#     create a new unique subdirectory for our process there
#     and remember this subdirectory in namespace variable.
#     The function has no effect when called more than once.
#
# Results:
#     Temporary location in use.

proc ::kitmom::init {} {
    if {![info exists ::kitmom::playdir]} {
        # When tcllib is available the function ::fileutil::tempdir is very similar.
        # Unfortunately tcllib may be unavailable and kitmom must be standalone.
        set places {
            ::env(TMPDIR)
            ::env(TMP)
            ::env(TEMP)
            ::env(TRASH_FOLDER)
        }
        # Guess a temporary location by default.
        # We keep that if we're unable to find any better.
        set base "/tmp"
        # Search for temporary location that exists on this system
        foreach where $places {
            if {[info exists $where]} {
                if {[file exists [set $where]]} {
                    set base [set $where]
                    break
                }
            }
        }
        # Get a subdirectory name within temporary location that does not exist yet
        for {set name [pid]} {[file exists [set result [file join $base [format TCL%08x $name]]]]} {set name [expr {$name + 1}]} {
        }
        # Create that directory and remember the location
        file mkdir $result
        set ::kitmom::playdir $result
    }
    return $::kitmom::playdir
}


package provide kitmom $::kitmom::version

# Initialize when namespace is created
if {![info exists ::kitmom::playdir]} {
    ::kitmom::init
}
