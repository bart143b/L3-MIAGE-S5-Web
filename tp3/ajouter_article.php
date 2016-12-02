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
session_start();

require_once "__autoload.inc";
__autoload("donnees");
__autoload("menu");

$persitance = (isset($_SESSION['persistance'])) ? __getPersistance($_SESSION['persistance']) : __getPersistance();

// Message affiché après une tentative de création d'article
$message = "";

// Verifie s'il y a une demande de création d'article
if(isset($_POST['ajouterArticle'])) {
	// Verifie si l'article à bien été crée
	if($persitance->ajouterArtcile($_POST['categorie'], $_POST['titre'], $_POST['auteur'], $_POST['texte'])) {
		$message = "<p class='succes'>L'article à bien été ajouté !<p>";
		// Si l'article a bien été ajouté, on sauvgarde les modifications
		$persitance->save();
	} else {
		$message = "<p class='erreur'>Erreur, l'article n'a pas été ajouté !<p>";
	}
}

// Récupère les noms de tous les catégories
$nomsCategorie = $persitance->getNomsCategorie();

// Construction une selection des catégories existantes
$selection = "<select name='categorie'>";
foreach ($nomsCategorie as $nom) {
	$selection .= "<option>{$nom}</option>";
}
$selection .= "</select>";
?>
<!doctype html>
<html lang="fr">
<head>
       <title>Créer un article</title>
       <meta charset="utf-8">
       <?php echo __getCss("style"); ?>
</head>
<body>
	<div id="head"><?php echo __getMenu(); ?></div>
	<div id="body">
		<div class="message"><?php echo $message; ?></div>
		<form action="" method="post">
			<p>Catégorie : <?php echo $selection; ?></p>
			<p>Titre : <input type="text" name="titre" placeholder="Le titre de l'article" required></p>
			<p>Auteur : <input type="text" name="auteur" placeholder="Le nom de l'auteur" required></p>
			<p>Texte : <br><textarea rows="4" cols="50" name="texte" placeholder="Le texte de l'article" required></textarea></p>
			<p><input type="submit" value="Créer l'article" name="ajouterArticle"></p>
		</form>
	</div>
	<div id="foot"></div>

</body>
</html>