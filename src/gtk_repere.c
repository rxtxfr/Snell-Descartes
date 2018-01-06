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

#include <math.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "gtk_repere.h"

static double x, y;
static double radius;
static cairo_surface_t *surface;

struct _ReperePrivate {

};

G_DEFINE_TYPE (GtkRepere, gtk_repere, GTK_TYPE_DRAWING_AREA);

/**************************************
Constructeur du repere
****************************************/
GtkWidget *gtk_repere_new(void){
	return g_object_new (GTK_TYPE_REPERE, NULL);
}

/**************************************
Fonction de mise à jour du repere
****************************************/
gboolean gtk_repere_update(gpointer data){

    GtkRepere* repere=(GtkRepere*)data;
	gtk_widget_queue_draw(GTK_WIDGET(repere));

	return TRUE;
}

/**************************************
Fonction d'initialisation de la classe du repere
****************************************/
static void gtk_repere_class_init (GtkRepereClass *class){

	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (class);


	widget_class->configure_event = configure_event_cb;
	widget_class->draw = gtk_draw_repere;

}

/**************************************
Fonction d'initialisation du repere
****************************************/
static void gtk_repere_init (GtkRepere *repere)
{

	repere->incident = 45.0;
	repere->reflected = 45.0;
	repere->refracted = 45.0;

	repere->speed1 = 300000000;
	repere->speed2 = 300000000;

	repere->arcs = FALSE;
	repere->reflechi = FALSE;
	repere->refracte = TRUE;
}

/**************************************
Fonction dessinant le texte du repere
****************************************/
gboolean draw_text (cairo_t *cr, int x, int y, char *_text){
    cairo_text_extents_t extents;
    cairo_font_options_t *font_options;

    cairo_save(cr);

    cairo_select_font_face (cr, "Arial Bold",
			    CAIRO_FONT_SLANT_NORMAL,
			    CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 12);

    font_options = cairo_font_options_create ();

    cairo_font_options_set_hint_style (font_options, CAIRO_HINT_STYLE_FULL);
    cairo_font_options_set_antialias (font_options, CAIRO_ANTIALIAS_GRAY);
    cairo_font_options_set_hint_metrics(font_options, CAIRO_HINT_METRICS_ON);

    cairo_set_font_options (cr, font_options);
    cairo_font_options_destroy (font_options);

    cairo_set_source_rgb (cr, 0, 0, 0.67);
    cairo_text_extents (cr, _text, &extents);
    cairo_move_to (cr, x - extents.width/2, y + extents.height+6);
    cairo_show_text (cr, _text);

    cairo_restore (cr);

    return FALSE;
}

/**************************************
Fonction dessinant le repere
****************************************/
void gtk_draw_repere (GtkWidget *repere, cairo_t *cr){

	x = gtk_widget_get_allocated_width (repere) / 2;
	y = gtk_widget_get_allocated_height (repere) / 2;
	radius = MIN (gtk_widget_get_allocated_width (repere) / 2, gtk_widget_get_allocated_height (repere) / 2) - 10;


    gtk_draw_incident(repere, cr);

    if( getRefracte( GTK_REPERE( repere) ) )
            gtk_draw_refracte(repere, cr);


	if( getReflechi( GTK_REPERE( repere) ) )
		gtk_draw_reflechi(repere, cr);


    cairo_set_source_rgb(cr, 0, 0, 0);

	cairo_save(cr);
	cairo_move_to(cr, 5, y);
	cairo_line_to(cr, gtk_widget_get_allocated_width (repere) - 5, y );

	cairo_move_to(cr, x , 5);
	cairo_line_to(cr, x, gtk_widget_get_allocated_height (repere) - 5);

	cairo_restore(cr);
	cairo_stroke(cr);

	draw_text(cr, 30, y - 20, "Milieu 1");
	draw_text(cr, 30, y - 3, "Milieu 2");
	cairo_stroke(cr);

    gtk_repere_update(repere);
}



gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data){
    if (surface) cairo_surface_destroy (surface);

    surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
                                       CAIRO_CONTENT_COLOR,
                                       gtk_widget_get_allocated_width (widget),
                                       gtk_widget_get_allocated_height (widget));

    clear_surface ();

    return TRUE;
}

