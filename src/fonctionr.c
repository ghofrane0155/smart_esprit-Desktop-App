#include "fonctionr.h"
#include "callbacks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

enum{
ID,
VALEUR,
DATE_INSTALLATION,
TYPE,
ETAGE,
COLUMNS
};

void ajouter_capteur(Capteur c)
{
    FILE *fp;
    fp = fopen("capteurs.bin", "ab+");
    if (fp!=NULL)
    {
        

        fwrite(&c, sizeof(c), 1, fp);
        
    }
    else
    {
        printf("\n non trouver");
    }
fclose(fp);
}
void afficher_capteur(GtkWidget *liste)
{
Capteur c;
char DATE[30];
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
store = NULL;
FILE *fp;


store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Id",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Valeur",renderer,"text",VALEUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Date d'installation",renderer,"text",DATE_INSTALLATION,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Type",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Etage",renderer,"text",ETAGE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
	store = gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	fp = fopen("capteurs.bin", "rb");

	if(fp==NULL)
	{
	return;
	}

	else
	{
		fp = fopen("capteurs.bin", "ab+");	
		while(fread(&c, sizeof(c), 1, fp))
		{
		sprintf(DATE, "%d/%d/%d", c.date_installation.jour,c.date_installation.mois,c.date_installation.annee);
		
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, ID, c.id, VALEUR, c.valeur,DATE_INSTALLATION, DATE, TYPE, c.type,  ETAGE, c.etage,-1);
		}
		fclose(fp);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}

}
void supprimer_capteur(Capteur c, char id[], char type[])
{

FILE *fp1, *fp2;
    fp1 = fopen("capteurs.bin", "rb");
    fp2 = fopen("temp.bin", "ab+");
    if (fp1==NULL)
    {
        printf("\nEchec lors de l'ouverture du fichier 'capteurs.bin'");
    }
    else
    {
        while (fread(&c, sizeof(c), 1, fp1))
        {
            if ((strcmp(id, c.id)!=0) && (strcmp(type, c.type)!=0))
                fwrite(&c, sizeof(c), 1, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("capteurs.bin");
    rename("temp.bin", "capteurs.bin");
}


void afficher_capteurModif(GtkWidget *liste)
{
Capteur c;
char DATE[30];
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;

store = NULL;

FILE *fp;



store = gtk_tree_view_get_model(liste);

if (store == NULL)
{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Id",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Valeur",renderer,"text",VALEUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Date d'installation",renderer,"text",DATE_INSTALLATION,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Type",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Etage",renderer,"text",ETAGE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
	store = gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	fp = fopen("temp1.bin", "rb");

	if(fp==NULL)
	{
	return;
	}

	else
	{
		fp = fopen("temp1.bin", "ab+");	
		while(fread(&c, sizeof(c), 1, fp))
		{
		sprintf(DATE, "%d/%d/%d", c.date_installation.jour,c.date_installation.mois,c.date_installation.annee);
		
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, ID, c.id, VALEUR, c.valeur, TYPE, c.type, DATE_INSTALLATION, DATE, ETAGE, c.etage,-1);
		}
		fclose(fp);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}

}
void modifier_capteur(Capteur r, char id[])
{
FILE *fp1, *fp2;
Capteur c;
fp1 = fopen("capteurs.bin", "rb");
fp2 = fopen("tmpp.bin","ab+");
if (fp1==NULL)
{
	return ;
}
else
{
	while (fread(&c,sizeof(c),1,fp1))
	{
		if (strcmp(c.id,id)!=0)
			fwrite(&c,sizeof(c),1,fp2);
		else
		{
			fwrite(&r,sizeof(r),1,fp2);			
		}
	}
}
fclose(fp1);
fclose(fp2);
remove("capteurs.bin");
rename("tmpp.bin", "capteurs.bin");

}

void afficher_capteur_alarmant(GtkWidget *liste)
{
Capteur c;
float max1=50, min1=0, min2=40, max2=90;
char DATE[30];
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
store = NULL;
FILE *fp;


store = gtk_tree_view_get_model(liste);
if (store == NULL)
{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Id",renderer,"text",ID,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Valeur",renderer,"text",VALEUR,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Date d'installation",renderer,"text",DATE_INSTALLATION,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Type",renderer,"text",TYPE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes(" Etage",renderer,"text",ETAGE,NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
	store = gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	fp = fopen("capteurs.bin", "rb");

	if(fp==NULL)
	{
	return;
	}

	else
	{
		fp = fopen("capteurs.bin", "ab+");	
		while(fread(&c, sizeof(c), 1, fp))
		{
		 if( ((strcmp(c.type,"Temperature")==0)&&((atoi(c.valeur)<min1) || (atoi(c.valeur)>max1)))||((strcmp(c.type,"Humidite")==0)&&((atoi(c.valeur)<min2) || (atoi(c.valeur)>max2))) ){
		sprintf(DATE, "%d/%d/%d", c.date_installation.jour,c.date_installation.mois,c.date_installation.annee);
		
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, ID, c.id, VALEUR, c.valeur,DATE_INSTALLATION, DATE, TYPE, c.type,  ETAGE, c.etage,-1);
		}
		}
		fclose(fp);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}

}



void chercher_capteur_supp(Capteur c, char id[20],char type[20], int *ok)
{
FILE *fp ,*fp1;
fp = fopen("capteurs.bin", "rb");
fp1 = fopen("temp1.bin", "wb");
*ok=0;

if(fp==NULL)
{
return;
}
else
{
while(fread(&c, sizeof(c), 1, fp))
{
	if  ((strcmp(id, c.id)==0) && (strcmp(type, c.type)==0))
	{
		fwrite(&c, sizeof(c), 1, fp1);
		*ok=1; // ok prends la valeur 1 si cin existe *********** sinon ok = 0
	}

}
}
fclose(fp);
fclose(fp1);
}

int nbre_alarmants(float max1, float min1, float max2, float min2)
{
Capteur c;
float max11=50, min11=0, min22=40, max22=90;
FILE *f1;
int nbr=0;
f1 = fopen("capteurs.bin", "rb");
if(f1==NULL)
{
return -1 ;
}
else
{
while(fread(&c, sizeof(c), 1, f1))
{
if( ((strcmp(c.type,"Temperature")==0)&&((atoi(c.valeur)<min1) || (atoi(c.valeur)>max1)))||((strcmp(c.type,"Humidite")==0)&&((atoi(c.valeur)<min2) || (atoi(c.valeur)>max2))) )
{
nbr++;
}
}
fclose(f1);
return nbr;
}
}








