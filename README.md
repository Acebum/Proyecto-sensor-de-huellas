# Sistema de Control de Acceso a Sala de Estudios con ESP32 y Sensor de Huellas

Este proyecto implementa un sistema inteligente de control de acceso para una sala de estudios, utilizando un sensor de huellas dactilares conectado a un ESP32. El objetivo es garantizar que solo personas autorizadas puedan ingresar, mejorando la seguridad y el control del espacio.

## Características Principales

* **Autenticación biométrica:** Utiliza un sensor de huellas dactilares para identificar a los usuarios.
* **Control de acceso:** Permite el ingreso únicamente a personas autorizadas.
* **Conectividad:** Emplea el ESP32 para la comunicación y posiblemente para la interacción con una base de datos en la nube.
* **Seguridad mejorada:** Restringe el acceso a la sala de estudios.
* **Gestión de usuarios:** (Implícito) Posibilidad de añadir o eliminar huellas dactilares autorizadas.

##  Tecnologías Utilizadas

* **ESP32:** Microcontrolador potente con conectividad Wi-Fi integrada, ideal para proyectos IoT.
* **Sensor de huellas dactilares:** Modelos como el R305 o AS608, encargados de la lectura y verificación de las huellas.
* **Firebase Realtime Database / Firestore:** Bases de datos NoSQL en la nube de Google, utilizadas para almacenar y gestionar los datos de los usuarios autorizados y los registros de acceso.
