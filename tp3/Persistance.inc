<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Isabelle Mirbel <Isabelle.Mirbel@unice.fr>
 * @version    1.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */
 
interface Persistance {
	
	/**
	 * permet de charger toutes les catégories et tous les articles
	 * @return boolean : vrai en cas de succès, faux sinon
	 */
	public function charger();
	
	/**
	 * @return array retourne un tableau de toutes les catégories lues
	 */
	public function getCategories();
	/**
	 * @return array retourne un tableau de toutes les articles lus de toutes les catégories lues
	 */
	public function getArticles();
	

}
?>