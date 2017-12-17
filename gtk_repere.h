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

#ifndef __GTK_Repere_H__
#define __GTK_Repere_H__

#include <math.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GTK_TYPE_REPERE		(gtk_repere_get_type ())
#define GTK_REPERE(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_REPERE, GtkRepere))
#define GTK_REPERE_CLASS(obj)	(G_TYPE_CHECK_CLASS_CAST ((obj), GTK_REPERE, GtkRepereClass))
#define GTK_IS_REPERE(obj)	(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_REPERE))
#define GTK_IS_REPERE_CLASS(obj)	(G_TYPE_CHECK_CLASS_TYPE ((obj), GTK_TYPE_REPERE))
#define GTK_REPERE_GET_CLASS	(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_REPERE, GtkRepereClass))

#define TO_RAD( deg ) deg*M_PI/180
#define TO_DEG( rad ) rad*180/M_PI


typedef struct _GtkRepere	GtkRepere;
typedef struct _GtkRepereClass	GtkRepereClass;
typedef struct _ReperePrivate ReperePrivate;

struct _GtkRepere
{
	GtkDrawingArea parent;

	gdouble incident;
	gdouble reflected;
	gdouble refracted;

	gdouble speed1;
	gdouble speed2;

	gboolean arcs;
	gboolean reflechi;
	gboolean refracte;
};

struct _GtkRepereClass
{
	GtkDrawingAreaClass parent_class;

};


GtkWidget *gtk_repere_new(void);
GType gtk_repere_get_type (void);


/*******************************************************************************
Prototypes des fonctions
*******************************************************************************/
void gtk_draw_repere (GtkWidget *repere, cairo_t *cr);
gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean draw_text (cairo_t *cr, int x, int y, char *_text);
gboolean gtk_repere_expose (GtkWidget *repere, GdkEventExpose *event);
gboolean gtk_repere_destroy (GtkWidget *repere, GdkEventExpose *event);

gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data);
void clear_surface (void);

void gtk_draw_incident(GtkWidget *rep, cairo_t *local_cr);
void gtk_draw_reflechi(GtkWidget *rep, cairo_t *local_cr);
void gtk_draw_refracte(GtkWidget *rep, cairo_t *local_cr);

double computeRefracted( GtkWidget *rep );

void setIncident( GtkRepere *widget, gdouble angle);
const gdouble getIncident( GtkRepere *widget );

void setReflected( GtkRepere *widget, gdouble angle);
const gdouble getReflected( GtkRepere *widget );

void setRefracted( GtkRepere *widget, gdouble angle);
const gdouble getRefracted( GtkRepere *widget );

void setSpeed1( GtkRepere *widget, gdouble speed);
const gdouble getSpeed1( GtkRepere *widget );

void setSpeed2( GtkRepere *widget, gdouble speed);
const gdouble getSpeed2( GtkRepere *widget );

void setArcs( GtkRepere *widget, gboolean value );
gboolean getArcs( GtkRepere *widget );

void setReflechi( GtkRepere *widget, gboolean value );
const gboolean getReflechi( GtkRepere *widget );

void setRefracte( GtkRepere *widget, gboolean value );
const gboolean getRefracte( GtkRepere *widget );

G_END_DECLS
#endif /* __GTK_Repere_H__ */
