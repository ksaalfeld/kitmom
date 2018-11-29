package require platform
package require Tcl 8.5

# This method will provide the package
proc ::pkgProvide {} {
    set dir [file dirname [info script]]
    # split os-cpu (e.g. win32-x86_64) identification string here
    lassign [split [platform::generic] -] os cpu
    switch -glob -- $os {
        win* {
            if {[string match *_64 $cpu]} {
                load [file join $dir kitmom64[info sharedlibextension]]
            } else {
                load [file join $dir kitmom32[info sharedlibextension]]
            }
        }
        default {
            # Unix and mac targets should have a /tmp directory.
            # This is already cleaned by the system on reboot.
            # We only need to create a temporary location in there.
            source [file join $dir kitmom.tcl]
        }
    }
}

::pkgProvide

rename ::pkgProvide {}
