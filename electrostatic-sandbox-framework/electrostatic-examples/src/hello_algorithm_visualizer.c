#include <gtk/gtk.h>

#define INITIAL_GRID_SIZE 8

typedef struct {
    GtkWidget *grid;
    int grid_size;
} AppData;

void create_grid(AppData *app_data) {
    // Remove all existing children from the grid
    GList *children = gtk_container_get_children(GTK_CONTAINER(app_data->grid));
    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    // Create new buttons and attach them to the grid
    for (int i = 0; i < app_data->grid_size; ++i) {
        for (int j = 0; j < app_data->grid_size; ++j) {
            GtkWidget *button = gtk_button_new_with_label(g_strdup_printf("%d,%d", i, j));
            gtk_widget_set_size_request(button, 50, 50);  // Set button size

            // Apply a CSS class to the button
            gtk_widget_set_name(button, "grid-button");

            gtk_grid_attach(GTK_GRID(app_data->grid), button, i, j, 1, 1);
        }
    }
    gtk_widget_show_all(app_data->grid);
}

void apply_css(GtkWidget *widget, const char *css) {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
}

void on_size_button_clicked(GtkButton *button, AppData *app_data) {
    GtkWidget *size_entry = g_object_get_data(G_OBJECT(button), "size_entry");
    const char *size_text = gtk_entry_get_text(GTK_ENTRY(size_entry));
    int new_size = atoi(size_text);
    if (new_size > 0) {
        app_data->grid_size = new_size;
        create_grid(app_data);
    }
}

void on_combo_box_changed(GtkComboBoxText *combo_box, AppData *app_data) {
    const char *active_text = gtk_combo_box_text_get_active_text(combo_box);
    if (g_strcmp0(active_text, "Algorithm 1") == 0) {
        // Placeholder for Algorithm 1
    } else if (g_strcmp0(active_text, "Algorithm 2") == 0) {
        // Placeholder for Algorithm 2
    } else if (g_strcmp0(active_text, "Algorithm 3") == 0) {
        // Placeholder for Algorithm 3
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    AppData app_data = {0};
    app_data.grid_size = INITIAL_GRID_SIZE;
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Algorithm Visualizer");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    
    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_pack_start(GTK_BOX(main_box), input_box, FALSE, FALSE, 0);
    
    GtkWidget *size_label = gtk_label_new("Grid Size:");
    gtk_box_pack_start(GTK_BOX(input_box), size_label, FALSE, FALSE, 0);
    
    GtkWidget *size_entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(size_entry), g_strdup_printf("%d", INITIAL_GRID_SIZE));
    gtk_box_pack_start(GTK_BOX(input_box), size_entry, FALSE, FALSE, 0);
    
    GtkWidget *size_button = gtk_button_new_with_label("Set Size");
    g_object_set_data(G_OBJECT(size_button), "size_entry", size_entry);
    g_signal_connect(size_button, "clicked", G_CALLBACK(on_size_button_clicked), &app_data);
    gtk_box_pack_start(GTK_BOX(input_box), size_button, FALSE, FALSE, 0);
    
    GtkWidget *combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Select Algorithm");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Algorithm 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Algorithm 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Algorithm 3");
    g_signal_connect(combo_box, "changed", G_CALLBACK(on_combo_box_changed), &app_data);
    gtk_box_pack_start(GTK_BOX(input_box), combo_box, FALSE, FALSE, 0);
    
    app_data.grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(main_box), app_data.grid, TRUE, TRUE, 0);
    
    create_grid(&app_data);

    // Apply CSS to the window
    const char *css = "#grid-button { background-color: #00008B; color: white; }";
    apply_css(window, css);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
