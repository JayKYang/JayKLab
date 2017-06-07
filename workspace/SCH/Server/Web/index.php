<?php
	require_once("../dbconfig.php");
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<title>뉴톤 LoRa 모니터링</title>
	<link rel="stylesheet" href="./css/normalize.css" />
	<link rel="stylesheet" href="./css/board.css" />

	<script language='javascript'> 
  		window.setTimeout('window.location.reload()',10000);
	</script>

</head>
<body>
	<article class="boardArticle">
		<table style="width: 80%; margin: auto; text-align: center;">
			<thead>
				<tr>
					<th scope="col" class="seq">seq</th>
					<th scope="col" class="time">time</th>
					<th scope="col" class="gwid">gateway-id</th>
					<th scope="col" class="eui">eui</th>
					<th scope="col" class="data">data</th>
				</tr>
			</thead>
			<tbody>
					<?php
						$sql = 'select * from lux order by seq desc';
						$result = mysqli_query($conn, $sql) or die(mysqli_error($conn));
						while($row = mysqli_fetch_array($result))
						{
						?>
				<tr>
					<td class="seq"><?php echo $row['seq']?></td>
					<td class="time"><?php echo $row['date_time']?></td>
					<td class="gwid"><?php echo $row['gateway_id']?></td>
					<td class="eui"><?php echo $row['eui']?></td>
					<td class="data"><?php echo $row['data']?></td>
				</tr>
					<?php
						}
					?>
			</tbody>
		</table>
	</article>
</body>
</html>