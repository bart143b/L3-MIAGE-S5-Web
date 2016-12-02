<?php
if (session_status() !== PHP_SESSION_ACTIVE) {
    session_name("AdamTp2");
	session_start();
}

require_once "entetes.inc";

$titre = array("Nom du fichier", "Date de modification", "taille");

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
			$body[] = array("<a href=".dirname($_SERVER['PHP_SELF'])."/{$nomFichier}>{$nomFichier}</a>", date("d-m-Y", filemtime($nomFichier)), filesize($nomFichier));			}
	}

	return $body;
}

// Retourne un tableau representant la liste des fichier prensent sur le repertoire courant
function genereTableau($titre, $body) {
	$tab = "<table border='1'><caption>Nombre de ligne ".count($body)."</caption><thead><tr>";
	foreach($titre as $val) {
		$tab .= "<th>{$val}</th>";
	}
	$tab .= "</tr></thead><tbody>";
	foreach($body as $col) {
		$tab .= "<tr>";
		foreach($col as $val) {
			$tab .= "<td>{$val}</td>";
		}
		$tab .= "</tr>";
	}
	$tab .= "</tbody></table>";
	
	return $tab;
}
?>
<!doctype html>
<html lang="fr">
<?php echo __getEntete(); ?>
<body>
<div id="body">
<pre>
<?php
	echo genereTableau($titre, fichierCourent());
?>
</pre>
</div>
</body>
</html>