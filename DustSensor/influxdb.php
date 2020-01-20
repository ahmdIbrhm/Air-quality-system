<?php
require '/var/www/html/air-quality-control/DustSensor/vendor/autoload.php';
$client = new InfluxDB\Client("localhost", "8086");

$database = $client->selectDB('cps2');

// executing a query will yield a resultset object
$result = $database->query('select * from dust');

// get the points from the resultset yields an array
$points = $result->getPoints();
print_r ($points);
echo "<br><br>";

$insertedPoints = array(
	new \InfluxDB\Point(
		'dust', // name of the measurement
		null, // the measurement value
		['station' => 'station4'], // optional tags
		['pm25' => 25, 'pm10' => 10],
		1435255849 // optional additional fields
	)
);
print_r ($insertedPoints);

$result = $database->writePoints($insertedPoints);


echo "inserted";

$result = $database->query('select * from dust');
$points = $result->getPoints();


?>