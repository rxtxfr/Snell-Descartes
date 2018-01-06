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

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#include "interface.h"
#include "callbacks.h"
#include "gtk_repere.h"


void check_arcs_clicked( GtkEditable *editable, gpointer user_data ){

	Widgets *widgets = (Widgets *)user_data;

    if( !getArcs( GTK_REPERE( widgets->repere) ) )
    	setArcs(GTK_REPERE( widgets->repere), TRUE);
    else setArcs(GTK_REPERE( widgets->repere), FALSE);
}

void check_reflechi_clicked( GtkEditable *editable, gpointer user_data ){

	Widgets *widgets = (Widgets *)user_data;

    if( !getReflechi( GTK_REPERE( widgets->repere) ) )
    	setReflechi(GTK_REPERE( widgets->repere), TRUE);
    else setReflechi(GTK_REPERE( widgets->repere), FALSE);
}

void check_refracte_clicked( GtkEditable *editable, gpointer user_data ){

	Widgets *widgets = (Widgets *)user_data;

    if( !getRefracte( GTK_REPERE( widgets->repere) ) )
    	setRefracte(GTK_REPERE( widgets->repere), TRUE);
    else setRefracte(GTK_REPERE( widgets->repere), FALSE);
}


gboolean barre_incident_change_value( GtkRange *range, GtkScrollType scroll, gdouble value, gpointer user_data ){

    char string[STR_SIZE];
    gdouble angle = 0;
    Widgets *widgets = (Widgets *)user_data;

    angle = gtk_range_get_value(range);

    sprintf(string, "%2.0lf", angle);

    gtk_entry_set_text(GTK_ENTRY(widgets->entree_incident), string);

    setIncident( GTK_REPERE( widgets->repere), angle );
    computeIncident( widgets, string );

    return FALSE;
}


void entree_incident_changed( GtkEditable *editable, gpointer user_data ){


	int i;
	gboolean extra = FALSE;
	const gchar *sIncident;

	Widgets *widgets = (Widgets *)user_data;

	sIncident =  gtk_entry_get_text(GTK_ENTRY(widgets->entree_incident));

	for(i=strlen(sIncident)-1; i>=0; i--){

		if( (sIncident[i] < 0x30 ) || (sIncident[i] > 0x39 )  ){

			extra = TRUE;
			break;
		}
		else
			extra = FALSE;

	}

	if( extra ){

		ErreurNumerique( widgets->window );

		gtk_entry_set_text(GTK_ENTRY(widgets->entree_incident), "45");
        gtk_range_set_value(GTK_RANGE(widgets->barre_incident), 45);
        
        setIncident( GTK_REPERE( widgets->repere ), 45);
        updateValues( widgets );

	}
	else{

		computeIncident( widgets, sIncident );
	}
}

void computeIncident( Widgets *widgets, const gchar *sIncident ){
 
    gdouble angleIncident = atof(sIncident);
    
    if( angleIncident >= 0 && angleIncident<= 90){

        gtk_range_set_value(GTK_RANGE(widgets->barre_incident), angleIncident);

        setIncident( GTK_REPERE( widgets->repere ), angleIncident );
        setReflected( GTK_REPERE( widgets->repere ), angleIncident );

        readValues( widgets );
        updateValues( widgets );

    }
    else{

        ErreurValeur( widgets->window );
        gtk_entry_set_text(GTK_ENTRY(widgets->entree_incident), "45");
        
        updateValues( widgets );
    }
}
gboolean barre_V1_change_value( GtkRange *range, GtkScrollType scroll, gdouble value, gpointer user_data ){

    gdouble v1;
    char string[STR_SIZE];
    Widgets *widgets = (Widgets *)user_data;

    v1 = gtk_range_get_value(range);

    sprintf(string, "%2.0f", v1);

    setSpeed1( GTK_REPERE( widgets->repere ), v1);
    gtk_entry_set_text(GTK_ENTRY(widgets->entree_V1), string);

    computeV1( widgets, string );

    return FALSE;
}


void entree_V1_changed( GtkEditable *editable, gpointer user_data ){

    int i;
    gboolean extra = FALSE;
    const gchar *sV1;

    Widgets *widgets = (Widgets *)user_data;

    sV1 =  gtk_entry_get_text(GTK_ENTRY(widgets->entree_V1));

    for(i=strlen(sV1)-1; i>=0; i--){

        if( (sV1[i] < 0x30 ) || (sV1[i] > 0x39 )  ){

            extra = TRUE;
            break;
        }
        else
            extra = FALSE;
    }

    if( extra ){

        ErreurNumerique( widgets->window );

        gtk_entry_set_text(GTK_ENTRY(widgets->entree_V1), "300000000");
        
        setSpeed1( GTK_REPERE( widgets->repere ), VITESSE_MAX );
        
        updateValues( widgets ); 
    }
    else{
        
        computeV1( widgets, sV1 );
        
    }
}

