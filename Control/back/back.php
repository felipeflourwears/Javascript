<?php

// URL del endpoint para enviar la solicitud POST
$url = "#";

// Token de autorización para la solicitud POST
$token = "#";

$valor = $_POST['value'];
echo $valor;

// Datos a enviar en formato JSON
$data = json_encode(["id" => $valor]);

$headers = [
    'Accept: application/json',
    'Content-Type: application/json',
    'Authorization: Token ' . $token // Espacio después de 'Bearer'
];

// Inicializar cURL para la solicitud POST
$ch = curl_init($url);

// Configurar las opciones de la solicitud cURL
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

// Ejecutar la solicitud cURL y obtener la respuesta
$response = curl_exec($ch);
$http_status = curl_getinfo($ch, CURLINFO_HTTP_CODE);

// Comprobar el resultado de la solicitud
if ($http_status == 200) {
    echo "Solicitud exitosa!\n";
    echo $response;
    header('Location: ../index.html');
    exit();

} else {
    echo "Error en la solicitud: " . $http_status . "\n";
}

// Cerrar la sesión cURL
curl_close($ch);

?>
