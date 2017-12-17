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

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "gtk_repere.h"

struct _Widgets{

	GtkWidget *window;
	GtkWidget *vbox2;
	GtkWidget *vbox3;
	GtkWidget *vbox4;

	GtkWidget *hbox4;
	GtkWidget *hbox5;
	GtkWidget *hbox6;
	GtkWidget *hbox7;
	GtkWidget *hbox8;
	GtkWidget *hbox10;
	GtkWidget *hbox11;
	GtkWidget *hbox12;
	GtkWidget *hbox13;

	GtkWidget *aspectframe1;
	GtkWidget *alignment1;
	GtkWidget *aspectframe2;
	GtkWidget *alignment2;
	GtkWidget *aspectframe3;
	GtkWidget *alignment3;
	GtkWidget *aspectframe5;
	GtkWidget *alignment5;
	GtkWidget *aspectframe6;
	GtkWidget *alignment6;

	GtkWidget *label2;
	GtkWidget *label3;
	GtkWidget *label4;
	GtkWidget *label5;
	GtkWidget *label6;
	GtkWidget *label8;
	GtkWidget *label12;
	GtkWidget *label13;
	GtkWidget *label14;
	GtkWidget *label15;
	GtkWidget *label16;
	GtkWidget *label17;
	GtkWidget *label18;


	GtkWidget *barre_incident;
	GtkWidget *entree_incident;
	GtkWidget *barre_V1;
	GtkWidget *entree_V1;
	GtkWidget *barre_V2;
	GtkWidget *entree_V2;
	GtkWidget *sortie_refracte;
	GtkWidget *sortie_reflechi;
	GtkWidget *repere;
	GtkWidget *check_arcs;
	GtkWidget *check_reflechi;
	GtkWidget *check_refracte;

	char *label_text;
} widgets;

typedef struct _Widgets Widgets;

GtkWidget* create_window (void);

#endif
