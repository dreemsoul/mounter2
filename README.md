mounter2
========

Hello ALL version 1.4.0 is finished.

this version has removed the text fields and placed in a button to
select the iso file.  the text field now displays the file chosen.
it also still works fine if you type in the file by hand.

^^ done upon request ^^

also instead of using system() command it now uses execv()

the result of having a button leaves me with little need to set up
a config file with default directory containing iso files.
i hope people are happy with the change.

also in later updates i hope to but in a couple different mount
points so that the program does not take up all of /mnt.

thank you again all,
cheers.

----1.3.6 updates ----

i wrote some error handling so now when the mount command
fails it will send an error back instead of telling you it is
still mounted.

thank you for your patience this is after all the first
project ive released so it goes slow as i learn

in the next release im going to have the option for a default
directory to mount from and also to.  thanks again for using this software.

----1.3.5 updates ----


now runs with gksu.

----1.3.4 updates ----

A lot of cosmetics fixes in this version

removed the close button and just added a menu item for it

cleaned up some of the files too 

gonna call this version a first release

----------------------------------------

in the tar.gz you will find the make file
and everything you need to build it
as well as the gpl v1.2 license
so removed the install script
also removed the older files as i considered
the 1.3 version incomplete.
--TODO--

requires gtk and gksu

mounter2 is desgined to make mounting iso files
much simpler. :-D

