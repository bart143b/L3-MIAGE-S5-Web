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

//
$persitance = (isset($_SESSION['persistance'])) ? __getPersistance($_SESSION['persistance']) : __getPersistance();

// Message affiché après une tentative de création de catégorie
$message = "";

// Verifie s'il y a une demande de création de cétagorie
if(isset($_POST['ajouterCategorie'])) {
	// Verifie si la catégorie à bien été créee
	if($persitance->ajouterCategorie($_POST['nom'])) {
		$message = "<p class='succes'>La cathégorie à bien été ajoutée !<p>";
		// Si la catégorie a bien été ajoutée, on sauvgarde les modifications
		$persitance->save();
	} else {
		$message = "<p class='erreur'>Erreur, la cathégorie n'a pas été ajoutée !<p>";
	}
}

// Récupère les noms de tous les catégories
$nomsCategorie = $persitance->getNomsCategorie();

// Construction de la liste des catégories existantes
$liste = "<ul name='categorie'>";
foreach ($nomsCategorie as $nom) {
	$liste .= "<li>{$nom}</li>";
}
$liste .= "</ul>";

?>
<!doctype html>
<html lang="fr">
<head>
       <title>Créer une cathégorie</title>
       <meta charset="utf-8">
       <?php echo __getCss("style"); ?>
</head>
<body>
	<div id="head"><?php echo __getMenu(); ?></div>
	<div id="body">
		<div class="message"><?php echo $message; ?></div>
		<form action="" method="post">
			<p>Catégories existantes : <br>
			<?php echo $liste; ?></p>
			<p>Nom : <input type="text" name="nom" placeholder="Le nom de la categorie" required></p>
			<p><input type="submit" value="Créer la catégorie" name="ajouterCategorie"></p>
		</form>
	</div>
	<div id="foot"></div>

</body>
</html>
