TurboMutipleExes:
Turbo Studio doesn't allow for multiple entry points
this program will circumvit this limitation.
This program will pass command line arguments
to the new entry point (new Turbo Studio entry point)
and will start specific executables.

On first part the Entry Points (output exes) are new
exes created by this program; you should specify their
full path on ListBox from which their short name is grabbed
and also from full name are grabbed resources: icons
and version information.
So first browse for exe by choosing "..." button and then click Add
button to add it to ListBox. You can clear all ListBox items
by Clear All button.
The process entries button is optional and only needed for custom
entry points paths information will be grabbed from full path ListBox
to TextBox - it will get short file name of Entry Points from full path.

Start-up exe short file name (Virtualized Turbo output exe) is the only
file name which can't be renamed afterwards - you need to stick to the
Virtualized Turbo output exe - output as an .dat file is a cool thing to do.

If you don't specify "Start-up exe icon and information" resources (icons/version)
will be missing from NewEntryPoint.exe file generated;
NewEntryPoint.exe should be the new Start-up exe specified in Turbo Studio.

The final step is pressing the Create Now button and choose an output
directory for new files.

