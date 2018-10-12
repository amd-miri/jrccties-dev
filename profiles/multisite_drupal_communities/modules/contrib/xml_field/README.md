##Summary
A complete solution for entering, storing and working with XML and Drupal.  The versatility of this module spans from simply storing and displaying informational XML to your visitors, to using XML as a configuration mechanism and never displaying the actual XML to the end user.


The module provides API functions for working with XML, which extend PHP's own [SimpleXML](http://php.net/manual/en/book.simplexml.php), and defines an XML field type, widget and formatters.  Starting in version 1.6, the XML widget leverages [CodeMirror](http://codemirror.net/) for awesome data entry.  You can format the XML to be hidden, display in color coded, escaped HTML, print directly as hidden XML, or show as a read-only text area for easy copy-and-paste.  The formatter you choose will depend on your use case.

The module also adds `theme_xml()` for displaying XML in colorized, HTML entities, and adds a new form element: `xmltext`.

## Highlights
* Create fields on your entities to **store XML data**, which validate upon form submission.
* Use the **CodeMirror** widget for awesome inline XML entry (as of 1.6).
* **XML Schema Support** (as of 1.7).  You may choose to define a schema for each field instance; your XML will validate against this schema when the entity edit form is saved.
* **Extensive developer functions** for working with XML and XML as fields attached to entities.  Functions include: sorting, outputting, validating and testing XML elements.
* **Superior CDATA handling** from that of standard SimpleXML.  See Advanced Help documents for specific info on this.
* Automatic CDATA escaping when enabled.
* **FAPI Integration** with XML elements provided.

##Requirements
* SimpleXML <http://www.php.net/manual/en/book.simplexml.php>
* The SimpleXML extension requires PHP 5.

##Installation
* Download and unzip this module into your modules directory.
* Goto Administer > Site Building > Modules and enable this module.
* Optionally, enable `xml_field_codemirror` to have an XML widget available.

