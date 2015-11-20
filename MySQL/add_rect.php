<?php

	$servername = "myresdb.seas.wustl.edu";
	$username = "furukawa_sim";
	$password = "xiu56iuq83#";
	
	$database = "furukawa_sim_web";
	
	//Create connection
	$conn = mysql_connect($servername, $username, $password);
	
	//Check connection
	if(!$conn){
	
		die("Connection failed: ".mysqli_error());
	}
	echo "Connected successfully";
	
	//make furukawa_sim_web the current db
	$db = mysql_select_db($database, $conn);
	if(!$db){
	
		die("Cannot use furukawa_sim_web : ".mysql_error());
	}
	
	//insert into db
	
	$sql = "INSERT INTO RECT (ID, upper_x, upper_y, width, height)
			VALUES (1, 2.0, 2.0, 3.2354464, 5.23657)";
			
	$retval = mysql_query($sql, $conn);
	
	if(!$retval){
	
		die("Could not enter rectangle data: ".mysql_error());
	}
	
	echo("Rectangle data entered successfully");
	
	
	
	//get the number of rectangles associated with a scan
	$get_rects = mysql_query("SELECT rect_id FROM RECTS WHERE ID = '  ' ");
	if(!$get_rects){
	
		die("Could not get rectangles from scan.");
	}
	
	$num_rects = mysql_field_len($get_rects, 0);
	
	$update = "INSERT INTO SCANS (num_rect) VALUES ('$numrects')";
	
	if(!$update){
	
		die("Could not update the number of rectangles in a scan.");
	}
	
	echo("Number of rectangles successfully updated.");
	
	
	mysql_close($conn);
	
		
	
?>