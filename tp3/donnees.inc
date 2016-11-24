<?php
function __getPersistance($typepersistance = "PersistanceXml") {

	// pour utiliser la persitance
	$persitance = new $typepersistance();

	$persitance->charger();

	return $persitance;
}
?>