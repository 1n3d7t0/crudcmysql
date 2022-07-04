#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <ctype.h>

void finalizar_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int main(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);

	if(con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

  	if (mysql_real_connect(con, "localhost", "root", "x647799",
          "mysql_c", 0, NULL, 0) == NULL)
  	{
      		finalizar_error(con);
	}

	char opcion;

	while(opcion != 6){

		printf("\n");
		printf("1 - Agregar registro\n");
		printf("2 - Eliminar registro\n");
		printf("3 - Mirar registros\n");
		printf("4 - Modificar un registro\n");
		printf("5 - Mirar un registro\n");
		printf("6 - Salir\n");
		printf("Opcion >> ");
		scanf("%s", &opcion);

		if(opcion == '1'){
       			char nombre[50];
			char email[50];
       			printf("\nUsuario a agregar: ");
       			scanf("%s", nombre);
			printf("\nEmail de %s: ", nombre);
			scanf("%s", email);

			if(strlen(nombre) >= 50) return printf("Maxima longitud de cadena: 50");
			if(strlen(email) >= 50) return printf("Maxima longitud del email: 50");
       			char sql_statement[2048];
       			sprintf(sql_statement, "INSERT INTO informacion(id, nombre, email) VALUES(NULL, '%s', '%s')", nombre, email);

       			if(mysql_query(con, sql_statement) !=0)
       			{
               			printf("Query failed  with the following message:\n");
               			printf("%s\n", mysql_error(con));
              			exit(1);
	    		}
        		printf("Usuario %s agregado\n\n", nombre);
		}

		else if(opcion == '2'){
			int id;
			printf("\nInsertar id del registro: ");
			scanf("%d", &id);
			char sql_statement[2048];
			sprintf(sql_statement, "DELETE FROM informacion WHERE id = %d", id);
			if(mysql_query(con, sql_statement) != 0)
			{
				printf("%s\n", mysql_error(con));
				exit(1);
			}

			printf("Id %d eliminado\n\n", id);
		}

		else if(opcion == '3'){
			printf("\n");
			if (mysql_query(con, "SELECT * FROM informacion"))
  			{
				finalizar_error(con);
  			}

  			MYSQL_RES *result = mysql_store_result(con);

  			if (result == NULL)
  			{
      				finalizar_error(con);
  			}

  			int num_fields = mysql_num_fields(result);

  			MYSQL_ROW row;

			printf("Id | Nombre | Email\n");
  			while ((row = mysql_fetch_row(result)))
  			{
      				for(int i = 0; i < num_fields; i++)
      				{
          				printf("%s ", row[i] ? row[i] : "NULL");
      				}
      				printf("\n");
  			}

  			mysql_free_result(result);
			printf("\n");
		}

		else if(opcion == '4'){
			int id;
			char nombre[50];
			char email[50];
			char sql_statement[2048];
			printf("\nInserte id del registro a modificar: ");
			scanf("%d", &id);
			printf("\nInserte nombre nuevo para el id %d: ", id);
			scanf("%s", nombre);
			printf("\nInserte email nuevo para el id %d: ", id);
			scanf("%s", email);

                        if(strlen(nombre) >= 50) return printf("Maxima longitud de cadena: 50");
                        if(strlen(email) >= 50) return printf("Maxima longitud del email: 50");

                	sprintf(sql_statement, "UPDATE informacion SET nombre = '%s', email = '%s' WHERE id = %d", nombre, email, id);
                	if(mysql_query(con, sql_statement) != 0)
                	{
                        	printf("%s\n\n", mysql_error(con));
                        	exit(1);
                	}

                	printf("Id: %d\nNuevo nombre: %s\nNuevo email: %s\n\n", id, nombre, email);
		}

		else if(opcion == '5'){
                	printf("\n");
			int id;
                	char sql_statement[2048];
			printf("Inserte ID para ver informacion del registro: ");
			scanf("%d", &id);
                	sprintf(sql_statement, "SELECT * FROM informacion WHERE id = %d", id);
                	if(mysql_query(con, sql_statement) != 0)
                	{
                        	finalizar_error(con);
                	}

                	MYSQL_RES *result = mysql_store_result(con);

                	if (result == NULL)
                	{
                        	finalizar_error(con);
                	}

                	int num_fields = mysql_num_fields(result);

                	MYSQL_ROW row;

                	printf("Id | Nombre | Email\n\n");
                	while ((row = mysql_fetch_row(result)))
                	{
                        	for(int i = 0; i < num_fields; i++)
                        	{
                                	printf("%s ", row[i] ? row[i] : "NULL");
                        	}
                	}

                	mysql_free_result(result);
                	printf("\n");
		}

		else if(opcion == '6'){
			mysql_close(con);
			exit(0);
		}

		else{
			printf("Opcion invalida\n");
		}

	}
	mysql_close(con);
	exit(0);
}
