#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	

	logger = iniciar_logger();
	

	// Usando el logger creado previamente (VIDEO PAUSADO EN EL MINUTO 13:23)
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Soy un logger creado por Ivan\n");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "VALOR");

	log_info(logger,"Lei la IP %s y el puerto %s\n", ip, puerto);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion); //remplazar el valor harcodeado con el la variable: valor
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion,logger,config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	if ((nuevo_logger  = log_create("tp0.log","TP0",true,LOG_LEVEL_INFO)) == NULL){
		printf("No se creo el logger");
		exit(1);
	};

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if ((nuevo_config  = config_create("./cliente.config")) == NULL){
		printf("Error en leer la config");
		exit(2);
	};

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while (1) {
        leido = readline(">");

        if ((strcmp(leido,"\0")) == 0 ) {
            break;
        }
        log_info(logger,leido);
		free(leido);
	}

	// ¡No te olvides de liberar las lineas antes de regresar!
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();
	// Leemos y esta vez agregamos las lineas al paquete
	while (1) {

        leido = readline(">");

        if ((strcmp(leido,"\0")) == 0 ) {
            enviar_paquete(paquete,conexion);
			break;
        }
        int longitud = strlen(leido);
		agregar_a_paquete(paquete,leido,longitud);
		free(leido);
	}
	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	if (logger != NULL){
		log_destroy(logger);
	}
	if (config != NULL){
		config_destroy(config); /*aca se destruye la estructura en memoria. No el archivo*/
	}
	liberar_conexion(conexion);
}
