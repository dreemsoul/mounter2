// Mounter2 v1.4.2
/*this program allows you to specify a iso file and its directory and mount it in /mnt  there is also an option to unmout the file.
Copyright (C) 2013  James Fortini

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA*/

// Headers

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

// Random Variables
    char              textlab[64];
    char              aboutlab[100];
    int               textlength = 35;
    const char*       folderpathx;
    char              fullpath[150];
    char              command[200];
    char*             filename;

// Widgets
    GtkWidget *fpath;
    GtkWidget *window;
    GtkWidget *vertbox;
    GtkWidget *checkwin;
    GtkWidget *checkwinbox;
    GtkWidget *textstuff;
    GtkWidget *pokeme;
    GtkWidget *toolbar;
    GtkWidget *menu;
    GtkWidget *filemenu;
    GtkWidget *filesubmenu;
    GtkWidget *aboutmenu;
    GtkWidget *aboutsubmenu;
    GtkWidget *closeswitch;
    GtkWidget *aboutswitch;
    GtkWidget *dialog;

// Events
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
   return FALSE;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

// Unmount
static void unmount (GtkWidget *wid, GtkWidget *win)
{
  int checkfail;
  folderpathx =  gtk_entry_get_text(GTK_ENTRY(fpath));
  char *const args[] = {"/usr/bin/udevil","umount",(char*)folderpathx,NULL} ;

  pid_t pid = fork() ;

  if (pid == 0)
  {
	  execv(args[0], args);
  }else{
	  waitpid( pid,&checkfail,0 ) ;
	  if (WEXITSTATUS(checkfail) == 0)
	  {
		  GtkWidget *dialog = NULL;
		  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Unmounted");
		  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
		  gtk_dialog_run (GTK_DIALOG (dialog));
		  gtk_widget_destroy (dialog);
	  }
	  else
	  {
		  GtkWidget *dialog = NULL;
		  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Image couldn't unmount\nYou may want to check\nthe folder.\n");
		  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
		  gtk_dialog_run (GTK_DIALOG (dialog));
		  gtk_widget_destroy (dialog);
	  }
  }
}

//Mount
static void mount ( GtkWidget *wid, GtkWidget *win )
{
  int checkfail;
  folderpathx =  gtk_entry_get_text(GTK_ENTRY(fpath));
  char *const args[] = { "/usr/bin/udevil", "mount",(char*)folderpathx,NULL };

  pid_t pid = fork() ;

  if (pid == 0)
  {
	  execv(args[0], args);
  }else{
	  waitpid( pid,&checkfail,0 ) ;
	  if (WEXITSTATUS(checkfail) == 0)
	  {
		  GtkWidget *dialog = NULL;
		  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Mounted");
		  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
		  gtk_dialog_run (GTK_DIALOG (dialog));
		  gtk_widget_destroy (dialog);
	  }
	  else
	  {
		  GtkWidget *dialog = NULL;
		  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Could not mount file...\nCheck and make sure\nfolder path is correct.\nand that nothing else\nis mounted there.");
		  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
		  gtk_dialog_run (GTK_DIALOG (dialog));
		  gtk_widget_destroy (dialog);
	  }
  }



}

// About Menu Item
static void aboutit (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;
  sprintf(aboutlab,"%s", "Mounter2\n\n""Version 1.4.2\n""Is an application designed to make\n""mounting iso files easy to do.");
  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, aboutlab);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
static void openpath()
{
    dialog = gtk_file_chooser_dialog_new ("Open File",
				      GTK_WINDOW (window),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
        {
            filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

        }
    gtk_entry_set_text(GTK_ENTRY(fpath), filename);
    gtk_widget_destroy (dialog);
}

// Main Function
int main( int   argc, char *argv[] )
{

 // Build the main window
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Mounter2");
    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
    g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (destroy), NULL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window), 2);

// Slap on a container
    vertbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vertbox);

// Menu
    menu = gtk_menu_bar_new();
    filemenu = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), filemenu);
    aboutmenu = gtk_menu_item_new_with_label("About");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), aboutmenu);
    gtk_box_pack_start (GTK_BOX (vertbox), menu, TRUE, TRUE, 0);
    filesubmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(filemenu), filesubmenu);
    closeswitch = gtk_menu_item_new_with_label("Close");
    gtk_menu_shell_append(GTK_MENU_SHELL(filesubmenu), closeswitch);
    g_signal_connect(closeswitch, "activate", gtk_main_quit, NULL);
    gtk_container_add(GTK_CONTAINER(vertbox), menu);
    gtk_box_set_child_packing(GTK_BOX(vertbox), menu, FALSE, FALSE, FALSE, GTK_PACK_START);
    g_signal_connect(window, "destroy", gtk_main_quit, NULL);
    gtk_widget_realize(window);
    aboutsubmenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(aboutmenu), aboutsubmenu);
    aboutswitch = gtk_menu_item_new_with_label("About Mounter2");
    gtk_menu_shell_append(GTK_MENU_SHELL(aboutsubmenu), aboutswitch);
    g_signal_connect(aboutswitch, "activate", G_CALLBACK(aboutit), NULL);


// Text
    sprintf(textlab, "%s", "<big><b>Mounter2</b></big>\n\n");
    textstuff = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL (textstuff), textlab);
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);
    sprintf(textlab, "<small>%s</small>", "Select an ISO to be mounted / unmounted.");
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);
    textstuff = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL (textstuff), textlab);
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);

// File field
    fpath = gtk_entry_new();
    GtkStyle *style = gtk_widget_get_style(fpath);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(fpath, style->font_desc);
    gtk_entry_set_width_chars(GTK_ENTRY(fpath), textlength);
    gtk_editable_set_editable(GTK_EDITABLE(fpath), TRUE);
    gtk_entry_set_text(GTK_ENTRY(fpath), fullpath);
    gtk_box_pack_start (GTK_BOX (vertbox), fpath, TRUE, TRUE, 0);
// Folder Button
    pokeme = gtk_button_new_from_stock ("Choose File");
    g_signal_connect (G_OBJECT (pokeme), "clicked", G_CALLBACK (openpath), (gpointer) window);
    gtk_box_pack_start (GTK_BOX (vertbox), pokeme, TRUE, TRUE, 0);

// Unmount Button
    pokeme = gtk_button_new_from_stock ("Unmount ISO");
    g_signal_connect (G_OBJECT (pokeme), "clicked", G_CALLBACK (unmount), (gpointer) window);
    gtk_box_pack_start (GTK_BOX (vertbox), pokeme, TRUE, TRUE, 0);

// Mount Button
    pokeme = gtk_button_new_from_stock ("Mount ISO");
    g_signal_connect (G_OBJECT (pokeme), "clicked", G_CALLBACK (mount), (gpointer) window);
    gtk_box_pack_start (GTK_BOX (vertbox), pokeme, TRUE, TRUE, 0);

// Shove it all together and make it go weeeeeeeeeee
    gtk_container_add (GTK_CONTAINER (window), vertbox);

    gtk_widget_show_all(window);

    gtk_main ();

    return 0;
}
