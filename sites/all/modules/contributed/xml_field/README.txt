SUMMARY: Defines an xml field type. Provides XML related API functions for
working with XML code.


REQUIREMENTS:
* SimpleXMLElement class: http://php.net/manual/en/class.simplexmlelement.php


INSTALLATION:
* Download and unzip this module into your modules directory.
* Goto Administer > Site Building > Modules and enable this module.


CONFIGURATION:
* Create an XML field and attach it to an entity, as with any field type.


USAGE:
There are three modes for XML usage.
* Output the XML so it can been seen in the browser window, by first converting
  it to html entities. For visual display of XML.
* Output the XML to the browser directly. SECURITY WARNING, SEE BELOW!
* Hide the field (Manage Display) and use xml_field_xml() and xml_field() to
  extract the xml data, from within your custom module. This latter usage allows
  for very sophisticated layout and theming, while still allowing admins to
  modify content. (See Advanced Use Case)


SIMPLE USE CASE
You have a node type, which needs to display XML data below the body content and
you just want an easy way to do it without having to write your own validation
and sanitization code. How then? Install the module, create a field, and set the
formatter to XML for display. You're done! You have instant XML validation and
sanitized output. Viola.


ADVANCED USE CASE
* As a developer, you designate a page node to be the foundation of a page, as
  it provides a solid page callback, menu link, title and body text.

* To this page node you add a single field called field_xml_page_data In
  hook_node_view_alter() you add extra content to $build, content that is
  generated dynamically based on any number of rules.

* The problem is that you want to allow a title to this content and maybe a
  footer, text which needs to be accessible for modification by an content
  manager. How do you do it? You create an XML representation of the editable
  content, which is intuitive to a content manager with only a little knowledge
  of XML, something like this:

@code
<page>
  <title>The Lone Ranger</title>
  <footer format="1">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla at massa sed nulla consectetur malesuada.</description>
</page>
@endcode

* Now back in hook_node_view_alter() you will parse the xml and use the fields
  to insert the title and the description (after sanitizing as needed), like
  this:

@code
$xml = $node->field_xml_page_data['und'][0]['xml'];
$title = xml_field($xml, 'title');
$format = xml_field($xml, 'description', 'format');
$description = xml_field($xml, 'description', NULL, array('check_markup', $format));
@endcode

* With this method you have a very robust way to allow disparate elements on the
  page to still be accessible to content managers, while maintaining absolute
  theme control at the PHP level. And, the beauty of XML is that you can make it
  as simple and descriptive as needed or as technical and nested as you desire
  since the tags are completely arbitrary (unlike trying to get content managers
  to understand HTML tags!)


LEVERAGING XML_FIELD_XML()
This function is at the heart of the module and should be understood by
developers. It will extract the xml from many different input sources and (used
in conjunction with xml_field()) allows you to save code. As a brief example,
the Advanced Case will be rewritten here, but there are assumptions to be made
which allow this to happen. The first assumption is that there is only one XML
field in the entity. The second assumption is that the entity is not translated
into other languages. And the last assumption is that the field only allows one
value. If all of these are true then we can simply pass the entity, in this case
$node to our api funtions and save steps. Observe...

@code
$title = xml_field($node, 'title');
$format = xml_field($node, 'description', 'format');
$description = xml_field($node, 'description', NULL, array('check_markup', $format));
@endcode

Study the docblocks in the code for more info.


API
The three main API Functions:
* xml_field_xml(): to obtain an XML object
* xml_field(): to access XML values
* xml_field_format(): to obtain a string version of any XML
* xml_field_output(): to output XML to the browser

Additional API functions:
* xml_field_is_valid_xml_string()
* xml_field_load_string(): use to create a simpleXMLElement compatible object instead of simplexml_load_string()
* xml_field_xml_fields()
* theme_xml()


OTHER EXAMPLE CODE:

--------------------------------------------------------
Example A
This example shows how to iterate over multiple nodes and also to access
properties.

@code
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
$build['buttons']['#weight'] = $body_weight + 1;
@endcode
--------------------------------------------------------
Example B
@code
<page>
  <dvd_button>Order your free DVDs and host a screening</dvd_button>
  <learn_button>Learn more about screenings</learn_button>
</page>

<?php
$build['buttons'] = array(
  '#weight' => $body_weight + 1,
);
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
@endcode
--------------------------------------------------------
CONTACT:
In the Loft Studios
Aaron Klump - Web Developer
PO Box 29294 Bellingham, WA 98228-1294
aim: theloft101
skype: intheloftstudios

http://www.InTheLoftStudios.com
