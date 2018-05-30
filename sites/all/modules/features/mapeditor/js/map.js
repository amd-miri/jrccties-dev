L.custom = {
  init: function (obj, params) {

    // Defines map height.
    obj.style.minHeight = map_height;

    // Creates map object.
    var map = L.map(obj, mapeditor_map_settings);

    // Defines tile layer.
    var tileLayer = L.wt.TileLayer([{"zoom": mapeditor_map_settings.zoom, "map": mapeditor_map_settings.map}]).addTo(map);

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
    map.fitBounds(all_coordinates);

    // Processes next components.
    $wt._queue("next");

  }
};