###CodeMirror XML Widget (7.x-1.6+)
To use the XML widget (using [CodeMirror](http://codemirror.net)), you must do the following:

1. Download the CodeMirror package (Tested with versions 3.x and 4.x) and unzip in to your libraries folder <http://codemirror.net/codemirror.zip>.
2. Rename the folder to simply `codemirror`
1. Enable the included module `CodeMirror XML Widget` (`xml_field_codemirror`).  You do not need to install <http://drupal.org/project/codemirror>
3. Make sure `codemirror.js` is located in the following location: `libraries/codemirror/lib/codemirror.js`.
4. Check `admin/reports/status` and you should see the CodeMirror version number.
5. Note that after setting an XML field's widget to CodeMirror XML, there are additional settings available under the Edit tab.  This includes the CodeMirror color scheme (or theme).

####CodeMirror Global Default Theme
Code mirror uses themes for colorizing the input widget.  You can set a global theme and save yourself from lots of clicks by setting a `$conf` variable in your `settings.php`.  To set a global default theme add the following line to your `settings.php` file:

    $conf['xml_field_codemirror_default_theme'] = 'cobalt'
    
You do not have to do this in `settings.php`, rather you can do it in your own custom module using a hook.  To do this using a custom module hook, implement the following in your custom module:

    function my_module_xml_field_codemirror_defaults_alter(&$config) {
      $config['theme'] = 'cobalt';
    }

Do either of these steps BEFORE creating fields and all your fields will default to this value.


####API: CodeMirror Options
Check out `xml_field_codemirror.api.php` for API options.

####Known Issues
2. XML fields inside collapsed fieldsets may not show upon expansion; usually clicking the xml field brings it back.

##Upgrade Path
### to 7.x-1.6
To begin using the XML widget introduced in version 1.6:

1. Upgrade XML Field to version 7.x-1.6
2. Install the CodeMirror XML Widget (7.x-1.6+) as described above.
3. Edit each XML field and change the widget to CodeMirror XML.  Optionally, adjust the theme under the field's Edit tab.
4. Edit a node to see the new widget in action.

##Configuration
* Create an XML field and attach it to an entity, as with any field type.

##FAPI
###xmltext
This module adds a new form element called `xmltext` which does xml validation on form submit.

##Usage
There are essentially three use case modes for XML and this module.

1. Output the XML so it can been seen in the browser window, by first converting it to html entities. For visual display of XML.
1. Output the XML to the browser directly to influence the actual page load in some way. SECURITY WARNING, SEE BELOW!
1. Hide the field (Manage Display) and use `xml_field_xml()` and `xml_field()` to extract the xml data, from within your custom module. This latter usage allows for very sophisticated layout and theming, while still allowing admins to modify content. (See Advanced Use Case)


###Simple Use Case
You have a node type, which needs to display XML data below the body content and you just want an easy way to do it without having to write your own validation and sanitization code. How then? Install the module, create a field, and set the formatter to XML for display. You're done! You have instant XML validation and sanitized output. Viola.


###Advanced Use Case
As a developer, you designate a page node to be the foundation of a page, as it provides a solid page callback, menu link, title and body text.

To this page node you add a single field called field_xml_page_data In hook_node_view_alter() you add extra content to $build, content that is generated dynamically based on any number of rules.

The problem is that you want to allow a title to this content and maybe a footer, text which needs to be accessible for modification by an content manager. How do you do it? You create an XML representation of the editable content, which is intuitive to a content manager with only a little knowledge of XML, something like this:

    <page>
      <title>The Lone Ranger</title>
      <footer format="1">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla at massa sed nulla consectetur malesuada.</description>
    </page>

Now back in hook_node_view_alter() you will parse the xml and use the fields to insert the title and the description (after sanitizing as needed), like this:

    $xml = $node->field_xml_page_data['und'][0]['xml'];
    $title = xml_field($xml, 'title');
    $format = xml_field($xml, 'description', 'format');
    $description = xml_field($xml, 'description', NULL, array('check_markup', $format));

With this method you have a very robust way to allow disparate elements on the page to still be accessible to content managers, while maintaining absolute theme control at the PHP level. And, the beauty of XML is that you can make it as simple and descriptive as needed or as technical and nested as you desire since the tags are completely arbitrary (unlike trying to get content managers to understand HTML tags!)


###Leveraging `xml_field_xml()`
This function is at the heart of the module and should be understood by
developers. It will extract the xml from many different input sources and (used in conjunction with xml_field()) allows you to save code. As a brief example, the Advanced Case will be rewritten here, but there are assumptions to be made which allow this to happen. The first assumption is that there is only one XML field in the entity. The second assumption is that the entity is not translated into other languages. And the last assumption is that the field only allows one value. If all of these are true then we can simply pass the entity, in this case $node to our api funtions and save steps. Observe...

    $title = xml_field($node, 'title');
    $format = xml_field($node, 'description', 'format');
    $description = xml_field($node, 'description', NULL, array('check_markup', $format));

Study the docblocks in the code for more info.

##API
###The main API Functions:
* `xml_field_xml()`: to obtain an XML object
* `xml_field()`: to access XML values
* `xml_field_format()`: to obtain a string version of any XML
* `xml_field_output()`: to output XML to the browser
* `xml_field_sort()`: sort children by an attribute

###Additional API functions:
* `xml_field_boolean`: test for a boolean value
* `xml_field_has()`: verify if a node or attribute exists, even if empty
* `xml_field_is_valid_xml_string()`
* `xml_field_load_string()`: use to create a simpleXMLElement compatible object instead of `simplexml_load_string()`
* `xml_field_xml_fields()`
* `xml_field_append`: append an xml node inside another
* `theme_xml()`

##Security Warning!
This module contains a raw XML formatter that allows the output of unfiltered text directly to the browser, if malicious users are allowed to enter data into a field with this formatter, they could create a security problem. This is similiar to giving the PHP filter to untrusted users. The result could be the same.

This formatter can be used beneficially too, by trusted users, so it is included, however you must understand what you are doing if you employ it.

##Similar Projects

* <http://drupal.org/project/xmlcontent>
* <http://drupal.org/project/codemirror>

##Sponsored by
[In the Loft Studios](http://www.intheloftstudios.com/) and [Global Oneness Project](http://www.globalonenessproject.org)

##More Examples

###Example A
This example shows how to iterate over multiple nodes and also to access
properties.

    <page>
      <button color="green">Order your free DVDs and host a screening</button>
      <button color="beige" class="more-link">Learn more about screenings</button>
    </page>
    
    <?php
    // Add the buttons
    $xml = xml_field_xml($node);
    $build['buttons'] = $class = array();
    foreach ($xml->button as $button) {
      $class[] = 'button-link';
      $class[] = xml_field($button, NULL, 'color');
      $class[] = xml_field($button, NULL, 'class');
      $build['buttons'][] = array('#markup' => l(xml_field($button), 'node/add/screening', array(
        'attributes' => array(
          'class' => $class
        ),
      )));
    }
    ?>

###Example B
This example shows how to populate two links' text using an XML field.

    <page>
      <dvd_button>Order your free DVDs and host a screening</dvd_button>
      <learn_button>Learn more about screenings</learn_button>
    </page>
    
    <?php
    $build['buttons'] = array()
    if ($title = xml_field($node, 'dvd_button')) {
      $build['buttons'][] = array('#markup' => l($title, 'node/add/screening', array(
        'attributes' => array(
          'class' => array('button-link', 'green'),
        ),
      )));
    }
    if ($title = xml_field($node, 'learn_button')) {
      $build['buttons'][] = array('#markup' => l($title, 'node/2186', array(
        'attributes' => array(
          'class' => array('button-link', 'beige', 'more-link'),
        ),
      )));
    }
    ?>

##Contact
In the Loft Studios  
Aaron Klump  
PO Box 29294 Bellingham, WA 98228-1294  
aim: theloft101  
skype: intheloftstudios  

<http://www.InTheLoftStudios.com>
