<?php

	$year = date('Y');
	$month = date('m');
	$day = date('d');

	echo json_encode(array(
	
		array(
			'id' => 111,
			'title' => "Event1",
			'start' => "$year-$month-$day",
			'url' => "http://google.com/",
            'resourceId' => 1
		),
		
		array(
			'id' => 222,
			'title' => "Event2",
			'start' => "$year-$month-${day}T08:00:00Z",
			'end' => "$year-$month-${day}T12:00:00Z",
            'allDay' => false,
			'url' => "http://google.com/",
            'resourceId' => 2
		),

        array(
			'id' => 333,
			'title' => "Event3",
			'start' => "$year-$month-${day}T14:30:00Z",
			'end' => "$year-$month-${day}T16:00:00Z",
            'allDay' => false,
            'resourceId' => 3
		)
	
	));

?>
