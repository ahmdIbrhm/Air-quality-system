<?php
$pm25=$_GET['pm25'];
$pm10=$_GET['pm10'];

// Generated by curl-to-PHP: http://incarnate.github.io/curl-to-php/
$ch = curl_init();

curl_setopt($ch, CURLOPT_URL, 'http://localhost:3030/dust/update');
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, "update= insert {<http://www.example.org/sensor1> <http://www.example.org/pm25> ". $pm25.". <http://www.example.org/sensor1> <http://www.example.org/pm10> ".$pm10."} where {}  ");
$headers = array();
$headers[] = 'Accept: application/json';
$headers[] = 'Content-Type: application/x-www-form-urlencoded';
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

$result = curl_exec($ch);
if (curl_errno($ch)) {
    echo 'Error:' . curl_error($ch);
}
else
{
	echo $result;
}
curl_close($ch);

?>