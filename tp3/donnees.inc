<?php
function __getPersistance($typepersistance = "PersistanceXml") {

	// pour utiliser la persitance
	$persitance = new $typepersistance();

	return ($persitance->charger()) ? $persitance : null;
}

function __getCss($nom = "style") {
	return "<link rel='stylesheet' href='{$nom}.css'/>";
}
?>