void computeV1( Widgets *widgets, const gchar *sV1 ){
 
    gdouble v1 = atof( sV1 );
    if( v1 >= VITESSE_MIN && v1 <= VITESSE_MAX){

        gtk_range_set_value(GTK_RANGE(widgets->barre_V1), v1);
        
        readValues( widgets );
        updateValues( widgets );

    }
    else if( v1 > VITESSE_MAX ){

        ErreurValeur( widgets->window );

        gtk_entry_set_text(GTK_ENTRY(widgets->entree_V1), "300000000");
        
        setSpeed1( GTK_REPERE( widgets->repere ), VITESSE_MAX );
        
        updateValues( widgets );        
    }
}

gboolean barre_V2_change_value( GtkRange *range, GtkScrollType scroll, gdouble value, gpointer user_data ){

	char string[STR_SIZE];
	gdouble v2;
	Widgets *widgets = (Widgets *)user_data;

	v2 = gtk_range_get_value(range);

	sprintf(string, "%2.0lf", v2);

	setSpeed2( GTK_REPERE( widgets->repere ), v2);
	gtk_entry_set_text(GTK_ENTRY(widgets->entree_V2), string);

    computeV2( widgets, string );
	return FALSE;
}



void entree_V2_changed( GtkEditable *editable, gpointer user_data ){

	int i;
	gboolean extra = FALSE;

	const gchar *sV2;
    
	Widgets *widgets = (Widgets *)user_data;

	sV2 =  gtk_entry_get_text(GTK_ENTRY(widgets->entree_V2));

	for(i=strlen(sV2)-1; i>=0; i--){

		if( (sV2[i] < 0x30 ) || (sV2[i] > 0x39 )  ){

			extra = TRUE;
			break;
		}
		else
			extra = FALSE;
	}

	if( extra ){

		ErreurNumerique( widgets->window );

		gtk_entry_set_text(GTK_ENTRY(widgets->entree_V2), "300000000");
        
        setSpeed2( GTK_REPERE( widgets->repere ), VITESSE_MAX );
        
        updateValues( widgets );
	}
	else{
        
        computeV2( widgets, sV2 );
	}
}

void computeV2( Widgets *widgets, const gchar *sV2 ){
 
    gdouble v2 = atof( sV2 );
    
    if( v2 >= VITESSE_MIN && v2 <= VITESSE_MAX){

        gtk_range_set_value(GTK_RANGE(widgets->barre_V2), v2);
        
        readValues( widgets );
        updateValues( widgets );
    }
    else if( v2 > VITESSE_MAX){

        ErreurValeur( widgets->window );

        gtk_entry_set_text(GTK_ENTRY(widgets->entree_V2), "300000000");
        
        setSpeed2( GTK_REPERE( widgets->repere ), VITESSE_MAX );
        
        updateValues( widgets );
    }
}
void ErreurNumerique( gpointer user_data ){

	GtkWidget *pErreur;

	pErreur = gtk_message_dialog_new (GTK_WINDOW(user_data),
								  GTK_DIALOG_MODAL,
								  GTK_MESSAGE_ERROR,
								  GTK_BUTTONS_OK,
								  g_locale_to_utf8("Seule une valeur numerique peut etre entree.",-1,NULL,NULL,NULL));
	gtk_dialog_run(GTK_DIALOG(pErreur));
	gtk_widget_destroy(pErreur);

}

void ErreurValeur( gpointer user_data ){

	GtkWidget *pErreur;

	pErreur = gtk_message_dialog_new (GTK_WINDOW(user_data),
								  GTK_DIALOG_MODAL,
								  GTK_MESSAGE_ERROR,
								  GTK_BUTTONS_OK,
								  g_locale_to_utf8("Seule une valeur entre 1 et 300000000 peut etre entree.",-1,NULL,NULL,NULL));

	gtk_dialog_run(GTK_DIALOG(pErreur));

	gtk_widget_destroy(pErreur);

}

void readValues( Widgets *widgets ){
    
    gdouble v1, v2;
    
    v1 = atof( gtk_entry_get_text(GTK_ENTRY(widgets->entree_V1)) );
    v2 = atof( gtk_entry_get_text(GTK_ENTRY(widgets->entree_V2)) );

    setSpeed1( GTK_REPERE( widgets->repere ), v1);
    setSpeed2( GTK_REPERE( widgets->repere ), v2);
}

void updateValues( Widgets *widgets ){
    
    char string[STR_SIZE];
    gdouble angleRefracted;
    gdouble angleReflected;
    
    angleReflected = computeReflected( GTK_REPERE( widgets->repere ) );
    angleRefracted = computeRefracted( GTK_REPERE( widgets->repere ) );

    sprintf(string, "%2.2lf", angleRefracted);
    gtk_entry_set_text(GTK_ENTRY(widgets->sortie_refracte), string);
    
    sprintf(string, "%2.0lf", angleReflected);
    gtk_entry_set_text(GTK_ENTRY(widgets->sortie_reflechi), string);
}
