<?php
include_once "bandeau.inc";

function __getCSS($fichier) {
	return (isset($fichier)) ? "<link rel='stylesheet' type='text/css' media='screen' href='{$fichier}'/>" : "";
}

function __getEntete($titre = "tp2 - Adam") {
	$mapCSS = array("nav.css.fs");
	$bandeau = new Bandeau();

	$headers = "<head>\n<title>{$titre}</title>\n<meta charset='utf-8'>\n";
	$headers .= (isset($_SESSION['styleCSS'])) ? __getCSS($_SESSION['styleCSS']) : "";
	for($i=0; $i<count($mapCSS); $i++)
		$headers.= __getCSS($mapCSS[$i]);
	$headers .= "</head>";
	$headers .= (isset($_SESSION['u_connecte'])) ? $bandeau->genererBarNav($_SESSION['u_nom']) : $bandeau->genererBarNav();
	return $headers;
}
?>