void clear_surface (void){
    cairo_t *cr;

    cr = cairo_create (surface);

    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    cairo_destroy (cr);
}

/**************************************
 Rayon incident
****************************************/
void gtk_draw_incident(GtkWidget *rep, cairo_t *local_cr){

	gdouble angleIncident = getIncident( GTK_REPERE( rep ) );

	angleIncident = TO_RAD( angleIncident );
	angleIncident += M_PI_2;

	cairo_set_source_rgb(local_cr, 1, 0, 0);

	// Dessin du rayon
	cairo_move_to (local_cr, x, y);
	cairo_line_to(local_cr,
				   x + (radius) * cos ( (angleIncident) ),
				   y + (radius) * -1*sin ( (angleIncident) ));

	// Dessin de la fleche
	cairo_move_to (local_cr,
				   (x + (radius/2) * cos ( (angleIncident))),
				   (y + (radius/2) * -1*sin ((angleIncident))));
	cairo_line_to(local_cr,
				  (x + (radius/2) * cos ( angleIncident )) + 15 * cos( angleIncident - TO_RAD(30) ),
				   ((y + (radius/2) * -1*sin ( angleIncident ))) + 15 * -1 * sin( angleIncident - TO_RAD(30) ));

	cairo_move_to (local_cr,
				   (x + (radius/2) * cos ( angleIncident )),
				   (y + (radius/2) * -1*sin ( angleIncident )));
	cairo_line_to(local_cr,
				  (x + (radius/2) * cos ( angleIncident )) + 15 * cos( angleIncident + TO_RAD(30) ),
				   ((y + (radius/2) * -1*sin ( angleIncident ))) + 15 * -1 * sin( angleIncident + TO_RAD(30)  ));

	if( getArcs( GTK_REPERE( rep ) ) ){

		cairo_move_to (local_cr, x, y);
		cairo_arc (local_cr, x, y, radius/3, -angleIncident, -M_PI_2 );
	}

	cairo_stroke(local_cr);
	gtk_repere_update(rep);
}


/**************************************
 Rayon reflechi
****************************************/
void gtk_draw_reflechi(GtkWidget *rep, cairo_t *local_cr){

	gdouble angleReflechi = getReflected( GTK_REPERE( rep ) );

	angleReflechi = TO_RAD( angleReflechi );
	angleReflechi = M_PI_2 - angleReflechi;

    cairo_set_source_rgb(local_cr, 0, 0, 0.7);

	// Dessin du rayon
    cairo_move_to (local_cr, x, y);
    cairo_line_to(local_cr,
                   x + (radius) * cos( angleReflechi ),
		           y + (radius) * -1*sin( angleReflechi ));

    // Dessin de la fleche
    cairo_move_to (local_cr,
                   (x + (radius * 3/4) * cos ( angleReflechi )),
		           (y + (radius * 3/4) * -1*sin ( angleReflechi )));
    cairo_line_to(local_cr,
                  (x + (radius * 3/4) * cos ( angleReflechi ) - 15 * cos( TO_RAD(30) + angleReflechi) ),
		          (y + (radius * 3/4) * -1*sin ( angleReflechi ) - 15 * -1 * sin( TO_RAD(30) + angleReflechi)  ) );

    cairo_move_to (local_cr,
                   (x + (radius * 3/4) * cos ( angleReflechi )),
		           (y + (radius * 3/4) * -1*sin ( angleReflechi )));
    cairo_line_to(local_cr,
                  (x + (radius * 3/4) * cos ( angleReflechi )) - 15 * cos((TO_RAD(330) + angleReflechi)),
		           ((y + (radius * 3/4) * -1*sin ( angleReflechi ))) - 15 * -1 * sin( TO_RAD(330) + angleReflechi ));

    if( getArcs( GTK_REPERE( rep ) ) ){

        cairo_move_to (local_cr, x, y);
        cairo_arc (local_cr, x, y, radius*5/8, -M_PI_2, -angleReflechi);
    }

    cairo_stroke(local_cr);
    gtk_repere_update(rep);
}

