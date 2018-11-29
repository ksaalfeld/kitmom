if {![package vsatisfies [package provide Tcl] 8.5]} {return}

package ifneeded kitmom 1.0.0 [list source [file join $dir pkgProvide.tcl]]
