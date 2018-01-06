/*************************************************************************
  Copyright 2017 Antoine FLORENTIN

  This file is part of Snell-Descartes.

  Snell-Descartes is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Snell-Descartes is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Snell-Descartes.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "gtk_repere.h"

GtkWidget* create_window (void)
{

	Widgets *widget = &widgets;

	widget->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable(GTK_WINDOW(widget->window), FALSE);
	gtk_window_set_title (GTK_WINDOW (widget->window), "Loi de Snell-Descartes");
	gtk_widget_set_size_request (widget->window, 600, 700);

	widget->vbox2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (widget->vbox2);
	gtk_container_add (GTK_CONTAINER (widget->window), widget->vbox2);

	widget->hbox4 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox4);
	gtk_box_pack_start (GTK_BOX (widget->vbox2), widget->hbox4, FALSE, TRUE, 0);

	widget->aspectframe1 = gtk_aspect_frame_new (NULL, 0.5, 0.5, 1, TRUE);
	gtk_widget_show (widget->aspectframe1);
	gtk_box_pack_start (GTK_BOX (widget->hbox4), widget->aspectframe1, TRUE, TRUE, 0);
	gtk_frame_set_shadow_type (GTK_FRAME (widget->aspectframe1), GTK_SHADOW_NONE);

	widget->hbox5 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox5);
	gtk_container_add (GTK_CONTAINER (widget->aspectframe1), widget->hbox5);
	gtk_widget_set_halign (widget->hbox5, GTK_ALIGN_CENTER);

	widget->barre_incident = gtk_scale_new_with_range( GTK_ORIENTATION_HORIZONTAL, 0, 90, 10);
	gtk_range_set_value( GTK_RANGE(widget->barre_incident), 45 );
	gtk_scale_set_draw_value(GTK_SCALE(widget->barre_incident) , FALSE);
	gtk_scale_set_digits(GTK_SCALE(widget->barre_incident), 0);
	gtk_box_pack_start (GTK_BOX (widget->hbox5), widget->barre_incident, TRUE, TRUE, 0);
	gtk_widget_set_size_request (widget->barre_incident, 200, -1);
	gtk_widget_show (widget->barre_incident);

	widget->entree_incident = gtk_entry_new ();
	gtk_box_pack_start (GTK_BOX (widget->hbox5), widget->entree_incident, TRUE, TRUE, 0);
	gtk_entry_set_max_length (GTK_ENTRY (widget->entree_incident), 2);
	gtk_entry_set_text (GTK_ENTRY (widget->entree_incident), "45");
	gtk_entry_set_width_chars (GTK_ENTRY (widget->entree_incident), 2);
	gtk_widget_show (widget->entree_incident);

	widget->label4 = gtk_label_new (" °");
	gtk_widget_show (widget->label4);
	gtk_box_pack_start (GTK_BOX (widget->hbox5), widget->label4, FALSE, FALSE, 0);

	widget->label2 = gtk_label_new ("<b>Angle d'incidence</b>");
	widget->label_text = g_strdup_printf("<span weight=\"bold\" foreground=\"#FF0000\">%s</span>", gtk_label_get_text(GTK_LABEL(widget->label2)));
	gtk_label_set_markup (GTK_LABEL(widget->label2), widget->label_text);
	g_free (widget->label_text);
	gtk_widget_show (widget->label2);
	gtk_frame_set_label_widget (GTK_FRAME (widget->aspectframe1), widget->label2);
	gtk_label_set_use_markup (GTK_LABEL (widget->label2), TRUE);

	widget->aspectframe2 = gtk_aspect_frame_new (NULL, 0.5, 0.5, 1, TRUE);
	gtk_widget_show (widget->aspectframe2);
	gtk_box_pack_start (GTK_BOX (widget->hbox4), widget->aspectframe2, TRUE, TRUE, 0);
	gtk_frame_set_shadow_type (GTK_FRAME (widget->aspectframe2), GTK_SHADOW_NONE);


	widget->vbox4 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (widget->vbox4);
	gtk_container_add (GTK_CONTAINER (widget->aspectframe2), widget->vbox4);

	widget->hbox6 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox6);
	gtk_box_pack_start (GTK_BOX (widget->vbox4), widget->hbox6, TRUE, TRUE, 0);

	widget->hbox13 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox13);
	gtk_box_pack_start (GTK_BOX (widget->vbox4), widget->hbox13, TRUE, TRUE, 0);

	widget->barre_V1 = gtk_scale_new_with_range( GTK_ORIENTATION_HORIZONTAL, VITESSE_MIN, VITESSE_MAX, 1000);
	gtk_range_set_value( GTK_RANGE(widget->barre_V1), VITESSE_MAX );
	gtk_scale_set_draw_value(GTK_SCALE(widget->barre_V1) , FALSE);
	gtk_scale_set_digits(GTK_SCALE(widget->barre_V1), 0);

	gtk_widget_show (widget->barre_V1);
	gtk_box_pack_start (GTK_BOX (widget->hbox6), widget->barre_V1, TRUE, FALSE, 0);
	gtk_widget_set_size_request (widget->barre_V1, 200, -1);

	widget->entree_V1 = gtk_entry_new ();
	gtk_widget_show (widget->entree_V1);
	gtk_box_pack_start (GTK_BOX (widget->hbox6), widget->entree_V1, TRUE, FALSE, 0);
	gtk_entry_set_max_length (GTK_ENTRY (widget->entree_V1), 9);
	gtk_entry_set_text (GTK_ENTRY (widget->entree_V1), "300000000");
	gtk_entry_set_width_chars (GTK_ENTRY (widget->entree_V1), 9);

	widget->label5 = gtk_label_new (" m/s");
	gtk_widget_show (widget->label5);
	gtk_box_pack_start (GTK_BOX (widget->hbox6), widget->label5, FALSE, FALSE, 0);

	widget->label3 = gtk_label_new ("<b>Vitesse Milieu 1</b>");
	gtk_widget_show (widget->label3);
	gtk_frame_set_label_widget (GTK_FRAME (widget->aspectframe2), widget->label3);
	gtk_label_set_use_markup (GTK_LABEL (widget->label3), TRUE);



	widget->label15 = gtk_label_new ("<b>\tAngle de réflexion</b>");
	gtk_widget_show (widget->label15);
	gtk_box_pack_start (GTK_BOX (widget->hbox13), widget->label15, FALSE, FALSE, 2);
	gtk_label_set_use_markup (GTK_LABEL (widget->label15), TRUE);

	widget->sortie_reflechi = gtk_entry_new ();
	gtk_widget_show (widget->sortie_reflechi);
	gtk_box_pack_start (GTK_BOX (widget->hbox13), widget->sortie_reflechi, FALSE, TRUE, 0);
	gtk_entry_set_max_length (GTK_ENTRY (widget->sortie_reflechi), 2);
	gtk_editable_set_editable (GTK_EDITABLE (widget->sortie_reflechi), FALSE);
	gtk_entry_set_text (GTK_ENTRY (widget->sortie_reflechi), "45");
	gtk_entry_set_width_chars (GTK_ENTRY (widget->sortie_reflechi), 2);

	widget->label16 = gtk_label_new ("°");
	gtk_widget_show (widget->label16);
	gtk_box_pack_start (GTK_BOX (widget->hbox13), widget->label16, FALSE, FALSE, 2);
	gtk_label_set_justify (GTK_LABEL (widget->label16), GTK_JUSTIFY_CENTER);



	widget->repere = gtk_repere_new();
	gtk_box_pack_start (GTK_BOX (widget->vbox2), widget->repere , TRUE, TRUE, 0);
	gtk_widget_show( widget->repere );



	widget->aspectframe3 = gtk_aspect_frame_new (NULL, 0.5, 0.5, 1, TRUE);
	gtk_widget_show (widget->aspectframe3);
	gtk_box_pack_start (GTK_BOX (widget->vbox2), widget->aspectframe3, FALSE, TRUE, 5);
	gtk_frame_set_shadow_type (GTK_FRAME (widget->aspectframe3), GTK_SHADOW_NONE);

	widget->vbox3 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_show (widget->vbox3);
	gtk_container_add (GTK_CONTAINER (widget->aspectframe3), widget->vbox3);
	gtk_container_set_border_width (GTK_CONTAINER (widget->vbox3), 4);

	widget->hbox7 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox7);
	gtk_box_pack_start (GTK_BOX (widget->vbox3), widget->hbox7, FALSE, TRUE, 0);

	widget->hbox11 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox11);
	gtk_box_pack_start (GTK_BOX (widget->hbox7), widget->hbox11, TRUE, TRUE, 0);

	widget->barre_V2 = gtk_scale_new_with_range( GTK_ORIENTATION_HORIZONTAL, VITESSE_MIN, VITESSE_MAX, 1000);
	gtk_range_set_value( GTK_RANGE(widget->barre_V2), VITESSE_MAX );
	gtk_scale_set_draw_value(GTK_SCALE(widget->barre_V2) , FALSE);
	gtk_scale_set_digits(GTK_SCALE(widget->barre_V2), 0);

	gtk_widget_show (widget->barre_V2);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->barre_V2, TRUE, TRUE, 5);
	gtk_widget_set_size_request (widget->barre_V2, 150, -1);

	widget->entree_V2 = gtk_entry_new ();
	gtk_widget_show (widget->entree_V2);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->entree_V2, TRUE, TRUE, 0);
	gtk_entry_set_max_length (GTK_ENTRY (widget->entree_V2), 9);
	gtk_entry_set_text (GTK_ENTRY (widget->entree_V2), "300000000");
	gtk_entry_set_width_chars (GTK_ENTRY (widget->entree_V2), 9);

	widget->label14 = gtk_label_new ("m/s");
	gtk_widget_show (widget->label14);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->label14, FALSE, FALSE, 2);
	gtk_label_set_justify (GTK_LABEL (widget->label14), GTK_JUSTIFY_CENTER);

	widget->label15 = gtk_label_new ("<b>\tAngle de réfraction</b>");
	gtk_widget_show (widget->label15);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->label15, FALSE, FALSE, 2);
	gtk_label_set_use_markup (GTK_LABEL (widget->label15), TRUE);

	widget->sortie_refracte = gtk_entry_new ();
	gtk_widget_show (widget->sortie_refracte);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->sortie_refracte, TRUE, TRUE, 0);
	gtk_entry_set_max_length (GTK_ENTRY (widget->sortie_refracte), 5);
	gtk_editable_set_editable (GTK_EDITABLE (widget->sortie_refracte), FALSE);
	gtk_entry_set_text (GTK_ENTRY (widget->sortie_refracte), "45,00");
	gtk_entry_set_width_chars (GTK_ENTRY (widget->sortie_refracte), 5);

	widget->label16 = gtk_label_new ("°");
	gtk_widget_show (widget->label16);
	gtk_box_pack_start (GTK_BOX (widget->hbox11), widget->label16, FALSE, FALSE, 2);
	gtk_label_set_justify (GTK_LABEL (widget->label16), GTK_JUSTIFY_CENTER);

	widget->label13 = gtk_label_new ("   <b>Vitesse Milieu 2</b>");
	widget->label_text = g_strdup_printf("<span weight=\"bold\" foreground=\"#00b500\">%s</span>", gtk_label_get_text(GTK_LABEL(widget->label13)));
	gtk_label_set_markup (GTK_LABEL(widget->label13), widget->label_text);
	g_free (widget->label_text);
	gtk_widget_show (widget->label13);
	gtk_frame_set_label_widget (GTK_FRAME (widget->aspectframe3), widget->label13);
	gtk_label_set_use_markup (GTK_LABEL (widget->label13), TRUE);

	widget->hbox12 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_show (widget->hbox12);
	gtk_box_pack_start (GTK_BOX (widget->vbox2), widget->hbox12, FALSE, TRUE, 0);

	widget->check_arcs = gtk_check_button_new_with_label ("Arcs");
	gtk_widget_show (widget->check_arcs);
	gtk_box_pack_start(GTK_BOX(widget->hbox12), widget->check_arcs, FALSE, FALSE, 100);

	widget->check_reflechi = gtk_check_button_new_with_label ("Réfléchi");
	gtk_widget_show (widget->check_reflechi);
	gtk_box_pack_start(GTK_BOX(widget->hbox12), widget->check_reflechi, FALSE, FALSE, 0);

	widget->check_refracte = gtk_check_button_new_with_label ("Réfracté");
	gtk_widget_show (widget->check_refracte);
	gtk_button_clicked(GTK_BUTTON(widget->check_refracte));
	gtk_box_pack_start(GTK_BOX(widget->hbox12), widget->check_refracte, FALSE, FALSE, 100);


	g_signal_connect ((gpointer) widget->check_arcs, "clicked", G_CALLBACK (check_arcs_clicked), widget);
	g_signal_connect ((gpointer) widget->check_reflechi, "clicked", G_CALLBACK (check_reflechi_clicked), widget);
	g_signal_connect ((gpointer) widget->check_refracte, "clicked", G_CALLBACK (check_refracte_clicked), widget);

	g_signal_connect ((gpointer) widget->barre_incident, "change-value", G_CALLBACK (barre_incident_change_value), widget);
	g_signal_connect ((gpointer) widget->entree_incident, "activate", G_CALLBACK (entree_incident_changed), widget);

	g_signal_connect ((gpointer) widget->barre_V1, "change_value", G_CALLBACK (barre_V1_change_value), widget);
	g_signal_connect ((gpointer) widget->entree_V1, "activate", G_CALLBACK (entree_V1_changed), widget);

	g_signal_connect ((gpointer) widget->barre_V2, "change_value", G_CALLBACK (barre_V2_change_value), widget);
	g_signal_connect ((gpointer) widget->entree_V2, "activate", G_CALLBACK (entree_V2_changed), widget);

	g_signal_connect ((gpointer) widget->repere, "configure-event", G_CALLBACK (configure_event_cb), widget);


	return widget->window;
}

