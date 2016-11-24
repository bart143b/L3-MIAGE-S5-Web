<?php
	require_once "__autoload.inc";
	__autoload("donnees");
	__autoload("menu");

	$persitance = __getPersistance();
	$articles = $persitance->getArticles();

	function afficher($doc) {

		foreach ($doc as $value) {
			echo $value->getHtml();
		}
	}
?>
<!doctype html>
<html lang="fr">
<head>
       <title>pages pour le cours Web...</title>
       <!-- ligne pour l'encodage de la page -->
       <meta charset="utf-8">
</head>
<body>
	<div id="head"><?php echo __getMenu(); ?></div>
	<div id="body"><?php afficher($articles); ?></div>
	<div id="foot"></div>
</body>
</html>