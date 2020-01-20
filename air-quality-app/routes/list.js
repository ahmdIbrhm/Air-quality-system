var express = require('express');
var router = express.Router();
const fetch = require('node-fetch');
/* GET users listing. */


router.get('/', function(req, res, next) {

  var stations = []
  const request = async () => {
    const response = await fetch('https://territoire.emse.fr/applications/air-quality-control/station-info');
    const json = await response.json();
    for (var i = 0; i < json.length; i++){
      const response_sensor = await fetch('https://territoire.emse.fr/applications/air-quality-control/sensor-value?id='+json[i].station_id+'&last=1');
      const json_sensor = await response_sensor.json();
      for (var j = 0; j < json_sensor.length; j++){
        stations.push(new Station(json_sensor[j].station_id,json_sensor[j].geom,json_sensor[j].pm10,json_sensor[j].pm25,json_sensor[j].currenttime))
      }
    }
    var data = { stations: stations}
    res.render('list', {data: data})
  }
  request();

});

class Station {
  constructor(id,position,pm10,pm25,timestamp){
    this.id = id
    this.position = position
    this.pm10 = pm10
    this.pm25 = pm25
    this.timestamp = timestamp
  }
}
module.exports = router;
