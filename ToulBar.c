#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct
{
  GtkWidget *toolbar;
  int style;
  int space;
  int icon_size;

} ToolBar;

ToolBar *initialiser_toolbar(int icon_size, int space, int style)
{
  ToolBar *T = (ToolBar *)malloc(sizeof(ToolBar));
  if (!T)
  {
    printf("\n erreur d'allocation[Toolbar]");
    exit(0);
  }
  T->icon_size = icon_size;
  T->space = space;
  T->style = style;

  return (ToolBar *)T;
}

void add_toolbar_button(GtkToolbar *toolbar,
                        const char *stock_id,
                        const char *tooltip_text)
{
  GtkToolItem *button = gtk_tool_button_new_from_stock(stock_id);
  gtk_tool_item_set_tooltip_text(GTK_TOOL_ITEM(button), tooltip_text);
  gtk_toolbar_insert(toolbar, button, -1);
}

void Creer_Toolbar(ToolBar *T)
{

  T->toolbar = gtk_toolbar_new();

  switch (T->style)
  {
  case 0:
    gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), GTK_TOOLBAR_TEXT);
    break;
  case 1:
    gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), GTK_TOOLBAR_ICONS);
    break;
  case 2:
    gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), GTK_TOOLBAR_BOTH);
    break;
  case 3:
    gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), GTK_TOOLBAR_BOTH_HORIZ);
    break;
  }

  gtk_container_set_border_width(GTK_CONTAINER(T->toolbar), T->space);

  switch (T->style)
  {
  case 0:
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(T->toolbar), GTK_ICON_SIZE_SMALL_TOOLBAR);
    break;
  case 1:
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(T->toolbar), GTK_ICON_SIZE_LARGE_TOOLBAR);
    break;
  case 2:
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(T->toolbar), GTK_ICON_SIZE_BUTTON);
    break;
  case 3:
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(T->toolbar), GTK_ICON_SIZE_DIALOG);
    break;
  }

  add_toolbar_button(GTK_TOOLBAR(T->toolbar), GTK_STOCK_NEW, "New File");
  add_toolbar_button(GTK_TOOLBAR(T->toolbar), GTK_STOCK_OPEN, "Open File");
  add_toolbar_button(GTK_TOOLBAR(T->toolbar), GTK_STOCK_SAVE, "Save File");
  gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar), gtk_separator_tool_item_new(), -1);
  add_toolbar_button(GTK_TOOLBAR(T->toolbar), GTK_STOCK_QUIT, "Quit");
}

int main(int argc, char *argv[])
{

  gtk_init(&argc, &argv);

  GtkWidget *window;
  ToolBar *toolbar;
  GtkWidget *BOX;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Exemple");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  toolbar = initialiser_toolbar(1, 4, 1);
  Creer_Toolbar(toolbar);

  BOX = gtk_box_new(GTK_ORIENTATION_VERTICAL, TRUE);
  gtk_container_add(GTK_CONTAINER(BOX), toolbar->toolbar);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_container_add(GTK_CONTAINER(window), BOX);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
