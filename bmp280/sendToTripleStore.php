<?php
$station_name = $_GET['sensor_id'];
$temp=$_GET['temp'];
$pressure=$_GET['pressure'];
$alt=$_GET['alt'];
$timeStamp = $_GET['time_stamp'];
// echo $timeStamp.'<br/>';
// echo $station_name.'<br/>';
// echo $alt.'<br/>';
// echo $pressure.'<br/>';
// echo $temp.'<br/>';

$request = "update= insert {
	<http://www.example.org/$station_name> <http://www.example.org/hasState> <http://www.example.org/$station_name/$timeStamp>.
	<http://www.example.org/$station_name/$timeStamp> <http://www.example.org/timeStamp> $timeStamp .
	 <http://www.example.org/$station_name/$timeStamp> <http://www.example.org/hasBMP> <http://www.example.org/BMP/$station_name/$timeStamp> . 
	<http://www.example.org/BMP/$station_name/$timeStamp> <http://www.example.org/temperatureValue> $temp .
	<http://www.example.org/BMP/$station_name/$timeStamp> <http://www.example.org/pressureValue> $pressure .
	<http://www.example.org/$station_name/$timeStamp> <http://www.example.org/hasSDS> <http://www.example.org/SDS/$station_name/$timeStamp> . 
	<http://www.example.org/SDS/$station_name/$timeStamp> <http://www.example.org/pm2.5Value> 1.25 .
	<http://www.example.org/SDS/$station_name/$timeStamp> <http://www.example.org/pm10Value> 8.7 .
	
} where {}  ";

	
// Generated by curl-to-PHP: http://incarnate.github.io/curl-to-php/
$ch = curl_init();

curl_setopt($ch, CURLOPT_URL, 'http://localhost:3030/bmp/update');
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS,$request);
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
