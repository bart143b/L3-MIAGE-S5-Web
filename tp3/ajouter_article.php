<?php
	require_once "__autoload.inc";
	__autoload("donnees");
	__autoload("menu");

	$persitance = __getPersistance();

	if(isset($_POST['ajouterArticle'])) {
		$persitance->ajouterArtcile(
			$_POST['categorie'],
			$_POST['titre'], 
			$_POST['auteur'], 
			$_POST['texte']);
		$persitance->save();
	}

	$nomsCategorie = $persitance->getNomsCategorie();

	$selection = "<select name='categorie'>";
	foreach ($nomsCategorie as $nom) {
		$selection .= "<option>".$nom."</option>";
	}
	$selection .= "</select>";

?>
<!doctype html>
<html lang="fr">
<head>
       <title>Créer un article</title>
       <meta charset="utf-8">
</head>
<body>
	<div id="head"><?php echo __getMenu(); ?></div>
	<div id="body">
		<form action="" method="post">
			<p>Catégorie <br>
			<?php echo $selection; ?></p>
			<p>Titre<br><input type="text" name="titre" placeholder="Le titre de l'article" required></p>
			<p>Auteur<br><input type="text" name="auteur" placeholder="Le nom de l'auteur" required></p>
			<p>Texte<br><textarea rows="4" cols="50" name="texte" placeholder="Le texte de l'article" required></textarea></p>
			<p><input type="submit" value="Créer l'article" name="ajouterArticle"></p>
		</form>
	</div>
	<div id="foot"></div>

</body>
</html>
