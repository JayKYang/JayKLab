<?php
	$conn = new mysqli('localhost', 'root', 'test', 'luxDB');

	if ($conn->connect_error) {
		die('DB connect Error');
	}

?>