<?php

require '/var/www/html/air-quality-control/bmp280/vendor/autoload.php';

$station_name = $_GET['sensor_id'];
$temp=$_GET['temp'];
$pressure=$_GET['pressure'];
$alt=$_GET['alt'];



$client = new InfluxDB\Client("192.168.43.132", "8086");

$database = $client->selectDB('cps2');

// // executing a query will yield a resultset object
// $result = $database->query('select * from dust');

// // get the points from the resultset yields an array
// $points = $result->getPoints();
// print_r ($points);
// echo "<br><br>";

// change later if possible the date ...

$now = new DateTime();
$unixTime= $now->getTimestamp();
$insertedPoints = array(
	new \InfluxDB\Point(
		'temp', // name of the measurement
		null, // the measurement value
		['station' => $station_name], // optional tags
		['temp' => $temp, 'alt' => $alt, 'pressure' => $pressure],
		$unixTime // optional additional fields
	)
);
#print_r ($insertedPoints);

$result = $database->writePoints($insertedPoints);

echo "OK ---------------------------------------- > !";

?>