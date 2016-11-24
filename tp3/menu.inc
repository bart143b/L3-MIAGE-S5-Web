<?php
	function __getMenu(){

		$url = "http://".$_SERVER['HTTP_HOST']."/web/tp3/";
		$menu = "<ul id='menu_principal'>";
		$menu .= "<li><a href='".$url."articles.php'>Articles</a></li>";
		$menu .= "<li><a href='".$url."ajouter_article.php'>Créer un article</a></li>";
		$menu .= "<li><a href='".$url."ajouterCategorie.php'>Créer une catégorie</a></li>";
		$menu .= "</ul>";

		return $menu;
	}
	

?>


	