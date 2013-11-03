// Mounter2 v1.3.6
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

// Random Variables
    char        textlab[64];
    char        aboutlab[100];
    int         textlength = 35;
    char*       folderpathx;
    char        folderpath[100];
    char*       isox;
    char        iso[60];
    char        command[200];


// Widgets
    GtkWidget *window;
    GtkWidget *vertbox;
    GtkWidget *textstuff;
    GtkWidget *pokeme;
    GtkWidget *textenter1;
    GtkWidget *textenter;
    GtkWidget *toolbar;
    GtkWidget *menu;
    GtkWidget *filemenu;
    GtkWidget *filesubmenu;
    GtkWidget *aboutmenu;
    GtkWidget *aboutsubmenu;
    GtkWidget *closeswitch;
    GtkWidget *aboutswitch;

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
  system("gksu umount /mnt/");
  GtkWidget *dialog = NULL;
  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Unmounted");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

//Mount
static void mount ( GtkWidget *wid, GtkWidget *win)
{
  int checkfail;
  folderpathx =  gtk_entry_get_text(GTK_ENTRY(textenter1));
  isox =  gtk_entry_get_text(GTK_ENTRY(textenter));
  strcpy(command, "exec gksu mount  ");
  strcat(command, folderpathx);
  strcat(command, isox);
  strcat(command, " /mnt/");
  checkfail = system(command);
  if (checkfail == 0)
  {
     GtkWidget *dialog = NULL;
     dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Check your folder...\nSeems mounted");
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

// About Menu Item
static void aboutit (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;
  sprintf(aboutlab,"%s", "Mounter2\n\n""Version 1.3.6\n""Is an application designed to make\n""mounting iso files easy to do.");
  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, aboutlab);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

// Main Function
int main( int   argc, char *argv[] )
{


// Set some spiffy colors
    GdkColor colorBlack;
    GdkColor colorBlue;
    colorBlack.red=0;
    colorBlack.green=0;
    colorBlack.blue=0;
    colorBlue.red=0;
    colorBlue.green=65535;
    colorBlue.blue=65535;

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
    sprintf(textlab, "%s", "<big><b>Mounter2</b></big>\n\n""Please select the folder");
    textstuff = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL (textstuff), textlab);
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);
    sprintf(textlab, "<small>%s</small>", "containing your ISO files.");
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);
    textstuff = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL (textstuff), textlab);
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);

// Folder Path
    textenter1 = gtk_entry_new();
    gtk_widget_modify_text(textenter1, GTK_STATE_NORMAL, &colorBlue);
    gtk_widget_modify_base(textenter1, GTK_STATE_NORMAL, &colorBlack);
    GtkStyle *style = gtk_widget_get_style(textenter1);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(textenter1, style->font_desc);
    gtk_entry_set_width_chars(GTK_ENTRY(textenter1), textlength);
    gtk_editable_set_editable(GTK_EDITABLE(textenter1), TRUE);
    gtk_entry_set_text(GTK_ENTRY(textenter1), folderpath);
    gtk_box_pack_start (GTK_BOX (vertbox), textenter1, TRUE, TRUE, 0);

    sprintf(textlab, "<small>%s</small>", "Name of ISO file:");
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);
    textstuff = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL (textstuff), textlab);
    gtk_label_set_justify(GTK_LABEL (textstuff),GTK_JUSTIFY_LEFT);
    gtk_misc_set_alignment (GTK_MISC (textstuff), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (vertbox), textstuff, TRUE, TRUE, 0);

// ISO File
    textenter = gtk_entry_new();
    gtk_widget_modify_text(textenter, GTK_STATE_NORMAL, &colorBlue);
    gtk_widget_modify_base(textenter, GTK_STATE_NORMAL, &colorBlack);
    GtkStyle *style1 = gtk_widget_get_style(textenter);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(textenter, style->font_desc);
    gtk_entry_set_width_chars(GTK_ENTRY(textenter), textlength);
    gtk_editable_set_editable(GTK_EDITABLE(textenter), TRUE);
    gtk_entry_set_text(GTK_ENTRY(textenter), iso);
    gtk_box_pack_start (GTK_BOX (vertbox), textenter, TRUE, TRUE, 0);
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
