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

//$_SESSION['persistance'] = "PersistanceXml";

require_once "__autoload.inc";
__autoload("donnees");
__autoload("menu");

$persitance = (isset($_SESSION['persistance'])) ? __getPersistance($_SESSION['persistance']) : __getPersistance();

if($persitance == null) {
	echo "<p>Fichier xml ivalide !</p>";
	exit();
}
$articles = $persitance->getArticles();

function afficher($doc) {

	foreach ($doc as $value) {
		echo $value->getHtml();
	}
}
?>
<!doctype html>
<html lang="fr">
<head>
       <title>pages pour le cours Web...</title>
       <meta charset="utf-8">
       <?php echo __getCss("style"); ?>
</head>
<body>
	<div id="head"><?php echo __getMenu(); ?></div>
	<div id="body">
		<?php afficher($articles); ?>
	</div>
	<div id="foot"></div>
</body>
</html>