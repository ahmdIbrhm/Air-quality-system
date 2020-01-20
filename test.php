<?php

$pm25=$_GET['p25'];
$pm10=$_GET['p10'];
$pressure=$_GET['pressure'];
$temperature=$_GET['temp'];

require '/var/www/html/air-quality-control/DustSensor/vendor/autoload.php';
$client = new InfluxDB\Client("localhost", "8086");

$database = $client->selectDB('cps2');

// // executing a query will yield a resultset object
// $result = $database->query('select * from dust');

// // get the points from the resultset yields an array
// $points = $result->getPoints();
// print_r ($points);
// echo "<br><br>";
$nanotime = system('date +%s%N');
// echo $nanotime;

$insertedPoints = array(
	new \InfluxDB\Point(
		'dust', // name of the measurement
		null, // the measurement value
		['station' => 'station1'], // optional tags
		['pm25' => $pm25, 'pm10' => $pm10, 'pressure' => $pressure, 'temp' => $temperature],
		// $unixTime // optional additional fields
		$nanotime
	)
);
// print_r ($insertedPoints);

$result = $database->writePoints($insertedPoints);


// echo "inserted";

// $result = $database->query('select * from dust');
// $points = $result->getPoints();


?>