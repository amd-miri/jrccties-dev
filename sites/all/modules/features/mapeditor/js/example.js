/**
 * Defines content for webtools map.
 */
L.custom = {
  init: function (obj, params) {

    // Defines map height.
    obj.style.minHeight = map_height;

    // Creates map object.
    var map = L.map(obj, {
      "center": [48, 9],
      "zoom": 5,
      "attributionControl": false,
      "loadingControl": true   // enable loading plugins: see below
    });

    // Defines tile layer.
    var TileLayer = L.wt.TileLayer([{"zoom": 0, "map": "osmec"}]).addTo(map);

    // Defines example features.
    var features = [{
      "type":"Feature",
      "properties":{
        "name":"Gunwalls",
        "popupContent":"Somewhere in Alaska"
      },
      "geometry":{
        "type":"Point",
        "coordinates":[-144.2181,65.8607]
      }
    },{
      "type":"Feature",
      "properties":{
        "name":"Man-of-war",
        "popupContent":"Some place in Brazil"
      },
      "geometry":{
        "type":"Point",
        "coordinates":[-51.1682,-5.9104]
      }
    }];

    // Adds GeoJson formatted features to map.
    L.geoJson(features).addTo(map);
    L.geoJson(features, {
       onEachFeature: onEachFeature
    }).addTo(map);

    // Creates pop up event and defines popup content for each feature.
    function onEachFeature(feature, layer) {
       // does this feature have a property named popupContent?
       if (feature.properties && feature.properties.popupContent) {
         layer.bindPopup(feature.properties.popupContent);
       }
    }

    // Fits the map to the available features.
    var all_coordinates = [[65.8607,-144.2181],[-5.9104,-51.1682]];
    map.fitBounds(all_coordinates);

    // Processes next components.
    $wt._queue("next");

  }
};