/**************************************
 Rayon refracte
****************************************/
void gtk_draw_refracte(GtkWidget *rep, cairo_t *local_cr){

	gdouble angleRefracted = getRefracted( GTK_REPERE( rep ) );

	angleRefracted = TO_RAD( angleRefracted );
	angleRefracted = angleRefracted - M_PI_2;

	cairo_set_source_rgb(local_cr, 0, 0.7, 0);

	// Dessin du rayon
	cairo_move_to (local_cr, x, y);
	cairo_line_to(local_cr,
			   x + (radius) * cos(( angleRefracted)),
			   y + (radius) * -1 * sin(( angleRefracted)));

	// Dessin de la fleche
	cairo_move_to (local_cr,
			   (x + (radius) * cos ( angleRefracted )),
			   (y + (radius) * -1*sin ( angleRefracted )));
	cairo_line_to(local_cr,
			  (x + (radius) * cos ( angleRefracted )) - 15 * cos( angleRefracted + TO_RAD(30) ),
			   ((y + (radius) * -1*sin ( angleRefracted ))) - 15 * -1 * sin( angleRefracted + TO_RAD(30) ));

	cairo_move_to (local_cr,
			   (x + (radius) * cos ( angleRefracted )),
			   (y + (radius) * -1*sin ( angleRefracted )));
	cairo_line_to(local_cr,
			  (x + (radius) * cos ( angleRefracted )) - 15 * cos( angleRefracted - TO_RAD(30) ),
			   ((y + (radius) * -1*sin ( angleRefracted ))) - 15 * -1 * sin( angleRefracted - TO_RAD(30) ));

	if( getArcs( GTK_REPERE( rep ) ) ){
		cairo_move_to (local_cr, x, y);
		cairo_arc (local_cr, x, y, radius*5/8, -angleRefracted, -3*M_PI_2 );
	}

	cairo_stroke(local_cr);
		gtk_repere_update(rep);
}

gdouble computeReflected( GtkRepere *rep ){

	gdouble angleIncident = getIncident( GTK_REPERE( rep ) );

	setReflected( GTK_REPERE( rep ), angleIncident);
    
    return angleIncident;
}

gdouble computeRefracted( GtkRepere *rep ){


	gdouble v1 = getSpeed1( GTK_REPERE( rep ) );
	gdouble v2 = getSpeed2( GTK_REPERE( rep ) );

	gdouble angleIncident = getIncident( GTK_REPERE( rep ) );
	gdouble angleRefracted;

	if( ( (v2/v1)* sin(angleIncident * (M_PI/180)) ) < -1 || ( (v2/v1)* sin(angleIncident * (M_PI/180)) ) > 1 )
		angleRefracted = 90;

	else angleRefracted = (180/M_PI)*asin( (v2/v1) * sin(angleIncident * (M_PI/180)) );

	setRefracted( GTK_REPERE( rep ), angleRefracted);

	return angleRefracted;

}

void setIncident( GtkRepere *widget, gdouble angle){

	widget->incident = angle;
}

const gdouble getIncident( GtkRepere *widget ){

	return widget->incident;
}

void setReflected( GtkRepere *widget, gdouble angle){

	widget->reflected = angle;
}

const gdouble getReflected( GtkRepere *widget ){

	return widget->reflected;
}

void setRefracted( GtkRepere *widget, gdouble angle){

	widget->refracted = angle;
}

const gdouble getRefracted( GtkRepere *widget ){

	return widget->refracted;
}

void setSpeed1( GtkRepere *widget, gdouble speed){

	widget->speed1 = speed;
}

const gdouble getSpeed1( GtkRepere *widget ){

	return widget->speed1;
}

void setSpeed2( GtkRepere *widget, gdouble speed){

	widget->speed2 = speed;
}

const gdouble getSpeed2( GtkRepere *widget ){

	return widget->speed2;
}

void setArcs( GtkRepere *widget, gboolean value ){

	widget->arcs = value;
}

gboolean getArcs( GtkRepere *widget ){

	return widget->arcs;
}

void setReflechi( GtkRepere *widget, gboolean value ){

	widget->reflechi = value;
}

const gboolean getReflechi( GtkRepere *widget ){

	return widget->reflechi;
}

void setRefracte( GtkRepere *widget, gboolean value ){

	widget->refracte = value;
}

const gboolean getRefracte( GtkRepere *widget ){

	return widget->refracte;
}

