<?php 
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_name("AdamTp2");
	session_start();
}

require_once "entetes.inc";

function getSelections() {
	$listeFichierCSS = glob("*.css");
	$selectionParDefaut = (isset($_SESSION['styleCSS'])) ? $_SESSION['styleCSS'] : "";

	$option = "<select name='selectionCSS'>";
	foreach($listeFichierCSS as $fichier) {
		if(is_file($fichier)) {
			if(strcmp($selectionParDefaut, $fichier) == 0)
				$option .= "<option selected value='{$fichier}'>{$fichier}</option>";
			else
				$option .= "<option value='{$fichier}'>{$fichier}</option>";
		}
	}
	$option .='</select>';
	return $option;
}

if((isset($_GET['selectionCSS']))) {
	$_SESSION['styleCSS'] = $_GET['selectionCSS'];
}


?>
<!doctype html>
<html lang="fr">
<?php echo __getEntete(); ?>
<body>
	<div id="body">
	<form method="get" action="preference.php">
		<?php echo getSelections(); ?>
		<input type="submit" name="Envoyer">
	</form>
	</div>
</body>
</html>