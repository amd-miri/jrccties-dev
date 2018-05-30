/**
 * Provides custom functionality as input for Webtools' load.js.
 */
L.custom = {
  init: function (obj, params) {

    // Defines height of the map.
    obj.style.minHeight = map_height;

    // Initializes the map object.
    var map = L.map(obj, mapeditor_map_settings);

    // Adds the tiles layer.
    var tileLayer = L.wt.TileLayer([{"zoom": mapeditor_map_settings.zoom, "map": mapeditor_map_settings.map}]).addTo(map);

    // Defines custom actions for predefined options.
    var nuts_options = {
      style: function(feature) {
        return {
          fillColor: "#C8E9F2",
          weight: 1,
          opacity: 1,
          color: "#0065B1",
          fillOpacity: 0.9
        };
      },
      onEachFeature: function (feature, layer) {
        var id	= (feature.properties.NUTS_ID||feature.properties.CNTR_ID);
        var customEvents = {
          click: function (e) {
            window.location.href = mapeditor_nuts[id].url;
          }
        };
        layer.on({
          click: customEvents.click
        });
      }
    };

    // Adds countries as Nuts to map.
    var nuts = L.wt.countries([{
      "level": 0,
      "countries": mapeditor_nuts_keys
    }], nuts_options).addTo(map);

    // Processes next components.
    $wt._queue("next");

  }
};
