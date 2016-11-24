<?php

	//$listeFichier = glob("*.php");

	$titre = array("Nom du fichier", "Date de modification", "taille");
	//$body[] = array("date.php", "23-09-2016", "1485");
	//$body[] = array("tableau.php", "23-09-2016", "1485");

	// Retourne un tableau contenant tous les noms de fichier avec leur taille et leur date de dernière modification
	function fichierCourent() {
		$body = array();
		$listeFichier = glob("*.php");

		// On efffectue le trie en fonctionne des paramettre passé par GET
		if (!empty($_GET["tri"])) {
			switch ($_GET["tri"]) {
				case 'sort':
					sort($listeFichier);
					break;
				case 'rsort':
					rsort($listeFichier);
					break;
				default:
					break;
			}
		}

		foreach ($listeFichier as $nomFichier) {
			if(is_file($nomFichier)) {
				$body[] = array("<a href=".dirname($_SERVER['PHP_SELF'])."/".$nomFichier.">".$nomFichier."</a>", date("d-m-Y", filemtime($nomFichier)), filesize($nomFichier));			}
		}

		return $body;
	}
	
	// Retourne un tableau representant la liste des fichier prensent sur le repertoire courant
	function genereTableau($titre, $body) {
		$tab = "<table border='1'><caption>Nombre de ligne ".count($body)."</caption><thead><tr>";
		foreach($titre as $val) {
			$tab = $tab."<th>".$val."</th>";
		}
		$tab = $tab."</tr></thead><tbody>";
		foreach($body as $col) {
			$tab = $tab."<tr>";
			foreach($col as $val) {
				$tab = $tab."<td>".$val."</td>";
			}
			$tab = $tab."</tr>";
		}
		$tab = $tab."</tbody></table>";
		
		return $tab;
	}
?>
<!doctype html>
<html lang="fr">
<head>
       <title>Point 2</title>
       <meta charset="utf-8">
</head>
<body>
<pre>
<?php
	echo genereTableau($titre, fichierCourent());
?>
</pre>
</body>
</html>