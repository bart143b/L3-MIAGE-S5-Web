<?php 
	session_name("tp2");
	session_start();
	
	$meta = "";
	$selDefaut = "";
	$listeFichierCSS = glob("*.css");

	if(isset($_GET['selectionCSS'])) {
		$selDefaut = $_GET['selectionCSS'];
		$meta = sprintf("<link rel='stylesheet' type='text/css' media='screen' href='%s'/>", $_GET['selectionCSS']);
	}

	$option = "<select name='selectionCSS'>";
	foreach($listeFichierCSS as $fichier) {
		if(is_file($fichier)) {
			if(strcmp($selDefaut, $fichier) == 0)
				$option = $option.sprintf("<option selected value='%s'>%s</option>", $fichier, $fichier);
			else
				$option = $option.sprintf("<option value='%s'>%s</option>", $fichier, $fichier);
		}
	}
	$option = $option.'</select>';

	funtion getHead($titrePage) {
		$entete = "<title>".$titrePage."</title><meta charset='utf-8'>";

		if(isset($_GET['selectionCSS'])) {
			$selDefaut = $_GET['selectionCSS'];
			$meta = sprintf("<link rel='stylesheet' type='text/css' media='screen' href='%s'/>", $_GET['selectionCSS']);
		}
	}
?>
<!doctype html>
<html lang="fr">
<head>
   	<title>Point 3-a</title>
   	<meta charset="utf-8">
   	<?php echo $meta; ?>
</head>
<body>
	<form method="get" action="preference.php">
		<?php echo $option; ?>
		<input type="submit" name="Envoyer">
	</form>
</body>
</html>