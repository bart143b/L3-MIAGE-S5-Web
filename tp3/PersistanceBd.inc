<?php
require_once "__autoload.inc";
__autoload("Categorie");
__autoload("Article");

class PersistanceBd implements Persistance {

	/**
	 * permet de charger toutes les catégories et tous les articles
	 * @return boolean : vrai en cas de succès, faux sinon
	 */
	public function charger() {
		return false;
	}
	
	/**
	 * @return array retourne un tableau de toutes les catégories lues
	 */
	public function getCategories() {

	}

	/**
	 * @return array retourne un tableau de toutes les articles lus de toutes les catégories lues
	 */
	public function getArticles() {
		
	}
}

?>