<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Adam Issoufi <issoufi.adam1@gmail.com>
 * @version    1.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */
 
function __getMenu(){

	$url = "http://".$_SERVER['HTTP_HOST']."/web/tp3/";
	$menu = "<ul id='menu_principal'>";
	$menu .= "<li><a href='{$url}articles.php'>Articles</a></li>";
	$menu .= "<li><a href='{$url}ajouter_article.php'>Créer un article</a></li>";
	$menu .= "<li><a href='{$url}ajouter_categorie.php'>Créer une catégorie</a></li>";
	$menu .= "</ul>";

	return $menu;
}

?>


	