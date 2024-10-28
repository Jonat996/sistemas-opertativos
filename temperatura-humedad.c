#include <Arduino.h>
#include "DHTesp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Configuración del DHT y parámetros de muestreo
int pinDHT = 15;
DHTesp dht;
#define SAMPLE_INTERVAL 600000 // Intervalo de 10 minutos en milisegundos
#define TOTAL_SAMPLES 1008     // 7 días x 24 horas x 6 muestras por hora

// Estructura para almacenar los datos de temperatura y humedad
struct DatoClimatico
{
    float temperatura;
    float humedad;
};

// Puntero para almacenamiento dinámico
DatoClimatico *datos_climaticos;

void tomarMuestras(void *pvParameters)
{
    for (int i = 0; i < TOTAL_SAMPLES; i++)
    {
        TempAndHumidity data = dht.getTempAndHumidity();
        datos_climaticos[i].temperatura = data.temperature;
        datos_climaticos[i].humedad = data.humidity;

        Serial.print("Muestra ");
        Serial.print(i + 1);
        Serial.print(" - Temperatura: ");
        Serial.print(data.temperature, 2);
        Serial.print("°C, Humedad: ");
        Serial.print(data.humidity, 1);
        Serial.println("%");

        // Esperar hasta el siguiente intervalo de toma de muestra
        vTaskDelay(pdMS_TO_TICKS(SAMPLE_INTERVAL));
    }

    // Liberar la memoria asignada al finalizar las muestras
    free(datos_climaticos);
    Serial.println("Toma de muestras completada. Memoria liberada.");

    // Finaliza la tarea
    vTaskDelete(NULL);
}

void setup()
{
    Serial.begin(115200);
    dht.setup(pinDHT, DHTesp::DHT22);

    // Asignar memoria dinámica para almacenar las muestras
    datos_climaticos = (DatoClimatico *)malloc(TOTAL_SAMPLES * sizeof(DatoClimatico));
    if (datos_climaticos == NULL)
    {
        Serial.println("Error al asignar memoria dinámica.");
        return;
    }

    // Crear la tarea de muestreo en FreeRTOS
    xTaskCreate(&tomarMuestras, "Tarea de Toma de Muestras", 2048, NULL, 5, NULL);
}

void loop()
{
    // No se necesita código en el loop, ya que la tarea toma los datos
}
