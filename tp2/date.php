<?php 
	$date_saisi = (!empty($_GET['date_saisi'])) ? new DateTime($_GET['date_saisi']) : new DateTime("2016/11/01");
	$date_ajrd = new DateTime('NOW');
	$heure = $date_ajrd->format('H:i:s');
	$interval = $date_ajrd->diff($date_saisi);

	$texte1 = sprintf("Nous somme le %s et il est %s", strftime("%d %B %G", strtotime($date_ajrd->format("d/m/Y"))), $date_ajrd->format("G:i:s"));
	$texte2 = sprintf("Il y'a %s jours et %d secondes entre le %s et %s", $interval->format('%r%D'), $interval->format('%r%S'), $date_ajrd->format("d/m/Y"), $date_saisi->format("d/m/Y"));
?>
<!doctype html>
<html lang="fr">
<head>
       <title>Point 1</title>
       <meta charset="utf-8">
</head>
<body>
	
	<p><?php echo $texte1; ?></p>
	<p><?php echo $texte2; ?></p>
	<hr>
	<form action="date.php" method="get">
		<p>Entrez une date <input type="text" name="date_saisi" placeholder="AAAA/MM/JJ"></p>
		<input type="submit" value="Valider">
	</form>

</body>
</html>