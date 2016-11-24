
<?php
	require_once "__autoload.inc";
	__autoload("Categorie");
	__autoload("Article");

	$xml = new DOMDocument();
	$categories = array();

	$xml->load("news.xml");

	$list_categ = $xml->getElementsByTagName('categorie');

	foreach($list_categ as $categorie) {
		$noms = $categorie->getElementsByTagName('nom');
		$categorie_tmp = new Categorie($noms->item(0)->nodeValue);
		$articles = $categorie->getElementsByTagName('article');

		foreach($articles as $article) {
			$titres = $article->getElementsByTagName('titre');
			$auteurs = $article->getElementsByTagName('auteur');
			$textes = $article->getElementsByTagName('texte');

			$categorie_tmp->addArticle(new Article($titres->item(0)->nodeValue, $auteurs->item(0)->nodeValue, $textes->item(0)->nodeValue));
		}
		
		$categories[] = $categorie_tmp;
	}

	foreach ($categories as $value) {
		echo $value->getHtml();
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
</body>
</html>